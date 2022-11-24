#! /usr/bin/env python

"""
Pytest test script to test the A1Controller TANGO Device
"""

import time
import pytest
from automation1_client import Automation1Proxy

TASK_STATUS = {"Unavailable" : 0, "Inactive" : 1, "Idle" : 2, "Program Ready" : 3,
               "Program Running" : 4, "Program Feedhold" : 5, "Program Paused" : 6,
               "Program Complete" : 7, "Error" : 8, "Queue Running" : 9, "Queue Paused" : 10}


@pytest.fixture
def a1_controller_proxy():
    """
    Pytest fixture providing a client to access and use the A1Controller TANGO device
    """
    return Automation1Proxy("test/test/controller", True)


@pytest.fixture
def a1_axis0_proxy():
    """
    Pytest fixture providing a client to access and use one instance of the A1Axis TANGO device
    """
    return Automation1Proxy("test/test/axis0", True)


@pytest.fixture
def a1_axis1_proxy():
    """
    Pytest fixture providing a client to access and use a second insatnce of the A1Axis TANGO
    device
    """
    return Automation1Proxy("test/test/axis1", True)

# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
@pytest.fixture
def aeroscript_files(a1_controller_proxy):
    """
    Pytest fixture providing a list of the AeroScript files loaded on the Automation1 controller
    """
    _, out = a1_controller_proxy.call("get", "AeroScriptFiles")
    return out


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_enable(a1_controller_proxy, a1_axis0_proxy, a1_axis1_proxy):
    """
    Tests the Enable command byt checking we can run it and that the state and status of the two
    A1Axis devices controlled by this A1Controller device are correct.
    """
    a1_controller_proxy.call("Enable", None)
    time.sleep(1)
    stat, enabled = a1_axis0_proxy.call("get", "Enabled")
    assert stat == 0 and enabled
    stat, state = a1_axis0_proxy.call("State")
    assert stat == 0 and str(state) == "ON"
    stat, status = a1_axis0_proxy.call("Status")
    assert stat == 0 and status == "Axis is enabled"

    stat, enabled = a1_axis1_proxy.call("get", "Enabled")
    assert stat == 0 and enabled
    stat, state = a1_axis1_proxy.call("State")
    assert stat == 0 and str(state) == "ON"
    stat, status = a1_axis1_proxy.call("Status")
    assert stat == 0 and status == "Axis is enabled"


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_command_execute(a1_controller_proxy, a1_axis0_proxy):
    """
    Tests the CommandExecute command by running the Enable([axis]) and Disable([axis]) AeroScript
    functions via the command. The command should be able to execute any arbitrary Aeroscript and
    these two functions provide a simple test case where we can just check that the axis on which
    the function is called has its state and status updated to reflect whether it has been enabled
    or disabled.
    """
    a1_controller_proxy.call("CommandExecute", "Disable([X1])")

    time.sleep(1)
    stat, enabled = a1_axis0_proxy.call("get", "Enabled")
    assert stat == 0 and not enabled
    stat, state = a1_axis0_proxy.call("State")
    assert stat == 0 and str(state) == "OFF"
    stat, status = a1_axis0_proxy.call("Status")
    assert stat == 0 and status == "Axis is off"

    a1_controller_proxy.call("CommandExecute", "Enable([X1])")

    time.sleep(1)
    stat, enabled = a1_axis0_proxy.call("get", "Enabled")
    assert stat == 0 and enabled
    stat, state = a1_axis0_proxy.call("State")
    assert stat == 0 and str(state) == "ON"
    stat, status = a1_axis0_proxy.call("Status")
    assert stat == 0 and status == "Axis is enabled"


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_aeroscript_program_start1(a1_controller_proxy, aeroscript_files):
    """
    The first of two tests of the AeroScriptProgramStart command. This test uses the
    AeroScriptProgramStart command to run an AeroScript which completes quickly and checks that we
    get the correct task status at each point of execution. It also indirectly tests the behaviour
    where whenever a value is written to the AeroScriptFilePath attribute, the
    AeroScriptProgramLoad command should be implicitly called on the input.
    """
    if "/faultThrow.ascript" not in aeroscript_files:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")

    stat, _ = a1_controller_proxy.call("set", "AeroScriptFilePath", "/faultThrow.ascript")
    assert stat == 0
    time.sleep(1)
    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Program Ready"]

    stat, _ = a1_controller_proxy.call("AeroScriptProgramStart", None)
    assert stat == 0
    time.sleep(1)
    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Program Complete"]


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_clear_errors(a1_controller_proxy, a1_axis0_proxy, a1_axis1_proxy):
    """
    Tests the ClearErrors command, which should clear the fault status of any A1Axis device
    controlled by this controller and then disable it. The test relies on the previous test
    putting the axes into fault status, so the test is skipped if the axes do not currently have
    any faults.b The test simply calls the ClearErrors command and then checks the error status of
    the axes. It then re-enables them for the next test.
    """
    stat, _ = a1_controller_proxy.call("ClearErrors", None)
    assert stat == 0

    time.sleep(1)

    axis0_stat, axis0_fault = a1_axis0_proxy.call("get", "Error")
    axis1_stat, axis1_fault = a1_axis1_proxy.call("get", "Error")

    assert axis0_stat == 0 and axis1_stat == 0
    assert not axis0_fault and not axis1_fault

    # ClearErrors diables axes, so re-enable them here
    axis0_stat, _ = a1_axis0_proxy.call("Enable", None)
    axis1_stat, _ = a1_axis1_proxy.call("Enable", None)

    assert axis0_stat == 0 and axis1_stat == 0


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_aeroscript_program_start2(a1_controller_proxy, aeroscript_files):
    """
    This command has a second test firstly to check that the command still works as expected when
    an AeroScript that runs endlessly is executed with it, and secondly because running an endless
    scipt facilitates the next tests which require a script to be currently running. The tests
    works largely in the same way as the other test, but with different statuses since the script
    does not complete.
    """
    if "/endless_monitor.ascript" not in aeroscript_files:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")

    stat, _ = a1_controller_proxy.call("set", "AeroScriptFilePath", "/endless_monitor.ascript")
    assert stat == 0
    time.sleep(1)
    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Program Ready"]

    stat, _ = a1_controller_proxy.call("AeroScriptProgramStart", None)
    assert stat == 0
    time.sleep(0.5)
    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Program Running"]


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_aeroscript_program_pause(a1_controller_proxy, aeroscript_files):
    """
    Tests the AeroScriptProgram Pause command. This requires that a program is already running,
    which should be handled by the previous test. However, the test is skipped if there is no
    program running in case the previous test fails. The test itself simply calls the command and
    checks that we get the correct task status afterwards.
    """
    if "/endless_monitor.ascript" not in aeroscript_files:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")

    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0
    if task_status != TASK_STATUS["Program Running"]:
        pytest.skip("No AeroScript running on controller, skipping...")

    stat, _ = a1_controller_proxy.call("AeroScriptProgramPause", None)
    assert stat == 0
    time.sleep(0.5)
    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Program Paused"]


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_aeroscript_program_stop(a1_controller_proxy, aeroscript_files):
    """
    Tests the AeroScriptProgramStop command. This requires that a program is either running or
    paused when the test is run. A program should be in one of these two states after the last two
    tests but this test will be skipped if this is not the case to prevent failures. The test works
    by simply calling the AeroScriptProgramStop command and checking that the task status updates
    as expected. This command also unloads the current AeroScript, so there is an additional check
    that this happens.
    """
    if "/endless_monitor.ascript" not in aeroscript_files:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")

    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0
    if task_status not in (TASK_STATUS["Program Running"], TASK_STATUS["Program Paused"]):
        pytest.skip("No AeroScript running on controller, skipping...")

    stat, _ = a1_controller_proxy.call("AeroScriptProgramStop", None)
    assert stat == 0
    time.sleep(0.5)
    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Idle"]

    stat, file_loaded = a1_controller_proxy.call("get", "AeroScriptFilePath")
    assert stat == 0 and file_loaded == ""


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_aeroscript_program_load(a1_controller_proxy, aeroscript_files):
    """
    Tests the AeroScriptProgramLoad command. After the previous test, there should be no AeroScript
    loaded in the Automation1 Controller, but if there is due to a test failure, then this test is
    skipped to avoid additional failures. While the AeroScriptProgramStop command unloads the
    current AeroScript, the value currently written to the AeroScriptFilePath attribute should
    remain. So, this test simply calls the AeroScriptProgramLoad command to check that the file
    path stored in this attribute is successfully loaded to the controller once again.
    """
    if "/endless_monitor.ascript" not in aeroscript_files:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")

    _, file_loaded = a1_controller_proxy.call("get", "AeroScriptFilePath")
    if file_loaded != "":
        pytest.skip("File is already loaded in Automation1 Controller, skipping...")

    stat, _ = a1_controller_proxy.call("AeroScriptProgramLoad", None)
    assert stat == 0
    time.sleep(0.5)
    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Program Ready"]

    stat, file_loaded = a1_controller_proxy.call("get", "AeroScriptFilePath")
    assert stat == 0 and file_loaded == "/endless_monitor.ascript"


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_aeroscript_program_run(a1_controller_proxy, aeroscript_files):
    """
    Tests the AeroScriptProgramRun command. This is essentially a combination of the
    AeroScriptProgramLoad and AeroScriptProgramStart commands. Therefore, it requires that no
    AeroScript is currently loaded on the Automation1 Controller. Therefore, we call
    AeroScripProgramStop to clean the Controller, then call AeroScriptProgramRun, check that the
    program is loaded and runs as expected, with the correct task status, and then run the
    AeroScriptProgramStop command again to bring the system to a consistent state.
    """
    if "/endless_monitor.ascript" not in aeroscript_files:
        pytest.skip("Required AeroScipts not installed on controller, skipping...")

    # Call AeroScriptProgramStop to unload the current AeroScript from the controller but leave
    # the value in the write attribute of AeroScriptFilePath so we can test that
    # AeroScriptProgramRun loads te program before running
    stat, _ = a1_controller_proxy.call("AeroScriptProgramStop", None)
    assert stat == 0
    time.sleep(0.5)

    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Idle"]

    stat, file_loaded = a1_controller_proxy.call("get", "AeroScriptFilePath")
    assert stat == 0 and file_loaded == ""

    stat, _ = a1_controller_proxy.call("AeroScriptProgramRun", None)
    assert stat == 0
    time.sleep(0.5)

    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Program Running"]

    stat, _ = a1_controller_proxy.call("AeroScriptProgramStop", None)
    assert stat == 0
    time.sleep(0.5)

    stat, task_status = a1_controller_proxy.call("get", "Automation1TaskStatus")
    assert stat == 0 and task_status == TASK_STATUS["Idle"]

    stat, file_loaded = a1_controller_proxy.call("get", "AeroScriptFilePath")
    assert stat == 0 and file_loaded == ""


# Pylint thinks fixtures are redefining names of outer functions, disable warning
# pylint: disable=redefined-outer-name
def test_disable(a1_controller_proxy, a1_axis0_proxy, a1_axis1_proxy):
    """
    Tests the Disable command. This command simply disables all A1Axis devices controlled by this
    controller. The test works by calling the Disable command and then checking the state and
    status of the two A1Axis devices controlled by this A1Controller device have updated as
    appropriate.
    """
    a1_controller_proxy.call("Disable", None)
    time.sleep(1)
    stat, enabled = a1_axis0_proxy.call("get", "Enabled")
    assert stat == 0 and not enabled
    stat, state = a1_axis0_proxy.call("State")
    assert stat == 0 and str(state) == "OFF"
    stat, status = a1_axis0_proxy.call("Status")
    assert stat == 0 and status == "Axis is off"

    stat, enabled = a1_axis1_proxy.call("get", "Enabled")
    assert stat == 0 and not enabled
    stat, state = a1_axis1_proxy.call("State")
    assert stat == 0 and str(state) == "OFF"
    stat, status = a1_axis1_proxy.call("Status")
    assert stat == 0 and status == "Axis is off"
