#pragma once 

#include <iostream>
#include <string> 
// #include <tango.h> 

namespace A1BridgeNS {

class NotImplemented: public std::logic_error
{
public:
    NotImplemented(): std::logic_error("Method has not been implemented in child class") {};
};


class A1CommBase
{
  protected: 
    bool m_connected; 
    bool m_simulation; 
    std::string m_username; 
    std::string m_password; 
    std::string m_ip; 
    virtual void connect_impl(std::string username, std::string password, std::string ip) {throw NotImplemented();}; 
    virtual void disconnect_impl() {throw NotImplemented();}; 


  public: 
    A1CommBase();
    virtual ~A1CommBase();
    bool isSimulation();
    bool isConnected();
    void connect(std::string username, std::string password, std::string ip);
    void disconnect();
    void reconnect();

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

//================================================================
//  State                   |  Inherited (no method)
//  Status                  |  Inherited (no method)
//  Reset                   |  reset
//  Start                   |  start
//  Stop                    |  stop
//  Enable                  |  enable
//  Disable                 |  disable
//  ClearErrors             |  clear_errors
//  AeroScriptProgramRun    |  aero_script_program_run
//  AeroScriptProgramLoad   |  aero_script_program_load
//  AeroScriptProgramStart  |  aero_script_program_start
//  AeroScriptProgramStop   |  aero_script_program_stop
//  AeroScriptProgramPause  |  aero_script_program_pause
//================================================================
//  State                     |  Inherited (no method)
//  Status                    |  Inherited (no method)
//  Abort                     |  abort
//  Home                      |  home
//  Move                      |  move
//  Enable                    |  enable
//  Disable                   |  disable
//  BrakeOn                   |  brake_on
//  BrakeOff                  |  brake_off
//  MoveFromLimit             |  move_from_limit
//  FreeRun                   |  free_run
//  FreeRunStop               |  free_run_stop
//  ThrowAllFaults            |  throw_all_faults
//  AcknowledgeFaults         |  acknowledge_faults
//  DataCollectionStart       |  data_collection_start
//  DataCollectionStop        |  data_collection_stop
//  DataCollectionRefresh     |  data_collection_refresh
//  DataCollectionGetResults  |  data_collection_get_results
//================================================================
//  ControllerRunning   |  Tango::DevBoolean	Scalar
//  AxisCount           |  Tango::DevUShort	Scalar
//  TaskCount           |  Tango::DevUShort	Scalar
//  APIVersion          |  Tango::DevString	Scalar
//  AeroScriptFilePath  |  Tango::DevString	Scalar
//  AxisHealth          |  Tango::DevBoolean	Spectrum  ( max = 32)
//  TaskStatus0         |  Tango::DevBoolean	Spectrum  ( max = 16)
//  TaskStatus1         |  Tango::DevBoolean	Spectrum  ( max = 17)
//  TaskStatus2         |  Tango::DevBoolean	Spectrum  ( max = 24)
//  AeroScriptFiles     |  Tango::DevString	Spectrum  ( max = 32)
//================================================================
//  PositionFeedback         |  Tango::DevDouble	Scalar
//  VelocityFeedback         |  Tango::DevDouble	Scalar
//  AccelerationFeedback     |  Tango::DevDouble	Scalar
//  InPosition               |  Tango::DevBoolean	Scalar
//  Enabled                  |  Tango::DevBoolean	Scalar
//  Homed                    |  Tango::DevBoolean	Scalar
//  Error                    |  Tango::DevBoolean	Scalar
//  FirmwareVersion          |  Tango::DevString	Scalar
//  PositionError            |  Tango::DevDouble	Scalar
//  CurrentFeedback          |  Tango::DevDouble	Scalar
//  MotorType                |  Tango::DevString	Scalar
//  HomeType                 |  Tango::DevEnum	Scalar
//  MoveType                 |  Tango::DevEnum	Scalar
//  LastMoveDuration         |  Tango::DevDouble	Scalar
//  PositionTarget           |  Tango::DevDouble	Scalar
//  VelocityTarget           |  Tango::DevDouble	Scalar
//  VelocityError            |  Tango::DevDouble	Scalar
//  AccelerationTarget       |  Tango::DevDouble	Scalar
//  AccelerationError        |  Tango::DevDouble	Scalar
//  CurrentTarget            |  Tango::DevDouble	Scalar
//  CurrentError             |  Tango::DevDouble	Scalar
//  ServoUpdateRate          |  Tango::DevDouble	Scalar
//  DataCollectionNumPoints  |  Tango::DevULong	Scalar
//  DataCollectionFrequency  |  Tango::DevEnum	Scalar
//  DataCollectionMode       |  Tango::DevEnum	Scalar
//  RampType                 |  Tango::DevEnum	Scalar
//  RampMode                 |  Tango::DevEnum	Scalar
//  RampValue                |  Tango::DevDouble	Scalar
//  AxisStatus               |  Tango::DevBoolean	Spectrum  ( max = 24)
//  AxisFault                |  Tango::DevBoolean	Spectrum  ( max = 25)
//  DriveStatus              |  Tango::DevBoolean	Spectrum  ( max = 27)
//================================================================



} // namespace A1BridgeNS