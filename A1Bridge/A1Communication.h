#pragma once 

#include <iostream>
#include <string> 
#include <map> 
#include <tango.h> 

#include "A1Bridge.h"
#include "A1Defines.h"

#include "Automation1.h"

namespace A1Bridge_ns {

class A1Communication: public A1Bridge
{
  protected:
    unsigned errMessageLength=2048; 
    void connect_impl(std::string username, std::string password, std::string ip); 
    void disconnect_impl(); 
    void readHardware_impl(); 
    Automation1Controller *m_controller;
	Automation1StatusConfig_T *m_statusPollOnceConfig; 
    Automation1StatusConfig_T *m_statusPollConfig;
    Automation1StatusConfig_T *m_statusAxPollConfig;
    unsigned statusAxPollLength, statusPollLength; 
    unsigned ax = 0;
    void return_checker(bool ret, std::string strTrue="", std::string strFalse="");

    void createStatusPollConfig(); 
    void deleteStatusPollConfig(); 
    void throwWithLastA1Error(std::string reason, std::string origin);

  public:
    ~A1Communication(); 
    A1Communication(); 
    void controller_Reset();
    void controller_Start();
    void controller_Stop();
    void controller_Enable();
    void controller_Disable();
    void controller_ClearErrors();
    void controller_AeroScriptProgramRun();
    void controller_AeroScriptProgramLoad();
    void controller_AeroScriptProgramStart();
    void controller_AeroScriptProgramStop();
    void controller_AeroScriptProgramPause();
    void axis_Abort(int32_t axis);
    void axis_Home(int32_t axis);
    void axis_Move(int32_t axis);
    void axis_Enable(int32_t axis);
    void axis_Disable(int32_t axis);
    void axis_BrakeOn(int32_t axis);
    void axis_BrakeOff(int32_t axis);
    void axis_MoveFromLimit(int32_t axis);
    void axis_FreeRun(int32_t axis, double vel);
    void axis_FreeRunStop(int32_t axis);
    void axis_ThrowAllFaults(int32_t axis);
    void axis_AcknowledgeFaults(int32_t axis);
    void axis_DataCollectionStart(int32_t axis);
    void axis_DataCollectionStop(int32_t axis);
    void axis_DataCollectionRefresh(int32_t axis);
    void axis_DataCollectionGetResults(int32_t axis);

protected:
    map<std::string, Tango::DevBoolean> attributes =
        {{std::string("AxisHomed"), attr_Homed_read}}; 
    // map<std::string, Tango::Attribute*, Automation1AxisStatus> attributes =
        // {{"AxisHomed", &attr_Homed_read, Automation1AxisStatus::Automation1AxisStatus_Homed}}; 


};

} // namespace A1Bridge_ns