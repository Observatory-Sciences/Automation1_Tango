#include "A1Communication.h"


namespace A1Bridge_ns {


void throwWithLastA1Error_origin(const std::string& reason, const std::string& origin)
{
    char errorMessage[2048];
    Automation1_GetLastErrorMessage(errorMessage, 2048);
    Tango::Except::throw_exception(
        "DRIVER_FAILURE", 
        reason + ": " + errorMessage,
        origin
    );
}


A1PollConfig::A1PollConfig(): 
    m_ptr(nullptr)
{
    if (!Automation1_StatusConfig_Create(&m_ptr))
    {
        m_ptr = nullptr; 
        Tango::Except::throw_exception(
            "DRIVER_FAILURE", 
            "Automation1_StatusConfig_Create failed to create status config", 
            __func__
        ); 
    }
}


A1PollConfig::~A1PollConfig() 
{
    if (!Automation1_StatusConfig_Destroy(m_ptr))
    {
        Tango::Except::throw_exception(
            "DRIVER_FAILURE", 
            "Automation1_StatusConfig_Create failed to create status config", 
            __func__
        ); 
    }
    m_ptr = nullptr; 
}


Automation1StatusConfig_T* A1PollConfig::get()
{
    return m_ptr; 
}


void A1PollManager::push(double* destination, unsigned axis, Automation1AxisStatusItem item)
{
    if (!Automation1_StatusConfig_AddAxisStatusItem(m_config.get(), axis, item, 0))
    {
        Tango::Except::throw_exception(
            "DRIVER_FAILURE",
            "Failed to add axis status item",
            __func__);
    }
    m_axisStatusItems.push_back({destination, axis, item}); 
}


void A1PollManager::push(double* destination, unsigned task, Automation1TaskStatusItem item)
{

    if (!Automation1_StatusConfig_AddTaskStatusItem(m_config.get(), task, item, 0))
    {
        Tango::Except::throw_exception(
            "DRIVER_FAILURE",
            "Failed to add task status item",
            __func__);
    }
    m_taskStatusItems.push_back({destination, task, item}); 
}


void A1PollManager::push(double* destination, Automation1SystemStatusItem item)
{
    if (!Automation1_StatusConfig_AddSystemStatusItem(m_config.get(), item, 0))
    {
        Tango::Except::throw_exception(
            "DRIVER_FAILURE",
            "Failed to add system status item",
            __func__);
    }
    m_systemStatusItems.push_back({destination, item}); 
}


void A1PollManager::poll(Automation1Controller* controller)
{
    size_t length = this->size(); 

    double results[length]; 

    A1_GENERIC_CALL_AND_THROW(Automation1_Status_GetResults, *controller, m_config.get(), results, length); 
    
    for (auto item : m_axisStatusItems)
    {
        A1_GENERIC_CALL_AND_THROW(Automation1_Status_GetAxisResult, m_config.get(), results, length, 
                                  item.index, item.item, 0, item.destination); 
    }

    for (auto item : m_taskStatusItems)
    {
        A1_GENERIC_CALL_AND_THROW(Automation1_Status_GetTaskResult, m_config.get(), results, length, 
                                  item.index, item.item, 0, item.destination);
    }

    for (auto item : m_systemStatusItems)
    {
        A1_GENERIC_CALL_AND_THROW(Automation1_Status_GetSystemResult, m_config.get(), results, length, 
                                item.item, 0, item.destination);
    }
}


size_t A1PollManager::size()
{
    return m_axisStatusItems.size() + 
           m_taskStatusItems.size() + 
           m_systemStatusItems.size();
}


void A1PollManager::incrementRefCount()
{
    m_refCount++; 
}


void A1PollManager::decrementRefCount()
{
    // Note we only clear(), not delete. The instance should live as long as the A1Bridge 
    // parent class but the polling configuration may have to be setup more than once. 
    m_refCount--; 
    if (m_refCount == 0)
    {
        clear(); 
    }
}


void A1PollManager::clear()
{
    m_axisStatusItems.clear(); 
    m_taskStatusItems.clear(); 
    m_systemStatusItems.clear(); 
    A1_GENERIC_CALL_AND_THROW(Automation1_StatusConfig_ClearAllStatusItems, m_config.get()); 
}


void A1Communication::initialiseCommonPolling()
{
    if (m_pollManagerCommon.size() > 0)
    {
        return; 
    }

    for (unsigned axis = 0; axis < attr_AxisCount_read; axis++)
    {
        m_pollManagerCommon.push(&attr_axes[axis].axisStatus,                     axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AxisStatus);
        m_pollManagerCommon.push(&attr_axes[axis].axisFault,                      axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AxisFault);
        m_pollManagerCommon.push(&attr_axes[axis].driveStatus,                    axis, Automation1AxisStatusItem::Automation1AxisStatusItem_DriveStatus);
    }
}


void A1Communication::initialiseController_impl()
{
    if (m_pollManagerController.size() > 0)
    {
        return; 
    }

    initialiseCommonPolling();
    m_pollManagerCommon.incrementRefCount(); 

    m_pollManagerController.push(&attr_taskStatus0,                           m_taskID, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus0); 
    m_pollManagerController.push(&attr_taskStatus1,                           m_taskID, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus1); 
    m_pollManagerController.push(&attr_taskStatus2,                           m_taskID, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus2); 
}


void A1Communication::initialiseAxis_impl(unsigned axis)
{
    if (m_pollManagerAxis[axis].size() > 0)
    {
        return; 
    }

    initialiseCommonPolling(); 
    m_pollManagerCommon.incrementRefCount(); 

    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_PositionFeedback_read,     axis, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionFeedback);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_PositionError_read,        axis, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionError);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_PositionTarget_read,       axis, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionCommand);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_VelocityFeedback_read,     axis, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityFeedback);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_VelocityError_read,        axis, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityError);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_VelocityTarget_read,       axis, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityCommand);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_AccelerationFeedback_read, axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationFeedback);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_AccelerationError_read,    axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationError);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_AccelerationTarget_read,   axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationCommand);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_CurrentFeedback_read,      axis, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentFeedback);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_CurrentError_read,         axis, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentError);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_CurrentTarget_read,        axis, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentCommand);
    m_pollManagerAxis[axis].push(&attr_axes[axis].attr_LastMoveDuration_read,     axis, Automation1AxisStatusItem::Automation1AxisStatusItem_TotalMoveTime);
}


