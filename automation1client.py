#! /usr/bin/env python

from __future__ import print_function 

import argparse
import tango
from pprint import pprint
import numpy

verbose = False

def verbose_print(*args):
    """
    Verbose print function. 
    """
    global verbose

    if verbose:
        print(*args)
    else:
        pass


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


class Automation1Proxy:
    """
    Wrapper around tango.DeviceProxy to interact with TANGO device
    """
    def __init__(self, device):
        self.m_automation1 = tango.DeviceProxy(device)
        self.callbacks = {
            "set": self.attr_set,
            "get": self.attr_get,
            "info": self.attr_info
        }

    def call(self, action, *args):
        """
        If "action" string matches pre-defined keyword in callback dictionary, call corresponding function;
        else pass to TANGO as a command
        :param action: string defining action to take
        :param args: passed to action function
        :return: returns value from action function (0 for success, 1 for failure)
        """
        # if we've predefined the action, call it now
        if action in self.callbacks:
            return self.callbacks[action](*args)
        # else pass to TANGO as a command
        else:
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
        verbose_print("Set attribute:\t {}\nWith input:\t {}".format(attribute, values))

        try:
            att_info = self.m_automation1[attribute]
        except tango.DevFailed as e:
            print("Error:", e)
            return 1

        att = att_info.value
        verbose_print("Attr. current value:\t {}".format(att))
        t_att = type(att)
        verbose_print("Attr. requires type:\t {}".format(t_att))

        if isinstance(att, numpy.ndarray):
            # if attribute is a spectrum (ndarray), must be set using flattened ndarray
            out = numpy.zeros_like(att).flatten()
            try:
                out[:] = values
            except ValueError as e:
                print("Error:", e)
                return 1
        else:
            # attempt to convert to matching type
            try:
                out = t_att(values)
            except Exception as e:
                print("Error:", e)
                return 1

        verbose_print("Input after conversion:\t {}".format(out))
        try:
            self.m_automation1[attribute] = out
        except Exception as e:
            print("Error: failed to set attribute {}: \n".format(attribute), e)
            return 1

        return 0

    def attr_get(self, attribute):
        """
        Get value of TANGO device attribute and print
        :param attribute: attribute to get
        :return: 0 for success, 1 for failure
        """
        verbose_print("Get attribute:\t {}".format(attribute))
        try:
            att_info = self.m_automation1[attribute]
            att = att_info.value
            verbose_print("Value:")
            print(att)
            return 0
        except Exception as e:
            print("Error:", e)
        return 1

    def attr_info(self, attribute):
        """
        Get info on TANGO device attribute and print
        :param attribute: attribute to get info for
        :return: 0 for success, 1 for failure
        """
        verbose_print("Get info for attribute:\t {}".format(attribute))
        try:
            att = self.m_automation1[attribute]
            print(att)
            return 0
        except Exception as e:
            print("Error:", e)
        return 1

    def command(self, command, *arguments):
        """
        Send command to TANGO device and print response
        :param command: name of command, string
        :param arguments: command arguments
        :return: 0 for success, 1 for failure
        """
        verbose_print("Send command:\t {}".format(command))

        if len(arguments) == 0:
            arguments = None
        elif len(arguments) == 1:
            arguments = arguments[0]
        verbose_print("Arguments:\t {}".format(arguments))

        try:
            out = self.m_automation1.command_inout(command, arguments)
            verbose_print("Response:")
            print(out)
            return 0
        except Exception as e:
            print("Error: command {} failed:\n{}".format(command, e))
        return 1


def _main():
    """
    Main function. Parses command line arguments and takes appropriate action.
    usage: automation1client.py [-h] [--device DEVICE] [--verbose]
                  action [arguments ...]
    :return: exits with 0 for success, 1 for failure
    """
    global verbose

    cmdArgs = parse_args()

    # turn on printing
    verbose = cmdArgs.verbose

    verbose_print("Arguments:\t", cmdArgs)

    # if (cmdArgs.device is None):
    #     print("No device provided. See usage")
    #     return 1
    device = cmdArgs.device
    verbose_print("Using device:\t", device)

    try:
        automation1 = Automation1Proxy(device)
    except tango.DevFailed as e:
        print("Error: failed to connect to device {}:\n{}".format(device, e))
        exit(1)

    verbose_print("Device state:\t", automation1.m_automation1.state())

    out = automation1.call(cmdArgs.action, *cmdArgs.arguments)

    exit(out)


if __name__ == "__main__":
    _main()
