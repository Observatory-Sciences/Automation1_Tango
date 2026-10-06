#include "A1Communication.h"
#include "A1Defines.h"
#if TANGO_VERSION_MAJOR < 10 && TANGO_VERSION_MINOR < 4
    // Maintain compatibility with cppTango 9.3-backports
    #include "log4tango.h"
    #include "tango.h"
#else
    #include <common/log4tango/Logger.h>
    #include <tango.h>
#endif

#include <mutex>
#include <thread>
#include <cmath>


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


bool A1PollManager::poll(Automation1Controller* controller,bool* controllerRunningStatus)
{
    // Poll all items that have been added to the list of items to be polled by this manager
    // Returns false if the controller was not polled, true otherwise

    // Nothing to do if the manager is empty
    if(this->size()==0) return false;

    // We wait a minimum interval between updates to avoid choking the hardware
    if(!pollingClock.checkAndUpdate(minimumPollingInterval_ms)) return false;

    // Do not do updates if controller is not running
    Automation1_Controller_IsRunning(*controller, controllerRunningStatus);
    if(!*controllerRunningStatus) {
        return false;
    }
    size_t length = this->size(); 

    double results[length]; 

    // Start thread-safe (on the controller) polling methods
    std::vector<std::thread> threads;
    for(auto& func : pollingMethods)
    {
        threads.emplace_back(func);
    }

    // First connect to the controller to populate the results array...
    if(!Automation1_Status_GetResults(*controller, m_config.get(), results, length))
    {
        for(auto& thread : threads)
        {
            if(thread.joinable())
            {
                thread.join();
            }
        }
        if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
        {
            throwWithLastA1Error("Controller communication error");
        }
        else
        {
            throwWithLastA1Error("ERROR: Automation1_Status_GetResults failed");
        }
    }
    // ...then unpack results to each polled item
    for (auto item : m_axisStatusItems)
    {
        if(!Automation1_Status_GetAxisResult(m_config.get(), results, length,
                                  item.index, item.item, 0, item.destination))
        {
            for(auto& thread : threads)
            {
                if(thread.joinable())
                {
                    thread.join();
                }
            }
            if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
            {
                throwWithLastA1Error("Controller communication error");
            }
            else
            {
                throwWithLastA1Error("ERROR: Automation1_Status_GetAxisResult failed");
            }
        }
    }

    for (auto item : m_taskStatusItems)
    {
        if(!Automation1_Status_GetTaskResult(m_config.get(), results, length, 
                                  item.index, item.item, 0, item.destination))
        {
            for(auto& thread : threads)
            {
                if(thread.joinable())
                {
                    thread.join();
                }
            }
            if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
            {
                throwWithLastA1Error("Controller communication error");
            }
            else
            {
                throwWithLastA1Error("ERROR: Automation1_Status_GetTaskResult failed");
            }
        }
    }

    for (auto item : m_systemStatusItems)
    {
        if(!Automation1_Status_GetSystemResult(m_config.get(), results, length, 
                                item.item, 0, item.destination))
        {
            for(auto& thread : threads)
            {
                if(thread.joinable())
                {
                    thread.join();
                }
            }
            if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
            {
                throwWithLastA1Error("Controller communication error");
            }
            else
            {
                throwWithLastA1Error("ERROR: Automation1_Status_GetSystemResult failed");
            }
        }
    }

    for(auto& thread : threads)
    {
        if(thread.joinable())
        {
            thread.join();
        }
    }
    return true;
}


size_t A1PollManager::size()
{
    return m_axisStatusItems.size() + 
           m_taskStatusItems.size() + 
           m_systemStatusItems.size();
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

    for(int i = 0; i < MAX_AXES; ++i)
    {
        attr_axes[i].attr_FirmwareVersion_read = Tango::string_dup("");
        attr_axes[i].attr_MotorType_read = Tango::string_dup("");
    }
}

A1Communication::~A1Communication()
{
    for(int i = 0; i < MAX_AXES; ++i)
    {
        if(attr_axes[i].attr_FirmwareVersion_read != nullptr)
        {
            delete[] attr_axes[i].attr_FirmwareVersion_read;
            attr_axes[i].attr_FirmwareVersion_read = nullptr;
        }
        if(attr_axes[i].attr_MotorType_read != nullptr)
        {
            delete[] attr_axes[i].attr_MotorType_read;
            attr_axes[i].attr_MotorType_read = nullptr;
        }
    }
    for(int i = 0; i< MAX_TASKS; ++i)
    {
        if(longRunningThread[i].joinable()) longRunningThread[i].join();
    }
}


