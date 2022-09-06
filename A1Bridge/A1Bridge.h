#pragma once 

#include <iostream>
#include <string>  
#include <chrono> 
#include <mutex>
#include <tango.h>

#include "A1AxisEnum.h"


#define DEFAULT_TO_SIMULATION false
#define MAX_AXES 32


namespace A1Bridge_ns {


void NotImplemented(const std::string& feature);


class PeriodicClock
{
  private: 
    std::chrono::time_point<std::chrono::steady_clock> m_lastPoll; 
  public: 
    PeriodicClock() : m_lastPoll(std::chrono::steady_clock::time_point::min()) {}; 
    bool checkAndUpdate(std::chrono::milliseconds interval);
};


typedef struct A1AxisAttributes
{
    Tango::DevDouble	                    attr_PositionFeedback_read;
	Tango::DevDouble	                    attr_VelocityFeedback_read;
	Tango::DevDouble	                    attr_AccelerationFeedback_read;
	Tango::DevBoolean	                    attr_InPosition_read;
	Tango::DevBoolean	                    attr_Enabled_read;
	Tango::DevBoolean	                    attr_Homed_read;
	Tango::DevBoolean	                    attr_Error_read;
	Tango::DevString	                    attr_FirmwareVersion_read;
	Tango::DevDouble	                    attr_PositionError_read;
	Tango::DevDouble	                    attr_CurrentFeedback_read;
	Tango::DevString	                    attr_MotorType_read;
    A1Axis_ns::HomeTypeEnum 	            attr_HomeType_read;
    A1Axis_ns::MoveTypeEnum 	            attr_MoveType_read;
	Tango::DevDouble	                    attr_LastMoveDuration_read;
	Tango::DevDouble	                    attr_PositionTarget_read;
	Tango::DevDouble	                    attr_VelocityTarget_read;
	Tango::DevDouble	                    attr_VelocityError_read;
	Tango::DevDouble	                    attr_AccelerationTarget_read;
	Tango::DevDouble	                    attr_AccelerationError_read;
	Tango::DevDouble	                    attr_CurrentTarget_read;
	Tango::DevDouble	                    attr_CurrentError_read;
	Tango::DevDouble	                    attr_ServoUpdateRate_read;
	Tango::DevULong 	                    attr_DataCollectionNumPoints_read;
    A1Axis_ns::DataCollectionFrequencyEnum	attr_DataCollectionFrequency_read;
    A1Axis_ns::DataCollectionModeEnum	    attr_DataCollectionMode_read;
    A1Axis_ns::RampTypeEnum	                attr_RampType_read;
    A1Axis_ns::RampModeEnum	                attr_RampMode_read;
	Tango::DevDouble	                    attr_RampValue_read;
    Tango::DevDouble                        axisStatus; 
	Tango::DevBoolean	                    attr_AxisStatus_read[24];
    Tango::DevDouble                        axisFault; 
	Tango::DevBoolean	                    attr_AxisFault_read[25];
    Tango::DevDouble                        driveStatus; 
	Tango::DevBoolean	                    attr_DriveStatus_read[27];
} A1AxisAttributes; 


class A1Bridge
{
  protected: 
    // Member variables
    bool m_connected; 
    bool m_simulation; 
    bool m_verbose; 
    std::string m_username; 
    std::string m_password; 
    std::string m_ip; 
    std::chrono::milliseconds m_pollInterval_ms;
    PeriodicClock m_lastPoll; 
    PeriodicClock m_lastAxisPoll[MAX_AXES]; 

    // Methods
    A1Bridge(); 
    virtual ~A1Bridge();

    // implementation of connection
    virtual void connect_impl(const std::string& username, const std::string& password, const std::string& ip) {}; 
    virtual void disconnect_impl() {}; 
    virtual void checkConnection_impl() {}; 

    // initialise an axis or controller
    virtual void initialiseController_impl() {};
    virtual void initialiseAxis_impl(unsigned axis) {};

    // clean up an axis or controller
    virtual void deleteController_impl() {}; 
    virtual void deleteAxis_impl(unsigned axis) {}; 

