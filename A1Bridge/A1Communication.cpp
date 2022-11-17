#include "A1Communication.h"
#include "tango.h"


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
    // Create the status config
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
    // Free the status config
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
    // Add an Automation1AxisStatusItem to the list of items to be polled by this manager
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
    // Add an Automation1TaskStatusItem to the list of items to be polled by this manager
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
    // Add an Automation1SystemStatusItem to the list of items to be polled by this manager
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
    // Poll all items that have been added to the list of items to be polled by this manager

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
    // Note we only clear(), not delete. The instance must live as long as the A1Bridge 
    // parent class, but the polling configuration may have to be setup more than once. 
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


A1Communication::A1Communication() :
    m_connectionRetries(0)
{
    m_simulation = false;
    attr_Automation1ProgramStopTimeout_read = 100;
    attr_Automation1TaskID_read = 1;
}


void A1Communication::initialiseCommonPolling()
{
    // Add all relevant items to the common polling manager

    // If already done, return early 
    // This is only called after mutex lock so no problem with threads. 
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
    // Add all relevant items to the controller polling manager
    if (m_pollManagerController.size() > 0)
    {
        return; 
    }

    // Controller requires common polling. 
    initialiseCommonPolling();
    m_pollManagerCommon.incrementRefCount(); 

    m_pollManagerController.push(&attr_taskStatus0,                           attr_Automation1TaskID_read, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus0); 
    m_pollManagerController.push(&attr_taskStatus1,                           attr_Automation1TaskID_read, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus1); 
    m_pollManagerController.push(&attr_taskStatus2,                           attr_Automation1TaskID_read, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus2); 

    int32_t api[3];
    Automation1_GetApiVersion(&api[0], &api[1], &api[2]);
    std::stringstream apiS; 
    apiS << api[0] << "." << api[1] << "." << api[2]; 
    if(attr_APIVersion_read != nullptr)
    {
        delete[] attr_APIVersion_read; 
    }
    attr_APIVersion_read = Tango::string_dup(apiS.str().c_str());

    attr_AeroScriptFilePath_read = Tango::string_dup("");
}


void A1Communication::initialiseAxis_impl(unsigned axis)
{
    // Add all relevant items to the axis polling manager
    if (m_pollManagerAxis[axis].size() > 0)
    {
        return; 
    }

    // Axis requires common polling. 
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

    attr_axes[axis].attr_FirmwareVersion_read = Tango::string_dup(getFirmwareVersionString(axis).c_str()); 
    attr_axes[axis].attr_MotorType_read = Tango::string_dup(getMotorTypeString(axis).c_str());
}


void A1Communication::deleteController_impl()
{
    // Delete the controller if it is no longer required
    // (but keep the A1Communication instance alive)
    delete[] attr_APIVersion_read;
    attr_APIVersion_read = nullptr;
    for (unsigned i = 0; i++; MAX_AEROSCRIPTS)
    {
        delete[] attr_AeroScriptFiles_read[i];
    }

    Tango::string_free(attr_AeroScriptFilePath_read);
    m_pollManagerController.clear(); 
    m_pollManagerCommon.decrementRefCount(); 
}


void A1Communication::deleteAxis_impl(unsigned axis)
{
    // Delete the axis if it is no longer required
    // (but keep the A1Communication instance alive)
    Tango::string_free(attr_axes[axis].attr_FirmwareVersion_read); 
    Tango::string_free(attr_axes[axis].attr_MotorType_read); 
    m_pollManagerAxis[axis].clear(); 
    m_pollManagerCommon.decrementRefCount(); 
}


bool A1Communication::isConnected()
{
    // Prevent reading of connection state if another thread is communicating with device
    // This is so that the other thread has the opportunity to update the connection state 
    // before this thread tries to communicate. 
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    return m_connected; 
}


