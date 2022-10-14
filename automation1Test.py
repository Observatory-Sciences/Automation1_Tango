import pytest
import time
from automation1client import PmacProxy

@pytest.fixture
def pmacProxy():
    return PmacProxy("test/test/axis0", True)

def testEnable(pmacProxy):
    pmacProxy.call("Enable", None)
    time.sleep(1)
    stat, enabled = pmacProxy.call("get", "Enabled")
    assert(stat == 0 and enabled)
    stat, state = pmacProxy.call("State")
    assert(stat == 0 and str(state) == "ON")
    stat, status = pmacProxy.call("Status")
    assert(stat == 0 and status == "Axis is enabled")

def testMove(pmacProxy):
    stat, out = pmacProxy.call("Home")
    assert(stat == 0)
    time.sleep(0.5)
    stat, home = pmacProxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = pmacProxy.call("get", "Homed")

    targetPos = 0.5
    targetVel = 0.1
    tol = 1e-03
    pmacProxy.call("set", "PositionFeedback", targetPos)
    pmacProxy.call("set", "VelocityFeedback", targetVel)

    stat, out = pmacProxy.call("Move")
    assert(stat == 0)

    time.sleep(3)

    stat, state = pmacProxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = pmacProxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")

    stat, inPos = pmacProxy.call("get", "InPosition")
    while not inPos:
        time.sleep(0.5)
        stat, inPos = pmacProxy.call("get", "InPosition")

    stat, pos = pmacProxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - targetPos) < tol)

def testMoveReverse(pmacProxy):
    stat, out = pmacProxy.call("Home")
    assert(stat == 0)
    time.sleep(0.5)
    stat, home = pmacProxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = pmacProxy.call("get", "Homed")

    targetPos = -0.5
    targetVel = -0.1
    tol = 1e-03
    pmacProxy.call("set", "PositionFeedback", targetPos)
    pmacProxy.call("set", "VelocityFeedback", targetVel)

    stat, out = pmacProxy.call("Move")
    assert(stat == 0)

    time.sleep(3)

    stat, state = pmacProxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = pmacProxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")

    stat, inPos = pmacProxy.call("get", "InPosition")
    while not inPos:
        time.sleep(0.5)
        stat, inPos = pmacProxy.call("get", "InPosition")

    stat, pos = pmacProxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - targetPos) < tol)

def testHome(pmacProxy):
    stat, out = pmacProxy.call("Home")
    assert(stat == 0)

    time.sleep(2)

    stat, state = pmacProxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = pmacProxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")
    
    stat, home = pmacProxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = pmacProxy.call("get", "Homed")

    stat, pos = pmacProxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos) < 1e-03)

def testFreeRun(pmacProxy):
    stat, out = pmacProxy.call("Home")
    assert(stat == 0)

    time.sleep(0.5)

    stat, home = pmacProxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = pmacProxy.call("get", "Homed")

    targetPos = 0.5
    targetVel = 0.1
    tol = targetPos / 10.0

    pmacProxy.call("set", "PositionFeedback", targetPos)
    pmacProxy.call("set", "VelocityFeedback", targetVel)
    
    stat, out = pmacProxy.call("FreeRun")
    time.sleep(3)
    assert(stat == 0)
    stat, state = pmacProxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = pmacProxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")
    time.sleep(2)
    stat, out = pmacProxy.call("FreeRunStop")
    assert(stat == 0)

    stat, pos = pmacProxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - targetPos) < tol)

def testFreeRunReverse(pmacProxy):
    stat, out = pmacProxy.call("Home")
    assert(stat == 0)

    time.sleep(0.5)

    stat, home = pmacProxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = pmacProxy.call("get", "Homed")

    targetPos = -0.5
    targetVel = -0.1
    tol = -targetPos / 10.0

    pmacProxy.call("set", "PositionFeedback", targetPos)
    pmacProxy.call("set", "VelocityFeedback", targetVel)
    
    stat, out = pmacProxy.call("FreeRun")
    time.sleep(3)
    assert(stat == 0)
    stat, state = pmacProxy.call("State")
    assert(stat == 0 and str(state) == "MOVING")
    stat, status = pmacProxy.call("Status")
    assert(stat == 0 and status == "Axis is jogging")
    time.sleep(2)
    stat, out = pmacProxy.call("FreeRunStop")
    assert(stat == 0)

    stat, pos = pmacProxy.call("get", "PositionFeedback")
    assert(stat == 0 and abs(pos - targetPos) < tol)

def testMoveFromLimit(pmacProxy):
    targetPos = 58.1
    targetVel = 7.0
    pmacProxy.call("set", "PositionFeedback", targetPos)
    pmacProxy.call("set", "VelocityFeedback", targetVel)

    stat, out = pmacProxy.call("Move")
    assert(stat == 0)

    stat, hasFault = pmacProxy.call("get", "Error")
    while not hasFault:
        time.sleep(0.5)
        stat, hasFault = pmacProxy.call("get", "Error")

    time.sleep(1)

    stat, out = pmacProxy.call("MoveFromLimit")
    assert(stat == 0)

    time.sleep(0.5)

    stat, inPos = pmacProxy.call("get", "InPosition")
    while not inPos:
        time.sleep(1)
        stat, inPos = pmacProxy.call("get", "InPosition")

    stat, pos = pmacProxy.call("get", "PositionFeedback")
    expectedPos = 51.0
    tol = 1.0
    assert(abs(pos - expectedPos) < tol)

def testAcknowledgeFaults(pmacProxy):
    targetPos = 58.1
    targetVel = 4.0
    pmacProxy.call("set", "PositionFeedback", targetPos)
    pmacProxy.call("set", "VelocityFeedback", targetVel)

    stat, out = pmacProxy.call("Move")
    assert(stat == 0)

    stat, hasFault = pmacProxy.call("get", "Error")
    while not hasFault:
        time.sleep(0.5)
        stat, hasFault = pmacProxy.call("get", "Error")

    time.sleep(1)

    stat, out = pmacProxy.call("AcknowledgeFaults")
    assert(stat == 0)

    time.sleep(0.5)

    stat, inPos = pmacProxy.call("get", "InPosition")
    while not inPos:
        time.sleep(1)
        stat, inPos = pmacProxy.call("get", "InPosition")

    stat, pos = pmacProxy.call("get", "PositionFeedback")
    expectedPos = 51.0
    tol = 1.0
    assert(abs(pos - expectedPos) < tol)

def testDisable(pmacProxy):
    stat, out = pmacProxy.call("Home")
    assert(stat == 0)

    time.sleep(0.5)

    stat, home = pmacProxy.call("get", "Homed")
    while not home:
        time.sleep(0.5)
        stat, home = pmacProxy.call("get", "Homed")
        
    pmacProxy.call("Disable")
    time.sleep(0.5)
    stat, enabled = pmacProxy.call("get", "Enabled")
    assert(stat == 0 and not enabled)
    stat, state = pmacProxy.call("State")
    assert(stat == 0 and str(state) == "OFF")
    stat, status = pmacProxy.call("Status")
    assert(stat == 0 and status == "Axis is off")