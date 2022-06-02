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
    catch Tango::DevFailed &e
    {
        std::cout << "ERROR: Failed to delete Automation1 status config" << std::endl; 
    }
}


void A1Communication::throwWithLastA1Error(std::string reason, std::string origin)
{
    char errorMessage[ERR_MSG_SZ];
    Automation1_GetLastErrorMessage(errorMessage, ERR_MSG_SZ);
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
        !Automation1_StatusConfig_Create(&m_statusPollConfig))
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
    if (m_statusPollOnceConfig != NULL || m_statusPollOnceConfig != NULL)
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

    if (!Automation1_Controller_IsRunning(*controller, attr_ControllerRunning_read))
    {
        throwWithLastA1Error(
            "Failed to determine if controller is running",
            "A1Communication::connect_impl"
        );
    }

    if (!*attr_ControllerRunning_read)
    {
        std::cout << "Controller is not running; starting..." << endl;
        if (!Automation1_Controller_Start(*controller))
        {
            throwWithLastA1Error(
                "Failed to start controller",
                "A1Communication::connect_impl"
            );
        }
        if (!Automation1_Controller_IsRunning(*controller, attr_ControllerRunning_read))
        {
            throwWithLastA1Error(
                "Failed to determine if controller is running",
                "A1Communication::connect_impl"
            );
        }
        if (!attr_ControllerRunning_read)
        {
            Automation1_GetLastErrorMessage(errorMessage, ERR_MSG_SZ);
            throwWithLastA1Error(
                "Controller not running after start request",
                "A1Communication::connect_impl"
            );
        }
    }

    std::cout << "Controller is running" << std::endl; 
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