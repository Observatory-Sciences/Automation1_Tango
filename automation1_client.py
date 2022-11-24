#! /usr/bin/env python

"""
A python script that can get, set and provide info about any attribute for the given TANGO device.
The script can also send any command to a TANGO device.
"""

from __future__ import print_function

import argparse
import tango
import numpy


def _parse_auto_type(string):
    """
    Try to convert command line input to int/float/string (in that order) if possible
    :param string: string passed in from command line (parse uses white space sep.)
    :return: converted value
    """
    try:
        return int(string)
    except ValueError:
        pass

    try:
        return float(string)
    except ValueError:
        pass

    return string


def parse_args():
    """
    Parse command line arguments
    :return: namespace of parsed command line arguments
    """
    parser = argparse.ArgumentParser(description="Interact with Automation1 TANGO device server")
    parser.add_argument("--device", type=str, required=True,
                        help='TANGO device')
    parser.add_argument("--verbose", action="store_true",
                        help='Turn on additional printing')
    parser.add_argument("action", type=str,
                        help='action to take. Use a TANGO command or "get"/"set"/"info" '
                             '(respectively) to get, set and get info on an attribute')
    parser.add_argument("arguments", nargs="*", type=_parse_auto_type, default=None,
                        help='depending on action, either: '
                             'an attribute for a "get"/"info" action, or '
                             'an attribute and a value for the "set" action, or '
                             'arguments to pass to a TANGO command. ')
    return parser.parse_args()


class Automation1Proxy(object):
    """
    Wrapper around tango.DeviceProxy to interact with TANGO device
    """
    def __init__(self, device, print_response, verbose=False):
        self.m_automation1 = tango.DeviceProxy(device)
        self.m_print_response = print_response
        self.callbacks = {
            "set": self.attr_set,
            "get": self.attr_get,
            "info": self.attr_info
        }
        self.verbose = verbose

    def verbose_print(self, *args):
        """
        Verbose print function
        """
        if self.verbose:
            print(*args)

    def call(self, action, *args):
        """
        If "action" string matches pre-defined keyword in callback dictionary, call corresponding
        function; else pass to TANGO as a command
        :param action: string defining action to take
        :param args: passed to action function
        :return: returns value from action function (0 for success, 1 for failure)
        """
        # if we've predefined the action, call it now
        if action in self.callbacks:
            return self.callbacks[action](*args)
        # else pass to TANGO as a command
        return self.command(action, *args)

    def attr_set(self, attribute, *values):
        """
        Set TANGO device attribute value
        :param attribute: attribute to set
        :param values: values; converted to single scalar value or ndarray for spectrum attributes
        :return: 0 for success, 1 for error
        """
        if len(values) == 1:
            values = values[0]
        self.verbose_print("Set attribute:\t {}\nWith input:\t {}".format(attribute, values))

        try:
            att_info = self.m_automation1[attribute]
        except tango.DevFailed as err:
            print("Error:", err)
            return 1, None

        att = att_info.value
        self.verbose_print("Attr. current value:\t {}".format(att))
        t_att = type(att)
        self.verbose_print("Attr. requires type:\t {}".format(t_att))

        if isinstance(att, numpy.ndarray):
            # if attribute is a spectrum (ndarray), must be set using flattened ndarray
            out = numpy.zeros_like(att).flatten() # pylint: disable=no-member
            try:
                out[:] = values
            except ValueError as err:
                print("Error:", err)
                return 1, None
        else:
            # attempt to convert to matching type
            try:
                out = t_att(values)
            except Exception as err: # pylint: disable=broad-except
                print("Error:", err)
                return 1, None

        self.verbose_print("Input after conversion:\t {}".format(out))
        try:
            self.m_automation1[attribute] = out
        except Exception as err: # pylint: disable=broad-except
            print("Error: failed to set attribute {}: \n".format(attribute), err)
            return 1, None

        return 0, "OK"

    def attr_get(self, attribute):
        """
        Get value of TANGO device attribute and print
        :param attribute: attribute to get
        :return: 0 for success, 1 for failure
        """
        self.verbose_print("Get attribute:\t {}".format(attribute))
        try:
            att_info = self.m_automation1[attribute]
            att = att_info.value
            self.verbose_print("Value:")
            if self.m_print_response:
                print(att)
            return 0, att
        except Exception as err: # pylint: disable=broad-except
            print("Error:", err)
        return 1, None

    def attr_info(self, attribute):
        """
        Get info on TANGO device attribute and print
        :param attribute: attribute to get info for
        :return: 0 for success, 1 for failure
        """
        self.verbose_print("Get info for attribute:\t {}".format(attribute))
        try:
            att = self.m_automation1[attribute]
            if self.m_print_response:
                print(att)
            return 0, att
        except Exception as err: # pylint: disable=broad-except
            print("Error:", err)
        return 1, None

    def command(self, command, *arguments):
        """
        Send command to TANGO device and print response
        :param command: name of command, string
        :param arguments: command arguments
        :return: 0 for success, 1 for failure
        """
        self.verbose_print("Send command:\t {}".format(command))

        # If arguments is empty
        if not arguments:
            arguments = None
        elif len(arguments) == 1:
            arguments = arguments[0]
        self.verbose_print("Arguments:\t {}".format(arguments))

        try:
            out = self.m_automation1.command_inout(command, arguments)
            self.verbose_print("Response:")
            if self.m_print_response:
                print(out)
            return 0, out
        except Exception as err: # pylint: disable=broad-except
            print("Error: command {} failed:\n{}".format(command, err))
        return 1, None


def _main():
    """
    Main function. Parses command line arguments and takes appropriate action.
    usage: automation1client.py [-h] [--device DEVICE] [--verbose]
                  action [arguments ...]
    :return: exits with 0 for success, 1 for failure
    """
    cmd_args = parse_args()

    # turn on printing
    verbose = cmd_args.verbose

    if verbose:
        print("Arguments:\t", cmd_args)

    device = cmd_args.device
    if verbose:
        print("Using device:\t", device)

    try:
        automation1 = Automation1Proxy(device, True, verbose)
    except tango.DevFailed as err:
        print("Error: failed to connect to device {}:\n{}".format(device, err))
        exit(1)

    if verbose:
        print("Device state:\t", automation1.m_automation1.state())

    stat, _ = automation1.call(cmd_args.action, *cmd_args.arguments)

    exit(stat)


if __name__ == "__main__":
    _main()
