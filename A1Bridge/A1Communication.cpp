#include "A1Communication.h"


namespace A1Bridge_ns {


A1Communication::A1Communication()
{
    m_simulation = false;
    m_controller = new Automation1Controller();
    m_statusControllerPollConfigOnce = NULL;
    m_statusControllerPollConfig = NULL;
    for (int axis = 0; axis < MAX_AXES; axis++)
    {
        m_statusAxisPollConfig[axis] = NULL; 
    }
}


A1Communication::~A1Communication()
{
    delete m_controller; 
    try
    {
        deleteControllerPollConfig();
        for (int axis = 0; axis < MAX_AXES; axis++)
        {
            deleteAxisPollConfig(axis); 
        }
    }
    catch (Tango::DevFailed &e)
    {
        std::cout << "ERROR: Failed to delete Automation1 status config" << std::endl; 
    }
}


void A1Communication::return_checker(bool ret, std::string strTrue, std::string strFalse)
{
    if(!ret)
    {
        throwWithLastA1Error(strFalse, "");
    }
    else 
    {
        if(strTrue != "") std::cout << strTrue << std::endl;
    }
    return;
}


void A1Communication::throwWithLastA1Error(std::string reason, std::string origin)
{
    char errorMessage[errMessageLength];
    Automation1_GetLastErrorMessage(errorMessage, errMessageLength);
    Tango::Except::throw_exception(
        "DRIVER_FAILURE", 
        reason + ": " + errorMessage,
        origin
    );
}


void A1Communication::createPollConfig(Automation1StatusConfig_T **config)
{
    try
    {
        deletePollConfig(config);
    }
    catch (Tango::DevFailed &e)
    {
        Tango::Except::re_throw_exception(e,
            "DRIVER_FAILURE",
            "Failed to delete Automation1 status config before create",
            __func__
        );
    }
    if (!Automation1_StatusConfig_Create(config))
    {
        try
        {
            deletePollConfig(config);
        }
        catch (Tango::DevFailed &e)
        {
            Tango::Except::re_throw_exception(e,
                "DRIVER_FAILURE",
                "Failed to delete Automation1 status config after failure to create",
                __func__
            );
        }

        Tango::Except::throw_exception(
            "DRIVER_FAILURE",
            "Failed to create Automation1 status config",
            __func__
        );
    }
}


void A1Communication::deletePollConfig(Automation1StatusConfig_T **config)
{
    // TODO: Should we throw exception if these fail? 
    // Want to catch errors, however
    // not allowed to throw during Tango device init
    if (*config != NULL)
    {
        if (Automation1_StatusConfig_Destroy(*config))
        {
            *config = NULL; 
            return; 
        }
        else 
        {
            Tango::Except::throw_exception(
                "DRIVER_FAILURE", 
                "Failed to destroy Automation1 status config",
                __func__
            );
        }
    }
}


void A1Communication::createControllerPollConfig()
{
    try
    {
        createPollConfig(&(m_statusControllerPollConfigOnce));
        createPollConfig(&(m_statusControllerPollConfig));
    }
    catch (Tango::DevFailed &e)
    {
        Tango::Except::re_throw_exception(e,
            "DRIVER_FAILURE",
            "Failed to create Automation1 controller status config",
            __func__
        );
    }
}


void A1Communication::createAxisPollConfig(unsigned axis)
{
    try
    {
        createPollConfig(&(m_statusAxisPollConfig[axis]));
    }
    catch (Tango::DevFailed &e)
    {
        Tango::Except::re_throw_exception(e,
            "DRIVER_FAILURE",
            "Failed to create Automation1 axis status config",
            __func__
        );
    }
}


void A1Communication::deleteControllerPollConfig()
{
    try
    {
        deletePollConfig(&(m_statusControllerPollConfigOnce));
        deletePollConfig(&(m_statusControllerPollConfig));
    }
    catch (Tango::DevFailed &e)
    {
        Tango::Except::re_throw_exception(e,
            "DRIVER_FAILURE",
            "Failed to delete Automation1 controller status config",
            __func__
        );
    }
}


void A1Communication::deleteAxisPollConfig(unsigned axis)
{
    try
    {
        deletePollConfig(&(m_statusAxisPollConfig[axis]));
    }
    catch (Tango::DevFailed &e)
    {
        Tango::Except::re_throw_exception(e,
            "DRIVER_FAILURE",
            "Failed to delete Automation1 axis status config",
            __func__
        );
    }
}


void A1Communication::initialiseController_impl()
{
    // createControllerPollConfig(); 
}


void A1Communication::initialiseAxis_impl(unsigned axis)
{
    createAxisPollConfig(axis); 
    
    // TODO: tidy up
    attr_axisContainer[axis] = A1AttributeVector 
    {
        A1AttributeContainer {"PositionFeedback",     (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_PositionFeedback_read),     Automation1AxisStatusItem::Automation1AxisStatusItem_PositionFeedback}},
        A1AttributeContainer {"PositionError",        (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_PositionError_read),        Automation1AxisStatusItem::Automation1AxisStatusItem_PositionError}},
        A1AttributeContainer {"PositionTarget",       (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_PositionTarget_read),       Automation1AxisStatusItem::Automation1AxisStatusItem_PositionCommand}},
        A1AttributeContainer {"VelocityFeedback",     (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_VelocityFeedback_read),     Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityFeedback}},
        A1AttributeContainer {"VelocityError",        (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_VelocityError_read),        Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityError}},
        A1AttributeContainer {"VelocityTarget",       (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_VelocityTarget_read),       Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityCommand}},
        A1AttributeContainer {"AccelerationFeedback", (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_AccelerationFeedback_read), Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationFeedback}},
        A1AttributeContainer {"AccelerationError",    (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_AccelerationError_read),    Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationError}},
        A1AttributeContainer {"AccelerationTarget",   (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_AccelerationTarget_read),   Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationCommand}},
        A1AttributeContainer {"CurrentFeedback",      (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_CurrentFeedback_read),      Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentFeedback}},
        A1AttributeContainer {"CurrentError",         (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_CurrentError_read),         Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentError}},
        A1AttributeContainer {"CurrentTarget",        (A1Attribute) {A1AttrVariant(&attr_axes[axis].attr_CurrentTarget_read),        Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentCommand}},
        A1AttributeContainer {"AxisStatus",           (A1Attribute) {A1AttrVariant(&attr_axes[axis].axisStatus),                     Automation1AxisStatusItem::Automation1AxisStatusItem_AxisStatus}},
        A1AttributeContainer {"AxisFault",            (A1Attribute) {A1AttrVariant(&attr_axes[axis].axisFault),                      Automation1AxisStatusItem::Automation1AxisStatusItem_AxisFault}},
        A1AttributeContainer {"DriveStatus",          (A1Attribute) {A1AttrVariant(&attr_axes[axis].driveStatus),                    Automation1AxisStatusItem::Automation1AxisStatusItem_DriveStatus}}
    };

    m_statusAxisPollLength = attr_axisContainer[axis].size(); 

    for (auto attr : attr_axisContainer[axis])
    {
        std::cout << attr.second.A1Enum.get<Automation1AxisStatusItem>() << std::endl; 
        if (!Automation1_StatusConfig_AddAxisStatusItem(m_statusAxisPollConfig[axis], axis, attr.second.A1Enum.get<Automation1AxisStatusItem>(), 0))
        {
            Tango::Except::throw_exception(
                "DRIVER_FAILURE",
                "Failed to add axis status item: " + attr.first,
                __func__
            );
        }
    }
}


