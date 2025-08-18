import PyTango
import time

"""
Test controller stop/starting/resetting states:
    STOP the controller
        Test controller/axes states, attributes can be read/written, commands are rejected
    START the controller; whilst starting
        Test controller/axes states, attributes can be read/written, commands are rejected
    Once the controller is started
        Test controller commands, ending with RESET
    whilst the controller is resetting
        Test controller/axes states, attributes can be read/written, commands are rejected
"""

CTRL = "Automation1/TestDevices/controller"
AXIS = "Automation1/TestDevices/axis0"


SLEEP = time.sleep

def controllerTest(expectPass=True):
    try:
        ctrl.command_inout("commandexecute","Enable(@0)")
        OK = True
    except Exception as e:
        OK = False
    assert OK==expectPass

    for cmd in ["Enable","Disable","Reset"]:
        OK = True
        try:
            ctrl.command_inout(cmd)
        except:
            OK = False
        assert OK==expectPass

def axisTest(expectPass=True):
    for cmd in ["Abort","AcknowledgeFaults","BrakeOff","BrakeOn","Disable","Enable","FreeRun","FreeRunStop","Home","HomeAsync","Move","MoveFromLimit"]:
        OK = True
        try:
            axis.command_inout(cmd)
        except Exception as e:
            OK = False
        assert OK==expectPass

# Connect to controller and axis
ctrl = PyTango.DeviceProxy(CTRL)
axis = PyTango.DeviceProxy(AXIS)

stopped = True
while ctrl.command_inout("state")==PyTango.DevState.INIT:
    stopped = False
    SLEEP(0.25)
if ctrl.command_inout("state")!=PyTango.DevState.OFF:
    stopped = False

# Ensure controller is stopped
ctrl.command_inout("stop")
SLEEP(0.5)
if not stopped: SLEEP(1)

# First check the controller state
state = ctrl.command_inout("state")
assert state==PyTango.DevState.OFF
status = ctrl.command_inout("status")
print(status)

controllerTest(False)


# Now check the axis state
state = axis.command_inout("state")
assert state==PyTango.DevState.ALARM
status = axis.command_inout("status")
print(status)

# Test that we can read axis attributes
for attr in ["PositionFeedback","VelocityFeedback","InPosition","Enabled","Homed","Error"]:
    state = axis.read_attribute(attr)

# Test that we can write appropriate attributes ...
axis.write_attribute("PositionTarget",0.)
axis.write_attribute("VelocityTarget",1.)

# ... and test that we can read back those
assert axis.read_attribute("PositionTarget").value==0
assert axis.read_attribute("VelocityTarget").value==1

axisTest(False)


# Now start the controller and test starting state
startTime = time.time()
ctrl.command_inout("start")
SLEEP(1)
state = ctrl.command_inout("state")
assert state==PyTango.DevState.INIT
print(ctrl.command_inout("status"))

try:
    ctrl.command_inout("start")
    assert True
except:
    pass

controllerTest(False)

# Now check the axis state
state = axis.command_inout("state")
assert state==PyTango.DevState.ALARM
status = axis.command_inout("status")
print(status)

# Test that we can read axis attributes
for attr in ["PositionFeedback","VelocityFeedback","InPosition","Enabled","Homed","Error"]:
    state = axis.read_attribute(attr)

# Test that we can write appropriate attributes ...
axis.write_attribute("PositionTarget",2.)
axis.write_attribute("VelocityTarget",1.5)

# ... and test that we can read back those
assert axis.read_attribute("PositionTarget").value==2
assert axis.read_attribute("VelocityTarget").value==1.5

axisTest(False)

while time.time()-startTime<10 and ctrl.command_inout("state")!=PyTango.DevState.STANDBY:
    SLEEP(0.25)
assert ctrl.command_inout("state")==PyTango.DevState.STANDBY

controllerTest(True)
SLEEP(1)

state = ctrl.command_inout("state")
assert state==PyTango.DevState.INIT
print(ctrl.command_inout("status"))

try:
    ctrl.command_inout("start")
    assert True
except:
    pass

controllerTest(False)

# Now check the axis state
state = axis.command_inout("state")
assert state==PyTango.DevState.ALARM
status = axis.command_inout("status")
print(status)

# The controller should now be resetting!

axisTest(False)