void A1Communication::initialisePolling()
{
    std::lock_guard<std::recursive_mutex> lock(m_dataLock); 

    // If the size is greater than zero we've already done this...
    if (pollManager.size()>0)
    {
        return; 
    }
    pollManager.registerPollingMethod([this](){this->getFileList();});
    pollManager.registerPollingMethod([this](){this->getTaskStatuses();});

    // First add status bits; used by controller and axes
    for (unsigned axis = 0; axis < attr_AxisCount_read; axis++)
    {
        pollManager.push(&attr_axes[axis].axisStatus,                     axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AxisStatus);
        pollManager.push(&attr_axes[axis].axisFault,                      axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AxisFault);
        pollManager.push(&attr_axes[axis].driveStatus,                    axis, Automation1AxisStatusItem::Automation1AxisStatusItem_DriveStatus);
    }

    // Next add task statuses; used by controller
    for (unsigned task = 0; task < attr_TaskCount_read; task++)
    {
        pollManager.push(&attr_taskStatus0[task],                           task, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus0);
        pollManager.push(&attr_taskStatus1[task],                           task, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus1);
        pollManager.push(&attr_taskStatus2[task],                           task, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus2);
    }


    // Finally add axes items
    for (unsigned axis = 0; axis < attr_AxisCount_read; axis++)
    {
        pollManager.push(&attr_axes[axis].attr_PositionFeedback_read,     axis, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionFeedback);
        pollManager.push(&attr_axes[axis].attr_PositionError_read,        axis, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionError);
        pollManager.push(&attr_axes[axis].attr_VelocityFeedback_read,     axis, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityFeedback);
        pollManager.push(&attr_axes[axis].attr_VelocityError_read,        axis, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityError);
        pollManager.push(&attr_axes[axis].attr_AccelerationFeedback_read, axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationFeedback);
        pollManager.push(&attr_axes[axis].attr_AccelerationError_read,    axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationError);
        pollManager.push(&attr_axes[axis].attr_AccelerationTarget_read,   axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationCommand);
        pollManager.push(&attr_axes[axis].attr_CurrentFeedback_read,      axis, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentFeedback);
        pollManager.push(&attr_axes[axis].attr_CurrentError_read,         axis, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentError);
        pollManager.push(&attr_axes[axis].attr_CurrentTarget_read,        axis, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentCommand);
        pollManager.push(&attr_axes[axis].attr_LastMoveDuration_read,     axis, Automation1AxisStatusItem::Automation1AxisStatusItem_TotalMoveTime);
        pollManager.push(&attr_axes[axis].attr_RampValueRate_read,        axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationRate);
        pollManager.push(&attr_axes[axis].attr_RampValueTime_read,        axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationTime);
        pollManager.push(&attr_axes[axis].attr_RampMode_read,             axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationMode);
        pollManager.push(&attr_axes[axis].attr_RampType_read,             axis, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationType);
    }
}


void A1Communication::initialiseController_impl()
{
    std::lock_guard<std::recursive_mutex> lock(m_dataLock);
    initialisePolling();

    int32_t api[3];
    Automation1_GetApiVersion(&api[0], &api[1], &api[2]);
    std::stringstream apiS; 
    apiS << api[0] << "." << api[1] << "." << api[2]; 
    if(attr_APIVersion_read != nullptr)
    {
        delete[] attr_APIVersion_read; 
    }
    attr_APIVersion_read = Tango::string_dup(apiS.str().c_str());

    char controllerName[120];
    Automation1_Controller_Name(*m_controller, controllerName, 120);
    attr_ControllerName_read = Tango::string_dup(controllerName);

    attr_AeroScriptFilePath_read = Tango::string_dup("");
}


void A1Communication::initialiseAxis_impl(unsigned axis)
{
    std::lock_guard<std::recursive_mutex> lock(m_dataLock); 
    initialisePolling();

    attr_axes[axis].attr_FirmwareVersion_read = Tango::string_dup(getFirmwareVersionString(axis).c_str()); 
    attr_axes[axis].attr_MotorType_read = Tango::string_dup(getMotorTypeString(axis).c_str());
}


void A1Communication::deleteController_impl()
{
    std::lock_guard<std::recursive_mutex> lock(m_dataLock); 
    // Delete the controller if it is no longer required
    // (but keep the A1Communication instance alive)
    delete[] attr_APIVersion_read;
    attr_APIVersion_read = nullptr;

    for (unsigned i = 0; i < MAX_AEROSCRIPTS; i++)
    {
        delete[] attr_AeroScriptFiles_read[i];
    }
    Tango::string_free(attr_AeroScriptFilePath_read);
}


void A1Communication::deleteAxis_impl(unsigned axis)
{
    std::lock_guard<std::recursive_mutex> lock(m_dataLock); 
    // Delete the axis if it is no longer required
    // (but keep the A1Communication instance alive)
    if(attr_axes[axis].attr_FirmwareVersion_read != nullptr)
    {
        Tango::string_free(attr_axes[axis].attr_FirmwareVersion_read);
        attr_axes[axis].attr_FirmwareVersion_read = nullptr;
    }

    if(attr_axes[axis].attr_MotorType_read != nullptr)
    {
        Tango::string_free(attr_axes[axis].attr_MotorType_read);
        attr_axes[axis].attr_MotorType_read = nullptr; 
    }
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
        std::cout << "Connect to A1 controller failed, retrying in " << interval * 2 << "ms..." << std::endl; 
        m_connectionRetries++; 
        Tango::Except::throw_exception("COMMUNICATION_BROKEN", 
                                    "Connect to A1 controller failed",
                                    __func__);
    }

    checkControllerRunning(); 

    onConnectController(); 

    for (unsigned axis = 0; axis < attr_AxisCount_read; axis++)
    {
        onConnectAxis(axis); 
    }
    
    m_connected = true; 
    m_connectionRetries = 0; 
}


void A1Communication::checkControllerRunning()
{
    std::lock_guard<std::recursive_mutex> lock(m_runningLock); 

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
        controller_Start();
    }
}

void A1Communication::checkConnection_impl()
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    if (!isConnected())
    {
        std::cout << "Attempting reconnect..." << std::endl;
        reconnect();
    }
}

std::unique_lock<std::recursive_mutex> A1Communication::holdConnection_impl()
{
    return std::unique_lock<std::recursive_mutex>(m_dataLock);
}


void A1Communication::onConnectController()
{
    {
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 

    // Get number of axis and task slots.
    attr_AxisCount_read = Automation1_Controller_AvailableAxisCount(*m_controller);
    attr_TaskCount_read = Automation1_Controller_AvailableTaskCount(*m_controller);
    }

    initialiseController(); 
}


void A1Communication::onConnectAxis(unsigned axis)
{
    initialiseAxis(axis);  
}

