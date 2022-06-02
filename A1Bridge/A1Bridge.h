#pragma once 

#include <iostream>
#include <string> 
#include <tango.h> 

#define DEFAULT_TO_SIMULATION false

namespace A1Bridge_ns {


void NotImplemented(std::string feature);


class A1Bridge
{
  protected: 
    static A1Bridge* m_instance; 
    bool m_connected; 
    bool m_simulation; 
    bool m_verbose; 
    std::string m_username; 
    std::string m_password; 
    std::string m_ip; 
    virtual void connect_impl(std::string username, std::string password, std::string ip) {NotImplemented("connect_impl");}; 
    virtual void disconnect_impl() {NotImplemented("disconnect_impl");}; 
    virtual void readHardware_impl() {NotImplemented("readHardware_impl");}; 


  public: 
    A1Bridge();
    virtual ~A1Bridge();
    static A1Bridge* getInstance();
    static A1Bridge* getInstance(bool simulation);
    static A1Bridge* setSimulation(bool simulation); 
    bool isSimulation();
    bool isConnected();
    void connect(std::string username, std::string password, std::string ip); 
    void disconnect(); 
    void reconnect(); 


    // Interface between Tango <-> Automation1 API is left up to the children
    // We just call the Tango command or retrieve the attributes 
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
};

} // namespace A1Bridge_ns