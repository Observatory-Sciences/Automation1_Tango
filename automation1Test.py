import pytest
import time
from automation1client import PmacProxy

@pytest.fixture
def pmacProxy():
    return PmacProxy("test/test/axis0", True)

def testEnable(pmacProxy):
    #pmacProxy.call("Init", None)
    #time.sleep(1)
    pmacProxy.call("Enable", None)
    stat, enabled = pmacProxy.call("get", "Enabled")

    assert(stat == 0 and enabled)

def testHome(pmacProxy):
    stat, out = pmacProxy.call("Home")
    assert(stat == 0)
    stat, home = pmacProxy.call("get", "Homed")
    while not home:
        time.sleep(1)
        stat, home = pmacProxy.call("get", "Homed")

    stat, pos = pmacProxy.call("get", "PositionFeedback")

    assert(stat == 0 and abs(pos) < 1e-03)

def testSetPosition(pmacProxy):
    targetPos = 0.5
    targetVel = 0.1
    tol = 1e-03
    pmacProxy.call("set", "PositionFeedback", targetPos)
    pmacProxy.call("set", "VelocityFeedback", targetVel)
    stat, out = pmacProxy.call("Move")

    assert(stat == 0)

    stat, inPos = pmacProxy.call("get", "InPosition")
    while not inPos:
        time.sleep(1)
        stat, inPos = pmacProxy.call("get", "InPosition")


    stat, pos = pmacProxy.call("get", "PositionFeedback")

    assert(stat == 0 and abs(pos - targetPos) < tol)