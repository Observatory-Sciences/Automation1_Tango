#include "A1Communication.h"


namespace A1Bridge_ns {


A1Communication::A1Communication()
{
    m_simulation = false;
    m_controller = new Automation1Controller();
}


A1Communication::~A1Communication()
{
    delete m_controller; 
    try
    {
        deleteStatusPollConfig();
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


void A1Communication::createStatusPollConfig()
{
    try
    {
        deleteStatusPollConfig();
    }
    catch (Tango::DevFailed &e)
    {
        Tango::Except::re_throw_exception(e,
            "DRIVER_FAILURE",
            "Failed to create Automation1 status config",
            "A1Communication::createStatusPollConfig"
        );
    }
    if (!Automation1_StatusConfig_Create(&m_statusPollOnceConfig) ||
        !Automation1_StatusConfig_Create(&m_statusPollConfig) ||
        !Automation1_StatusConfig_Create(&m_statusAxPollConfig))
    {
        try
        {
            deleteStatusPollConfig();
        }
        catch (Tango::DevFailed &e)
        {
            Tango::Except::re_throw_exception(e,
                "DRIVER_FAILURE",
                "Failed to create Automation1 status config",
                "A1Communication::createStatusPollConfig"
            );
        }

        Tango::Except::throw_exception(
            "DRIVER_FAILURE",
            "Failed to create Automation1 status config",
            "A1Communication::createStatusPollConfig"
        );
    }
}


void A1Communication::deleteStatusPollConfig()
{
    // TODO: Should we throw exception if these fail? 
    if (m_statusPollOnceConfig != NULL)
    {
        if (Automation1_StatusConfig_Destroy(m_statusPollOnceConfig))
        {
            m_statusPollOnceConfig = NULL; 
        }
    }
    if (m_statusPollConfig != NULL)
    {
        if (Automation1_StatusConfig_Destroy(m_statusPollConfig))
        {
            m_statusPollConfig = NULL;
        }
    }
    if (m_statusAxPollConfig != NULL)
    {
        if (Automation1_StatusConfig_Destroy(m_statusAxPollConfig))
        {
            m_statusAxPollConfig = NULL;
        }
    }
    if (m_statusPollOnceConfig != NULL || m_statusPollOnceConfig != NULL || m_statusAxPollConfig != NULL)
    {
        Tango::Except::throw_exception(
            "DRIVER_FAILURE", 
            "Failed to destroy Automation1 status config",
            "A1Communication::deleteStatusPollConfig"
        );
    }
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
                                       "A1Communication::connect_impl");
    }
    m_connected = true; 
    std::cout << "Connected to A1 controller" << std::endl;

    createStatusPollConfig(); 

    if (!Automation1_Controller_IsRunning(*m_controller, attr_ControllerRunning_read))
    {
        throwWithLastA1Error(
            "Failed to determine if controller is running",
            "A1Communication::connect_impl"
        );
    }

    if (!*attr_ControllerRunning_read)
    {
        std::cout << "Controller is not running; starting..." << endl;
        if (!Automation1_Controller_Start(*m_controller))
        {
            throwWithLastA1Error(
                "Failed to start controller",
                "A1Communication::connect_impl"
            );
        }
        if (!Automation1_Controller_IsRunning(*m_controller, attr_ControllerRunning_read))
        {
            throwWithLastA1Error(
                "Failed to determine if controller is running",
                "A1Communication::connect_impl"
            );
        }
        if (!attr_ControllerRunning_read)
        {
            throwWithLastA1Error(
                "Controller not running after start request",
                "A1Communication::connect_impl"
            );
        }
    }

    std::cout << "Controller is running" << std::endl; 

    bool ret; 

    double aliveAxesMask, allResultsOut; 
    int allResultsLen = 0; 

    ret = Automation1_StatusConfig_AddSystemStatusItem(m_statusPollOnceConfig, Automation1SystemStatusItem::Automation1SystemStatusItem_AliveAxesMask, 0);
    return_checker(ret, std::string(""),std::string("Unable to add status item: Automation1SystemStatusItem::Automation1SystemStatusItem_AliveAxesMask"));
    if(!ret) return;
    allResultsLen++;

    ret = Automation1_Status_GetResults(*m_controller, m_statusPollOnceConfig, &allResultsOut, allResultsLen);
    return_checker(ret, std::string(""),std::string("Unable to get status results from controller."));
    if(!ret) return;

    ret = Automation1_Status_GetSystemResult(m_statusPollOnceConfig, &allResultsOut, allResultsLen, Automation1SystemStatusItem::Automation1SystemStatusItem_AliveAxesMask, 0, &aliveAxesMask);
    return_checker(ret, std::string(""),std::string("Failed to extract system status item from all results."));
    if(!ret) return;

    Automation1_StatusConfig_ClearAllStatusItems(m_statusPollOnceConfig);

        //Get number of axis and task slots.
    *attr_AxisCount_read = Automation1_Controller_AvailableAxisCount(*m_controller);
    *attr_TaskCount_read = Automation1_Controller_AvailableTaskCount(*m_controller);

    int32_t apiVersion[3];
    Automation1_GetApiVersion(&apiVersion[0], &apiVersion[1], &apiVersion[2]);
    std::string str = std::to_string(apiVersion[0]) + "." + std::to_string(apiVersion[1]) + "." + std::to_string(apiVersion[2]);
    *attr_APIVersion_read = Tango::string_dup(str.c_str()); 
    // char *cstr = new char[str.length() +1];
    // strcpy(cstr,str.c_str());
    // *attr_APIVersion_read = cstr;
    //delete[] cstr; causes the output to be garbæge

    ret = Automation1_StatusConfig_AddTaskStatusItem(m_statusPollConfig, 1, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus0, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add status item: Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus0"));
    if(ret) statusPollLength++;

    ret = Automation1_StatusConfig_AddTaskStatusItem(m_statusPollConfig, 1, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus1, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add status item: Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus1"));
    if(ret) statusPollLength++;

    ret = Automation1_StatusConfig_AddTaskStatusItem(m_statusPollConfig, 1, Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus2, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add status item: Automation1TaskStatusItem::Automation1TaskStatusItem_TaskStatus2"));
    if(ret) statusPollLength++;

    statusAxPollLength = 0;		//Should be 0 anyway.

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionFeedback, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_PositionFeedback"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionCommand, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_PositionCommand"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionError, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_PositionError"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityFeedback, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityFeedback"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityCommand, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityCommand"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityError, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityError"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationFeedback, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationFeedback"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationCommand, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationCommand"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationError, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationError"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentFeedback, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentFeedback"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentCommand, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentCommand"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentError, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentError"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AxisStatus, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_AxisStatus"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AxisParameter, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_AxisParameter"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_DriveStatus, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_DriveStatus"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AxisFault, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_AxisFault"));
    if(ret) statusAxPollLength++;

    ret = Automation1_StatusConfig_AddAxisStatusItem(m_statusAxPollConfig, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_TotalMoveTime, 0);
    return_checker(ret, std::string(""),std::string("ERROR: Failed to add axis status item: Automation1AxisStatusItem::Automation1AxisStatusItem_TotalMoveTime!"));
    if(ret) statusAxPollLength++;

    
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
                                       "A1Communication::disconnect_impl");
    }
}


