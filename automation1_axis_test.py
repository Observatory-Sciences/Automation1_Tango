#! /usr/bin/env python

"""
Pytest test script to test the A1Axis TANGO Device
"""

import time
import pytest
from automation1_client import Automation1Proxy

MOVE_TIMEOUT = 15

@pytest.fixture
def automation1_proxy():
    """
    Pytest fixture providing a client to access and use the A1Axis TANGO device
    """
    return Automation1Proxy("test/test/axis0", True)

# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_enable(automation1_proxy):
    """
    Tests the Enable successfully enables an axis and sets the state and status correctly
    """
    automation1_proxy.call("Enable", None)
    time.sleep(1)
    stat, enabled = automation1_proxy.call("get", "Enabled")
    assert stat == 0 and enabled
    stat, state = automation1_proxy.call("State")
    assert stat == 0 and str(state) == "ON"
    stat, status = automation1_proxy.call("Status")
    assert stat == 0 and status == "Axis is enabled"


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_move(automation1_proxy):
    """
    Tests the Move command to ensure that the axis moves to the correct position and reports that
    it is in position once completed. Also checks that the state and status update as appropriate
    during the move.
    """
    stat, _ = automation1_proxy.call("HomeAsync")
    assert stat == 0
    time.sleep(0.5)
    check_cmd_with_timeout(automation1_proxy, "Homed", MOVE_TIMEOUT, "reach home")

    target_pos = 0.5
    target_vel = 0.1
    tol = 1e-02
    automation1_proxy.call("set", "PositionTarget", target_pos)
    automation1_proxy.call("set", "VelocityTarget", target_vel)

    stat, _ = automation1_proxy.call("Move")
    assert stat == 0

    time.sleep(3)

    stat, state = automation1_proxy.call("State")
    assert stat == 0 and str(state) == "MOVING"
    stat, status = automation1_proxy.call("Status")
    assert stat == 0 and status == "Axis is jogging"

    check_cmd_with_timeout(automation1_proxy, "InPosition", MOVE_TIMEOUT,
                           "reach requested position")

    stat, pos = automation1_proxy.call("get", "PositionFeedback")
    assert stat == 0 and abs(pos - target_pos) < tol


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_move_reverse(automation1_proxy):
    """
    Does the same as test_move() but moves the axis in the opposite direction.
    """
    stat, _ = automation1_proxy.call("HomeAsync")
    assert stat == 0
    time.sleep(0.5)
    check_cmd_with_timeout(automation1_proxy, "Homed", MOVE_TIMEOUT, "reach home")

    target_pos = -0.5
    target_vel = -0.1
    tol = 1e-02
    automation1_proxy.call("set", "PositionTarget", target_pos)
    automation1_proxy.call("set", "VelocityTarget", target_vel)

    stat, _ = automation1_proxy.call("Move")
    assert stat == 0

    time.sleep(3)

    stat, state = automation1_proxy.call("State")
    assert stat == 0 and str(state) == "MOVING"
    stat, status = automation1_proxy.call("Status")
    assert stat == 0 and status == "Axis is jogging"

    check_cmd_with_timeout(automation1_proxy, "InPosition", MOVE_TIMEOUT,
                           "reach requested position")

    stat, pos = automation1_proxy.call("get", "PositionFeedback")
    assert stat == 0 and abs(pos - target_pos) < tol


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_home(automation1_proxy):
    """
    Tests the Home command and ensures that the axis moves back to the correct home position
    (0.000mm in this case) and reports that it is homed
    """
    exp_state = "MOVING"
    exp_status = "Axis is jogging"

    _, virtual = automation1_proxy.call("get", "VirtualAxis")
    if virtual:
        # Virtual axes are homed immediately
        exp_state = "ON"
        exp_status = "Axis is enabled"

    stat, _ = automation1_proxy.call("HomeAsync")
    assert stat == 0

    time.sleep(2)

    stat, state = automation1_proxy.call("State")
    assert stat == 0 and str(state) == exp_state
    stat, status = automation1_proxy.call("Status")
    assert stat == 0 and status == exp_status

    check_cmd_with_timeout(automation1_proxy, "Homed", MOVE_TIMEOUT, "reach home")

    tol = 1e-02
    stat, pos = automation1_proxy.call("get", "PositionFeedback")
    assert stat == 0 and abs(pos) < tol


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_free_run(automation1_proxy):
    """
    Tests the FreeRun and FreeRunStop commands. FreeRun essentially lets the axis move at a given
    velocity until it errors or is asked to stop with FreeRunStop. The function calls FreeRun, lets
    it run for some time, calls FreeRunStop and ensures that the axis moves the correct distance
    based on the provided velocity and the time it is allowed to move.
    """
    stat, _ = automation1_proxy.call("HomeAsync")
    assert stat == 0

    time.sleep(0.5)

    check_cmd_with_timeout(automation1_proxy, "Homed", MOVE_TIMEOUT, "reach home")

    target_pos = 0.5
    target_vel = 0.1
    tol = target_pos / 10.0

    automation1_proxy.call("set", "PositionTarget", target_pos)
    automation1_proxy.call("set", "VelocityTarget", target_vel)

    stat, _ = automation1_proxy.call("FreeRun")
    time.sleep(3)
    assert stat == 0
    stat, state = automation1_proxy.call("State")
    assert stat == 0 and str(state) == "MOVING"
    stat, status = automation1_proxy.call("Status")
    assert stat == 0 and status == "Axis is jogging"
    time.sleep(2)
    stat, _ = automation1_proxy.call("FreeRunStop")
    assert stat == 0

    stat, pos = automation1_proxy.call("get", "PositionFeedback")
    assert stat == 0 and abs(pos - target_pos) < tol


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_free_run_reverse(automation1_proxy):
    """
    Does the same as test_free_run() but moves the axis in the opposite direction.
    """
    stat, _ = automation1_proxy.call("Home")
    assert stat == 0

    time.sleep(0.5)

    check_cmd_with_timeout(automation1_proxy, "Homed", MOVE_TIMEOUT, "reach home")

    target_pos = -0.5
    target_vel = -0.1
    tol = -target_pos / 10.0

    automation1_proxy.call("set", "PositionTarget", target_pos)
    automation1_proxy.call("set", "VelocityTarget", target_vel)

    stat, _ = automation1_proxy.call("FreeRun")
    time.sleep(3)
    assert stat == 0
    stat, state = automation1_proxy.call("State")
    assert stat == 0 and str(state) == "MOVING"
    stat, status = automation1_proxy.call("Status")
    assert stat == 0 and status == "Axis is jogging"
    time.sleep(2)
    stat, _ = automation1_proxy.call("FreeRunStop")
    assert stat == 0

    stat, pos = automation1_proxy.call("get", "PositionFeedback")
    assert stat == 0 and abs(pos - target_pos) < tol


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_abort(automation1_proxy):
    """
    Tests the Abort command. This command should stop any command that is currently in progress
    (i.e. it will stop an axis which has had Move or FreeRun called on it). The function runs a
    FreeRun command, lets the axis move for a set time and then calls Abort and checks that the
    axis has moved the correct distance and is stopped. It then does the same but with a Move
    command.
    """
    stat, _ = automation1_proxy.call("Home")
    assert stat == 0

    time.sleep(0.5)

    check_cmd_with_timeout(automation1_proxy, "Homed", MOVE_TIMEOUT, "reach home")

    target_pos = 1.0
    target_vel = 0.1
    tol = target_pos / 10.0

    automation1_proxy.call("set", "PositionTarget", target_pos)
    automation1_proxy.call("set", "VelocityTarget", target_vel)

    stat, _ = automation1_proxy.call("FreeRun")
    time.sleep(3)
    assert stat == 0

    expected_pos = 0.3
    stat, _ = automation1_proxy.call("Abort")
    assert stat == 0

    # Sleep to ensure Axis stays in the correct posisiont and does not continue to move
    time.sleep(1)

    stat, pos = automation1_proxy.call("get", "PositionFeedback")
    assert stat == 0 and abs(pos - expected_pos) < tol

    stat, _ = automation1_proxy.call("Move")
    time.sleep(3)
    assert stat == 0

    expected_pos = 0.6
    stat, _ = automation1_proxy.call("Abort")
    assert stat == 0

    # Sleep to ensure Axis stays in the correct posisiont and does not continue to move
    time.sleep(1)

    stat, pos = automation1_proxy.call("get", "PositionFeedback")
    assert stat == 0 and abs(pos - expected_pos) < tol


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_move_from_limit(automation1_proxy):
    """
    Tests the MoveFromLimit command by moving the axis to its soft limit, then calling
    MoveFromLimit to check that the axis moves back a few mm from its limit and that there is no
    longer a fault on the axis.

    Test is skipped for virtual axes.
    """

    _, virtual = automation1_proxy.call("get", "VirtualAxis")

    if virtual:
        pytest.skip("Cannot run limits tests on virtual axes")

    target_pos = 58.1
    target_vel = 4.0
    automation1_proxy.call("set", "PositionTarget", target_pos)
    automation1_proxy.call("set", "VelocityTarget", target_vel)

    stat, _ = automation1_proxy.call("Move")
    assert stat == 0

    check_cmd_with_timeout(automation1_proxy, "Error", MOVE_TIMEOUT, "reach limit")

    stat, _ = automation1_proxy.call("MoveFromLimit")
    assert stat == 0

    time.sleep(0.5)

    check_cmd_with_timeout(automation1_proxy, "InPosition", MOVE_TIMEOUT,
                           "reach position away from limit")

    stat, pos = automation1_proxy.call("get", "PositionFeedback")
    expected_pos = 51.0
    tol = 1.0
    assert abs(pos - expected_pos) < tol


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_acknowledge_faults(automation1_proxy):
    """
    In the case of an axis hitting its limit, the AcknowledgeFaults command should do much the same
    as the  MoveFromLimit command. Therefore, this test does the same as the test_move_from_limit()
    function but with the AcknowledgeFaults command used in place of MoveFromLimit.

    Test is skipped for virtual axes.
    """

    _, virtual = automation1_proxy.call("get", "VirtualAxis")

    if virtual:
        pytest.skip("Cannot run limits tests on virtual axes")

    target_pos = 58.1
    target_vel = 4.0
    automation1_proxy.call("set", "PositionTarget", target_pos)
    automation1_proxy.call("set", "VelocityTarget", target_vel)

    stat, _ = automation1_proxy.call("Move")
    assert stat == 0

    check_cmd_with_timeout(automation1_proxy, "Error", MOVE_TIMEOUT, "reach limit")

    time.sleep(1)

    stat, _ = automation1_proxy.call("AcknowledgeFaults")
    assert stat == 0

    time.sleep(0.5)

    check_cmd_with_timeout(automation1_proxy, "InPosition", MOVE_TIMEOUT,
                           "reach position away from limit")

    stat, pos = automation1_proxy.call("get", "PositionFeedback")
    expected_pos = 51.0
    tol = 1.0
    assert abs(pos - expected_pos) < tol


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_disable(automation1_proxy):
    """
    Tests the Disable successfully disables an axis and sets the state and status correctly. The
    axis is also homed so that is it in a known state for next use.
    """
    stat, _ = automation1_proxy.call("HomeAsync")
    assert stat == 0

    time.sleep(0.5)

    check_cmd_with_timeout(automation1_proxy, "Homed", MOVE_TIMEOUT, "reach home")

    automation1_proxy.call("Disable")
    time.sleep(0.5)
    stat, enabled = automation1_proxy.call("get", "Enabled")
    assert stat == 0 and not enabled
    stat, state = automation1_proxy.call("State")
    assert stat == 0 and str(state) == "OFF"
    stat, status = automation1_proxy.call("Status")
    assert stat == 0 and status == "Axis is off"


def check_cmd_with_timeout(proxy, condition, timeout, verb):
    """
    Helper function to read a value from the controller and check if it is true. If it is not, then
    the function continues to loop over this until a timeout is reached or the value becomes true.
    If the timeout is reached, then the motor is told to attempt to go home, the provided verb is
    used to generate a useful error message and the test fails.
    """
    timeout_time = time.time() + timeout
    _, complete = proxy.call("get", condition)
    while not complete:
        time.sleep(0.5)
        _, complete = proxy.call("get", condition)
        # Check for timeout
        if time.time() > timeout_time:
            # Attempt to home motor after failure
            proxy.call("HomeAsync")
            pytest.fail("Motor failed to " + str(verb) + " within timeout time of " +\
                        str(timeout) + "s")
