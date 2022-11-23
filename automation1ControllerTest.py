import pytest
import time
from automation1Client import Automation1Proxy

TASK_STATUS = {
    "Unavailable" : 0,
	"Inactive" : 1,
	"Idle" : 2,
	"Program Ready" : 3,
	"Program Running" : 4,
	"Program Feedhold" : 5,
	"Program Paused" : 6,
	"Program Complete" : 7,
	"Error" : 8,
	"Queue Running" : 9,
	"Queue Paused" : 10,
    

}

@pytest.fixture
def a1ControllerProxy():
    return Automation1Proxy("test/test/controller", True)

@pytest.fixture
def a1Axis0Proxy():
    return Automation1Proxy("test/test/axis0", True)

@pytest.fixture
def a1Axis1Proxy():
    return Automation1Proxy("test/test/axis1", True)

@pytest.fixture
def aeroScriptFiles(a1ControllerProxy):
    stat, out = a1ControllerProxy.call("get", "AeroScriptFiles")
    return out

def testEnable(a1ControllerProxy, a1Axis0Proxy, a1Axis1Proxy):
    a1ControllerProxy.call("Enable", None)
    time.sleep(1)
    stat, enabled = a1Axis0Proxy.call("get", "Enabled")
    assert(stat == 0 and enabled)
    stat, state = a1Axis0Proxy.call("State")
    assert(stat == 0 and str(state) == "ON")
    stat, status = a1Axis0Proxy.call("Status")
    assert(stat == 0 and status == "Axis is enabled")

    stat, enabled = a1Axis1Proxy.call("get", "Enabled")
    assert(stat == 0 and enabled)
    stat, state = a1Axis1Proxy.call("State")
    assert(stat == 0 and str(state) == "ON")
    stat, status = a1Axis1Proxy.call("Status")
    assert(stat == 0 and status == "Axis is enabled")

def testCommandExecute(a1ControllerProxy, a1Axis0Proxy):
    a1ControllerProxy.call("CommandExecute", "Disable([X1])")

    time.sleep(1)
    stat, enabled = a1Axis0Proxy.call("get", "Enabled")
    assert(stat == 0 and not enabled)
    stat, state = a1Axis0Proxy.call("State")
    assert(stat == 0 and str(state) == "OFF")
    stat, status = a1Axis0Proxy.call("Status")
    assert(stat == 0 and status == "Axis is off")

    a1ControllerProxy.call("CommandExecute", "Enable([X1])")

    time.sleep(1)
    stat, enabled = a1Axis0Proxy.call("get", "Enabled")
    assert(stat == 0 and enabled)
    stat, state = a1Axis0Proxy.call("State")
    assert(stat == 0 and str(state) == "ON")
    stat, status = a1Axis0Proxy.call("Status")
    assert(stat == 0 and status == "Axis is enabled")

def testAeroScriptProgramStartFinite(a1ControllerProxy, aeroScriptFiles):
    if "/faultThrow.ascript" not in aeroScriptFiles:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")
    
    stat, _ = a1ControllerProxy.call("set", "AeroScriptFilePath", "/faultThrow.ascript")
    assert stat == 0
    time.sleep(1)
    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Program Ready"]

    stat, _ = a1ControllerProxy.call("AeroScriptProgramStart", None)
    assert stat == 0
    time.sleep(1)
    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Program Complete"]

def testClearErrors(a1ControllerProxy, a1Axis0Proxy, a1Axis1Proxy):
    stat, _ = a1ControllerProxy.call("ClearErrors", None)

    time.sleep(1)

    axis0Stat, axis0Fault = a1Axis0Proxy.call("get", "Error")
    axis1Stat, axis1Fault = a1Axis1Proxy.call("get", "Error")

    assert axis0Stat == 0 and axis1Stat == 0
    assert not axis0Fault and not axis1Fault

    # ClearErrors diables axes, so re-enable them here
    axis0Stat, _ = a1Axis0Proxy.call("Enable", None)
    axis1Stat, _ = a1Axis1Proxy.call("Enable", None)

    assert axis0Stat == 0 and axis1Stat == 0


