#pragma once 

#include <iostream>
#include <mutex>
#include <string>
#include <variant>
#include <map>
#include <tango.h> 

#include "A1Bridge.h"
#include "A1Defines.h"

#include "Automation1.h"

namespace A1Bridge_ns {


// Throws a TANGO error with the last error message from the A1 controller
void throwWithLastA1Error_origin(const std::string& reason, const std::string& origin);

// Macro that includes __func__ as location of error
#define throwWithLastA1Error(reason) throwWithLastA1Error_origin(reason, __func__)


// Macro to call an A1 function and report last A1 error if call returns an error code
#define A1_GENERIC_CALL_AND_THROW(A1F, ...) \
    if (!(A1F)(__VA_ARGS__)) \
    { \
        if (Automation1_IsControllerCommunicationError(Automation1_GetLastError())) \
        { \
            throwWithLastA1Error("Controller communication error"); \
        } \
        else \
        { \
            throwWithLastA1Error("ERROR: " #A1F " failed"); \
        } \
    } 


// Macro to call an A1 function - if error code indicates communication problem, 
// disconnect and then report last A1 error 
#define A1_TRY_CALL_AND_DISCONNECT(A1F, ...) \
    try \
    { \
        A1_GENERIC_CALL_AND_THROW(A1F, __VA_ARGS__); \
    } \
    catch (Tango::DevFailed &e) \
    { \
        if (Automation1_IsControllerCommunicationError(Automation1_GetLastError())) \
        { \
            std::cout << "Call to "#A1F" failed with error: " << e.errors.get_buffer()->desc << std::endl; \
            this->disconnect(); \
        } \
        throw(e); \
    } 


class A1PollConfig
{
    // This class is an RAII wrapper around Automation1StatusConfig_T 
    // which must be allocated and deallocated manually. 
  public: 
    A1PollConfig();
    A1PollConfig(const A1PollConfig&) = delete; 
    ~A1PollConfig(); 
    Automation1StatusConfig_T *get(); 
  private: 
    Automation1StatusConfig_T *m_ptr; 
};


template<typename T> struct Automation1StatusIndexItem
{
    // The item will be retrieved and put into destination.
    double*  destination;
    unsigned index; 
    T        item;  
};
template<typename T> struct Automation1StatusItem
{
    // The item will be retrieved and put into destination.
    double*  destination;
    T        item;  
};


class A1PollManager
{
    // This is a class that is initialised with a set of A1 status items which it then polls all in one go. 
    // Makes use of overloaded push() method during init to dispatch to appropriate container. 
    // Simplifies grouping of status items. 
  private:
    A1PollConfig m_config; 
    unsigned     m_refCount; 
    std::vector<Automation1StatusIndexItem<Automation1AxisStatusItem>> m_axisStatusItems; 
    std::vector<Automation1StatusIndexItem<Automation1TaskStatusItem>> m_taskStatusItems; 
    std::vector<Automation1StatusItem<Automation1SystemStatusItem>>    m_systemStatusItems; 
  public:
    A1PollManager() : m_refCount(0) {};
    ~A1PollManager() = default;
    void push(double* destination, unsigned axis, Automation1AxisStatusItem item); 
    void push(double* destination, unsigned task, Automation1TaskStatusItem item); 
    void push(double* destination, Automation1SystemStatusItem item); 
    void poll(Automation1Controller* controller);
    // All classes need the common polling, so we can't delete common poll manager until no one else is using it. 
    // We use a ref count for this. 
    void incrementRefCount(); 
    void decrementRefCount(); 
    void clear(); 
    size_t size();
};


// TODO: implement task ID 
// TODO: check usage MAX_AXES vs. attr_AxisCount_read (max vs. current)
// TODO: specify a timeout for program pause and stop
class A1Communication: public A1Bridge
{
    // Inherits from A1Bridge and implements communication with Automation1 controller. 
  protected:
    // Rate-limit reconnection attemps; clock and counter
    unsigned                m_connectionRetries;
    PeriodicClock           m_lastReconnectionAttempt; 

    // Automation1 API uses a pointer to controller instance, but we want RAII
    Automation1Controller   m_controller_instance;
    Automation1Controller   *m_controller = &m_controller_instance; 
    
    // We have three sets of polled data to configure: 
    // - common data 
    //      e.g. the controller needs error status of each axis to determine its own 
    //      error state - we only want to poll this once, not once per device
    // - controller-only data
    // - axis-only data (per axis)
    A1PollManager           m_pollManagerCommon; 
    A1PollManager           m_pollManagerController; 
    A1PollManager           m_pollManagerAxis[MAX_AXES];

    // Clock to rate-limit polling of common data
    PeriodicClock           m_lastCommonPoll; 
    
    // Mutex to wrap communication with hardware
    std::recursive_mutex    m_connectionLock;

    virtual void connect_impl(const std::string& username, const std::string& password, const std::string& ip); 
    virtual void disconnect_impl(); 
    virtual void reconnect_impl();
    virtual void checkConnection_impl(); 
    virtual std::unique_lock<std::recursive_mutex> holdConnection_impl();
    virtual bool isConnected(); 

    // Methods to set up controller and axis when connection is initiated
    void onConnectController(); 
    void onConnectAxis(unsigned axis);
    void checkControllerRunning(); 

    virtual void initialiseController_impl(); 
    virtual void initialiseAxis_impl(unsigned axis); 

    virtual void readController_impl(); 
    virtual void readAxis_impl(unsigned axis); 
    
    virtual void deleteController_impl(); 
    virtual void deleteAxis_impl(unsigned axis); 

    void initialiseCommonPolling();
    void readCommon(); 

  public: 
    A1Communication();
    virtual ~A1Communication(); 
    virtual void controller_Reset();
    virtual void controller_Start();
    virtual void controller_Stop();
    virtual void controller_Enable();
    virtual void controller_Disable();
    virtual void controller_ClearErrors();
    virtual void controller_AeroScriptProgramRun(const std::string& file);
    virtual void controller_AeroScriptProgramLoad(const std::string& file);
    virtual void controller_AeroScriptProgramStart();
    virtual void controller_AeroScriptProgramStop();
    virtual void controller_AeroScriptProgramPause();
    virtual void controller_CommandExecute(const std::string& aeroScriptText);
    virtual void axis_Abort(int32_t axis);
    virtual void axis_HomeAsync(int32_t axis);
    virtual void axis_Home(int32_t axis);
    virtual void axis_Move(int32_t axis, A1Axis_ns::_MoveTypeEnum moveType, Tango::DevDouble position, Tango::DevDouble velocity); 
    virtual void axis_Enable(int32_t axis);
    virtual void axis_Disable(int32_t axis);
    virtual void axis_BrakeOn(int32_t axis);
    virtual void axis_BrakeOff(int32_t axis);
    virtual void axis_MoveFromLimit(int32_t axis);
    virtual void axis_FreeRun(int32_t axis, Tango::DevDouble velocity);
    virtual void axis_FreeRunStop(int32_t axis);
    virtual void axis_ThrowAllFaults(int32_t axis);
    virtual void axis_AcknowledgeFaults(int32_t axis);
    virtual void axis_WriteRamp(unsigned axis, A1Axis_ns::RampTypeEnum type, A1Axis_ns::RampModeEnum mode, double value);
    virtual std::string axis_GetA1ParameterString(int32_t axis,int parameterID);
    virtual double axis_GetA1ParameterValue(int32_t axis,int parameterID);
    virtual void axis_SetA1ParameterValue(int32_t axis,int parameterID,double value);
    virtual void axis_SetA1ConfigValue(int32_t axis,int parameterID,double value);
    virtual void axis_SetA1ParameterString(int32_t axis,int parameterID,std::string value);
    virtual void axis_SetA1ConfigString(int32_t axis,int parameterID,std::string value);

  private:
    std::string getFirmwareVersionString(unsigned axis);
    std::string getMotorTypeString(unsigned axis);



};

} // namespace A1Bridge_ns
