
#pragma once

// axis status indices
#define AX_HOMED                                0
#define AX_PROFILING                            1
#define AX_WAIT_DONE                            2
#define AX_COMMAND_VALID                        3
#define AX_HOMING                               4
#define AX_ENABLING                             5
#define AX_JOG_GENERATING                       6
#define AX_JOGGING                              7
#define AX_DRIVE_PENDING                        8
#define AX_DRIVE_ABORT_PENDING                  9
#define AX_TRAJECTORY_FILTERING                 10
#define AX_IFOV_ENABLED                         11
#define AX_NOT_VIRTUAL                          12
#define AX_CAL_ENABLED1D                        13  
#define AX_CAL_ENABLED2D                        14  
#define AX_CAMMING_GEARING_CONTROL              15      
#define AX_JOYSTICK_CONTROL                     16          
#define AX_BACKLASH_ACTIVE                      17              
#define AX_GAIN_MAPPING_ENABLED                 18              
#define AX_MOTION_DONE                          19              
#define AX_MOTION_CLAMPED                       20          
#define AX_GANTRY_ALIGNED                       21
#define AX_GANTRY_DRIVE_CONTROL_REALIGNING      22
#define AX_THERMO_COMP_ENABLED                  23
#define AX_TRANSFORMATION_INPUT                 24
#define AX_TRANSFORMATION_OUTPUT                25


//Axis faults
#define AX_F_POSITION_ERROR         0
#define AX_F_OVER_CURRENT           1
#define AX_F_CW_EOT_LIMIT           2
#define AX_F_CCW_EOT_LIMIT          3
#define AX_F_CW_SOFT_LIMIT          4
#define AX_F_CCW_SOFT_LIMIT         5
#define AX_F_AMPLIFIER_FAULT        6
#define AX_F_FBK_INPUT0             7
#define AX_F_FBK_INPUT1             8
#define AX_F_HALL_FAULT             9
#define AX_F_MAX_VELOCITY           10
#define AX_F_E_STOP_FAULT           11
#define AX_F_VELOCITY_ERROR         12
#define AX_F_EXTERNAL_FAULT         13
#define AX_F_MOTOR_TEMP             14
#define AX_F_AMPLIFIER_TEMP         15
#define AX_F_ENCODER_FAULT          16
#define AX_F_MISALIGNMENT_FAULT     17
#define AX_F_FBK_SCALING_FAULT      18
#define AX_F_MRK_SEARCH_FAULT       19
#define AX_F_SAFE_ZONE_FAULT        20
#define AX_F_IN_POS_TIMEOUT         21
#define AX_F_VOLTAGE_CLAMP          22
#define AX_F_MOTOR_SUPPLY           23
#define AX_F_INTERNAL               24

//Drive Status
#define DRV_ENABLED                 0
#define DRV_CW_EOT_LIMIT            1
#define DRV_CCW_EOT_LIMIT           2
#define DRV_HOME_LIMIT              3
#define DRV_MARKER_INPUT            4
#define DRV_HALL_A_INPUT            5
#define DRV_HALL_B_INPUT            6
#define DRV_HALL_C_INPUT            7
#define DRV_SINE_ENCODER_ERROR      8
#define DRV_COSINE_ENCODER_ERROR    9
#define DRV_E_STOP_INPUT            10
#define DRV_BRAKE_OUTPUT            11
#define DRV_GALVO_POWER_CORRECTION  12
#define DRV_NO_MOTOR_SUPPLY         13
#define DRV_CURRENT_CLAMP           14
#define DRV_MARKER_LATCH            15
#define DRV_POWER_LIMITING          16
#define DRV_GALVO_CAL_ENABLED       17
#define DRV_AUTOFOCUS_ACTIVE        18
#define DRV_PROGRAM_FLASH           19
#define DRV_SERVO_CONTROL           20
#define DRV_IN_POSITION             21
#define DRV_MOVE_ACTIVE             22
#define DRV_ACCEL_PHASE             23
#define DRV_DECEL_PHASE             24
#define DRV_ENCODER_CLIPPING        25
#define DRV_DUAL_LOOP_ACTIVE        26
#define DRV_AMPLIFIER_ACTIVE        27

