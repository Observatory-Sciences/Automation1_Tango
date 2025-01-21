import pytest
import time
import random
import threading
from automation1_client import Automation1Proxy

pos_lo = -20
pos_hi = 20
vel_lo = 0.1
vel_hi = 2

@pytest.fixture
def automation1_proxies():
    """
    Pytest fixture providing a list of clients to access and use the A1Axis TANGO device
    """
    return [
        Automation1Proxy("test/test/axis2", True), Automation1Proxy("test/test/axis3", True),\
        Automation1Proxy("test/test/axis4", True),Automation1Proxy("test/test/axis5", True),\
        Automation1Proxy("test/test/axis6", True),Automation1Proxy("test/test/axis7", True),\
        Automation1Proxy("test/test/axis8", True),Automation1Proxy("test/test/axis9", True)
    ]

def axis_move_loop(automation1_proxy):
    """
    Constantly set a position and move the axis. This
    will run forever so will need to exit using ctrl+c.
    """
    automation1_proxy.call("Enable", None)
    time.sleep(0.5)
    stat, enabled = automation1_proxy.call("get", "Enabled")
    assert(stat == 0 and enabled)

    while True:
        targetPos = random.uniform(pos_lo, pos_hi)
        targetVel = random.uniform(vel_lo, vel_hi)
        tol = 1e-01
        
        automation1_proxy.call("set", "PositionTarget", targetPos)
        automation1_proxy.call("set", "VelocityTarget", targetVel)
        stat, out = automation1_proxy.call("Move")
        assert(stat == 0)
        time.sleep(1)

        stat, inPos = automation1_proxy.call("get", "InPosition")
        while not inPos:
            time.sleep(0.5)
            stat, inPos = automation1_proxy.call("get", "InPosition")
    
        # Check the position
        stat, pos = automation1_proxy.call("get", "PositionFeedback")
        assert(stat == 0 and abs(pos - targetPos) < tol)


def test_stress_multi_axes_moves(automation1_proxies):
    """
    Stress the software by constantly moving 8 axes in parallel.
    Test requires 8 virtual axes to be configured in Tango (axis2 - axis9).
    Test will run forever so needs to be cancelled using the keyboard
    interupt Ctrl+c.
    """
    threads = list()
    for automation1_proxy in automation1_proxies:
        x = threading.Thread(target=axis_move_loop, args=(automation1_proxy,))
        threads.append(x)
        x.daemon = True
        x.start()
    
    try:
        while True:
            time.sleep(0.5)
    except KeyboardInterrupt:
        print(" Calling end to test")