void A1Communication::readHardware_impl()
{
    std::cout << "readHardware_impl" << std::endl; 
    NotImplemented("read_hardware");

    // if(*m_controller == nullptr)
    // {
    //     Tango::Except::throw_exception(
    //     "DRIVER_FAILURE", 
    //     "No ",
    //     "A1Communication::readHardware_impl"); 
    // }


	bool isRunning;
    ret = Automation1_Controller_IsRunning(*m_controller, &isRunning);
	return_checker(ret, std::string(""),std::string("ERROR: Unable to determine if controller is running."));
	if (!isRunning)
	{
        Tango::Except::throw_exception(
            "DRIVER_FAILURE", 
            "Controller not running",
            "A1Communication::readHardware_impl"
        ); 
	}

    double *axisResults = new double[pollStatusLength];
	ret = Automation1_Status_GetResults(*controller, pollStatusConfig, axisResults, pollStatusLength);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to get axis status results from controller."));

	//Setup vars to store the data in.
	double axStatus;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionFeedback, 0, attr_PositionFeedback_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info:  Automation1AxisStatusItem::Automation1AxisStatusItem_PositionFeedback"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionError, 0, attr_PositionError_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info:  Automation1AxisStatusItem::Automation1AxisStatusItem_PositionError"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_PositionCommand, 0, attr_PositionTarget_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info:  Automation1AxisStatusItem::Automation1AxisStatusItem_PositionCommand"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityFeedback, 0, attr_VelocityFeedback_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityFeedback"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityError, 0, attr_VelocityError_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityError"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityCommand, 0, attr_VelocityTarget_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_VelocityTarget"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationFeedback, 0, attr_AccelerationFeedback_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationFeedback"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationError, 0, attr_AccelerationError_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationError"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationCommand, 0, attr_AccelerationTarget_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_AccelerationTarget"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentFeedback, 0, attr_CurrentFeedback_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentFeedback"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentError, 0, attr_CurrentError_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentError"));
	if(!ret) return;

	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentCommand, 0, attr_CurrentTarget_read);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_CurrentTarget"));
	if(!ret) return;
	
	ret = Automation1_Status_GetAxisResult(pollStatusConfig, axisResults, pollStatusLength, ax, Automation1AxisStatusItem::Automation1AxisStatusItem_AxisStatus, 0, &axStatus);
	return_checker(ret, std::string(""),std::string("ERROR: Failed to extract axis info: Automation1AxisStatusItem::Automation1AxisStatusItem_AxisStatus"));
	if(!ret) return;

	attr_AxisStatus_read[AX_HOMED] 								= (int(axStatus) >> 0 ) & 1U;		//Homed
	attr_AxisStatus_read[AX_PROFILING] 							= (int(axStatus) >> 1 ) & 1U;		//Profiling
	attr_AxisStatus_read[AX_WAIT_DONE] 							= (int(axStatus) >> 2 ) & 1U;		//WaitDone
	attr_AxisStatus_read[AX_COMMAND_VALID] 						= (int(axStatus) >> 3 ) & 1U;		//CommandValid
	attr_AxisStatus_read[AX_HOMING] 							= (int(axStatus) >> 4 ) & 1U;		//Homing
	attr_AxisStatus_read[AX_ENABLING] 							= (int(axStatus) >> 5 ) & 1U;		//Enabling
	attr_AxisStatus_read[AX_JOG_GENERATING] 					= (int(axStatus) >> 7 ) & 1U;		//JogGenerating
	attr_AxisStatus_read[AX_JOGGING] 							= (int(axStatus) >> 8 ) & 1U;		//Jogging
	attr_AxisStatus_read[AX_DRIVE_PENDING] 						= (int(axStatus) >> 9 ) & 1U;		//DrivePending
	attr_AxisStatus_read[AX_DRIVE_ABORT_PENDING] 				= (int(axStatus) >> 10) & 1U;		//DriveAbortPending
	attr_AxisStatus_read[AX_TRAJECTORY_FILTERING] 				= (int(axStatus) >> 11) & 1U;		//TrajectoryFiltering
	attr_AxisStatus_read[AX_IFOV_ENABLED] 						= (int(axStatus) >> 12) & 1U;		//IfovEnabled
	attr_AxisStatus_read[AX_NOT_VIRTUAL] 						= (int(axStatus) >> 13) & 1U;		//NotVirtual
	attr_AxisStatus_read[AX_CAL_ENABLED1D] 						= (int(axStatus) >> 14) & 1U;		//CalEnabled1D
	attr_AxisStatus_read[AX_CAL_ENABLED2D] 						= (int(axStatus) >> 15) & 1U;		//CalEnabled2D
	attr_AxisStatus_read[AX_CAMMING_GEARING_CONTROL] 			= (int(axStatus) >> 16) & 1U;		//CammingGearingControl
	attr_AxisStatus_read[AX_JOYSTICK_CONTROL] 					= (int(axStatus) >> 17) & 1U;		//JoystickControl
	attr_AxisStatus_read[AX_BACKLASH_ACTIVE] 					= (int(axStatus) >> 18) & 1U;		//BacklashActive
	attr_AxisStatus_read[AX_GAIN_MAPPING_ENABLED] 				= (int(axStatus) >> 19) & 1U;		//GainMappingEnabled
	attr_AxisStatus_read[AX_MOTION_DONE] 						= (int(axStatus) >> 22) & 1U;		//MotionDone
	attr_AxisStatus_read[AX_MOTION_CLAMPED] 					= (int(axStatus) >> 23) & 1U;		//MotionClamped
	attr_AxisStatus_read[AX_GANTRY_ALIGNED] 					= (int(axStatus) >> 24) & 1U;		//GantryAligned
	attr_AxisStatus_read[AX_GANTRY_DRIVE_CONTROL_REALIGNING] 	= (int(axStatus) >> 25) & 1U;		//GantryDriveControlRealigning
	attr_AxisStatus_read[AX_THERMO_COMP_ENABLED] 				= (int(axStatus) >> 27) & 1U;		//ThermoCompEnabled

	*attr_Homed_read = attr_AxisStatus_read[AX_HOMED];

	delete[] axisResults;
}