void A1Communication::disconnect_impl()
{
    {
    std::lock_guard<std::recursive_mutex> lock(m_dataLock);

    pollManager.clear();
    }

    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 

    if (m_connected)
    {
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

void A1Communication::reconnect_impl()
{
    this->disconnect();
    this->connect(m_username, m_password, m_ip);
}


bool A1Communication::readCommon()
{
    // Read the hardware and populate status bits used by controller and axes
    std::lock_guard<std::recursive_mutex> lock(m_dataLock); 

    try
    {
        // Only hold the connectionLock during the poll
        std::lock_guard<std::recursive_mutex> lock(m_connectionLock);
        auto now = std::chrono::steady_clock::now();
        if(!pollManager.poll(m_controller, &attr_ControllerRunning_read)) return false;
        attr_ControllerPollDuration_read = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-now).count();
    }
    catch (Tango::DevFailed &e)
    {
        if (Automation1_IsControllerCommunicationError(Automation1_GetLastError()))
        {
            std::cout << "Communication error in readCommon(): " << e.errors.get_buffer()->desc << std::endl;
            this->disconnect();
        }
        throw(e);
    }

    for (unsigned axis = 0; axis < attr_AxisCount_read; axis++)
    {
        // Axis status
        int statusBits = (int)attr_axes[axis].axisStatus;
        attr_axes[axis].attr_AxisStatus_read[AX_HOMED]                           = statusBits & Automation1AxisStatus::Automation1AxisStatus_Homed;
        attr_axes[axis].attr_AxisStatus_read[AX_PROFILING]                       = statusBits & Automation1AxisStatus::Automation1AxisStatus_Profiling;
        attr_axes[axis].attr_AxisStatus_read[AX_WAIT_DONE]                       = statusBits & Automation1AxisStatus::Automation1AxisStatus_WaitDone;
        attr_axes[axis].attr_AxisStatus_read[AX_COMMAND_VALID]                   = statusBits & Automation1AxisStatus::Automation1AxisStatus_CommandValid;
        attr_axes[axis].attr_AxisStatus_read[AX_HOMING]                          = statusBits & Automation1AxisStatus::Automation1AxisStatus_Homing;
        attr_axes[axis].attr_AxisStatus_read[AX_ENABLING]                        = statusBits & Automation1AxisStatus::Automation1AxisStatus_Enabling;
        attr_axes[axis].attr_AxisStatus_read[AX_JOG_GENERATING]                  = statusBits & Automation1AxisStatus::Automation1AxisStatus_JogGenerating;
        attr_axes[axis].attr_AxisStatus_read[AX_JOGGING]                         = statusBits & Automation1AxisStatus::Automation1AxisStatus_Jogging;
        attr_axes[axis].attr_AxisStatus_read[AX_DRIVE_PENDING]                   = statusBits & Automation1AxisStatus::Automation1AxisStatus_DrivePending;
        attr_axes[axis].attr_AxisStatus_read[AX_DRIVE_ABORT_PENDING]             = statusBits & Automation1AxisStatus::Automation1AxisStatus_DriveAbortPending;
        attr_axes[axis].attr_AxisStatus_read[AX_TRAJECTORY_FILTERING]            = statusBits & Automation1AxisStatus::Automation1AxisStatus_TrajectoryFiltering;
        attr_axes[axis].attr_AxisStatus_read[AX_IFOV_ENABLED]                    = statusBits & Automation1AxisStatus::Automation1AxisStatus_IfovEnabled;
        attr_axes[axis].attr_AxisStatus_read[AX_NOT_VIRTUAL]                     = statusBits & Automation1AxisStatus::Automation1AxisStatus_NotVirtual;
        attr_axes[axis].attr_AxisStatus_read[AX_CAL_ENABLED1D]                   = statusBits & Automation1AxisStatus::Automation1AxisStatus_CalibrationEnabled1D;
        attr_axes[axis].attr_AxisStatus_read[AX_CAL_ENABLED2D]                   = statusBits & Automation1AxisStatus::Automation1AxisStatus_CalibrationEnabled2D;
        attr_axes[axis].attr_AxisStatus_read[AX_CAMMING_GEARING_CONTROL]         = statusBits & Automation1AxisStatus::Automation1AxisStatus_CammingGearingControl;
        attr_axes[axis].attr_AxisStatus_read[AX_JOYSTICK_CONTROL]                = statusBits & Automation1AxisStatus::Automation1AxisStatus_JoystickControl;
        attr_axes[axis].attr_AxisStatus_read[AX_BACKLASH_ACTIVE]                 = statusBits & Automation1AxisStatus::Automation1AxisStatus_BacklashActive;
        attr_axes[axis].attr_AxisStatus_read[AX_GAIN_MAPPING_ENABLED]            = statusBits & Automation1AxisStatus::Automation1AxisStatus_GainMappingEnabled;
        attr_axes[axis].attr_AxisStatus_read[AX_MOTION_DONE]                     = statusBits & Automation1AxisStatus::Automation1AxisStatus_MotionDone;
        attr_axes[axis].attr_AxisStatus_read[AX_MOTION_CLAMPED]                  = statusBits & Automation1AxisStatus::Automation1AxisStatus_MotionClamped;
        attr_axes[axis].attr_AxisStatus_read[AX_GANTRY_ALIGNED]                  = statusBits & Automation1AxisStatus::Automation1AxisStatus_GantryAligned;
        attr_axes[axis].attr_AxisStatus_read[AX_GANTRY_DRIVE_CONTROL_REALIGNING] = statusBits & Automation1AxisStatus::Automation1AxisStatus_GantryDriveControlRealigning;
        attr_axes[axis].attr_AxisStatus_read[AX_THERMO_COMP_ENABLED]             = statusBits & Automation1AxisStatus::Automation1AxisStatus_ThermoCompEnabled;
        attr_axes[axis].attr_AxisStatus_read[AX_TRANSFORMATION_INPUT]            = statusBits & Automation1AxisStatus::Automation1AxisStatus_TransformationInput;
        attr_axes[axis].attr_AxisStatus_read[AX_TRANSFORMATION_OUTPUT]           = statusBits & Automation1AxisStatus::Automation1AxisStatus_TransformationOutput;

        attr_axes[axis].attr_Homed_read = attr_axes[axis].attr_AxisStatus_read[AX_HOMED];
        // Negated since the axis status item is "NOT_VIRTUAL"
        attr_axes[axis].attr_VirtualAxis_read = !(attr_axes[axis].attr_AxisStatus_read[AX_NOT_VIRTUAL]);

        // Drive status 
        statusBits = (int)attr_axes[axis].driveStatus;
        attr_axes[axis].attr_DriveStatus_read[DRV_ENABLED]                      = statusBits & Automation1DriveStatus::Automation1DriveStatus_Enabled;
        attr_axes[axis].attr_DriveStatus_read[DRV_CW_EOT_LIMIT]                 = statusBits & Automation1DriveStatus::Automation1DriveStatus_CwEndOfTravelLimitInput;
        attr_axes[axis].attr_DriveStatus_read[DRV_CCW_EOT_LIMIT]                = statusBits & Automation1DriveStatus::Automation1DriveStatus_CcwEndOfTravelLimitInput;
        attr_axes[axis].attr_DriveStatus_read[DRV_HOME_LIMIT]                   = statusBits & Automation1DriveStatus::Automation1DriveStatus_HomeLimitInput;
        attr_axes[axis].attr_DriveStatus_read[DRV_MARKER_INPUT]                 = statusBits & Automation1DriveStatus::Automation1DriveStatus_MarkerInput;
        attr_axes[axis].attr_DriveStatus_read[DRV_HALL_A_INPUT]                 = statusBits & Automation1DriveStatus::Automation1DriveStatus_HallAInput;
        attr_axes[axis].attr_DriveStatus_read[DRV_HALL_B_INPUT]                 = statusBits & Automation1DriveStatus::Automation1DriveStatus_HallBInput;
        attr_axes[axis].attr_DriveStatus_read[DRV_HALL_C_INPUT]                 = statusBits & Automation1DriveStatus::Automation1DriveStatus_HallCInput;
        attr_axes[axis].attr_DriveStatus_read[DRV_SINE_ENCODER_ERROR]           = statusBits & Automation1DriveStatus::Automation1DriveStatus_SineEncoderError;
        attr_axes[axis].attr_DriveStatus_read[DRV_COSINE_ENCODER_ERROR]         = statusBits & Automation1DriveStatus::Automation1DriveStatus_CosineEncoderError;
        attr_axes[axis].attr_DriveStatus_read[DRV_E_STOP_INPUT]                 = statusBits & Automation1DriveStatus::Automation1DriveStatus_EmergencyStopInput;
        attr_axes[axis].attr_DriveStatus_read[DRV_BRAKE_OUTPUT]                 = statusBits & Automation1DriveStatus::Automation1DriveStatus_BrakeOutput;
        attr_axes[axis].attr_DriveStatus_read[DRV_GALVO_POWER_CORRECTION]       = statusBits & Automation1DriveStatus::Automation1DriveStatus_GalvoPowerCorrection;
        attr_axes[axis].attr_DriveStatus_read[DRV_NO_MOTOR_SUPPLY]              = statusBits & Automation1DriveStatus::Automation1DriveStatus_NoMotorSupply;
        attr_axes[axis].attr_DriveStatus_read[DRV_CURRENT_CLAMP]                = statusBits & Automation1DriveStatus::Automation1DriveStatus_CurrentClamp;
        attr_axes[axis].attr_DriveStatus_read[DRV_MARKER_LATCH]                 = statusBits & Automation1DriveStatus::Automation1DriveStatus_MarkerLatch;
        attr_axes[axis].attr_DriveStatus_read[DRV_POWER_LIMITING]               = statusBits & Automation1DriveStatus::Automation1DriveStatus_PowerLimiting;
        attr_axes[axis].attr_DriveStatus_read[DRV_GALVO_CAL_ENABLED]            = statusBits & Automation1DriveStatus::Automation1DriveStatus_GalvoCalibrationEnabled;
        attr_axes[axis].attr_DriveStatus_read[DRV_AUTOFOCUS_ACTIVE]             = statusBits & Automation1DriveStatus::Automation1DriveStatus_AutofocusActive;
        attr_axes[axis].attr_DriveStatus_read[DRV_PROGRAM_FLASH]                = statusBits & Automation1DriveStatus::Automation1DriveStatus_ProgrammingFlash;
        attr_axes[axis].attr_DriveStatus_read[DRV_SERVO_CONTROL]                = statusBits & Automation1DriveStatus::Automation1DriveStatus_ServoControl;
        attr_axes[axis].attr_DriveStatus_read[DRV_IN_POSITION]                  = statusBits & Automation1DriveStatus::Automation1DriveStatus_InPosition;
        attr_axes[axis].attr_DriveStatus_read[DRV_MOVE_ACTIVE]                  = statusBits & Automation1DriveStatus::Automation1DriveStatus_MoveActive;
        attr_axes[axis].attr_DriveStatus_read[DRV_ACCEL_PHASE]                  = statusBits & Automation1DriveStatus::Automation1DriveStatus_AccelerationPhase;
        attr_axes[axis].attr_DriveStatus_read[DRV_DECEL_PHASE]                  = statusBits & Automation1DriveStatus::Automation1DriveStatus_DecelerationPhase;
        attr_axes[axis].attr_DriveStatus_read[DRV_ENCODER_CLIPPING]             = statusBits & Automation1DriveStatus::Automation1DriveStatus_EncoderClipping;
        attr_axes[axis].attr_DriveStatus_read[DRV_DUAL_LOOP_ACTIVE]             = statusBits & Automation1DriveStatus::Automation1DriveStatus_DualLoopActive;
        attr_axes[axis].attr_DriveStatus_read[DRV_AMPLIFIER_ACTIVE]             = statusBits & Automation1DriveStatus::Automation1DriveStatus_AmplifierActive;

        attr_axes[axis].attr_Enabled_read    = attr_axes[axis].attr_DriveStatus_read[DRV_ENABLED];
        attr_axes[axis].attr_InPosition_read = attr_axes[axis].attr_DriveStatus_read[DRV_IN_POSITION];

        // Axis fault
        statusBits = (int)attr_axes[axis].axisFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_POSITION_ERROR]     = statusBits & Automation1AxisFault::Automation1AxisFault_PositionErrorFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_OVER_CURRENT]       = statusBits & Automation1AxisFault::Automation1AxisFault_OverCurrentFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_CW_EOT_LIMIT]       = statusBits & Automation1AxisFault::Automation1AxisFault_CwEndOfTravelLimitFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_CCW_EOT_LIMIT]      = statusBits & Automation1AxisFault::Automation1AxisFault_CcwEndOfTravelLimitFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_CW_SOFT_LIMIT]      = statusBits & Automation1AxisFault::Automation1AxisFault_CwSoftwareLimitFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_CCW_SOFT_LIMIT]     = statusBits & Automation1AxisFault::Automation1AxisFault_CcwSoftwareLimitFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_AMPLIFIER_FAULT]    = statusBits & Automation1AxisFault::Automation1AxisFault_AmplifierFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_FBK_INPUT0]         = statusBits & Automation1AxisFault::Automation1AxisFault_FeedbackInput0Fault;
        attr_axes[axis].attr_AxisFault_read[AX_F_FBK_INPUT1]         = statusBits & Automation1AxisFault::Automation1AxisFault_FeedbackInput1Fault;
        attr_axes[axis].attr_AxisFault_read[AX_F_HALL_FAULT]         = statusBits & Automation1AxisFault::Automation1AxisFault_HallSensorFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_MAX_VELOCITY]       = statusBits & Automation1AxisFault::Automation1AxisFault_MaxVelocityCommandFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_E_STOP_FAULT]       = statusBits & Automation1AxisFault::Automation1AxisFault_EmergencyStopFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_VELOCITY_ERROR]     = statusBits & Automation1AxisFault::Automation1AxisFault_VelocityErrorFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_COMMUTATION]        = statusBits & Automation1AxisFault::Automation1AxisFault_CommutationFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_EXTERNAL_FAULT]     = statusBits & Automation1AxisFault::Automation1AxisFault_ExternalFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_MOTOR_TEMP]         = statusBits & Automation1AxisFault::Automation1AxisFault_MotorTemperatureFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_AMPLIFIER_TEMP]     = statusBits & Automation1AxisFault::Automation1AxisFault_AmplifierTemperatureFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_ENCODER_FAULT]      = statusBits & Automation1AxisFault::Automation1AxisFault_EncoderFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_MISALIGNMENT_FAULT] = statusBits & Automation1AxisFault::Automation1AxisFault_GantryMisalignmentFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_FBK_SCALING_FAULT]  = statusBits & Automation1AxisFault::Automation1AxisFault_FeedbackScalingFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_MRK_SEARCH_FAULT]   = statusBits & Automation1AxisFault::Automation1AxisFault_MarkerSearchFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_SAFE_ZONE_FAULT]    = statusBits & Automation1AxisFault::Automation1AxisFault_SafeZoneFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_IN_POS_TIMEOUT]     = statusBits & Automation1AxisFault::Automation1AxisFault_InPositionTimeoutFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_VOLTAGE_CLAMP]      = statusBits & Automation1AxisFault::Automation1AxisFault_VoltageClampFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_MOTOR_SUPPLY]       = statusBits & Automation1AxisFault::Automation1AxisFault_MotorSupplyFault;
        attr_axes[axis].attr_AxisFault_read[AX_F_INTERNAL]           = statusBits & Automation1AxisFault::Automation1AxisFault_InternalFault;

        attr_axes[axis].attr_Error_read = (int(attr_axes[axis].axisFault) & 0xffffff) != 0;
        attr_AxisHealth_read[axis]      = !attr_axes[axis].attr_Error_read; // Healthy if no error
    }
    return true;
}


