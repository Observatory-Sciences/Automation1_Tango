#include "A1Simulation.h"
#include <chrono>

namespace A1Bridge_ns {


void sim_axes(void *s_ptr)
{
    std::cout << "sim_axes called" << std::endl;
    // Call into the run routine
    ((A1Simulation *)s_ptr)->run();
}

A1Simulation::A1Simulation()
{
    m_simulation = true;
    m_axes.resize(MAX_AXES);
    m_motor_type = "Simulation";

    // Create thread to perform the simulations
    t_ptr = new std::thread(sim_axes, this);
}


A1Simulation::~A1Simulation()
{}


void A1Simulation::run()
{
    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // Loop over the axes and call update for each one
        for (int axis=0; axis < MAX_AXES; axis++){
            m_axes[axis].update();
        }
    }
}

void A1Simulation::connect_impl(std::string username, std::string password, std::string ip)
{
    std::cout << "Connected to A1 controller in simulation" << std::endl; 
    attr_ControllerRunning_read = true; 
    std::cout << "Controller is running." << std::endl;
}


void A1Simulation::disconnect_impl()
{
    
}

void A1Simulation::initialiseController_impl()
{
}


void A1Simulation::initialiseAxis_impl(unsigned axis)
{    
}

void A1Simulation::readAxis_impl(unsigned axis)
{
    //unsigned vectorLength = attr_axisContainer[axis].size();
    //double axisResults[vectorLength];

    // Read axis current position
    attr_axes[axis].attr_PositionFeedback_read = m_axes[axis].m_position;
    // Read axis velocity
    attr_axes[axis].attr_VelocityFeedback_read = m_axes[axis].m_current_velocity;
    // Read axis acceleration
    attr_axes[axis].attr_AccelerationFeedback_read = m_axes[axis].m_acceleration;
    // Motor type set to simulation
    attr_axes[axis].attr_MotorType_read = Tango::string_dup(m_motor_type.c_str());
//    for (auto attr : attr_axisContainer[axis])
//    {
//        getAxisResult(axis, axisResults, attr, std::string(__func__));
//    }

    // Axis status

    attr_axes[axis].attr_AxisStatus_read[SIM_AX_HOMED]                         = m_axes[axis].m_homed; //Homed
    //attr_axes[axis].attr_AxisStatus_read[SIM_AX_PROFILING]                       = (int(attr_axes[axis].axisStatus) >> 1 ) & 1U; //Profiling
    //attr_axes[axis].attr_AxisStatus_read[SIM_AX_WAIT_DONE]                       = (int(attr_axes[axis].axisStatus) >> 2 ) & 1U; //WaitDone
    // attr_axes[axis].attr_AxisStatus_read[AX_COMMAND_VALID]                   = (int(attr_axes[axis].axisStatus) >> 3 ) & 1U; //CommandValid
    // attr_axes[axis].attr_AxisStatus_read[AX_HOMING]                          = (int(attr_axes[axis].axisStatus) >> 4 ) & 1U; //Homing
     attr_axes[axis].attr_AxisStatus_read[SIM_AX_ENABLING]                     = m_axes[axis].m_enabled; //Enabling
    // attr_axes[axis].attr_AxisStatus_read[AX_JOG_GENERATING]                  = (int(attr_axes[axis].axisStatus) >> 7 ) & 1U; //JogGenerating
    // attr_axes[axis].attr_AxisStatus_read[AX_JOGGING]                         = (int(attr_axes[axis].axisStatus) >> 8 ) & 1U; //Jogging
    // attr_axes[axis].attr_AxisStatus_read[AX_DRIVE_PENDING]                   = (int(attr_axes[axis].axisStatus) >> 9 ) & 1U; //DrivePending
    // attr_axes[axis].attr_AxisStatus_read[AX_DRIVE_ABORT_PENDING]             = (int(attr_axes[axis].axisStatus) >> 10) & 1U; //DriveAbortPending
    // attr_axes[axis].attr_AxisStatus_read[AX_TRAJECTORY_FILTERING]            = (int(attr_axes[axis].axisStatus) >> 11) & 1U; //TrajectoryFiltering
    // attr_axes[axis].attr_AxisStatus_read[AX_IFOV_ENABLED]                    = (int(attr_axes[axis].axisStatus) >> 12) & 1U; //IfovEnabled
    attr_axes[axis].attr_AxisStatus_read[SIM_AX_NOT_VIRTUAL]                     = (int(attr_axes[axis].axisStatus) >> 13) & 1U; //NotVirtual
    // attr_axes[axis].attr_AxisStatus_read[AX_CAL_ENABLED1D]                   = (int(attr_axes[axis].axisStatus) >> 14) & 1U; //CalEnabled1D
    // attr_axes[axis].attr_AxisStatus_read[AX_CAL_ENABLED2D]                   = (int(attr_axes[axis].axisStatus) >> 15) & 1U; //CalEnabled2D
    // attr_axes[axis].attr_AxisStatus_read[AX_CAMMING_GEARING_CONTROL]         = (int(attr_axes[axis].axisStatus) >> 16) & 1U; //CammingGearingControl
    // attr_axes[axis].attr_AxisStatus_read[AX_JOYSTICK_CONTROL]                = (int(attr_axes[axis].axisStatus) >> 17) & 1U; //JoystickControl
    // attr_axes[axis].attr_AxisStatus_read[AX_BACKLASH_ACTIVE]                 = (int(attr_axes[axis].axisStatus) >> 18) & 1U; //BacklashActive
    // attr_axes[axis].attr_AxisStatus_read[AX_GAIN_MAPPING_ENABLED]            = (int(attr_axes[axis].axisStatus) >> 19) & 1U; //GainMappingEnabled
    // attr_axes[axis].attr_AxisStatus_read[AX_MOTION_DONE]                     = (int(attr_axes[axis].axisStatus) >> 22) & 1U; //MotionDone
    // attr_axes[axis].attr_AxisStatus_read[AX_MOTION_CLAMPED]                  = (int(attr_axes[axis].axisStatus) >> 23) & 1U; //MotionClamped
    // attr_axes[axis].attr_AxisStatus_read[AX_GANTRY_ALIGNED]                  = (int(attr_axes[axis].axisStatus) >> 24) & 1U; //GantryAligned
    // attr_axes[axis].attr_AxisStatus_read[AX_GANTRY_DRIVE_CONTROL_REALIGNING] = (int(attr_axes[axis].axisStatus) >> 25) & 1U; //GantryDriveControlRealigning
    // attr_axes[axis].attr_AxisStatus_read[AX_THERMO_COMP_ENABLED]             = (int(attr_axes[axis].axisStatus) >> 27) & 1U; //ThermoCompEnabled

    attr_axes[axis].attr_Homed_read = attr_axes[axis].attr_AxisStatus_read[SIM_AX_HOMED];
    attr_axes[axis].attr_VirtualAxis_read = attr_axes[axis].attr_AxisStatus_read[SIM_AX_NOT_VIRTUAL];

    // // Drive status 

    attr_axes[axis].attr_DriveStatus_read[SIM_DRV_ENABLED]                     =  m_axes[axis].m_enabled;
    // attr_axes[axis].attr_DriveStatus_read[DRV_CW_EOT_LIMIT]                 = (int(attr_axes[axis].driveStatus) >> 1 ) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_CCW_EOT_LIMIT]                = (int(attr_axes[axis].driveStatus) >> 2 ) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_HOME_LIMIT]                   = (int(attr_axes[axis].driveStatus) >> 3 ) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_MARKER_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 4 ) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_HALL_A_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 5 ) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_HALL_B_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 6 ) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_HALL_C_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 7 ) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_SINE_ENCODER_ERROR]           = (int(attr_axes[axis].driveStatus) >> 8 ) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_COSINE_ENCODER_ERROR]         = (int(attr_axes[axis].driveStatus) >> 9 ) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_E_STOP_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 10) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_BRAKE_OUTPUT]                 = (int(attr_axes[axis].driveStatus) >> 11) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_GALVO_POWER_CORRECTION]       = (int(attr_axes[axis].driveStatus) >> 12) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_NO_MOTOR_SUPPLY]              = (int(attr_axes[axis].driveStatus) >> 14) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_CURRENT_CLAMP]                = (int(attr_axes[axis].driveStatus) >> 15) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_MARKER_LATCH]                 = (int(attr_axes[axis].driveStatus) >> 16) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_POWER_LIMITING]               = (int(attr_axes[axis].driveStatus) >> 17) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_GALVO_CAL_ENABLED]            = (int(attr_axes[axis].driveStatus) >> 20) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_AUTOFOCUS_ACTIVE]             = (int(attr_axes[axis].driveStatus) >> 21) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_PROGRAM_FLASH]                = (int(attr_axes[axis].driveStatus) >> 22) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_SERVO_CONTROL]                = (int(attr_axes[axis].driveStatus) >> 24) & 1U;
    attr_axes[axis].attr_DriveStatus_read[SIM_DRV_IN_POSITION]                 = m_axes[axis].m_in_position;
    // attr_axes[axis].attr_DriveStatus_read[DRV_MOVE_ACTIVE]                  = (int(attr_axes[axis].driveStatus) >> 26) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_ACCEL_PHASE]                  = (int(attr_axes[axis].driveStatus) >> 27) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_DECEL_PHASE]                  = (int(attr_axes[axis].driveStatus) >> 28) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_ENCODER_CLIPPING]             = (int(attr_axes[axis].driveStatus) >> 29) & 1U;
    // attr_axes[axis].attr_DriveStatus_read[DRV_DUAL_LOOP_ACTIVE]             = (int(attr_axes[axis].driveStatus) >> 30) & 1U;

    attr_axes[axis].attr_Enabled_read        = attr_axes[axis].attr_DriveStatus_read[SIM_DRV_ENABLED];
    attr_axes[axis].attr_InPosition_read     = attr_axes[axis].attr_DriveStatus_read[SIM_DRV_IN_POSITION];
    attr_axes[axis].attr_PositionTarget_read = m_axes[axis].m_demand_position;
    // // Axis fault

    // attr_axes[axis].attr_AxisFault_read[0]    = (int(attr_axes[axis].axisFault) >> 0 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[1]    = (int(attr_axes[axis].axisFault) >> 1 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[2]    = (int(attr_axes[axis].axisFault) >> 2 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[3]    = (int(attr_axes[axis].axisFault) >> 3 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[4]    = (int(attr_axes[axis].axisFault) >> 4 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[5]    = (int(attr_axes[axis].axisFault) >> 5 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[6]    = (int(attr_axes[axis].axisFault) >> 6 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[7]    = (int(attr_axes[axis].axisFault) >> 7 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[8]    = (int(attr_axes[axis].axisFault) >> 8 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[9]    = (int(attr_axes[axis].axisFault) >> 9 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[10]   = (int(attr_axes[axis].axisFault) >> 10 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[11]   = (int(attr_axes[axis].axisFault) >> 11 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[12]   = (int(attr_axes[axis].axisFault) >> 12 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[13]   = (int(attr_axes[axis].axisFault) >> 13 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[14]   = (int(attr_axes[axis].axisFault) >> 14 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[15]   = (int(attr_axes[axis].axisFault) >> 15 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[16]   = (int(attr_axes[axis].axisFault) >> 16 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[17]   = (int(attr_axes[axis].axisFault) >> 17 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[18]   = (int(attr_axes[axis].axisFault) >> 18 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[19]   = (int(attr_axes[axis].axisFault) >> 19 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[20]   = (int(attr_axes[axis].axisFault) >> 20 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[21]   = (int(attr_axes[axis].axisFault) >> 21 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[22]   = (int(attr_axes[axis].axisFault) >> 22 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[23]   = (int(attr_axes[axis].axisFault) >> 23 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[24]   = (int(attr_axes[axis].axisFault) >> 24 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[25]   = (int(attr_axes[axis].axisFault) >> 25 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[26]   = (int(attr_axes[axis].axisFault) >> 26 ) & 1U;
    // attr_axes[axis].attr_AxisFault_read[27]   = (int(attr_axes[axis].axisFault) >> 27 ) & 1U;
}