void A1Communication::deleteController_impl()
{
    delete attr_APIVersion_read; 
    m_pollManagerController.clear(); 
    m_pollManagerCommon.decrementRefCount(); 
}


void A1Communication::deleteAxis_impl(unsigned axis)
{
    delete attr_axes[axis].attr_FirmwareVersion_read; 
    delete attr_axes[axis].attr_MotorType_read; 
    m_pollManagerAxis[axis].clear(); 
    m_pollManagerCommon.decrementRefCount(); 
}


void A1Communication::connect_impl(const std::string& username, const std::string& password, const std::string& ip)
{
    if (m_connected)
    {
        return; 
    }
    
    int interval = 5 * std::pow(2, m_connectionRetries); 
    if (!m_lastReconnectionAttempt.checkAndUpdate(std::chrono::milliseconds(interval)))
    {
        Tango::Except::throw_exception("COMMUNICATION_BROKEN", 
                                       "Connect to A1 controller failed",
                                       __func__);
    }


    if (!Automation1_ConnectWithHostAndUser(ip.c_str(), 
                                            username.c_str(), 
                                            password.c_str(), 
                                            m_controller))
    {
        std::cout << "Connect to A1 controller failed, retyring in " << interval * 2 << "ms..." << std::endl; 
        m_connectionRetries++; 
        Tango::Except::throw_exception("COMMUNICATION_BROKEN", 
                                       "Connect to A1 controller failed",
                                       __func__);
    }

    checkConnection_impl(); 

    std::cout << "Controller is running" << std::endl; 

    onConnectController(); 

    for (unsigned axis = 0; axis < attr_AxisCount_read; axis++)
    {
        onConnectAxis(axis); 
    }
    
    m_connected = true; 
    m_connectionRetries = 0; 
}

void A1Communication::checkConnection_impl()
{
    std::cout << "Check connection" << std::endl; 
    
    if (!Automation1_Controller_IsRunning(*m_controller, &attr_ControllerRunning_read))
    {
        if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
        {
            this->disconnect();
            throwWithLastA1Error("Controller communication error"); 
        }
        else
        {
            throwWithLastA1Error("Failed to determine if controller is running");
        }
    }

    if (!attr_ControllerRunning_read)
    {
        std::cout << "Controller is not running; starting..." << endl;
        if (!Automation1_Controller_Start(*m_controller))
        {
            throwWithLastA1Error("Failed to start controller");
        }
        if (!Automation1_Controller_IsRunning(*m_controller, &attr_ControllerRunning_read))
        {
            throwWithLastA1Error("Failed to determine if controller is running after start request");
        }
        if (!attr_ControllerRunning_read)
        {
            throwWithLastA1Error("Controller not running after start request");
        }
    }
}


void A1Communication::onConnectController()
{
    // TODO: axes mask
    // A1PollManager pollInit; 
    // pollInit.push(Automation1SystemStatusItem::Automation1SystemStatusItem_AliveAxesMask)
    // pollInit.poll(*m_controller)

    // Get number of axis and task slots.
    attr_AxisCount_read = Automation1_Controller_AvailableAxisCount(*m_controller);
    attr_TaskCount_read = Automation1_Controller_AvailableTaskCount(*m_controller);

    int32_t api[3];
    Automation1_GetApiVersion(&api[0], &api[1], &api[2]);
    std::stringstream apiS; 
    apiS << api[0] << "." << api[1] << "." << api[2]; 
    delete attr_APIVersion_read; 
    attr_APIVersion_read = Tango::string_dup(apiS.str().c_str()); 
}


