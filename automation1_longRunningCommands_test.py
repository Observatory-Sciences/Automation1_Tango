import PyTango
import time


CTRL = "Automation1/TestDevices/controller"
AXIS = "Automation1/TestDevices/axis1"
OTHERAXIS = "Automation1/TestDevices/axis0"

SLEEP = time.sleep

# Connect to controller and axis
ctrl = PyTango.DeviceProxy(CTRL)
axis = PyTango.DeviceProxy(AXIS)
other = PyTango.DeviceProxy(OTHERAXIS)

# Set the controller to a nominal state a0=5, a1=-20
ctrl.write_attribute("Automation1TaskID",1)
axis.write_attribute("MoveType",0)
other.write_attribute("MoveType",0)

axis.write_attribute("PositionTarget",-20)
axis.write_attribute("VelocityTarget",20)
other.write_attribute("PositionTarget",5)
other.write_attribute("VelocityTarget",5)
axis.command_inout("move")
other.command_inout("move")
SLEEP(1.2)

# Anticpate blocking move with axis1: a1=-15
axis.write_attribute("MoveType",2)
axis.write_attribute("VelocityTarget",1)
axis.write_attribute("PositionTarget",5)
# Anticipate axis0 move to a0=0
other.write_attribute("PositionTarget",-5)
other.write_attribute("VelocityTarget",2)

# Blocking move with axis1
axis.command_inout("Move")
SLEEP(0.5)

try:
    print("Trying to move axis0 asynchonously")
    other.command_inout("move")
    assert True
except Exception as E:
    error = E.args[0].desc
    assert error.find("The immediate command cannot execute because another immediate command is already executing.")>0
    print("    Move failed as expected with error:",error)

other.write_attribute("MoveType",2)
try:
    print("Trying to move axis0 with long-running command")
    other.command_inout("move")
    assert True
except Exception as E:
    error = E.args[0].desc
    assert error.find("This operation cannot be performed because another long-running command is active")>0
    print("    Move failed as expected again with error:",error)

# CommandExecute should fail for this task.
print("Trying CommandExecute")
try:
    ctrl.command_inout("CommandExecute","Abort(@0)")
except Exception as E:
    error = E.args[0].desc
    assert error.find("This operation cannot be performed because another long-running command is active")>0
    print("    CommandExecute failed as expected with error:",error)

# Change the task ID
ctrl.write_attribute("Automation1TaskID",2)
SLEEP(0.1)
print("Trying CommandExecute on task 2")
ctrl.command_inout("CommandExecute","Abort(@0)")

print("Trying to move axis0 again")
other.command_inout("move")

# CommandExecute should fail for this task.
print("Trying CommandExecute")
try:
    ctrl.command_inout("CommandExecute","Abort(@0)")
except Exception as E:
    error = E.args[0].desc
    assert error.find("This operation cannot be performed because another long-running command is active")>0
    print("    CommandExecute failed as expected with error:",error)

axis.command_inout("abort")
other.command_inout("abort")
SLEEP(0.2)

ctrl.write_attribute("Automation1TaskID",1)
axis.write_attribute("MoveType",0)
other.write_attribute("MoveTYpe",0)
axis.write_attribute("PositionTarget",-20)
axis.write_attribute("VelocityTarget",20)
other.write_attribute("PositionTarget",5)
other.write_attribute("VelocityTarget",5)

print("Using CommandExecute to set axes to nominal state")
ctrl.command_inout("CommandExecute","MoveAbsolute(@1,-20,20)")
ctrl.command_inout("CommandExecute","MoveAbsolute(@0,5,5)")
SLEEP(1.2)

print("Using CommandExecute for blocking move.")
axis.write_attribute("VelocityTarget",1)
ctrl.command_inout("CommandExecute","MoveLinear(@1,5)")
SLEEP(1)

print("Trying to move axis0")
other.write_attribute("PositionTarget",0)
try:
    other.command_inout("move")
    assert True
except Exception as E:
    error = E.args[0].desc
    assert error.find("The immediate command cannot execute because another immediate command is already executing")
    print("    Move failed as expected with error:",error)

print("Trying blocking move with axis0")
other.write_attribute("MoveType",2)
try:
    other.command_inout("move")
    assert True
except Exception as E:
    error = E.args[0].desc
    assert error.find("This operation cannot be performed because another long-running command is active")>0
    print("    Move failed as expected with error:",error)
other.write_attribute("MoveType",0)

print("Waiting up to 10s for axes to finish moving")
T = time.time()
while time.time()-T<10 and (other.command_inout("state")==PyTango.DevState.MOVING or axis.command_inout("state")==PyTango.DevState.MOVING):
    print("Axis0 at: {:.3f}".format(other.read_attribute("PositionFeedbacK").value))
    print("Axis1 at: {:.3f}".format(axis.read_attribute("PositionFeedbacK").value))
    SLEEP(1)

