import pytest
import time
from automation1Client import Automation1Proxy

@pytest.fixture
def automation1Proxy():
    return Automation1Proxy("test/test/axis0", True)

def testEnable(automation1Proxy):
    automation1Proxy.call("Enable", None)
    time.sleep(1)
    stat, enabled = automation1Proxy.call("get", "Enabled")
    assert(stat == 0 and enabled)
    stat, state = automation1Proxy.call("State")
    assert(stat == 0 and str(state) == "ON")
    stat, status = automation1Proxy.call("Status")
    assert(stat == 0 and status == "Axis is enabled")

def testMove(automation1Proxy):
    stat, out = automation1Proxy.call("Home")
    assert(stat == 0)
    time.sleep(0.5)
    stat, home = automation1Proxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = automation1Proxy.call("get", "Homed")

    targetPos = 0.5
    targetVel = 0.1
    tol = 1e-03
    automation1Proxy.call("set", "PositionFeedback", targetPos)
    automation1Proxy.call("set", "VelocityFeedback", targetVel)

    stat, out = automation1Proxy.call("Move")
    assert(stat == 0)

    time.sleep(3)

    stat, state = automation1Proxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = automation1Proxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")

    stat, inPos = automation1Proxy.call("get", "InPosition")
    while not inPos:
        time.sleep(0.5)
        stat, inPos = automation1Proxy.call("get", "InPosition")

    stat, pos = automation1Proxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - targetPos) < tol)

def testMoveReverse(automation1Proxy):
    stat, out = automation1Proxy.call("Home")
    assert(stat == 0)
    time.sleep(0.5)
    stat, home = automation1Proxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = automation1Proxy.call("get", "Homed")

    targetPos = -0.5
    targetVel = -0.1
    tol = 1e-03
    automation1Proxy.call("set", "PositionFeedback", targetPos)
    automation1Proxy.call("set", "VelocityFeedback", targetVel)

    stat, out = automation1Proxy.call("Move")
    assert(stat == 0)

    time.sleep(3)

    stat, state = automation1Proxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = automation1Proxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")

    stat, inPos = automation1Proxy.call("get", "InPosition")
    while not inPos:
        time.sleep(0.5)
        stat, inPos = automation1Proxy.call("get", "InPosition")

    stat, pos = automation1Proxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - targetPos) < tol)

def testHome(automation1Proxy):
    stat, out = automation1Proxy.call("Home")
    assert(stat == 0)

    time.sleep(2)

    stat, state = automation1Proxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = automation1Proxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")
    
    stat, home = automation1Proxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = automation1Proxy.call("get", "Homed")

    stat, pos = automation1Proxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos) < 1e-03)

def testFreeRun(automation1Proxy):
    stat, out = automation1Proxy.call("Home")
    assert(stat == 0)

    time.sleep(0.5)

    stat, home = automation1Proxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = automation1Proxy.call("get", "Homed")

    targetPos = 0.5
    targetVel = 0.1
    tol = targetPos / 10.0

    automation1Proxy.call("set", "PositionFeedback", targetPos)
    automation1Proxy.call("set", "VelocityFeedback", targetVel)
    
    stat, out = automation1Proxy.call("FreeRun")
    time.sleep(3)
    assert(stat == 0)
    stat, state = automation1Proxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = automation1Proxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")
    time.sleep(2)
    stat, out = automation1Proxy.call("FreeRunStop")
    assert(stat == 0)

    stat, pos = automation1Proxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - targetPos) < tol)

def testFreeRunReverse(automation1Proxy):
    stat, out = automation1Proxy.call("Home")
    assert(stat == 0)

    time.sleep(0.5)

    stat, home = automation1Proxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = automation1Proxy.call("get", "Homed")

    targetPos = -0.5
    targetVel = -0.1
    tol = -targetPos / 10.0

    automation1Proxy.call("set", "PositionFeedback", targetPos)
    automation1Proxy.call("set", "VelocityFeedback", targetVel)
    
    stat, out = automation1Proxy.call("FreeRun")
    time.sleep(3)
    assert(stat == 0)
    stat, state = automation1Proxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = automation1Proxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")
    time.sleep(2)
    stat, out = automation1Proxy.call("FreeRunStop")
    assert(stat == 0)

    stat, pos = automation1Proxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - targetPos) < tol)