void A1Communication::onConnectAxis(unsigned axis)
{
    double firmware[4]; 
    std::stringstream firmwareS; 
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, m_taskID, axis, Automation1DriveItem_FirmwareVersionMajor, 0, &firmware[0]);
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, m_taskID, axis, Automation1DriveItem_FirmwareVersionMinor, 0, &firmware[1]);
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, m_taskID, axis, Automation1DriveItem_FirmwareVersionPatch, 0, &firmware[2]);
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, m_taskID, axis, Automation1DriveItem_FirmwareVersionBuild, 0, &firmware[3]);

    firmwareS << firmware[0] << "." << firmware[0] << "." << firmware[0] << "." << firmware[0]; 
    delete attr_axes[axis].attr_FirmwareVersion_read; 
    attr_axes[axis].attr_FirmwareVersion_read = Tango::string_dup(firmwareS.str().c_str()); 

    double motorType; 
    std::string motorTypeS; 
    A1_GENERIC_CALL_AND_THROW(Automation1_Parameter_GetAxisValue, *m_controller, axis, Automation1AxisParameterId_MotorType, &motorType);

    switch(int(motorType))
    {
        case Automation1MotorType_ACBrushlessLinear:
            motorTypeS = "AC Brushless Linear";
            break;
        case Automation1MotorType_ACBrushlessRotary:
            motorTypeS = "AC Brushless Rotary";
            break;
        case Automation1MotorType_DCBrush:
            motorTypeS = "DC Brush";
            break;
        case Automation1MotorType_StepperMotor:
            motorTypeS = "Stepper Motor";
            break;
        case Automation1MotorType_TwoPhaseACBrushless:
            motorTypeS = "Two Phase AC Brushless";
            break;
        case Automation1MotorType_PiezoActuator:
            motorTypeS = "Piezo Actuator";
            break;
        case Automation1MotorType_Galvo:
            motorTypeS = "Galvo";
            break;
        default:
            motorTypeS = "Unknown";
    }

    delete attr_axes[axis].attr_MotorType_read; 
    attr_axes[axis].attr_MotorType_read = Tango::string_dup(motorTypeS.c_str()); 
}

void A1Communication::disconnect_impl()
{
    m_pollManagerCommon.clear(); 
    m_pollManagerController.clear(); 
    for (unsigned axis = 0; axis < MAX_AXES; axis++)
    {
        m_pollManagerAxis[axis].clear(); 
    }

    bool stat = Automation1_Disconnect(*m_controller);
    m_connected = false; 
    if (!stat)
    {
        std::cout << "ERROR: Disconnect from A1 controller failed" << std::endl; 
        Tango::Except::throw_exception("COMMUNICATION_BROKEN", 
                                       "Disconnect from A1 controller failed",
                                       __func__);
    }
}


