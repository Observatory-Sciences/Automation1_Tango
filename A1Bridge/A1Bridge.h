#pragma once 

#include <iostream>
#include <string>  
#include <chrono> 
#include <tango.h>

#define DEFAULT_TO_SIMULATION false

namespace A1Bridge_ns {


void NotImplemented(std::string feature);


// TODO: who calls the A1Bridge destructor? If both Axis and Controller we
// have double delete problem. If neither we don't have a clean exit.

// TODO: ensure Axis calls getInstance after Controller

class A1Bridge
{
  protected: 
    A1Bridge();
    virtual ~A1Bridge();
    static A1Bridge *m_instance; 
    bool m_connected; 
    bool m_simulation; 
    bool m_verbose; 
    std::string m_username; 
    std::string m_password; 
    std::string m_ip; 
    std::chrono::milliseconds m_pollInterval_ms; 
    std::chrono::time_point<std::chrono::steady_clock> m_lastPoll; 

    virtual void connect_impl(std::string username, std::string password, std::string ip) {NotImplemented("connect_impl");}; 
    virtual void disconnect_impl() {NotImplemented("disconnect_impl");}; 
    virtual void readHardware_impl() {NotImplemented("readHardware_impl");}; 

  public: 
    static A1Bridge* getInstance();
    static A1Bridge* getInstance(bool simulation);
    static A1Bridge* setSimulation(bool simulation); 
    bool isSimulation();
    bool isConnected();
    void connect(std::string username, std::string password, std::string ip); 
    void disconnect(); 
    void reconnect(); 
    void readHardware();
    template<class T = int> void setPollingInterval(T interval) 
    {
        m_pollInterval_ms = std::chrono::milliseconds(interval);
    };  

    // Interface between Tango <-> Automation1 API is left up to the children
    // We just call the Tango command or retrieve the attributes 

    // Commands
    virtual void controller_Reset() {NotImplemented("controller_Reset");}; 
    virtual void controller_Start() {NotImplemented("controller_Start");}; 
    virtual void controller_Stop() {NotImplemented("controller_Stop");}; 
    virtual void controller_Enable() {NotImplemented("controller_Enable");}; 
    virtual void controller_Disable() {NotImplemented("controller_Disable");}; 
    virtual void controller_ClearErrors() {NotImplemented("controller_ClearErrors");}; 
    virtual void controller_AeroScriptProgramRun() {NotImplemented("controller_AeroScriptProgramRun");}; 
    virtual void controller_AeroScriptProgramLoad() {NotImplemented("controller_AeroScriptProgramLoad");}; 
    virtual void controller_AeroScriptProgramStart() {NotImplemented("controller_AeroScriptProgramStart");}; 
    virtual void controller_AeroScriptProgramStop() {NotImplemented("controller_AeroScriptProgramStop");}; 
    virtual void controller_AeroScriptProgramPause() {NotImplemented("controller_AeroScriptProgramPause");}; 
    virtual void axis_Abort(int32_t axis) {NotImplemented("axis_Abort");}; 
    virtual void axis_Home(int32_t axis) {NotImplemented("axis_Home");}; 
    virtual void axis_Move(int32_t axis) {NotImplemented("axis_Move");}; 
    virtual void axis_Enable(int32_t axis) {NotImplemented("axis_Enable");}; 
    virtual void axis_Disable(int32_t axis) {NotImplemented("axis_Disable");}; 
    virtual void axis_BrakeOn(int32_t axis) {NotImplemented("axis_BrakeOn");}; 
    virtual void axis_BrakeOff(int32_t axis) {NotImplemented("axis_BrakeOff");}; 
    virtual void axis_MoveFromLimit(int32_t axis) {NotImplemented("axis_MoveFromLimit");}; 
    virtual void axis_FreeRun(int32_t axis) {NotImplemented("axis_FreeRun");}; 
    virtual void axis_FreeRunStop(int32_t axis) {NotImplemented("axis_FreeRunStop");}; 
    virtual void axis_ThrowAllFaults(int32_t axis) {NotImplemented("axis_ThrowAllFaults");}; 
    virtual void axis_AcknowledgeFaults(int32_t axis) {NotImplemented("axis_AcknowledgeFaults");}; 
    virtual void axis_DataCollectionStart(int32_t axis) {NotImplemented("axis_DataCollectionStart");}; 
    virtual void axis_DataCollectionStop(int32_t axis) {NotImplemented("axis_DataCollectionStop");}; 
    virtual void axis_DataCollectionRefresh(int32_t axis) {NotImplemented("axis_DataCollectionRefresh");}; 
    virtual void axis_DataCollectionGetResults(int32_t axis) {NotImplemented("axis_DataCollectionGetResults");}; 

    // Attributes
	Tango::DevBoolean	*attr_ControllerRunning_read;
	Tango::DevUShort	*attr_AxisCount_read;
	Tango::DevUShort	*attr_TaskCount_read;
	Tango::DevString	*attr_APIVersion_read;
	Tango::DevString	*attr_AeroScriptFilePath_read;
	Tango::DevBoolean	*attr_AxisHealth_read;
	Tango::DevBoolean	*attr_TaskStatus0_read;
	Tango::DevBoolean	*attr_TaskStatus1_read;
	Tango::DevBoolean	*attr_TaskStatus2_read;
	Tango::DevString	*attr_AeroScriptFiles_read;

// TODO: Axis number
// TODO: Move enum definitions
	Tango::DevDouble	*attr_PositionFeedback_read;
	Tango::DevDouble	*attr_VelocityFeedback_read;
	Tango::DevDouble	*attr_AccelerationFeedback_read;
	Tango::DevBoolean	*attr_InPosition_read;
	Tango::DevBoolean	*attr_Enabled_read;
	Tango::DevBoolean	*attr_Homed_read;
	Tango::DevBoolean	*attr_Error_read;
	Tango::DevString	*attr_FirmwareVersion_read;
	Tango::DevDouble	*attr_PositionError_read;
	Tango::DevDouble	*attr_CurrentFeedback_read;
	Tango::DevString	*attr_MotorType_read;
    Tango::DevUShort	*attr_HomeType_read;
	Tango::DevUShort	*attr_MoveType_read;
	Tango::DevDouble	*attr_LastMoveDuration_read;
	Tango::DevDouble	*attr_PositionTarget_read;
	Tango::DevDouble	*attr_VelocityTarget_read;
	Tango::DevDouble	*attr_VelocityError_read;
	Tango::DevDouble	*attr_AccelerationTarget_read;
	Tango::DevDouble	*attr_AccelerationError_read;
	Tango::DevDouble	*attr_CurrentTarget_read;
	Tango::DevDouble	*attr_CurrentError_read;
	Tango::DevDouble	*attr_ServoUpdateRate_read;
	Tango::DevULong	*attr_DataCollectionNumPoints_read;
	Tango::DevUShort	*attr_DataCollectionFrequency_read;
	Tango::DevUShort	*attr_DataCollectionMode_read;
	Tango::DevUShort	*attr_RampType_read;
	Tango::DevUShort	*attr_RampMode_read;
	Tango::DevDouble	*attr_RampValue_read;
	Tango::DevBoolean	*attr_AxisStatus_read;
	Tango::DevBoolean	*attr_AxisFault_read;
	Tango::DevBoolean	*attr_DriveStatus_read;
};


} // namespace A1Bridge_ns