def testAeroScriptProgramStartEndless(a1ControllerProxy, aeroScriptFiles):
    if "/endless_monitor.ascript" not in aeroScriptFiles:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")
    
    stat, _ = a1ControllerProxy.call("set", "AeroScriptFilePath", "/endless_monitor.ascript")
    assert stat == 0
    time.sleep(1)
    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Program Ready"]

    stat, _ = a1ControllerProxy.call("AeroScriptProgramStart", None)
    assert stat == 0
    time.sleep(0.5)
    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Program Running"]

def testAeroScriptProgramPause(a1ControllerProxy, aeroScriptFiles):
    if "/endless_monitor.ascript" not in aeroScriptFiles:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")
    
    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0
    if taskStatus != TASK_STATUS["Program Running"]:
        pytest.skip("No AeroScript running on controller, skipping...")

    stat, _ = a1ControllerProxy.call("AeroScriptProgramPause", None)
    assert stat == 0
    time.sleep(0.5)
    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Program Paused"]

def testAeroScriptProgramStop(a1ControllerProxy, aeroScriptFiles):
    if "/endless_monitor.ascript" not in aeroScriptFiles:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")
    
    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0
    if taskStatus not in (TASK_STATUS["Program Running"], TASK_STATUS["Program Paused"]):
        pytest.skip("No AeroScript running on controller, skipping...")

    stat, _ = a1ControllerProxy.call("AeroScriptProgramStop", None)
    assert stat == 0
    time.sleep(0.5)
    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Idle"]

    stat, fileLoaded = a1ControllerProxy.call("get", "AeroScriptFilePath")
    assert stat == 0 and fileLoaded == ""

def testAeroScriptProgramLoad(a1ControllerProxy, aeroScriptFiles):
    if "/endless_monitor.ascript" not in aeroScriptFiles:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")
    
    stat, _ = a1ControllerProxy.call("AeroScriptProgramLoad", None)
    assert stat == 0
    time.sleep(0.5)
    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Program Ready"]

    stat, fileLoaded = a1ControllerProxy.call("get", "AeroScriptFilePath")
    assert stat == 0 and fileLoaded == "/endless_monitor.ascript"

def testAeroScriptProgramRun(a1ControllerProxy, aeroScriptFiles):
    if "/endless_monitor.ascript" not in aeroScriptFiles:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")
    
    # Call AeroScriptProgramStop to unload the current AeroScript from the controller but leave
    # the value in the write attribute of AeroScriptFilePath so we can test that
    # AeroScriptProgramRun loads te program before running
    stat, _ = a1ControllerProxy.call("AeroScriptProgramStop", None)
    assert stat == 0
    time.sleep(0.5)

    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Idle"]

    stat, fileLoaded = a1ControllerProxy.call("get", "AeroScriptFilePath")
    assert stat == 0 and fileLoaded == ""

    stat, _ = a1ControllerProxy.call("AeroScriptProgramRun", None)
    assert stat == 0
    time.sleep(0.5)

    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Program Running"]

    stat, _ = a1ControllerProxy.call("AeroScriptProgramStop", None)
    assert stat == 0
    time.sleep(0.5)

    stat, taskStatus = a1ControllerProxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and taskStatus == TASK_STATUS["Idle"]

    stat, fileLoaded = a1ControllerProxy.call("get", "AeroScriptFilePath")
    assert stat == 0 and fileLoaded == ""



def testDisable(a1ControllerProxy, a1Axis0Proxy, a1Axis1Proxy):
    a1ControllerProxy.call("Disable", None)
    time.sleep(1)
    stat, enabled = a1Axis0Proxy.call("get", "Enabled")
    assert(stat == 0 and not enabled)
    stat, state = a1Axis0Proxy.call("State")
    assert(stat == 0 and str(state) == "OFF")
    stat, status = a1Axis0Proxy.call("Status")
    assert(stat == 0 and status == "Axis is off")

    stat, enabled = a1Axis1Proxy.call("get", "Enabled")
    assert(stat == 0 and not enabled)
    stat, state = a1Axis1Proxy.call("State")
    assert(stat == 0 and str(state) == "OFF")
    stat, status = a1Axis1Proxy.call("Status")
    assert(stat == 0 and status == "Axis is off")