void A1Communication::connect_impl(const std::string& username, const std::string& password, const std::string& ip)
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    // INFO_STREAM << "Connecting to controller" << std::endl;
    
    if (m_connected)
    {
        // DEBUG_STREAM << "Already connected to controller" << std::endl; 
        return; 
    }
    
    int interval = 5 * std::pow(2, m_connectionRetries); 
    if (!m_lastReconnectionAttempt.checkAndUpdate(std::chrono::milliseconds(interval)))
    {
        // DEBUG_STREAM << "Too soon since last reconnect attempt" << std::endl; 
        Tango::Except::throw_exception("COMMUNICATION_BROKEN", 
                                    "Connect to A1 controller failed",
                                    __func__);
    }

    // DEBUG_STREAM << "Connecting to controller through Automation1 API..." << std::endl; 
    if (!Automation1_ConnectWithHostAndUser(ip.c_str(), 
                                            username.c_str(), 
                                            password.c_str(), 
                                            m_controller))
    {
        std::cout << "Connect to A1 controller failed, retrying in " << interval * 2 << "ms..." << std::endl; 
        m_connectionRetries++; 
        Tango::Except::throw_exception("COMMUNICATION_BROKEN", 
                                    "Connect to A1 controller failed",
                                    __func__);
    }

    // We are connected 
    // DEBUG_STREAM << "Automation1 connect call succeeded" << std::endl;

    checkControllerRunning(); 

    // INFO_STREAM << "Controller is running" << std::endl; 

    onConnectController(); 

    for (unsigned axis = 0; axis < attr_AxisCount_read; axis++)
    {
        onConnectAxis(axis); 
    }
    
    m_connected = true; 
    m_connectionRetries = 0; 
    // DEBUG_STREAM << "Connected!" << std::endl; 
}


void A1Communication::checkControllerRunning()
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    // DEBUG_STREAM << "Checking if Automation1 controller is running" << std::endl; 

    if (!Automation1_Controller_IsRunning(*m_controller, &attr_ControllerRunning_read))
    {
        if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
        {
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

void A1Communication::checkConnection_impl()
{
    // DEBUG_STREAM << "Checking connection state" << std::endl; 
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    if (!isConnected())
    {
        reconnect();
    }
}


void A1Communication::onConnectController()
{
    // DEBUG_STREAM << "Setting up controller..." << std::endl; 
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    initialiseController(); 

    // Get number of axis and task slots.
    attr_AxisCount_read = Automation1_Controller_AvailableAxisCount(*m_controller);
    attr_TaskCount_read = Automation1_Controller_AvailableTaskCount(*m_controller); 
}


void A1Communication::onConnectAxis(unsigned axis)
{
    // DEBUG_STREAM << "Setting up axis " << axis << "..." << std::endl; 
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    initialiseAxis(axis);  
}

void A1Communication::disconnect_impl()
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    // INFO_STREAM << "Disconnecting from controller" << std::endl; 

    m_pollManagerCommon.clear(); 
    m_pollManagerController.clear(); 
    for (unsigned axis = 0; axis < MAX_AXES; axis++)
    {
        m_pollManagerAxis[axis].clear(); 
    }

    if (m_connected)
    {
        // DEBUG_STREAM << "Disconnecting through Automation1 API..." << std::endl; 
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
}


void A1Communication::readCommon()
{
    // DEBUG_STREAM << "Reading common data from controller" << std::endl; 
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    if (!m_lastCommonPoll.checkAndUpdate(m_pollInterval_ms))
    {
        return; 
    }

    try
    {
        attr_AxisCount_read = Automation1_Controller_AvailableAxisCount(*m_controller);
        attr_TaskCount_read = Automation1_Controller_AvailableTaskCount(*m_controller);

        m_pollManagerCommon.poll(m_controller); 
    }
    catch (Tango::DevFailed &e)
    {
        if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
        {
            this->disconnect();
        }
        throw(e);
    }

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
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    readCommon(); 

    // DEBUG_STREAM << "Reading controller-specific data from controller" << std::endl; 
    try
    {
        m_pollManagerController.poll(m_controller);
    }
    catch (Tango::DevFailed &e)
    {
        if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
        {
            this->disconnect();
        }
        throw(e);
    }
    
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

    int32_t fileCount, filenameLength; 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Files_GetAllFiles, *m_controller, NULL, &fileCount, &filenameLength); 

    int32_t maxFiles = min(fileCount, MAX_AEROSCRIPTS); 
    fileCount = maxFiles; 
    int32_t maxFilenameLength = min(fileCount, 50); 

    char files[maxFiles * maxFilenameLength];

    A1_TRY_CALL_AND_DISCONNECT(Automation1_Files_GetAllFiles, *m_controller, files, &fileCount, &maxFilenameLength); 

    int32_t file = 0;
    for (; file < fileCount; file++)
    {
        delete[] attr_AeroScriptFiles_read[file];
        attr_AeroScriptFiles_read[file] = Tango::string_dup(&files[file*maxFilenameLength]);
    }

    for (; file < MAX_AEROSCRIPTS; file++)
    {
        delete[] attr_AeroScriptFiles_read[file];
        attr_AeroScriptFiles_read[file] = Tango::string_dup("");
    }

    Automation1TaskStatus taskStatuses[attr_Automation1TaskID_read + 1];
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Task_GetStatus, *m_controller, taskStatuses, attr_Automation1TaskID_read + 1);

    std::string sourceName(taskStatuses[attr_Automation1TaskID_read].AeroScriptSourceFileName);
    std::string compiledName(taskStatuses[attr_Automation1TaskID_read].CompiledAeroScriptFileName);

    if(sourceName[0] != '\0')
    {
        attr_AeroScriptFilePath_read = Tango::string_dup(sourceName);
    }
    else
    {
        attr_AeroScriptFilePath_read = Tango::string_dup(compiledName);
    }

    attr_Automation1TaskStatus_read = (A1Controller_ns::Automation1TaskStatusEnum)taskStatuses[attr_Automation1TaskID_read].TaskState;
}


