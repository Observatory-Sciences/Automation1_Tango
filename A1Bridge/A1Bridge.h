#pragma once 

#include <iostream>
#include <string>  
#include <chrono> 
#include <mutex>
#include <tango.h>

#include <A1AxisEnum.h>
#include "A1ControllerEnum.h"
#include "A1Defines.h"


#define DEFAULT_TO_SIMULATION false


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


// NB: The RampType and RampMode are returned from the controller as doubles
//  and will need to be cast to the appropriate enums when read by the axes
typedef struct A1AxisAttributes
{
    Tango::DevDouble                        attr_PositionFeedback_read;
    Tango::DevDouble                        attr_VelocityFeedback_read;
    Tango::DevDouble                        attr_AccelerationFeedback_read;
    Tango::DevBoolean                       attr_InPosition_read;
    Tango::DevBoolean                       attr_Enabled_read;
    Tango::DevBoolean                       attr_Homed_read;
    Tango::DevBoolean                       attr_Error_read;
    Tango::DevString                        attr_FirmwareVersion_read;
    Tango::DevDouble                        attr_PositionError_read;
    Tango::DevDouble                        attr_CurrentFeedback_read;
    Tango::DevString                        attr_MotorType_read;
    A1Axis_ns::MoveTypeEnum                 attr_MoveType_read;
    Tango::DevDouble                        attr_LastMoveDuration_read;
    Tango::DevDouble                        attr_VelocityError_read;
    Tango::DevDouble                        attr_AccelerationTarget_read;
    Tango::DevDouble                        attr_AccelerationError_read;
    Tango::DevDouble                        attr_CurrentTarget_read;
    Tango::DevDouble                        attr_CurrentError_read;
    Tango::DevDouble                        attr_ServoUpdateRate_read;
    Tango::DevDouble                        attr_RampType_read;
    Tango::DevDouble                        attr_RampMode_read;
    Tango::DevDouble                        attr_RampValueTime_read;
    Tango::DevDouble                        attr_RampValueRate_read;
    Tango::DevDouble                        attr_RampValue_read;
        Tango::DevBoolean                       attr_VirtualAxis_read;
    Tango::DevDouble                        axisStatus; 
    Tango::DevBoolean                       attr_AxisStatus_read[32];
    Tango::DevDouble                        axisFault; 
    Tango::DevBoolean                       attr_AxisFault_read[32];
    Tango::DevDouble                        driveStatus; 
    Tango::DevBoolean                       attr_DriveStatus_read[32];
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

    // Methods
    A1Bridge(); 
    virtual ~A1Bridge(){};

    // implementation of connection
    virtual void connect_impl(const std::string& username, const std::string& password, const std::string& ip) {}; 
    virtual void disconnect_impl() {}; 
    virtual void reconnect_impl() {};
    virtual void checkConnection_impl() {}; 
    virtual std::unique_lock<std::recursive_mutex> holdConnection_impl() { return std::unique_lock<std::recursive_mutex>(); };

    // initialise an axis or controller
    virtual void initialiseController_impl() {};
    virtual void initialiseAxis_impl(unsigned axis) {};

    // clean up an axis or controller
    virtual void deleteController_impl() {}; 
    virtual void deleteAxis_impl(unsigned axis) {}; 

    // read data from axis or controller
    virtual void readController_impl() {NotImplemented(__func__);}; 
    virtual bool readAxis_impl(unsigned axis) {NotImplemented(__func__); return false; }; 

  public: 
    // Attributes
    Tango::DevBoolean   attr_ControllerRunning_read;
    Tango::DevUShort    attr_AxisCount_read;
    Tango::DevUShort    attr_TaskCount_read;
    Tango::DevString    attr_APIVersion_read;
    Tango::DevString    attr_AeroScriptFilePath_read;
    unsigned short      attr_Automation1ProgramStopTimeout_read; 
    unsigned short      attr_Automation1TaskID_read; 
    
    double              attr_axisHealth;
    Tango::DevBoolean   attr_AxisHealth_read[MAX_AXES];
    double              attr_taskStatus0[MAX_TASKS];
    Tango::DevBoolean   attr_TaskStatus0_read[TASK0_STATUSES];
    double              attr_taskStatus1[MAX_TASKS];
    Tango::DevBoolean   attr_TaskStatus1_read[TASK1_STATUSES];
    double              attr_taskStatus2[MAX_TASKS];
    Tango::DevBoolean   attr_TaskStatus2_read[TASK2_STATUSES];
    Tango::DevString    attr_AeroScriptFiles_read[MAX_AEROSCRIPTS];
    A1Controller_ns::Automation1TaskStatusEnum attr_Automation1TaskStatus_read;

    A1AxisAttributes attr_axes[MAX_AXES]; 

    // Methods
    virtual bool isSimulation();
    virtual bool isConnected();
    void connect(const std::string& username, const std::string& password, const std::string& ip); 
    void disconnect(); 
    void reconnect(); 
    void checkConnection();
    std::unique_lock<std::recursive_mutex> checkConnectionWithLock(); 

    void initialiseController(); 
    void initialiseAxis(unsigned axis); 

    void deleteController(); 
    void deleteAxis(unsigned axis); 

    void readController();
    bool readAxis(unsigned axis);
    
    virtual void setPollingInterval(std::chrono::milliseconds interval)
            {NotImplemented(__func__);};

    template<class T = int>
    void setPollingInterval_ms(T interval)
    {
        setPollingInterval(std::chrono::milliseconds(interval));
    };
    
    template<class T = unsigned short> void setAutomation1ProgramTimeout_ms(T interval) 
    {
        attr_Automation1ProgramStopTimeout_read = interval;
    };
    
    template<class T = unsigned short> void setTaskID(T taskID) 
    {
        attr_Automation1TaskID_read = taskID;
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
    virtual void controller_CommandExecute(const std::string& aeroScriptText)
            {NotImplemented(__func__);}; 
    virtual void axis_Abort(int32_t axis) 
            {NotImplemented(__func__);}; 
    virtual void axis_HomeAsync(int32_t axis) 
            {NotImplemented(__func__);};
    virtual void axis_Home(int32_t axis) 
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
    virtual std::string axis_GetA1ParameterString(int32_t axis,int parID) {
            NotImplemented(__func__);
            return "";
    }
    virtual double axis_GetA1ParameterValue(int32_t axis,int parID) {
            NotImplemented(__func__);
            return 0;
    }
    virtual void axis_SetA1ParameterValue(int32_t axis,int parID,double val)
            {NotImplemented(__func__);};
    virtual void axis_SetA1ConfigValue(int32_t axis,int parID,double val)
            {NotImplemented(__func__);};
    virtual void axis_SetA1ParameterString(int32_t axis,int parID,std::string val)
            {NotImplemented(__func__);};
    virtual void axis_SetA1ConfigString(int32_t axis,int parID,std::string val)
            {NotImplemented(__func__);};

    virtual double controller_CommandExecuteDouble(const std::string& aeroScriptText)
            {return 0.;};
    virtual int controller_CommandExecuteInt(const std::string& aeroScriptText)
            {return 0;};
    virtual std::string controller_CommandExecuteString(const std::string& aeroScriptText)
            {return "";};


    virtual void axis_WriteRamp(unsigned axis, A1Axis_ns::RampTypeEnum type, A1Axis_ns::RampModeEnum mode, double value)
            {};
};


static std::mutex instanceMutex;
static std::recursive_mutex connectionMutex;
static std::shared_ptr<A1Bridge> instance = nullptr; 
std::shared_ptr<A1Bridge> startInstance(bool simulation); 
std::shared_ptr<A1Bridge> getInstance();
bool checkInstance();
void stopInstance(); 


} // namespace A1Bridge_ns
