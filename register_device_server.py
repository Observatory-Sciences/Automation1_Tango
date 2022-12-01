#! /usr/bin/env python

"""
Python script to generate a TANGO device server for Automation1. The device server generated will
have labels for the spectrum attributes automatically generated using the accompanying JSON files.
If the labels need to be changed, then these JSON files can be updated and the device server
regenerated. The server and device name, number of axes, IP address and credentials for the
Automation1 Controller and whether or not the device is in simulation can all be specified at the
command line.
"""

import argparse
import json
from pprint import pprint
import fandango as fn

def get_args():
    """
    Function to parse the command line arguments passed to the script
    """
    parser = argparse.ArgumentParser(description="Setup a device server for an Automation1 motor")

    parser.add_argument("server_name", type=str, help="Name for the Tango device server")
    parser.add_argument("device_name", type=str, help="Part of the device names. The " +\
        "\"controller\" device name will be \"<device_name>/controller\" and the \"axis\" " +\
        "device names will be  \"<device_name>/axis<n>\", where n is the axis number")
    parser.add_argument("ip", type=str, help="IP address for the Automation1 Controller")
    parser.add_argument("num_axes", type=int, help="The number of axes to set up on the controller")
    parser.add_argument("--simulation", help="Sets this device to be in simulation",
                        required=False, default=False, action='store_true')
    parser.add_argument("--username", type=str, help="SSH username for connecting to the " +\
        "Automation1 Controller", required=False, default='')
    parser.add_argument("--password", type=str, help="SSH password for connecting to the " +\
        "Automation1 Controller", required=False, default='')

    return parser.parse_args()

# All locals and arguments required, so disabling warnings
# pylint: disable=too-many-arguments,too-many-locals
def create_devices(server_name, device_name, ip_address, username, password, simulation, num_axes):
    """
    Function to actually create devices in the TANGO database using the fandango module. The
    function creates the entries in the TANGO database and then loads labels for the spectrum
    attributes from various JSON files before adding them to the appropriate attributes in the
    database.
    """
    format_device_name = lambda d: "automation1/{0}/{1}".format(device_name, d)

    # Controller
    device_server = "Automation1/{}".format(server_name)
    main_device = format_device_name("controller")

    fn.tango.add_new_device(device_server, "A1Controller", main_device)
    fn.tango.put_device_property(main_device, "IpAddress", ip_address)
    fn.tango.put_device_property(main_device, "Username", username)
    fn.tango.put_device_property(main_device, "Password", password)
    fn.tango.put_device_property(main_device, "Simulate", simulation)

    axis_labels = ['Axis {}'.format(x) for x in range(32)]
    axis_labels_dict = {"AxisHealth" : {'BooleanLabels' : axis_labels}}
    fn.get_database(main_device).put_device_attribute_property(main_device, axis_labels_dict)

    for i in range(3):
        with open("TaskStatus{}Labels.json".format(i), 'r') as json_file:
            task_status_dict = byteify(json.load(json_file))
            fn.get_database(main_device)\
                .put_device_attribute_property(main_device, task_status_dict)

    # Axes

    # All axes have the same labels, so no use in loading the same json files multiple times
    axis_status_labels = {}
    axis_fault_labels = {}
    drive_status_labels = {}

    with open("AxisStatusLabels.json", 'r') as json_file:
        axis_status_labels = byteify(json.load(json_file))

    with open("AxisFaultLabels.json", 'r') as json_file:
        axis_fault_labels = byteify(json.load(json_file))

    with open("DriveStatusLabels.json", 'r') as json_file:
        drive_status_labels = byteify(json.load(json_file))

    for i in range(num_axes):
        axis_device = format_device_name("axis{}".format(i))
        fn.tango.add_new_device(device_server, "A1Axis", axis_device)
        fn.tango.put_device_property(axis_device, "Axis", "{}".format(i))
        fn.tango.put_device_property(axis_device, "MainDeviceName", main_device)

        fn.get_database(axis_device).put_device_attribute_property(axis_device, axis_status_labels)
        fn.get_database(axis_device).put_device_attribute_property(axis_device, axis_fault_labels)
        fn.get_database(axis_device)\
            .put_device_attribute_property(axis_device, drive_status_labels)


def byteify(inpt):
    """
    Converts any unicode text in a dictionary, list or string to standard UTF-8 encoded byte
    strings.
    """
    if isinstance(inpt, dict):
        return {byteify(key): byteify(value)
                for key, value in inpt.iteritems()}
    elif isinstance(inpt, list):
        return [byteify(element) for element in inpt]
    elif isinstance(inpt, unicode):
        return inpt.encode('utf-8')

    return inpt


if __name__ == "__main__":
    ARGS = get_args()

    pprint(ARGS)
    create_devices(ARGS.server_name, ARGS.device_name, ARGS.ip, ARGS.username, ARGS.password,
                   ARGS.simulation, ARGS.num_axes)