void A1Communication::readAxis_impl(unsigned axis)
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    readCommon(); 

    // DEBUG_STREAM << "Reading axis " << axis << " data from controller" << std::endl; 
    try
    {
        m_pollManagerAxis[axis].poll(m_controller); 
    }
    catch (Tango::DevFailed &e)
    {
        if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
        {
            this->disconnect();
        }
        throw(e);
    }
}


void A1Communication::controller_Reset() 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Controller_Reset, *m_controller); 
} 


void A1Communication::controller_Start() 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Controller_Start, *m_controller);
} 


void A1Communication::controller_Stop() 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Controller_Stop, *m_controller);
} 


void A1Communication::controller_Enable() 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    for (int i = 0; i < attr_AxisCount_read; i++)
    {
        A1Communication::axis_Enable(i); 
    }    
} 


void A1Communication::controller_Disable() 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    for (int i = 0; i < attr_AxisCount_read; i++)
    {
        A1Communication::axis_Disable(i); 
    }    
} 


void A1Communication::controller_ClearErrors() 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_AcknowledgeAll, *m_controller, attr_Automation1TaskID_read);
} 


void A1Communication::controller_AeroScriptProgramRun(const std::string& file) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Task_ProgramRun,   *m_controller, attr_Automation1TaskID_read, file.c_str());
} 


void A1Communication::controller_AeroScriptProgramLoad(const std::string& file) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Task_ProgramLoad,  *m_controller, attr_Automation1TaskID_read, file.c_str());
} 


void A1Communication::controller_AeroScriptProgramStart() 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Task_ProgramStart, *m_controller, attr_Automation1TaskID_read);
} 


void A1Communication::controller_AeroScriptProgramStop() 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Task_ProgramStop,  *m_controller, attr_Automation1TaskID_read, attr_Automation1ProgramStopTimeout_read);
} 


void A1Communication::controller_AeroScriptProgramPause() 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Task_ProgramPause, *m_controller, attr_Automation1TaskID_read, attr_Automation1ProgramStopTimeout_read);
} 


void A1Communication::controller_CommandExecute(const std::string& aeroScriptText)
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_Execute, *m_controller, attr_Automation1TaskID_read, aeroScriptText.c_str());
}


void A1Communication::axis_WriteRamp(unsigned axis, A1Axis_ns::RampTypeEnum type, A1Axis_ns::RampModeEnum mode, double value)
{
	Automation1RampType typeA1;
	Automation1RampMode modeA1;

    switch (type)
	{
		case A1Axis_ns::RampTypeEnum::_LINEAR:
            // DEBUG_STREAM << "Ramp type: LINEAR" << std::endl;
			typeA1 = Automation1RampType_Linear;
		    break;
		case A1Axis_ns::RampTypeEnum::_S_CURVE:
            // DEBUG_STREAM << "Ramp type: S_CURVE" << std::endl;
			typeA1 = Automation1RampType_SCurve;
		    break;
		case A1Axis_ns::RampTypeEnum::_SINE:
            // DEBUG_STREAM << "Ramp type: SINE" << std::endl;
			typeA1 = Automation1RampType_Sine;
		    break;
	}

	switch (mode)
	{
		case A1Axis_ns::RampModeEnum::_RATE:
            // DEBUG_STREAM << "Ramp mode: RATE" << std::endl;
			modeA1 = Automation1RampMode_Rate;
		    break;
		case A1Axis_ns::RampModeEnum::_TIME:
            // DEBUG_STREAM << "Ramp mode: TIME" << std::endl;
			modeA1 = Automation1RampMode_Time;
		    break;
	}
    
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
	A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_SetupAxisRampType,  *m_controller, attr_Automation1TaskID_read, axis, typeA1, 0.5, typeA1, 0.5);
	A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_SetupAxisRampValue, *m_controller, attr_Automation1TaskID_read, axis, modeA1, value, modeA1, value);

}


void A1Communication::axis_Abort(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_Abort, *m_controller, &axis, 1);
}