void A1Communication::controller_Reset() 
{
    NotImplemented("controller_Reset");
} 
void A1Communication::controller_Start() 
{
    NotImplemented("controller_Start");
} 
void A1Communication::controller_Stop() 
{
    NotImplemented("controller_Stop");
} 
void A1Communication::controller_Enable() 
{
    NotImplemented("controller_Enable");
} 
void A1Communication::controller_Disable() 
{
    NotImplemented("controller_Disable");
} 
void A1Communication::controller_ClearErrors() 
{
    NotImplemented("controller_ClearErrors");
} 
void A1Communication::controller_AeroScriptProgramRun() 
{
    NotImplemented("controller_AeroScriptProgramRun");
} 
void A1Communication::controller_AeroScriptProgramLoad() 
{
    NotImplemented("controller_AeroScriptProgramLoad");
} 
void A1Communication::controller_AeroScriptProgramStart() 
{
    NotImplemented("controller_AeroScriptProgramStart");
} 
void A1Communication::controller_AeroScriptProgramStop() 
{
    NotImplemented("controller_AeroScriptProgramStop");
} 
void A1Communication::controller_AeroScriptProgramPause() 
{
    NotImplemented("controller_AeroScriptProgramPause");
} 


void A1Communication::axis_Abort(int32_t axis) 
{
    if (!Automation1_Command_Abort(*m_controller, &axis, 1))
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Abort failed", 
                                       "A1Communication::axis_Abort");
    }
}