void A1Communication::deleteController_impl()
{
    deleteControllerPollConfig();
}


void A1Communication::deleteAxis_impl(unsigned axis)
{
    deleteAxisPollConfig(axis);
}


void A1Communication::connect_impl(std::string username, std::string password, std::string ip)
{
    bool stat = Automation1_ConnectWithHostAndUser(ip.c_str(), 
                                                   username.c_str(), 
                                                   password.c_str(), 
                                                   m_controller);
    if (!stat)
    {
        std::cout << "ERROR: Connect to A1 controller failed" << std::endl; 
        Tango::Except::throw_exception("COMMUNICATION_BROKEN", 
                                       "Connect to A1 controller failed",
                                       __func__);
    }
    m_connected = true; 
    std::cout << "Connected to A1 controller" << std::endl;

    createControllerPollConfig(); 

    if (!Automation1_Controller_IsRunning(*m_controller, &attr_ControllerRunning_read))
    {
        throwWithLastA1Error(
            "Failed to determine if controller is running",
            __func__
        );
    }

    if (!attr_ControllerRunning_read)
    {
        std::cout << "Controller is not running; starting..." << endl;
        if (!Automation1_Controller_Start(*m_controller))
        {
            throwWithLastA1Error(
                "Failed to start controller",
                __func__
            );
        }
        if (!Automation1_Controller_IsRunning(*m_controller, &attr_ControllerRunning_read))
        {
            throwWithLastA1Error(
                "Failed to determine if controller is running",
                __func__
            );
        }
        if (!attr_ControllerRunning_read)
        {
            throwWithLastA1Error(
                "Controller not running after start request",
                __func__
            );
        }
    }

    std::cout << "Controller is running" << std::endl; 

    bool ret; 

    double aliveAxesMask, allResultsOut; 
    int allResultsLen = 0; 

    ret = Automation1_StatusConfig_AddSystemStatusItem(m_statusControllerPollConfigOnce, Automation1SystemStatusItem::Automation1SystemStatusItem_AliveAxesMask, 0);
    return_checker(ret, std::string(""),std::string("Unable to add status item: Automation1SystemStatusItem::Automation1SystemStatusItem_AliveAxesMask"));
    if(!ret) return;
    allResultsLen++;

    ret = Automation1_Status_GetResults(*m_controller, m_statusControllerPollConfigOnce, &allResultsOut, allResultsLen);
    return_checker(ret, std::string(""),std::string("Unable to get status results from controller."));
    if(!ret) return;

    ret = Automation1_Status_GetSystemResult(m_statusControllerPollConfigOnce, &allResultsOut, allResultsLen, Automation1SystemStatusItem::Automation1SystemStatusItem_AliveAxesMask, 0, &aliveAxesMask);
    return_checker(ret, std::string(""),std::string("Failed to extract system status item from all results."));
    if(!ret) return;

    Automation1_StatusConfig_ClearAllStatusItems(m_statusControllerPollConfigOnce);

        //Get number of axis and task slots.
    attr_AxisCount_read = Automation1_Controller_AvailableAxisCount(*m_controller);
    attr_TaskCount_read = Automation1_Controller_AvailableTaskCount(*m_controller);

    int32_t apiVersion[3];
    Automation1_GetApiVersion(&apiVersion[0], &apiVersion[1], &apiVersion[2]);
    std::string str = std::to_string(apiVersion[0]) + "." + std::to_string(apiVersion[1]) + "." + std::to_string(apiVersion[2]);
    attr_APIVersion_read = Tango::string_dup(str.c_str()); 
    // char *cstr = new char[str.length() +1];
    // strcpy(cstr,str.c_str());
    // *attr_APIVersion_read = cstr;
    //delete[] cstr; causes the output to be garbæge

    ret = Automation1_StatusConfig_AddTaskStatusItem(m_statusControllerPollConfig, 1, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus0, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add status item: Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus0"));
    if(ret) m_statusAxisPollLength++;

    ret = Automation1_StatusConfig_AddTaskStatusItem(m_statusControllerPollConfig, 1, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus1, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add status item: Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus1"));
    if(ret) m_statusAxisPollLength++;

    ret = Automation1_StatusConfig_AddTaskStatusItem(m_statusControllerPollConfig, 1, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus2, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add status item: Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus2"));
    if(ret) m_statusAxisPollLength++;


}


void A1Communication::disconnect_impl()
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


void A1Communication::readController_impl()
{
    if(*m_controller == nullptr)
    {
        Tango::Except::throw_exception(
        "DRIVER_FAILURE", 
        "No controller",
        __func__); 
    }

    bool isRunning;
    bool ret; 
    if (!Automation1_Controller_IsRunning(*m_controller, &isRunning))
    {
        throwWithLastA1Error("ERROR: Unable to determine if controller is running.", 
                             "A1Communication::readHardware_impl()");
    }
    if (!isRunning)
    {
        Tango::Except::throw_exception("DRIVER_FAILURE", 
                                       "Controller not running",
                                       __func__); 
    }

    // TODO: controller implementation
}


void A1Communication::getAxisResult(unsigned axis, double *axisResults, A1AttributeContainer &attr, std::string origin)
{
    double d; 
    if (!Automation1_Status_GetAxisResult(m_statusAxisPollConfig[axis], axisResults, m_statusAxisPollLength, axis, 
                                          attr.second.A1Enum.get<Automation1AxisStatusItem>(), 0, &d))
    {
        throwWithLastA1Error(std::string("ERROR: Failed to extract axis info: ") + attr.first, origin);
    }
    attr.second.attr.set(d);
    std::cout << "Set " << attr.first << " to " << d << std::endl; 
    return;
}

void A1Communication::readAxis_impl(unsigned axis)
{
    double axisResults[m_statusAxisPollLength];

    if (!Automation1_Status_GetResults(*m_controller, m_statusAxisPollConfig[axis], axisResults, m_statusAxisPollLength))
    {
        throwWithLastA1Error(std::string("ERROR: Failed to get axis status results from controller."), __func__);
    }

    //Setup vars to store the data in.
    double axStatus, drvStatus;

    for (auto attr : attr_axisContainer[axis])
    {
        getAxisResult(axis, axisResults, attr, std::string(__func__));
    }

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

    attr_axes[axis].attr_Enabled_read =     attr_axes[axis].attr_DriveStatus_read[DRV_ENABLED];
    attr_axes[axis].attr_InPosition_read =  attr_axes[axis].attr_DriveStatus_read[DRV_IN_POSITION];

    // Axis fault

    attr_axes[axis].attr_AxisFault_read[0]    = (int(attr_axes[axis].axisFault) >> 0 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[1]    = (int(attr_axes[axis].axisFault) >> 1 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[2]    = (int(attr_axes[axis].axisFault) >> 2 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[3]    = (int(attr_axes[axis].axisFault) >> 3 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[4]    = (int(attr_axes[axis].axisFault) >> 4 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[5]    = (int(attr_axes[axis].axisFault) >> 5 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[6]    = (int(attr_axes[axis].axisFault) >> 6 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[7]    = (int(attr_axes[axis].axisFault) >> 7 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[8]    = (int(attr_axes[axis].axisFault) >> 8 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[9]    = (int(attr_axes[axis].axisFault) >> 9 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[10]   = (int(attr_axes[axis].axisFault) >> 10 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[11]   = (int(attr_axes[axis].axisFault) >> 11 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[12]   = (int(attr_axes[axis].axisFault) >> 12 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[13]   = (int(attr_axes[axis].axisFault) >> 13 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[14]   = (int(attr_axes[axis].axisFault) >> 14 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[15]   = (int(attr_axes[axis].axisFault) >> 15 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[16]   = (int(attr_axes[axis].axisFault) >> 16 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[17]   = (int(attr_axes[axis].axisFault) >> 17 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[18]   = (int(attr_axes[axis].axisFault) >> 18 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[19]   = (int(attr_axes[axis].axisFault) >> 19 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[20]   = (int(attr_axes[axis].axisFault) >> 20 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[21]   = (int(attr_axes[axis].axisFault) >> 21 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[22]   = (int(attr_axes[axis].axisFault) >> 22 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[23]   = (int(attr_axes[axis].axisFault) >> 23 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[24]   = (int(attr_axes[axis].axisFault) >> 24 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[25]   = (int(attr_axes[axis].axisFault) >> 25 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[26]   = (int(attr_axes[axis].axisFault) >> 26 ) & 1U;
    attr_axes[axis].attr_AxisFault_read[27]   = (int(attr_axes[axis].axisFault) >> 27 ) & 1U;
}


void A1Communication::controller_Reset() 
{
    NotImplemented(__func__);
} 
void A1Communication::controller_Start() 
{
    NotImplemented(__func__);
} 
void A1Communication::controller_Stop() 
{
    NotImplemented(__func__);
} 
void A1Communication::controller_Enable() 
{
    NotImplemented(__func__);
} 
void A1Communication::controller_Disable() 
{
    NotImplemented(__func__);
} 
void A1Communication::controller_ClearErrors() 
{
    if (!Automation1_Command_AcknowledgeAll(*m_controller, 1))
    {
        throwWithLastA1Error( 
            "Automation1_Command_AcknowledgeAll failed", 
            __func__
        );
    }
} 
void A1Communication::controller_AeroScriptProgramRun() 
{
    NotImplemented(__func__);
} 
void A1Communication::controller_AeroScriptProgramLoad() 
{
    NotImplemented(__func__);
} 
void A1Communication::controller_AeroScriptProgramStart() 
{
    NotImplemented(__func__);
} 
void A1Communication::controller_AeroScriptProgramStop() 
{
    NotImplemented(__func__);
} 
void A1Communication::controller_AeroScriptProgramPause() 
{
    NotImplemented(__func__);
} 


void A1Communication::axis_Abort(int32_t axis) 
{
    if (!Automation1_Command_Abort(*m_controller, &axis, 1))
    {
        throwWithLastA1Error( 
            "Automation1_Command_Abort failed", 
            __func__
        );
    }
}

void A1Communication::axis_Home(int32_t axis) 
{
    if (!Automation1_Command_Home(*m_controller, 1, &axis, 1))
    {
        throwWithLastA1Error(
            "Automation1_Command_Home failed", 
            __func__
        );
    }
} 

void A1Communication::axis_Move(int32_t axis) 
{
    NotImplemented(__func__);
} 

void A1Communication::axis_Enable(int32_t axis) 
{
    if (!Automation1_Command_Enable(*m_controller, 1, &axis, 1))
    {
        throwWithLastA1Error(
            "Automation1_Command_Enable failed", 
            __func__
        );
    }
} 

void A1Communication::axis_Disable(int32_t axis) 
{
    if (!Automation1_Command_Disable(*m_controller, &axis, 1))
    {
        throwWithLastA1Error(
            "Automation1_Command_Disable failed", 
            __func__
        );
    }
} 

void A1Communication::axis_BrakeOn(int32_t axis) 
{
    if (!Automation1_Command_DriveBrakeOn(*m_controller, 1, axis))
    {
        throwWithLastA1Error(
            "Automation1_Command_DriveBrakeOn failed", 
            __func__
        );
    }
} 

void A1Communication::axis_BrakeOff(int32_t axis) 
{
    if (!Automation1_Command_DriveBrakeOff(*m_controller, 1, axis))
    {
        throwWithLastA1Error(
            "Automation1_Command_DriveBrakeOff failed", 
            __func__
        );
    }
} 

void A1Communication::axis_MoveFromLimit(int32_t axis) 
{
    if (!Automation1_Command_MoveOutOfLimit(*m_controller, 1, axis))
    {
        throwWithLastA1Error(
            "Automation1_Command_MoveOutOfLimit failed", 
            __func__
        );
    }
} 

void A1Communication::axis_FreeRun(int32_t axis, double vel) 
{
    if (!Automation1_Command_MoveFreerun(*m_controller, 1, &axis, 1, &vel, 1))
    {
        throwWithLastA1Error(
            "Automation1_Command_MoveFreerun failed", 
            __func__
        );
    }
} 

void A1Communication::axis_FreeRunStop(int32_t axis) 
{
    if (!Automation1_Command_MoveFreerunStop(*m_controller, 1, &axis, 1))
    {
        throwWithLastA1Error(
            "Automation1_Command_MoveFreerunStop failed", 
            __func__
        );
    }
} 

void A1Communication::axis_ThrowAllFaults(int32_t axis) 
{
    int64_t faultMask = ~0x0; 
    if (!Automation1_Command_FaultThrow(*m_controller, 1, axis, faultMask))
    {
        throwWithLastA1Error(
            "Automation1_Command_FaultThrow failed", 
            __func__
        );
    }
} 

void A1Communication::axis_AcknowledgeFaults(int32_t axis) 
{
    if (!Automation1_Command_FaultAcknowledge(*m_controller, 1, &axis, 1))
    {
        throwWithLastA1Error(
            "Automation1_Command_FaultAcknowledge failed", 
            __func__
        );
    }
} 
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