void A1Communication::readController_impl()
{

    readCommon();

    // We still update all values in case the taskID has been updated
    std::lock_guard<std::recursive_mutex> lock(m_dataLock);

    int statusBits0 = (int)attr_taskStatus0[attr_Automation1TaskID_read];    
    attr_TaskStatus0_read[TSK0_PROGRAM_ASSOCIATED]             = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_ProgramAssociated;
    attr_TaskStatus0_read[TSK0_IMMEDIATE_EXECUTING]            = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_ImmediateExecuting;
    attr_TaskStatus0_read[TSK0_RETURN_MOTION_EXECUTING]        = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_ReturnMotionExecuting;
    attr_TaskStatus0_read[TSK0_PROGRAM_RESET]                  = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_ProgramReset;
    attr_TaskStatus0_read[TSK0_PENDING_AXES_STOP]              = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_PendingAxesStop;
    attr_TaskStatus0_read[TSK0_FEEDHOLD_ACTIVE]                = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_FeedholdActive;
    attr_TaskStatus0_read[TSK0_CALLBACK_HOLD_ACTIVE]           = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_CallbackHoldActive;
    attr_TaskStatus0_read[TSK0_CALLBACK_RESPONDING]            = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_CallbackResponding;
    attr_TaskStatus0_read[TSK0_SPINDLE_ACTIVE]                 = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_SpindleActive;
    attr_TaskStatus0_read[TSK0_RETRACE]                        = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_Retrace;
    attr_TaskStatus0_read[TSK0_INTERRUPT_MOTION_ACTIVE]        = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_InterruptMotionActive;
    attr_TaskStatus0_read[TSK0_JOYSTICK_ACTIVE]                = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_JoystickActive;
    attr_TaskStatus0_read[TSK0_CORNER_ROUNDING]                = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_CornerRounding;
    attr_TaskStatus0_read[TSK0_JOYSTICK_LOW_SPEED_ACTIVE]      = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_JoystickLowSpeedActive;
    attr_TaskStatus0_read[TSK0_SYNC_FUNCTION_EXECUTING]        = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_SynchronizedFunctionExecuting;
    attr_TaskStatus0_read[TSK0_TASK_CONTROL_RESTRICTED]        = statusBits0 & Automation1TaskStatus0::Automation1TaskStatus0_TaskControlRestricted;

    int statusBits1 = (int)attr_taskStatus1[attr_Automation1TaskID_read];
    attr_TaskStatus1_read[TSK1_ASYNC_SMC_MOTION_ABORT_PENDING] = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_AsyncSmcMotionAbortPending;
    attr_TaskStatus1_read[TSK1_RETRACE_REQUESTED]              = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_RetraceRequested;
    attr_TaskStatus1_read[TSK1_MSO_CHANGE]                     = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_MsoChange;
    attr_TaskStatus1_read[TSK1_SPINDLE_FEEDHOLD]               = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_SpindleFeedhold;
    attr_TaskStatus1_read[TSK1_FEEDHOLD_AXES_STOPPED]          = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_FeedholdAxesStopped;
    attr_TaskStatus1_read[TSK1_CUTTER_RADIUS_ENABLING]         = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_CutterRadiusEnabling;
    attr_TaskStatus1_read[TSK1_CUTTER_RADIUS_DISABLING]        = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_CutterRadiusDisabling;
    attr_TaskStatus1_read[TSK1_CUTTER_OFFSETS_ENABLING_POS]    = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_CutterOffsetsEnablingPositive;
    attr_TaskStatus1_read[TSK1_CUTTER_OFFSETS_ENABLING_NEG]    = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_CutterOffsetsEnablingNegative;
    attr_TaskStatus1_read[TSK1_CUTTER_OFFSETS_DISABLING]       = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_CutterOffsetsDisabling;
    attr_TaskStatus1_read[TSK1_ON_ERROR_HANDLER_PENDING]       = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_OnErrorHandlerPending;
    attr_TaskStatus1_read[TSK1_ON_ERROR_HANDLER_EXECUTING]     = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_OnErrorHandlerExecuting;
    attr_TaskStatus1_read[TSK1_PROGRAM_STOP_PENDING]           = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_ProgramStopPending;
    attr_TaskStatus1_read[TSK1_SYNC_FUNCTION_PENDING]          = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_SynchronizedFunctionPending;
    attr_TaskStatus1_read[TSK1_NO_MFO_FLOOR]                   = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_NoMfoFloor;
    attr_TaskStatus1_read[TSK1_INTERRUPTED]                    = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_Interrupted;
    attr_TaskStatus1_read[TSK1_IFOV_BUFFER_HOLD]               = statusBits1 & Automation1TaskStatus1::Automation1TaskStatus1_IfovBufferHold;

    int statusBits2 = (int)attr_taskStatus2[attr_Automation1TaskID_read];
    attr_TaskStatus2_read[TSK2_SCALING_ACTIVE]                 = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_ScalingActive;
    attr_TaskStatus2_read[TSK2_PROFILE_ACTIVE]                 = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_ProfileActive;
    attr_TaskStatus2_read[TSK2_MOTION_MODE_RAPID]              = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_MotionModeRapid;
    attr_TaskStatus2_read[TSK2_MOTION_MODE_LINEAR]             = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_MotionModeLinear;
    attr_TaskStatus2_read[TSK2_MOTION_PVT]                     = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_MotionPvt;
    attr_TaskStatus2_read[TSK2_MOTION_CONTINUOUS_ACTIVE]       = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_MotionContinuousActive;
    attr_TaskStatus2_read[TSK2_CUTTER_OFFSETS_ACTIVE_POS]      = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_CutterOffsetsActivePos;
    attr_TaskStatus2_read[TSK2_CUTTER_RADIUS_ACTIVE_LEFT]      = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_CutterRadiusActiveLeft;
    attr_TaskStatus2_read[TSK2_CUTTER_RADIUS_ACTIVE_RIGHT]     = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_CutterRadiusActiveRight;
    attr_TaskStatus2_read[TSK2_CUTTER_OFFSETS_ACTIVE_NEG]      = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_CutterOffsetsActiveNeg;
    attr_TaskStatus2_read[TSK2_NORMALCY_ACTIVE_LEFT]           = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_NormalcyActiveLeft;
    attr_TaskStatus2_read[TSK2_NORMALCY_ACTIVE_RIGHT]          = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_NormalcyActiveRight;
    attr_TaskStatus2_read[TSK2_NORMALCY_ALIGNMENT]             = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_NormalcyAlignment;
    attr_TaskStatus2_read[TSK2_MOTION_MODE_CW]                 = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_MotionModeCw;
    attr_TaskStatus2_read[TSK2_MOTION_MODE_CCW]                = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_MotionModeCcw;
    attr_TaskStatus2_read[TSK2_LIMIT_FEEDRATE_ACTIVE]          = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_LimitFeedrateActive;
    attr_TaskStatus2_read[TSK2_LIMIT_MFO_ACTIVE]               = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_LimitMfoActive;
    attr_TaskStatus2_read[TSK2_COORD1_PLANE1]                  = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_Coord1Plane1;
    attr_TaskStatus2_read[TSK2_COORD1_PLANE2]                  = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_Coord1Plane2;
    attr_TaskStatus2_read[TSK2_COORD1_PLANE3]                  = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_Coord1Plane3;
    attr_TaskStatus2_read[TSK2_COORD2_PLANE1]                  = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_Coord2Plane1;
    attr_TaskStatus2_read[TSK2_COORD2_PLANE2]                  = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_Coord2Plane2;
    attr_TaskStatus2_read[TSK2_COORD2_PLANE3]                  = statusBits2 & Automation1TaskStatus2::Automation1TaskStatus2_Coord2Plane3;


    int32_t file = 0;
    for (; file < fileCount; file++)
    {
        delete[] attr_AeroScriptFiles_read[file];
        attr_AeroScriptFiles_read[file] = Tango::string_dup(&filesList[file*maxFileNameLength]);
    }

    for (; file < MAX_AEROSCRIPTS; file++)
    {
        delete[] attr_AeroScriptFiles_read[file];
        attr_AeroScriptFiles_read[file] = Tango::string_dup("");
    }

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

void A1Communication::getFileList() {
    fileCount = MAX_AEROSCRIPTS;
    maxFileNameLength = MAX_FILENAME_LENGTH;
    // We DO NOT throw because this is expected to run in a thread;
    // if it fails we silently ignore.
    Automation1_Files_GetAllFiles(*m_controller, filesList, &fileCount, &maxFileNameLength);
}

void A1Communication::getTaskStatuses() {
    // We DO NOT throw because this is expected to run in a thread;
    // if it fails we silently ignore.
    Automation1_Task_GetStatus(*m_controller, taskStatuses, MAX_TASKS);
}

void A1Communication::readAxis_impl(unsigned axis)
{
    readCommon();
}


bool A1Communication::isControllerRunning()
{
    return (A1Bridge::isControllerRunning() && !startingFlag);
}

bool A1Communication::isControllerStarting()
{
    return startingFlag;
} 

void A1Communication::controller_Reset() 
{
    NONBLOCKING_STARTING_CHECK(Automation1_Controller_Reset);
    std::lock_guard<std::recursive_mutex> lock(m_runningLock);
    A1_TRY_START(Automation1_Controller_Reset, *m_controller); 
} 


void A1Communication::controller_Start() 
{
    if (startingFlag)
    {
        return;
    }
    std::lock_guard<std::recursive_mutex> lock(m_runningLock);
    A1_TRY_START(Automation1_Controller_Start, *m_controller);
} 


void A1Communication::controller_Stop() 
{
    NONBLOCKING_STARTING_CHECK(Automation1_Controller_Stop);
    std::lock_guard<std::recursive_mutex> lock(m_runningLock); 
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
    A1_TRY_LONG_RUNNING_COMMAND(blocking_CommandExecute, this, aeroScriptText, attr_Automation1TaskID_read);
}


void A1Communication::blocking_CommandExecute(const std::string& aeroScriptText, unsigned int taskID)
{
    longRunningException[taskID] = nullptr;
    try
    {
        A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_Execute, *m_controller, taskID, aeroScriptText.c_str());
        longRunningActive[taskID] = false;
    }
    catch (...)
    {
        std::lock_guard<std::mutex> lock(longRunningExceptionLock[taskID]);
        longRunningException[taskID] = std::current_exception();
        longRunningActive[taskID] = false;
    }
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
    
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_SetupAxisRampType,  *m_controller, attr_Automation1TaskID_read, axis, typeA1, 0.5, typeA1, 0.5);
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_SetupAxisRampValue, *m_controller, attr_Automation1TaskID_read, axis, modeA1, value, modeA1, value);

}