void A1Simulation::axis_Home(int32_t axis) 
{
    // Check the axis number is within index limits
    if (axis < 0 || axis > MAX_AXES)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Home failed - axis out of range", 
                                       "A1Simulation::axis_Home");
    }
    // Check the axis is enabled
    if (!m_axes[axis].m_enabled)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Home failed - axis not enabled", 
                                       "A1Simulation::axis_Home");
    }

    // Set the homed flag for the particular axis
    m_axes[axis].m_homed = true;
} 

void A1Simulation::axis_Move(int32_t axis, A1Axis_ns::_MoveTypeEnum moveType, Tango::DevDouble position, Tango::DevDouble velocity)
{
    // Check the axis number is within index limits
    if (axis < 0 || axis > MAX_AXES)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Move failed - axis out of range", 
                                       "A1Simulation::axis_Move");
    }
    // Check the axis is enabled
    if (!m_axes[axis].m_enabled)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Move failed - axis not enabled", 
                                       "A1Simulation::axis_Move");
    }

    switch (moveType)
    {
        case A1Axis_ns::_MoveTypeEnum::_ABSOLUTEMOVE:
            // Set the demand position to the new demand
            m_axes[axis].m_demand_position = position;
            break;
        case A1Axis_ns::_MoveTypeEnum::_INCREMENTALMOVE:
            m_axes[axis].m_demand_position = m_axes[axis].m_position + position;
            break;
        case A1Axis_ns::_MoveTypeEnum::_LINEARMOVE:
            m_axes[axis].m_demand_position = position;
            break;
        case A1Axis_ns::_MoveTypeEnum::_RAPIDMOVE:
            m_axes[axis].m_demand_position = position;
            break;
        default: 
            Tango::Except::throw_exception("DRIVER_FAILURE", "Unknown move type", __func__);
    }

    // Set the in position flag to false
    m_axes[axis].m_in_position = false;
    // Set the internal moving flag true for the axis
    m_axes[axis].m_moving = true;
}

void A1Simulation::axis_Enable(int32_t axis)
{
    // Check the axis number is within index limits
    if (axis < 0 || axis > MAX_AXES)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Enable failed - axis out of range", 
                                       "A1Simulation::axis_Enable");
    }

    // Set the enabled flag for the particular axis
    m_axes[axis].m_enabled = true;
}

void A1Simulation::axis_Disable(int32_t axis)
{
    // Check the axis number is within index limits
    if (axis < 0 || axis > MAX_AXES)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Disable failed - axis out of range", 
                                       "A1Simulation::axis_Disable");
    }

    // Set the enabled flag for the particular axis
    m_axes[axis].m_enabled = false;
}

} // namespace A1Bridge_ns