void A1Communication::readCommon()
{
    if (!m_lastCommonPoll.checkAndUpdate(m_pollInterval_ms))
    {
        return; 
    }

    attr_AxisCount_read = Automation1_Controller_AvailableAxisCount(*m_controller);
    attr_TaskCount_read = Automation1_Controller_AvailableTaskCount(*m_controller);

    m_pollManagerCommon.poll(m_controller); 

    for (unsigned axis = 0; axis < attr_AxisCount_read; axis++)
    {
        // Axis status
        attr_axes[axis].attr_AxisStatus_read[AX_HOMED]                           = (int(attr_axes[axis].axisStatus) >> 0 ) & 1U; //Homed
        attr_axes[axis].attr_AxisStatus_read[AX_PROFILING]                       = (int(attr_axes[axis].axisStatus) >> 1 ) & 1U; //Profiling
        attr_axes[axis].attr_AxisStatus_read[AX_WAIT_DONE]                       = (int(attr_axes[axis].axisStatus) >> 2 ) & 1U; //WaitDone
        attr_axes[axis].attr_AxisStatus_read[AX_COMMAND_VALID]                   = (int(attr_axes[axis].axisStatus) >> 3 ) & 1U; //CommandValid
        attr_axes[axis].attr_AxisStatus_read[AX_HOMING]                          = (int(attr_axes[axis].axisStatus) >> 4 ) & 1U; //Homing
        attr_axes[axis].attr_AxisStatus_read[AX_ENABLING]                        = (int(attr_axes[axis].axisStatus) >> 5 ) & 1U; //Enabling
        attr_axes[axis].attr_AxisStatus_read[AX_JOG_GENERATING]                  = (int(attr_axes[axis].axisStatus) >> 7 ) & 1U; //JogGenerating
        attr_axes[axis].attr_AxisStatus_read[AX_JOGGING]                         = (int(attr_axes[axis].axisStatus) >> 8 ) & 1U; //Jogging
        attr_axes[axis].attr_AxisStatus_read[AX_DRIVE_PENDING]                   = (int(attr_axes[axis].axisStatus) >> 9 ) & 1U; //DrivePending
        attr_axes[axis].attr_AxisStatus_read[AX_DRIVE_ABORT_PENDING]             = (int(attr_axes[axis].axisStatus) >> 10) & 1U; //DriveAbortPending
        attr_axes[axis].attr_AxisStatus_read[AX_TRAJECTORY_FILTERING]            = (int(attr_axes[axis].axisStatus) >> 11) & 1U; //TrajectoryFiltering
        attr_axes[axis].attr_AxisStatus_read[AX_IFOV_ENABLED]                    = (int(attr_axes[axis].axisStatus) >> 12) & 1U; //IfovEnabled
        attr_axes[axis].attr_AxisStatus_read[AX_NOT_VIRTUAL]                     = (int(attr_axes[axis].axisStatus) >> 13) & 1U; //NotVirtual
        attr_axes[axis].attr_AxisStatus_read[AX_CAL_ENABLED1D]                   = (int(attr_axes[axis].axisStatus) >> 14) & 1U; //CalEnabled1D
        attr_axes[axis].attr_AxisStatus_read[AX_CAL_ENABLED2D]                   = (int(attr_axes[axis].axisStatus) >> 15) & 1U; //CalEnabled2D
        attr_axes[axis].attr_AxisStatus_read[AX_CAMMING_GEARING_CONTROL]         = (int(attr_axes[axis].axisStatus) >> 16) & 1U; //CammingGearingControl
        attr_axes[axis].attr_AxisStatus_read[AX_JOYSTICK_CONTROL]                = (int(attr_axes[axis].axisStatus) >> 17) & 1U; //JoystickControl
        attr_axes[axis].attr_AxisStatus_read[AX_BACKLASH_ACTIVE]                 = (int(attr_axes[axis].axisStatus) >> 18) & 1U; //BacklashActive
        attr_axes[axis].attr_AxisStatus_read[AX_GAIN_MAPPING_ENABLED]            = (int(attr_axes[axis].axisStatus) >> 19) & 1U; //GainMappingEnabled
        attr_axes[axis].attr_AxisStatus_read[AX_MOTION_DONE]                     = (int(attr_axes[axis].axisStatus) >> 22) & 1U; //MotionDone
        attr_axes[axis].attr_AxisStatus_read[AX_MOTION_CLAMPED]                  = (int(attr_axes[axis].axisStatus) >> 23) & 1U; //MotionClamped
        attr_axes[axis].attr_AxisStatus_read[AX_GANTRY_ALIGNED]                  = (int(attr_axes[axis].axisStatus) >> 24) & 1U; //GantryAligned
        attr_axes[axis].attr_AxisStatus_read[AX_GANTRY_DRIVE_CONTROL_REALIGNING] = (int(attr_axes[axis].axisStatus) >> 25) & 1U; //GantryDriveControlRealigning
        attr_axes[axis].attr_AxisStatus_read[AX_THERMO_COMP_ENABLED]             = (int(attr_axes[axis].axisStatus) >> 27) & 1U; //ThermoCompEnabled

        attr_axes[axis].attr_Homed_read = attr_axes[axis].attr_AxisStatus_read[AX_HOMED];

        // Drive status 
        attr_axes[axis].attr_DriveStatus_read[DRV_ENABLED]                      = (int(attr_axes[axis].driveStatus) >> 0 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_CW_EOT_LIMIT]                 = (int(attr_axes[axis].driveStatus) >> 1 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_CCW_EOT_LIMIT]                = (int(attr_axes[axis].driveStatus) >> 2 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_HOME_LIMIT]                   = (int(attr_axes[axis].driveStatus) >> 3 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_MARKER_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 4 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_HALL_A_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 5 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_HALL_B_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 6 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_HALL_C_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 7 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_SINE_ENCODER_ERROR]           = (int(attr_axes[axis].driveStatus) >> 8 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_COSINE_ENCODER_ERROR]         = (int(attr_axes[axis].driveStatus) >> 9 ) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_E_STOP_INPUT]                 = (int(attr_axes[axis].driveStatus) >> 10) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_BRAKE_OUTPUT]                 = (int(attr_axes[axis].driveStatus) >> 11) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_GALVO_POWER_CORRECTION]       = (int(attr_axes[axis].driveStatus) >> 12) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_NO_MOTOR_SUPPLY]              = (int(attr_axes[axis].driveStatus) >> 14) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_CURRENT_CLAMP]                = (int(attr_axes[axis].driveStatus) >> 15) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_MARKER_LATCH]                 = (int(attr_axes[axis].driveStatus) >> 16) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_POWER_LIMITING]               = (int(attr_axes[axis].driveStatus) >> 17) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_GALVO_CAL_ENABLED]            = (int(attr_axes[axis].driveStatus) >> 20) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_AUTOFOCUS_ACTIVE]             = (int(attr_axes[axis].driveStatus) >> 21) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_PROGRAM_FLASH]                = (int(attr_axes[axis].driveStatus) >> 22) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_SERVO_CONTROL]                = (int(attr_axes[axis].driveStatus) >> 24) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_IN_POSITION]                  = (int(attr_axes[axis].driveStatus) >> 25) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_MOVE_ACTIVE]                  = (int(attr_axes[axis].driveStatus) >> 26) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_ACCEL_PHASE]                  = (int(attr_axes[axis].driveStatus) >> 27) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_DECEL_PHASE]                  = (int(attr_axes[axis].driveStatus) >> 28) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_ENCODER_CLIPPING]             = (int(attr_axes[axis].driveStatus) >> 29) & 1U;
        attr_axes[axis].attr_DriveStatus_read[DRV_DUAL_LOOP_ACTIVE]             = (int(attr_axes[axis].driveStatus) >> 30) & 1U;

        attr_axes[axis].attr_Enabled_read    = attr_axes[axis].attr_DriveStatus_read[DRV_ENABLED];
        attr_axes[axis].attr_InPosition_read = attr_axes[axis].attr_DriveStatus_read[DRV_IN_POSITION];

        // Axis fault
        attr_axes[axis].attr_AxisFault_read[AX_F_POSITION_ERROR]     = (int(attr_axes[axis].axisFault) >> 0 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_OVER_CURRENT]       = (int(attr_axes[axis].axisFault) >> 1 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_CW_EOT_LIMIT]       = (int(attr_axes[axis].axisFault) >> 2 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_CCW_EOT_LIMIT]      = (int(attr_axes[axis].axisFault) >> 3 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_CW_SOFT_LIMIT]      = (int(attr_axes[axis].axisFault) >> 4 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_CCW_SOFT_LIMIT]     = (int(attr_axes[axis].axisFault) >> 5 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_AMPLIFIER_FAULT]    = (int(attr_axes[axis].axisFault) >> 6 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_FBK_INPUT0]         = (int(attr_axes[axis].axisFault) >> 7 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_FBK_INPUT1]         = (int(attr_axes[axis].axisFault) >> 8 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_HALL_FAULT]         = (int(attr_axes[axis].axisFault) >> 9 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_MAX_VELOCITY]       = (int(attr_axes[axis].axisFault) >> 10 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_E_STOP_FAULT]       = (int(attr_axes[axis].axisFault) >> 11 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_VELOCITY_ERROR]     = (int(attr_axes[axis].axisFault) >> 12 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_EXTERNAL_FAULT]     = (int(attr_axes[axis].axisFault) >> 13 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_MOTOR_TEMP]         = (int(attr_axes[axis].axisFault) >> 14 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_AMPLIFIER_TEMP]     = (int(attr_axes[axis].axisFault) >> 15 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_ENCODER_FAULT]      = (int(attr_axes[axis].axisFault) >> 16 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_MISALIGNMENT_FAULT] = (int(attr_axes[axis].axisFault) >> 17 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_FBK_SCALING_FAULT]  = (int(attr_axes[axis].axisFault) >> 18 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_MRK_SEARCH_FAULT]   = (int(attr_axes[axis].axisFault) >> 19 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_SAFE_ZONE_FAULT]    = (int(attr_axes[axis].axisFault) >> 20 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_IN_POS_TIMEOUT]     = (int(attr_axes[axis].axisFault) >> 21 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_VOLTAGE_CLAMP]      = (int(attr_axes[axis].axisFault) >> 22 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_MOTOR_SUPPLY]       = (int(attr_axes[axis].axisFault) >> 23 ) & 1U;
        attr_axes[axis].attr_AxisFault_read[AX_F_INTERNAL]           = (int(attr_axes[axis].axisFault) >> 24 ) & 1U;

        attr_axes[axis].attr_Error_read = (int(attr_axes[axis].axisFault) & 0xffffff) != 0; 
        attr_AxisHealth_read[axis]      = !attr_axes[axis].attr_Error_read; // Healthy if no error
    }
}


