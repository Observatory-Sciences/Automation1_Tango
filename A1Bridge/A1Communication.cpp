#include "A1Communication.h"


namespace A1BridgeNS {


A1Communication::A1Communication()
{
    m_simulation = false;
    m_controller = new Automation1Controller();
}


A1Communication::~A1Communication()
{
    delete m_controller; 
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
}


void A1Communication::disconnect_impl()
{
    bool stat = Automation1_Disconnect(*m_controller);
    if (!stat)
    {
        std::cout << "ERROR: Disconnect from A1 controller failed" << std::endl; 
        Tango::Except::throw_exception("COMMUNICATION_BROKEN", 
                                       "Disconnect from A1 controller failed",
                                       "A1Communication::disconnect_impl");
    }
    m_connected = false; 

}


void A1Communication::readHardware()
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "read_hardware not implemented",
                                   "read_hardware not implemented");
}


void A1Communication::controller_Reset() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_Reset not implemented",
                                   "controller_Reset not implemented");
} 
void A1Communication::controller_Start() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_Start not implemented",
                                   "controller_Start not implemented");
} 
void A1Communication::controller_Stop() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_Stop not implemented",
                                   "controller_Stop not implemented");
} 
void A1Communication::controller_Enable() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_Enable not implemented",
                                   "controller_Enable not implemented");
} 
void A1Communication::controller_Disable() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_Disable not implemented",
                                   "controller_Disable not implemented");
} 
void A1Communication::controller_ClearErrors() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_ClearErrors not implemented",
                                   "controller_ClearErrors not implemented");
} 
void A1Communication::controller_AeroScriptProgramRun() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_AeroScriptProgramRun not implemented",
                                   "controller_AeroScriptProgramRun not implemented");
} 
void A1Communication::controller_AeroScriptProgramLoad() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_AeroScriptProgramLoad not implemented",
                                   "controller_AeroScriptProgramLoad not implemented");
} 
void A1Communication::controller_AeroScriptProgramStart() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_AeroScriptProgramStart not implemented",
                                   "controller_AeroScriptProgramStart not implemented");
} 
void A1Communication::controller_AeroScriptProgramStop() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_AeroScriptProgramStop not implemented",
                                   "controller_AeroScriptProgramStop not implemented");
} 
void A1Communication::controller_AeroScriptProgramPause() 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "controller_AeroScriptProgramPause not implemented",
                                   "controller_AeroScriptProgramPause not implemented");
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
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "axis_Move not implemented",
                                   "axis_Move not implemented");
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
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "axis_FreeRun not implemented",
                                   "axis_FreeRun not implemented");
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
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "axis_ThrowAllFaults not implemented",
                                   "axis_ThrowAllFaults not implemented");
} 
void A1Communication::axis_AcknowledgeFaults(int32_t axis) 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "axis_AcknowledgeFaults not implemented",
                                   "axis_AcknowledgeFaults not implemented");
} 
void A1Communication::axis_DataCollectionStart(int32_t axis) 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "axis_DataCollectionStart not implemented",
                                   "axis_DataCollectionStart not implemented");
} 
void A1Communication::axis_DataCollectionStop(int32_t axis) 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "axis_DataCollectionStop not implemented",
                                   "axis_DataCollectionStop not implemented");
} 
void A1Communication::axis_DataCollectionRefresh(int32_t axis) 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "axis_DataCollectionRefresh not implemented",
                                   "axis_DataCollectionRefresh not implemented");
} 
void A1Communication::axis_DataCollectionGetResults(int32_t axis) 
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "axis_DataCollectionGetResults not implemented",
                                   "axis_DataCollectionGetResults not implemented");
} 

}