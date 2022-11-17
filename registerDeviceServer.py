#! /usr/bin/env python 

import fandango as fn
import argparse 
from pprint import pprint


def get_args(): 
    parser = argparse.ArgumentParser(description="Setup a device server for an Automation1 motor")
    
    parser.add_argument("serverName", type=str, help="Name for the Tango device server")
    parser.add_argument("deviceName", type=str, help="Part of the device names. The " +\
        "\"controller\" device name will be \"automation1/<deviceName>/controller\"")
    parser.add_argument("ip", type=str, help="IP address for the motor")
    parser.add_argument("numAxes", type=int, help="The number of axes to set up on the controller")
    parser.add_argument("--simulation", help="Sets this device to be in simulation",
        required=False, default=False, action='store_true')
    parser.add_argument("--username", type=str, help="SSH username for the motor", required=False,
        default='')
    parser.add_argument("--password", type=str, help="SSH password for the motor", required=False,
        default='')

    return parser.parse_args()

def create_devices(serverName, deviceName, ipAddress, username, password, simulation, numAxes):
    formatDeviceName = lambda d: "automation1/{0}/{1}".format(deviceName, d)

    # main
    deviceServer = "Automation1/{}".format(serverName)
    mainDevice = formatDeviceName("controller") 

    fn.tango.add_new_device(deviceServer, "A1Controller", mainDevice)
    fn.tango.put_device_property(mainDevice, "IpAddress", ipAddress)
    fn.tango.put_device_property(mainDevice, "Username", username)
    fn.tango.put_device_property(mainDevice, "Password", password)
    fn.tango.put_device_property(mainDevice, "Simulate", simulation)
    fn.get_database(mainDevice).put_device_attribute_property(mainDevice, 
        {"AxisHealth": 
            {'BooleanLabels': 
                ['Axis {}'.format(x) for x in range(32)]
            }
        })
    fn.get_database(mainDevice).put_device_attribute_property(mainDevice, 
        {"TaskStatus0": 
            {'BooleanLabels': 
                ['Program Associated', 
                 'Immediate Executing',
                 'Return Motion Executing',
                 'Program Reset',
                 'Pending Axes Stop',
                 'Feedhold Active',
                 'Callback Hold Active',
                 'Callback Responding',
                 'Spindle Active',
                 'Retrace',
                 'Interrupt Motion Active',
                 'Joystick Active',
                 'Corner Rounding',
                 'Joystick Low Speed Active',
                 'Sync Function Executing',
                 'Task Control Restricted']
            }
        })
    fn.get_database(mainDevice).put_device_attribute_property(mainDevice, 
        {"TaskStatus1": 
            {'BooleanLabels': 
                ['Async SMC Motion Abort Pending', 
                 'Retrace Requested',
                 'MOS Change',
                 'Spindle Feedhold',
                 'Feedhold Axes Stopped',
                 'Cutter Radius Enabling',
                 'Cutter Radius Disabling',
                 'Cutter Offsets Enabling (Positive)',
                 'Cutter Offsets Enabling (Negative)',
                 'Cutter Offsets Disabling',
                 'On Error Handler Pending',
                 'On Error Handler Executing',
                 'Program Stop Pending',
                 'Sync Function Pending',
                 'No MFO Floor',
                 'Interrupted',
                 'IFOV Buffer Hold']
            }
        })
    fn.get_database(mainDevice).put_device_attribute_property(mainDevice, 
        {"TaskStatus2": 
            {'BooleanLabels': 
                ['Scaling Active',
                 'Offset Fixture Active',
                 'Profile Active',
                 'Motion Mode Rapid',
                 'Motion Mode Linear',
                 'Motion PVT',
                 'Motion Continuous Active',
                 'Cutter Offsets Active (Positive)',
                 'Cutter Offsets Active (Left)',
                 'Cutter Offsets Active (Right)',
                 'Cutter Offsets Active (Negative)',
                 'Normalcy Active (Left)',
                 'Normalcy Active (Right)',
                 'Normalcy Alignment',
                 'Motion Mode CW',
                 'Motion Mode CCW',
                 'Limit Feedrate Active',
                 'Limit MFO Active',
                 'Co-ordinate 1, Plane 1',
                 'Co-ordinate 1, Plane 2',
                 'Co-ordinate 1, Plane 3',
                 'Co-ordinate 2, Plane 1',
                 'Co-ordinate 2, Plane 2',
                 'Co-ordinate 2, Plane 3']
            }
        })

    # axes
    for i in range(numAxes): 
        axisDevice = formatDeviceName("axis{}".format(i))
        fn.tango.add_new_device(deviceServer, "A1Axis", axisDevice)
        fn.tango.put_device_property(axisDevice, "Axis", "{}".format(i))
        fn.tango.put_device_property(axisDevice, "MainDeviceName", mainDevice)
        fn.get_database(axisDevice).put_device_attribute_property(axisDevice, 
            {"AxisStatus": 
                {'BooleanLabels': 
                    ['Homed',
                     'Profiling',
                     'Wait Done',
                     'Command Valid',
                     'Homing',
                     'Enabling',
                     'Jog Generating',
                     'Jogging',
                     'Drive Pending',
                     'Drive Abort Pending',
                     'Trajectory Filtering',
                     'IFOV Enabled',
                     'Not Virtual',
                     'Cal. Enabled (1D)',
                     'Cal. Enabled (2D)',
                     'Camming Gearing Control',
                     'Joystick Control',
                     'Backlash Active',
                     'Gain Mapping Enabled',
                     'Motion Done',
                     'Motion Clamped',
                     'Gantry Aligned',
                     'Gantry Drive Control Realigning',
                     'Thermo Comp. Enabled']
                }
            })
        fn.get_database(axisDevice).put_device_attribute_property(axisDevice, 
            {"AxisFault": 
                {'BooleanLabels': 
                    ['Position Error',
                     'Over Current',
                     'CW EOT Limit',
                     'CCW EOT Limit',
                     'CW Soft Limit',
                     'CCW Soft Limit',
                     'Amplifier Fault',
                     'FBK Input 0',
                     'FBK Input 1',
                     'Hall Fault',
                     'Max. Velocity',
                     'E-Stop Fault',
                     'Velocity Error',
                     'External Fault',
                     'Motor Temperature',
                     'Amplifier Temperature',
                     'Encoder Fault',
                     'Misalignment Fault',
                     'FBK Scaling Fault',
                     'MRK Search Fault',
                     'Safe Zone Fault',
                     'In Position Timeout',
                     'Voltage Clamp',
                     'Motor Supply',
                     'Internal Fault']
                }
            })
        fn.get_database(axisDevice).put_device_attribute_property(axisDevice, 
            {"DriveStatus": 
                {'BooleanLabels': 
                    ['Enabled',
                     'CW EOT Limit',
                     'CCW EOT Limit',
                     'Home Limit',
                     'Marker Input',
                     'Hall A Input',
                     'Hall B Input',
                     'Hall C Input',
                     'Sine Encoder Error',
                     'Cosine Encoder Error',
                     'E-Stop Input',
                     'Brake Output',
                     'Galvo Power Correction',
                     'No Motor Supply',
                     'Current Clamp',
                     'Marker Latch',
                     'Power Limiting',
                     'Galvo Cal. Enabled',
                     'Autofocus Active',
                     'Program Flash',
                     'Servo Control',
                     'In Position',
                     'Move Active',
                     'Accel. Phase',
                     'Decel. Phase',
                     'Encoder Clipping',
                     'Dual Loop Active']
                }
            })


if __name__=="__main__": 
    args = get_args()
    
    pprint(args)
    create_devices(args.serverName, args.deviceName, args.ip, args.username, args.password, args.simulation, args.numAxes)