void A1Communication::axis_Abort(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_Abort, *m_controller, &axis, 1);
}


void A1Communication::axis_HomeAsync(int32_t axis) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock); 
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_HomeAsync, *m_controller, attr_Automation1TaskID_read, &axis, 1);
}


void A1Communication::axis_Move(int32_t axis, A1Axis_ns::_MoveTypeEnum moveType, Tango::DevDouble position, Tango::DevDouble velocity) 
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock);
    switch (moveType)
    {
        case A1Axis_ns::_MoveTypeEnum::_ABSOLUTEMOVE:
            A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveAbsolute, *m_controller, attr_Automation1TaskID_read, &axis, 1, &position, 1, &velocity, 1);
            break;
        case A1Axis_ns::_MoveTypeEnum::_INCREMENTALMOVE:
            A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveIncremental, *m_controller, attr_Automation1TaskID_read, &axis, 1, &position, 1, &velocity, 1);
            break;
        case A1Axis_ns::_MoveTypeEnum::_LINEARMOVE:
        case A1Axis_ns::_MoveTypeEnum::_RAPIDMOVE:
            A1_TRY_LONG_RUNNING_COMMAND(blocking_Move, this, axis, moveType, position, velocity, attr_Automation1TaskID_read);
            break;
        default: 
            Tango::Except::throw_exception("DRIVER_FAILURE", "Unknown move type", __func__);
    }
} 


