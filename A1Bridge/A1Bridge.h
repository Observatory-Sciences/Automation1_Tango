#pragma once 

#include <iostream>
#include <string> 
#include <tango.h> 

#define DEFAULT_TO_SIMULATION false

namespace A1BridgeNS {


class NotImplemented: public std::logic_error
{
public:
    NotImplemented(): std::logic_error("Method has not been implemented in child class") {};
};


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
    virtual void connect_impl(std::string username, std::string password, std::string ip) {throw NotImplemented();}; 
    virtual void disconnect_impl() {throw NotImplemented();}; 

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
    virtual void controller_Reset() {throw NotImplemented();}; 
    virtual void controller_Start() {throw NotImplemented();}; 
    virtual void controller_Stop() {throw NotImplemented();}; 
    virtual void controller_Enable() {throw NotImplemented();}; 
    virtual void controller_Disable() {throw NotImplemented();}; 
    virtual void controller_ClearErrors() {throw NotImplemented();}; 
    virtual void controller_AeroScriptProgramRun() {throw NotImplemented();}; 
    virtual void controller_AeroScriptProgramLoad() {throw NotImplemented();}; 
    virtual void controller_AeroScriptProgramStart() {throw NotImplemented();}; 
    virtual void controller_AeroScriptProgramStop() {throw NotImplemented();}; 
    virtual void controller_AeroScriptProgramPause() {throw NotImplemented();}; 
    virtual void axis_Abort(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_Home(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_Move(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_Enable(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_Disable(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_BrakeOn(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_BrakeOff(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_MoveFromLimit(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_FreeRun(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_FreeRunStop(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_ThrowAllFaults(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_AcknowledgeFaults(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_DataCollectionStart(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_DataCollectionStop(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_DataCollectionRefresh(int32_t axis) {throw NotImplemented();}; 
    virtual void axis_DataCollectionGetResults(int32_t axis) {throw NotImplemented();}; 
};

} // namespace A1BridgeNS