void A1Communication::readController_impl()
{
    readCommon(); 

    m_pollManagerController.poll(m_controller); 
    
    attr_TaskStatus0_read[TSK0_PROGRAM_ASSOCIATED]             = (int(attr_taskStatus0) >> TSK0_PROGRAM_ASSOCIATED) & 1U; 
    attr_TaskStatus0_read[TSK0_IMMEDIATE_EXECUTING]            = (int(attr_taskStatus0) >> TSK0_IMMEDIATE_EXECUTING) & 1U; 
    attr_TaskStatus0_read[TSK0_RETURN_MOTION_EXECUTING]        = (int(attr_taskStatus0) >> TSK0_RETURN_MOTION_EXECUTING) & 1U; 
    attr_TaskStatus0_read[TSK0_PROGRAM_RESET]                  = (int(attr_taskStatus0) >> TSK0_PROGRAM_RESET) & 1U; 
    attr_TaskStatus0_read[TSK0_PENDING_AXES_STOP]              = (int(attr_taskStatus0) >> TSK0_PENDING_AXES_STOP) & 1U; 
    attr_TaskStatus0_read[TSK0_FEEDHOLD_ACTIVE]                = (int(attr_taskStatus0) >> TSK0_FEEDHOLD_ACTIVE) & 1U; 
    attr_TaskStatus0_read[TSK0_CALLBACK_HOLD_ACTIVE]           = (int(attr_taskStatus0) >> TSK0_CALLBACK_HOLD_ACTIVE) & 1U; 
    attr_TaskStatus0_read[TSK0_CALLBACK_RESPONDING]            = (int(attr_taskStatus0) >> TSK0_CALLBACK_RESPONDING) & 1U; 
    attr_TaskStatus0_read[TSK0_SPINDLE_ACTIVE]                 = (int(attr_taskStatus0) >> TSK0_SPINDLE_ACTIVE) & 1U; 
    attr_TaskStatus0_read[TSK0_RETRACE]                        = (int(attr_taskStatus0) >> TSK0_RETRACE) & 1U; 
    attr_TaskStatus0_read[TSK0_INTERRUPT_MOTION_ACTIVE]        = (int(attr_taskStatus0) >> TSK0_INTERRUPT_MOTION_ACTIVE) & 1U; 
    attr_TaskStatus0_read[TSK0_JOYSTICK_ACTIVE]                = (int(attr_taskStatus0) >> TSK0_JOYSTICK_ACTIVE) & 1U; 
    attr_TaskStatus0_read[TSK0_CORNER_ROUNDING]                = (int(attr_taskStatus0) >> TSK0_CORNER_ROUNDING) & 1U; 
    attr_TaskStatus0_read[TSK0_JOYSTICK_LOW_SPEED_ACTIVE]      = (int(attr_taskStatus0) >> TSK0_JOYSTICK_LOW_SPEED_ACTIVE) & 1U; 
    attr_TaskStatus0_read[TSK0_SYNC_FUNCTION_EXECUTING]        = (int(attr_taskStatus0) >> TSK0_SYNC_FUNCTION_EXECUTING) & 1U; 
    attr_TaskStatus0_read[TSK0_TASK_CONTROL_RESTRICTED]        = (int(attr_taskStatus0) >> TSK0_TASK_CONTROL_RESTRICTED) & 1U; 

    attr_TaskStatus1_read[TSK1_ASYNC_SMC_MOTION_ABORT_PENDING] = (int(attr_taskStatus1) >> TSK1_ASYNC_SMC_MOTION_ABORT_PENDING) & 1U; 
    attr_TaskStatus1_read[TSK1_RETRACE_REQUESTED]              = (int(attr_taskStatus1) >> TSK1_RETRACE_REQUESTED) & 1U; 
    attr_TaskStatus1_read[TSK1_MSO_CHANGE]                     = (int(attr_taskStatus1) >> TSK1_MSO_CHANGE) & 1U; 
    attr_TaskStatus1_read[TSK1_SPINDLE_FEEDHOLD]               = (int(attr_taskStatus1) >> TSK1_SPINDLE_FEEDHOLD) & 1U; 
    attr_TaskStatus1_read[TSK1_FEEDHOLD_AXES_STOPPED]          = (int(attr_taskStatus1) >> TSK1_FEEDHOLD_AXES_STOPPED) & 1U; 
    attr_TaskStatus1_read[TSK1_CUTTER_RADIUS_ENABLING]         = (int(attr_taskStatus1) >> TSK1_CUTTER_RADIUS_ENABLING) & 1U; 
    attr_TaskStatus1_read[TSK1_CUTTER_RADIUS_DISABLING]        = (int(attr_taskStatus1) >> TSK1_CUTTER_RADIUS_DISABLING) & 1U; 
    attr_TaskStatus1_read[TSK1_CUTTER_OFFSETS_ENABLING_POS]    = (int(attr_taskStatus1) >> TSK1_CUTTER_OFFSETS_ENABLING_POS) & 1U; 
    attr_TaskStatus1_read[TSK1_CUTTER_OFFSETS_ENABLING_NEG]    = (int(attr_taskStatus1) >> TSK1_CUTTER_OFFSETS_ENABLING_NEG) & 1U; 
    attr_TaskStatus1_read[TSK1_CUTTER_OFFSETS_DISABLING]       = (int(attr_taskStatus1) >> TSK1_CUTTER_OFFSETS_DISABLING) & 1U; 
    attr_TaskStatus1_read[TSK1_ON_ERROR_HANDLER_PENDING]       = (int(attr_taskStatus1) >> TSK1_ON_ERROR_HANDLER_PENDING) & 1U; 
    attr_TaskStatus1_read[TSK1_ON_ERROR_HANDLER_EXECUTING]     = (int(attr_taskStatus1) >> TSK1_ON_ERROR_HANDLER_EXECUTING) & 1U; 
    attr_TaskStatus1_read[TSK1_PROGRAM_STOP_PENDING]           = (int(attr_taskStatus1) >> TSK1_PROGRAM_STOP_PENDING) & 1U; 
    attr_TaskStatus1_read[TSK1_SYNC_FUNCTION_PENDING]          = (int(attr_taskStatus1) >> TSK1_SYNC_FUNCTION_PENDING) & 1U; 
    attr_TaskStatus1_read[TSK1_NO_MFO_FLOOR]                   = (int(attr_taskStatus1) >> TSK1_NO_MFO_FLOOR) & 1U; 
    attr_TaskStatus1_read[TSK1_INTERRUPTED]                    = (int(attr_taskStatus1) >> TSK1_INTERRUPTED) & 1U; 
    attr_TaskStatus1_read[TSK1_IFOV_BUFFER_HOLD]               = (int(attr_taskStatus1) >> TSK1_IFOV_BUFFER_HOLD) & 1U; 

    attr_TaskStatus2_read[TSK2_SCALING_ACTIVE]                 = (int(attr_taskStatus2) >> TSK2_SCALING_ACTIVE) & 1U; 
    attr_TaskStatus2_read[TSK2_OFFSET_FIXTURE_ACTIVE]          = (int(attr_taskStatus2) >> TSK2_OFFSET_FIXTURE_ACTIVE) & 1U; 
    attr_TaskStatus2_read[TSK2_PROFILE_ACTIVE]                 = (int(attr_taskStatus2) >> TSK2_PROFILE_ACTIVE) & 1U; 
    attr_TaskStatus2_read[TSK2_MOTION_MODE_RAPID]              = (int(attr_taskStatus2) >> TSK2_MOTION_MODE_RAPID) & 1U; 
    attr_TaskStatus2_read[TSK2_MOTION_MODE_LINEAR]             = (int(attr_taskStatus2) >> TSK2_MOTION_MODE_LINEAR) & 1U; 
    attr_TaskStatus2_read[TSK2_MOTION_PVT]                     = (int(attr_taskStatus2) >> TSK2_MOTION_PVT) & 1U; 
    attr_TaskStatus2_read[TSK2_MOTION_CONTINUOUS_ACTIVE]       = (int(attr_taskStatus2) >> TSK2_MOTION_CONTINUOUS_ACTIVE) & 1U; 
    attr_TaskStatus2_read[TSK2_CUTTER_OFFSETS_ACTIVE_POS]      = (int(attr_taskStatus2) >> TSK2_CUTTER_OFFSETS_ACTIVE_POS) & 1U; 
    attr_TaskStatus2_read[TSK2_CUTTER_RADIUS_ACTIVE_LEFT]      = (int(attr_taskStatus2) >> TSK2_CUTTER_RADIUS_ACTIVE_LEFT) & 1U; 
    attr_TaskStatus2_read[TSK2_CUTTER_RADIUS_ACTIVE_RIGHT]     = (int(attr_taskStatus2) >> TSK2_CUTTER_RADIUS_ACTIVE_RIGHT) & 1U; 
    attr_TaskStatus2_read[TSK2_CUTTER_OFFSETS_ACTIVE_NEG]      = (int(attr_taskStatus2) >> TSK2_CUTTER_OFFSETS_ACTIVE_NEG) & 1U; 
    attr_TaskStatus2_read[TSK2_NORMALCY_ACTIVE_LEFT]           = (int(attr_taskStatus2) >> TSK2_NORMALCY_ACTIVE_LEFT) & 1U; 
    attr_TaskStatus2_read[TSK2_NORMALCY_ACTIVE_RIGHT]          = (int(attr_taskStatus2) >> TSK2_NORMALCY_ACTIVE_RIGHT) & 1U; 
    attr_TaskStatus2_read[TSK2_NORMALCY_ALIGNMENT]             = (int(attr_taskStatus2) >> TSK2_NORMALCY_ALIGNMENT) & 1U; 
    attr_TaskStatus2_read[TSK2_MOTION_MODE_CW]                 = (int(attr_taskStatus2) >> TSK2_MOTION_MODE_CW) & 1U; 
    attr_TaskStatus2_read[TSK2_MOTION_MODE_CCW]                = (int(attr_taskStatus2) >> TSK2_MOTION_MODE_CCW) & 1U; 
    attr_TaskStatus2_read[TSK2_LIMIT_FEEDRATE_ACTIVE]          = (int(attr_taskStatus2) >> TSK2_LIMIT_FEEDRATE_ACTIVE) & 1U; 
    attr_TaskStatus2_read[TSK2_LIMIT_MFO_ACTIVE]               = (int(attr_taskStatus2) >> TSK2_LIMIT_MFO_ACTIVE) & 1U; 
    attr_TaskStatus2_read[TSK2_COORD1_PLANE1]                  = (int(attr_taskStatus2) >> TSK2_COORD1_PLANE1) & 1U; 
    attr_TaskStatus2_read[TSK2_COORD1_PLANE2]                  = (int(attr_taskStatus2) >> TSK2_COORD1_PLANE2) & 1U; 
    attr_TaskStatus2_read[TSK2_COORD1_PLANE3]                  = (int(attr_taskStatus2) >> TSK2_COORD1_PLANE3) & 1U; 
    attr_TaskStatus2_read[TSK2_COORD2_PLANE1]                  = (int(attr_taskStatus2) >> TSK2_COORD2_PLANE1) & 1U; 
    attr_TaskStatus2_read[TSK2_COORD2_PLANE2]                  = (int(attr_taskStatus2) >> TSK2_COORD2_PLANE2) & 1U; 
    attr_TaskStatus2_read[TSK2_COORD2_PLANE3]                  = (int(attr_taskStatus2) >> TSK2_COORD2_PLANE3) & 1U; 


    // TODO: check for magic numbers 
    int32_t fileCount, filenameLength; 
    A1_GENERIC_CALL_AND_THROW(Automation1_Files_GetAllFiles, *m_controller, NULL, &fileCount, &filenameLength); 

    int32_t maxFiles = min(fileCount, 32); 
    fileCount = maxFiles; 

    char files[maxFiles * filenameLength];

    A1_GENERIC_CALL_AND_THROW(Automation1_Files_GetAllFiles, *m_controller, files, &fileCount, &filenameLength); 

    int32_t file = 0;
    for (; file < fileCount; file++)
    {
        delete attr_AeroScriptFiles_read[file]; 
        attr_AeroScriptFiles_read[file] = Tango::string_dup(&files[file*filenameLength]); 
    }

    for (; file < maxFiles; file++)
    {
        delete attr_AeroScriptFiles_read[file]; 
        attr_AeroScriptFiles_read[file] = Tango::string_dup(""); 
    }
}