void A1Communication::axis_Home(int32_t axis, A1Axis_ns::_HomeTypeEnum homeType) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    switch (homeType)
    {
        case A1Axis_ns::_HomeTypeEnum::_ASYNCHRONOUS: 
            // DEBUG_STREAM << "Home type: ASYNCHRONOUS" << std::endl; 
            A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_HomeAsync, *m_controller, attr_Automation1TaskID_read, &axis, 1);
            break; 
        case A1Axis_ns::_HomeTypeEnum::_SYNCHRONOUS: 
            // DEBUG_STREAM << "Home type: SYNCHRONOUS" << std::endl; 
            A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_Home, *m_controller, attr_Automation1TaskID_read, &axis, 1);
            break; 
        default: 
            Tango::Except::throw_exception("DRIVER_FAILURE", "Unknown home type", __func__);
    }
} 


void A1Communication::axis_Move(int32_t axis, A1Axis_ns::_MoveTypeEnum moveType, Tango::DevDouble position, Tango::DevDouble velocity) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    bool status; 
    switch (moveType)
    {
        case A1Axis_ns::_MoveTypeEnum::_ABSOLUTEMOVE:
            // DEBUG_STREAM << "Move type: ABSOLUTE" << std::endl; 
			A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveAbsolute, *m_controller, attr_Automation1TaskID_read, &axis, 1, &position, 1, &velocity, 1);
            break;
        case A1Axis_ns::_MoveTypeEnum::_INCREMENTALMOVE:
            // DEBUG_STREAM << "Move type: INCREMENTAL" << std::endl; 
			A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveIncremental, *m_controller, attr_Automation1TaskID_read, &axis, 1, &position, 1, &velocity, 1);
            break;
        case A1Axis_ns::_MoveTypeEnum::_LINEARMOVE:
            // DEBUG_STREAM << "Move type: LINEAR" << std::endl; 
			A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveLinear, *m_controller, attr_Automation1TaskID_read, &axis, 1, &position, 1, velocity);
            break;
        case A1Axis_ns::_MoveTypeEnum::_RAPIDMOVE:
            // DEBUG_STREAM << "Move type: RAPID" << std::endl; 
			A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveRapid, *m_controller, attr_Automation1TaskID_read, &axis, 1, &position, 1, &velocity, 1);
            break;
        default: 
            Tango::Except::throw_exception("DRIVER_FAILURE", "Unknown move type", __func__);
    }
} 


void A1Communication::axis_Enable(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_Enable, *m_controller, attr_Automation1TaskID_read, &axis, 1);
} 


void A1Communication::axis_Disable(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_Disable, *m_controller, &axis, 1);
} 


void A1Communication::axis_BrakeOn(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_DriveBrakeOn, *m_controller, attr_Automation1TaskID_read, axis);
} 


void A1Communication::axis_BrakeOff(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_DriveBrakeOff, *m_controller, attr_Automation1TaskID_read, axis);
} 


void A1Communication::axis_MoveFromLimit(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveOutOfLimit, *m_controller, attr_Automation1TaskID_read, axis);
} 


void A1Communication::axis_FreeRun(int32_t axis, Tango::DevDouble velocity) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveFreerun, *m_controller, attr_Automation1TaskID_read, &axis, 1, &velocity, 1);
} 


void A1Communication::axis_FreeRunStop(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveFreerunStop, *m_controller, attr_Automation1TaskID_read, &axis, 1);
} 


void A1Communication::axis_ThrowAllFaults(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    int64_t faultMask = 0xffffff; 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_FaultThrow, *m_controller, attr_Automation1TaskID_read, axis, faultMask);
} 


void A1Communication::axis_AcknowledgeFaults(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_FaultAcknowledge, *m_controller, attr_Automation1TaskID_read, &axis, 1);
}

string A1Communication::getFirmwareVersionString(unsigned axis)
{
    double firmware[4]; 
    std::stringstream firmwareS; 
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, attr_Automation1TaskID_read, axis, Automation1DriveItem_FirmwareVersionMajor, 0, &firmware[0]);
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, attr_Automation1TaskID_read, axis, Automation1DriveItem_FirmwareVersionMinor, 0, &firmware[1]);
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, attr_Automation1TaskID_read, axis, Automation1DriveItem_FirmwareVersionPatch, 0, &firmware[2]);
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, attr_Automation1TaskID_read, axis, Automation1DriveItem_FirmwareVersionBuild, 0, &firmware[3]);

    firmwareS << firmware[0] << "." << firmware[1] << "." << firmware[2] << "." << firmware[3];
    return firmwareS.str();
}

string A1Communication::getMotorTypeString(unsigned axis)
{
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

    return motorTypeS;
}

} // A1Bridge_ns