void A1Communication::axis_Home(int32_t axis) 
{
    if (!Automation1_Command_Home(*m_controller, 1, &axis, 1))
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Home failed", 
                                       "A1Communication::axis_Home");
    }
} 

void A1Communication::axis_Move(int32_t axis) 
{
    NotImplemented("axis_Move");
} 

void A1Communication::axis_Enable(int32_t axis) 
{
    if (!Automation1_Command_Enable(*m_controller, 1, &axis, 1))
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Enable failed", 
                                       "A1Communication::axis_Enable");
    }
} 

void A1Communication::axis_Disable(int32_t axis) 
{
    if (!Automation1_Command_Disable(*m_controller, &axis, 1))
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Disable failed", 
                                       "A1Communication::axis_Disable");
    }
} 

void A1Communication::axis_BrakeOn(int32_t axis) 
{
    if (!Automation1_Command_DriveBrakeOn(*m_controller, 1, axis))
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_DriveBrakeOn failed", 
                                       "A1Communication::axis_BrakeOn");
    }
} 

void A1Communication::axis_BrakeOff(int32_t axis) 
{
    if (!Automation1_Command_DriveBrakeOff(*m_controller, 1, axis))
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_DriveBrakeOff failed", 
                                       "A1Communication::axis_BrakeOff");
    }
} 

void A1Communication::axis_MoveFromLimit(int32_t axis) 
{
    if (!Automation1_Command_MoveOutOfLimit(*m_controller, 1, axis))
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_MoveOutOfLimit failed", 
                                       "A1Communication::axis_MoveFromLimit");
    }
} 

void A1Communication::axis_FreeRun(int32_t axis) 
{
    NotImplemented("axis_FreeRun");
} 

void A1Communication::axis_FreeRunStop(int32_t axis) 
{
    if (!Automation1_Command_MoveFreerunStop(*m_controller, 1, &axis, 1))
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_MoveFreerunStop failed", 
                                       "A1Communication::axis_FreeRunStop");
    }
} 

void A1Communication::axis_ThrowAllFaults(int32_t axis) 
{
    NotImplemented("axis_ThrowAllFaults");
} 
void A1Communication::axis_AcknowledgeFaults(int32_t axis) 
{
    NotImplemented("axis_AcknowledgeFaults");
} 
void A1Communication::axis_DataCollectionStart(int32_t axis) 
{
    NotImplemented("axis_DataCollectionStart");
} 
void A1Communication::axis_DataCollectionStop(int32_t axis) 
{
    NotImplemented("axis_DataCollectionStop");
} 
void A1Communication::axis_DataCollectionRefresh(int32_t axis) 
{
    NotImplemented("axis_DataCollectionRefresh");
} 
void A1Communication::axis_DataCollectionGetResults(int32_t axis) 
{
    NotImplemented("axis_DataCollectionGetResults");
} 

} // A1Bridge_ns