void A1Communication::readAxis_impl(unsigned axis)
{
    readCommon(); 

    m_pollManagerAxis[axis].poll(m_controller); 
}


void A1Communication::controller_Reset() 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Controller_Reset, *m_controller); 
} 


void A1Communication::controller_Start() 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Controller_Start, *m_controller);
} 


void A1Communication::controller_Stop() 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Controller_Stop, *m_controller);
} 


void A1Communication::controller_Enable() 
{
    for (int i = 0; i < attr_AxisCount_read; i++)
    {
        A1Communication::axis_Enable(i); 
    }    
} 


void A1Communication::controller_Disable() 
{
    for (int i = 0; i < attr_AxisCount_read; i++)
    {
        A1Communication::axis_Disable(i); 
    }    
} 


void A1Communication::controller_ClearErrors() 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_AcknowledgeAll, *m_controller, m_taskID);
} 


void A1Communication::controller_AeroScriptProgramRun(const std::string& file) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Task_ProgramRun,   *m_controller, m_taskID, file.c_str());
} 


void A1Communication::controller_AeroScriptProgramLoad(const std::string& file) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Task_ProgramLoad,  *m_controller, m_taskID, file.c_str());
} 


void A1Communication::controller_AeroScriptProgramStart() 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Task_ProgramStart, *m_controller, m_taskID);
} 