void A1Communication::blocking_Move(int32_t axis, A1Axis_ns::_MoveTypeEnum moveType, Tango::DevDouble position, Tango::DevDouble velocity, unsigned int taskID)
{
    longRunningException[taskID] = nullptr;
    try
    {
        switch (moveType)
        {
            case A1Axis_ns::_MoveTypeEnum::_LINEARMOVE:
                A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveLinear, *m_controller, taskID, &axis, 1, &position, 1, velocity);
                break;
            case A1Axis_ns::_MoveTypeEnum::_RAPIDMOVE:
                A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_MoveRapid, *m_controller, taskID, &axis, 1, &position, 1, &velocity, 1);
                break;
            default:
                break;
        }
        longRunningActive[taskID] = false;
    }
    catch (...)
    {
        std::lock_guard<std::mutex> lock(longRunningExceptionLock[taskID]);
        longRunningException[taskID] = std::current_exception();
        longRunningActive[taskID] = false;
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

std::string A1Communication::getFirmwareVersionString(unsigned axis)
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock);
    double firmware[4]; 
    std::stringstream firmwareS; 
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, attr_Automation1TaskID_read, axis, Automation1DriveItem_FirmwareVersionMajor, 0, &firmware[0]);
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, attr_Automation1TaskID_read, axis, Automation1DriveItem_FirmwareVersionMinor, 0, &firmware[1]);
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, attr_Automation1TaskID_read, axis, Automation1DriveItem_FirmwareVersionPatch, 0, &firmware[2]);
    A1_GENERIC_CALL_AND_THROW(Automation1_Command_DriveGetItem, *m_controller, attr_Automation1TaskID_read, axis, Automation1DriveItem_FirmwareVersionBuild, 0, &firmware[3]);

    firmwareS << firmware[0] << "." << firmware[1] << "." << firmware[2] << "." << firmware[3];
    return firmwareS.str();
}