def testAbort(automation1Proxy):
    stat, out = automation1Proxy.call("Home")
    assert stat == 0

    time.sleep(0.5)

    stat, home = automation1Proxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = automation1Proxy.call("get", "Homed")

    targetPos = 1.0
    targetVel = 0.1
    tol = targetPos / 10.0

    automation1Proxy.call("set", "PositionFeedback", targetPos)
    automation1Proxy.call("set", "VelocityFeedback", targetVel)

    stat, out = automation1Proxy.call("FreeRun")
    time.sleep(3)
    assert stat == 0

    expectedPos = 0.3
    stat, out = automation1Proxy.call("Abort")
    assert stat == 0

    stat, pos = automation1Proxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - expectedPos) < tol)

    stat, out = automation1Proxy.call("Move")
    time.sleep(3)
    assert stat == 0

    expectedPos = 0.6
    stat, out = automation1Proxy.call("Abort")
    assert stat == 0

    stat, pos = automation1Proxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - expectedPos) < tol)


def testMoveFromLimit(automation1Proxy):
    targetPos = 58.1
    targetVel = 7.0
    automation1Proxy.call("set", "PositionFeedback", targetPos)
    automation1Proxy.call("set", "VelocityFeedback", targetVel)

    stat, out = automation1Proxy.call("Move")
    assert(stat == 0)

    stat, hasFault = automation1Proxy.call("get", "Error")
    while not hasFault:
        time.sleep(0.5)
        stat, hasFault = automation1Proxy.call("get", "Error")

    time.sleep(1)

    stat, out = automation1Proxy.call("MoveFromLimit")
    assert(stat == 0)

    time.sleep(0.5)

    stat, inPos = automation1Proxy.call("get", "InPosition")
    while not inPos:
        time.sleep(1)
        stat, inPos = automation1Proxy.call("get", "InPosition")

    stat, pos = automation1Proxy.call("get", "PositionFeedback")
    expectedPos = 51.0
    tol = 1.0
    assert(abs(pos - expectedPos) < tol)

def testAcknowledgeFaults(automation1Proxy):
    targetPos = 58.1
    targetVel = 4.0
    automation1Proxy.call("set", "PositionFeedback", targetPos)
    automation1Proxy.call("set", "VelocityFeedback", targetVel)

    stat, out = automation1Proxy.call("Move")
    assert(stat == 0)

    stat, hasFault = automation1Proxy.call("get", "Error")
    while not hasFault:
        time.sleep(0.5)
        stat, hasFault = automation1Proxy.call("get", "Error")

    time.sleep(1)

    stat, out = automation1Proxy.call("AcknowledgeFaults")
    assert(stat == 0)

    time.sleep(0.5)

    stat, inPos = automation1Proxy.call("get", "InPosition")
    while not inPos:
        time.sleep(1)
        stat, inPos = automation1Proxy.call("get", "InPosition")

    stat, pos = automation1Proxy.call("get", "PositionFeedback")
    expectedPos = 51.0
    tol = 1.0
    assert(abs(pos - expectedPos) < tol)

def testDisable(automation1Proxy):
    stat, out = automation1Proxy.call("Home")
    assert(stat == 0)

    time.sleep(0.5)

    stat, home = automation1Proxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = automation1Proxy.call("get", "Homed")
        
    automation1Proxy.call("Disable")
    time.sleep(0.5)
    stat, enabled = automation1Proxy.call("get", "Enabled")
    assert(stat == 0 and not enabled)
    stat, state = automation1Proxy.call("State")
    assert(stat == 0 and str(state) == "OFF")
    stat, status = automation1Proxy.call("Status")
    assert(stat == 0 and status == "Axis is off")