void A1Communication::controller_AeroScriptProgramStop() 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Task_ProgramStop,  *m_controller, m_taskID, m_programHaltTimeout);
} 


void A1Communication::controller_AeroScriptProgramPause() 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Task_ProgramPause, *m_controller, m_taskID, m_programHaltTimeout);
} 


void A1Communication::axis_WriteRamp(unsigned axis, A1Axis_ns::RampTypeEnum type, A1Axis_ns::RampModeEnum mode, double value)
{
	Automation1RampType typeA1;
	Automation1RampMode modeA1;

    switch (type)
	{
		case A1Axis_ns::RampTypeEnum::_LINEAR:
			typeA1 = Automation1RampType_Linear;
		    break;
		case A1Axis_ns::RampTypeEnum::_S_CURVE:
			typeA1 = Automation1RampType_SCurve;
		    break;
		case A1Axis_ns::RampTypeEnum::_SINE:
			typeA1 = Automation1RampType_Sine;
		    break;
	}

	switch (mode)
	{
		case A1Axis_ns::RampModeEnum::_RATE:
			modeA1 = Automation1RampMode_Rate;
		    break;
		case A1Axis_ns::RampModeEnum::_TIME:
			modeA1 = Automation1RampMode_Time;
		    break;
	}

	A1_GENERIC_CALL_AND_THROW(Automation1_Command_SetupAxisRampType,  *m_controller, m_taskID, axis, typeA1, 0.5, typeA1, 0.5);
	A1_GENERIC_CALL_AND_THROW(Automation1_Command_SetupAxisRampValue, *m_controller, m_taskID, axis, modeA1, value, modeA1, value);

}