std::string A1Communication::getMotorTypeString(unsigned axis)
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

std::string A1Communication::axis_GetA1ParameterString(int32_t axis,int parameterID) {
    char parameter[255];
    A1_GENERIC_CALL_AND_THROW(Automation1_Parameter_GetAxisStringValue, *m_controller, axis, (Automation1AxisParameterId)parameterID, parameter, 255);
    return std::string{parameter};
}

double A1Communication::axis_GetA1ParameterValue(int32_t axis,int parameterID) {
    double value;
    A1_GENERIC_CALL_AND_THROW(Automation1_Parameter_GetAxisValue, *m_controller, axis, (Automation1AxisParameterId)parameterID, &value);
    return value;
}

void A1Communication::axis_SetA1ParameterValue(int32_t axis,int parameterID, double value) {
    A1_GENERIC_CALL_AND_THROW(Automation1_Parameter_SetAxisValue, *m_controller, axis, (Automation1AxisParameterId)parameterID, value);
}

void A1Communication::axis_SetA1ParameterString(int32_t axis,int parameterID, std::string value) {
    A1_GENERIC_CALL_AND_THROW(Automation1_Parameter_SetAxisStringValue, *m_controller, axis, (Automation1AxisParameterId)parameterID, value.c_str());
}

void A1Communication::axis_SetA1ConfigValue(int32_t axis,int parameterID, double value) {
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock);
    bool isSet;

    A1_GENERIC_CALL_AND_THROW( Automation1_Configuration_IsConfiguredParametersSet, *m_controller, &isSet);
    if(!isSet) {
        std::cout << "Automation1 Configuration is not set" << std::endl;
        return;
    }
    Automation1ConfiguredParameters configuredParameters;
    A1_GENERIC_CALL_AND_THROW(Automation1_ConfiguredParameters_Create, &configuredParameters);
    A1_GENERIC_CALL_AND_THROW(Automation1_ConfiguredParameters_SetAxisValue,configuredParameters,axis,(Automation1AxisParameterId)parameterID,value);
    A1_GENERIC_CALL_AND_THROW(Automation1_Configuration_SetConfiguredParameters, *m_controller, configuredParameters);
    A1_GENERIC_CALL_AND_THROW(Automation1_ConfiguredParameters_Destroy, configuredParameters);
}