//Task Statuses 0,1,2

//TaskStatus0
#define TSK0_PROGRAM_ASSOCIATED         0
#define TSK0_IMMEDIATE_EXECUTING        1
#define TSK0_RETURN_MOTION_EXECUTING    2
#define TSK0_PROGRAM_RESET              3
#define TSK0_PENDING_AXES_STOP          4
#define TSK0_FEEDHOLD_ACTIVE            5
#define TSK0_CALLBACK_HOLD_ACTIVE       6
#define TSK0_CALLBACK_RESPONDING        7
#define TSK0_SPINDLE_ACTIVE             8
#define TSK0_RETRACE                    9
#define TSK0_INTERRUPT_MOTION_ACTIVE    10
#define TSK0_JOYSTICK_ACTIVE            11
#define TSK0_CORNER_ROUNDING            12
#define TSK0_JOYSTICK_LOW_SPEED_ACTIVE  13
#define TSK0_SYNC_FUNCTION_EXECUTING    14
#define TSK0_TASK_CONTROL_RESTRICTED    15

//TaskStatus1
#define TSK1_ASYNC_SMC_MOTION_ABORT_PENDING 0
#define TSK1_RETRACE_REQUESTED              1
#define TSK1_MSO_CHANGE                     2
#define TSK1_SPINDLE_FEEDHOLD               3
#define TSK1_FEEDHOLD_AXES_STOPPED          4
#define TSK1_CUTTER_RADIUS_ENABLING         5
#define TSK1_CUTTER_RADIUS_DISABLING        6
#define TSK1_CUTTER_OFFSETS_ENABLING_POS    7
#define TSK1_CUTTER_OFFSETS_ENABLING_NEG    8
#define TSK1_CUTTER_OFFSETS_DISABLING       9
#define TSK1_ON_ERROR_HANDLER_PENDING       10
#define TSK1_ON_ERROR_HANDLER_EXECUTING     11
#define TSK1_PROGRAM_STOP_PENDING           12
#define TSK1_SYNC_FUNCTION_PENDING          13
#define TSK1_NO_MFO_FLOOR                   14
#define TSK1_INTERRUPTED                    15
#define TSK1_IFOV_BUFFER_HOLD               16

//TaskStatus2
#define TSK2_SCALING_ACTIVE             0
#define TSK2_PROFILE_ACTIVE             1
#define TSK2_MOTION_MODE_RAPID          2
#define TSK2_MOTION_MODE_LINEAR         3
#define TSK2_MOTION_PVT                 4
#define TSK2_MOTION_CONTINUOUS_ACTIVE   5
#define TSK2_CUTTER_OFFSETS_ACTIVE_POS  6
#define TSK2_CUTTER_RADIUS_ACTIVE_LEFT  7
#define TSK2_CUTTER_RADIUS_ACTIVE_RIGHT 8
#define TSK2_CUTTER_OFFSETS_ACTIVE_NEG  9
#define TSK2_NORMALCY_ACTIVE_LEFT       10
#define TSK2_NORMALCY_ACTIVE_RIGHT      11
#define TSK2_NORMALCY_ALIGNMENT         12
#define TSK2_MOTION_MODE_CW             13
#define TSK2_MOTION_MODE_CCW            14
#define TSK2_LIMIT_FEEDRATE_ACTIVE      15
#define TSK2_LIMIT_MFO_ACTIVE           16
#define TSK2_COORD1_PLANE1              17
#define TSK2_COORD1_PLANE2              18
#define TSK2_COORD1_PLANE3              19
#define TSK2_COORD2_PLANE1              20
#define TSK2_COORD2_PLANE2              21
#define TSK2_COORD2_PLANE3              22

//constants
#define ERR_MSG_SZ                      2048
#define AXIS_NAME_SZ                    256
#define DEFAULT_TIMEOUT_MS              300
#define SHORTEST_POLLING_INTERVAL_MS    50


#define MAX_AXES 32
#define MAX_TASKS 32
#define MAX_AEROSCRIPTS 1024
#define TASK0_STATUSES 16
#define TASK1_STATUSES 17
#define TASK2_STATUSES 23