void A1Communication::axis_Abort(int32_t axis) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_Abort, *m_controller, &axis, 1);
}


void A1Communication::axis_Home(int32_t axis, A1Axis_ns::_HomeTypeEnum homeType) 
{
    switch (homeType)
    {
        case A1Axis_ns::_HomeTypeEnum::_ASYNCHRONOUS: 
            A1_GENERIC_CALL_AND_THROW(Automation1_Command_HomeAsync, *m_controller, m_taskID, &axis, 1);
            break; 
        case A1Axis_ns::_HomeTypeEnum::_SYNCHRONOUS: 
            A1_GENERIC_CALL_AND_THROW(Automation1_Command_Home, *m_controller, m_taskID, &axis, 1);
            break; 
        default: 
            Tango::Except::throw_exception("DRIVER_FAILURE", "Unknown home type", __func__);
    }
} 


void A1Communication::axis_Move(int32_t axis, A1Axis_ns::_MoveTypeEnum moveType, Tango::DevDouble position, Tango::DevDouble velocity) 
{
    bool status; 
    switch (moveType)
    {
        case A1Axis_ns::_MoveTypeEnum::_ABSOLUTEMOVE:
			A1_GENERIC_CALL_AND_THROW(Automation1_Command_MoveAbsolute, *m_controller, m_taskID, &axis, 1, &position, 1, &velocity, 1);
            break;
        case A1Axis_ns::_MoveTypeEnum::_INCREMENTALMOVE:
			A1_GENERIC_CALL_AND_THROW(Automation1_Command_MoveIncremental, *m_controller, m_taskID, &axis, 1, &position, 1, &velocity, 1);
            break;
        case A1Axis_ns::_MoveTypeEnum::_LINEARMOVE:
			A1_GENERIC_CALL_AND_THROW(Automation1_Command_MoveLinear, *m_controller, m_taskID, &axis, 1, &position, 1, velocity);
            break;
        case A1Axis_ns::_MoveTypeEnum::_RAPIDMOVE:
			A1_GENERIC_CALL_AND_THROW(Automation1_Command_MoveRapid, *m_controller, m_taskID, &axis, 1, &position, 1, &velocity, 1);
            break;
        default: 
            Tango::Except::throw_exception("DRIVER_FAILURE", "Unknown move type", __func__);
    }
} 


void A1Communication::axis_Enable(int32_t axis) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_Enable, *m_controller, m_taskID, &axis, 1);
} 


void A1Communication::axis_Disable(int32_t axis) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_Disable, *m_controller, &axis, 1);
} 


void A1Communication::axis_BrakeOn(int32_t axis) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveBrakeOn, *m_controller, m_taskID, axis);
} 


void A1Communication::axis_BrakeOff(int32_t axis) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveBrakeOff, *m_controller, m_taskID, axis);
} 


void A1Communication::axis_MoveFromLimit(int32_t axis) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_MoveOutOfLimit, *m_controller, m_taskID, axis);
} 


void A1Communication::axis_FreeRun(int32_t axis, Tango::DevDouble velocity) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_MoveFreerun, *m_controller, m_taskID, &axis, 1, &velocity, 1);
} 


void A1Communication::axis_FreeRunStop(int32_t axis) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_MoveFreerunStop, *m_controller, m_taskID, &axis, 1);
} 


void A1Communication::axis_ThrowAllFaults(int32_t axis) 
{
    int64_t faultMask = 0xffffff; 
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_FaultThrow, *m_controller, m_taskID, axis, faultMask);
} 


void A1Communication::axis_AcknowledgeFaults(int32_t axis) 
{
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_FaultAcknowledge, *m_controller, m_taskID, &axis, 1);
}


// TODO: data collection methods
void A1Communication::axis_DataCollectionStart(int32_t axis) 
{
    NotImplemented(__func__);
} 


void A1Communication::axis_DataCollectionStop(int32_t axis) 
{
    NotImplemented(__func__);
} 


void A1Communication::axis_DataCollectionRefresh(int32_t axis) 
{
    NotImplemented(__func__);
} 


void A1Communication::axis_DataCollectionGetResults(int32_t axis) 
{
    NotImplemented(__func__);
} 

} // A1Bridge_ns