void A1Communication::axis_SetA1ConfigString(int32_t axis,int parameterID, std::string value) {
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock);
    bool isSet;

    A1_GENERIC_CALL_AND_THROW( Automation1_Configuration_IsConfiguredParametersSet, *m_controller, &isSet);
    if(!isSet) {
        std::cout << "Automation1 Configuration is not set" << std::endl;
        return;
    }
    Automation1ConfiguredParameters configuredParameters;
    A1_GENERIC_CALL_AND_THROW(Automation1_ConfiguredParameters_Create, &configuredParameters);
    A1_GENERIC_CALL_AND_THROW(Automation1_ConfiguredParameters_SetAxisStringValue,configuredParameters,axis,(Automation1AxisParameterId)parameterID,value.c_str());
    A1_GENERIC_CALL_AND_THROW(Automation1_Configuration_SetConfiguredParameters, *m_controller, configuredParameters);
    A1_GENERIC_CALL_AND_THROW(Automation1_ConfiguredParameters_Destroy, configuredParameters);
}

double A1Communication::controller_CommandExecuteDouble(const std::string& aeroScriptText)
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock);
    double returnDouble;
    std::string command = (aeroScriptText.substr(0,8)=="$rreturn") ? aeroScriptText : "$rreturn[0] = "+aeroScriptText;
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_ExecuteAndReturnAeroScriptReal, *m_controller, attr_Automation1TaskID_read, command.c_str(), &returnDouble);
    return returnDouble;
}

int A1Communication::controller_CommandExecuteInt(const std::string& aeroScriptText)
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock);
    long int returnInteger;
    std::string command = (aeroScriptText.substr(0,8)=="$ireturn") ? aeroScriptText : "$ireturn[0] = "+aeroScriptText;
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_ExecuteAndReturnAeroScriptInteger, *m_controller, attr_Automation1TaskID_read, command.c_str(), &returnInteger);
    return (int)returnInteger;
}

std::string A1Communication::controller_CommandExecuteString(const std::string& aeroScriptText)
{
    std::lock_guard<std::recursive_mutex> lock(m_connectionLock);
    char returnString[256];
    std::string command = (aeroScriptText.substr(0,8)=="$sreturn") ? aeroScriptText : "$sreturn[0] = "+aeroScriptText;
    A1_TRY_CALL_AND_DISCONNECT(Automation1_Command_ExecuteAndReturnAeroScriptString, *m_controller, attr_Automation1TaskID_read, command.c_str(), returnString, 256);
    return std::string(returnString);
}




} // A1Bridge_ns