    // read data from axis or controller
    virtual void readController_impl() {NotImplemented(__func__);}; 
    virtual void readAxis_impl(unsigned axis) {NotImplemented(__func__);}; 

  public: 
    // Attributes
	Tango::DevBoolean	attr_ControllerRunning_read;
	Tango::DevUShort	attr_AxisCount_read;
	Tango::DevUShort	attr_TaskCount_read;
	Tango::DevString	attr_APIVersion_read;
	Tango::DevString	attr_AeroScriptFilePath_read;
    
    double              attr_axisHealth;
	Tango::DevBoolean	attr_AxisHealth_read[32];
    double              attr_taskStatus0;
	Tango::DevBoolean	attr_TaskStatus0_read[16];
    double              attr_taskStatus1;
	Tango::DevBoolean	attr_TaskStatus1_read[17];
    double              attr_taskStatus2;
	Tango::DevBoolean	attr_TaskStatus2_read[24];
	Tango::DevString	attr_AeroScriptFiles_read[32];

    A1AxisAttributes attr_axes[MAX_AXES]; 

    // Methods
    bool isSimulation();
    bool isConnected();
    void connect(const std::string& username, const std::string& password, const std::string& ip); 
    void disconnect(); 
    void reconnect(); 
    void checkConnection(); 

    void initialiseController(); 
    void initialiseAxis(unsigned axis); 

    void deleteController(); 
    void deleteAxis(unsigned axis); 

    void readController();
    void readAxis(unsigned axis);
    
    template<class T = int> void setPollingInterval(T interval) 
    {
        m_pollInterval_ms = std::chrono::milliseconds(interval);
    };  

    // Interface between Tango <-> Automation1 API is left up to the derived class
    // We just call the Tango command or retrieve the attributes. 
    // In other words, we do not reimplement the Automation1 API for the simulator. 

    // Commands
    virtual void controller_Reset() 
            {NotImplemented(__func__);}; 
    virtual void controller_Start() 
            {NotImplemented(__func__);}; 
    virtual void controller_Stop() 
            {NotImplemented(__func__);}; 
    virtual void controller_Enable() 
            {NotImplemented(__func__);}; 
    virtual void controller_Disable() 
            {NotImplemented(__func__);}; 
    virtual void controller_ClearErrors() 
            {NotImplemented(__func__);}; 
    virtual void controller_AeroScriptProgramRun(const std::string& file) 
            {NotImplemented(__func__);}; 
    virtual void controller_AeroScriptProgramLoad(const std::string& file) 
            {NotImplemented(__func__);}; 
    virtual void controller_AeroScriptProgramStart() 
            {NotImplemented(__func__);}; 
    virtual void controller_AeroScriptProgramStop() 
            {NotImplemented(__func__);}; 
    virtual void controller_AeroScriptProgramPause() 
            {NotImplemented(__func__);}; 
    virtual void axis_Abort(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_Home(int32_t axis, A1Axis_ns::_HomeTypeEnum homeType) 
            {NotImplemented(__func__);}; 
    virtual void axis_Move(int32_t axis, A1Axis_ns::_MoveTypeEnum moveType, Tango::DevDouble position, Tango::DevDouble velocity) 
            {NotImplemented(__func__);}; 
    virtual void axis_Enable(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_Disable(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_BrakeOn(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_BrakeOff(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_MoveFromLimit(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_FreeRun(int32_t axis, Tango::DevDouble velocity) 
            {NotImplemented(__func__);}; 
    virtual void axis_FreeRunStop(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_ThrowAllFaults(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_AcknowledgeFaults(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_DataCollectionStart(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_DataCollectionStop(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_DataCollectionRefresh(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_DataCollectionGetResults(int32_t axis) 
            {NotImplemented(__func__);}; 

    virtual void axis_WriteRamp(unsigned axis, A1Axis_ns::RampTypeEnum type, A1Axis_ns::RampModeEnum mode, double value)
            {};
};


static std::mutex instanceMutex;
static std::shared_ptr<A1Bridge> instance = nullptr; 
std::shared_ptr<A1Bridge> startInstance(bool simulation); 
std::shared_ptr<A1Bridge> getInstance();
void stopInstance(); 


} // namespace A1Bridge_ns