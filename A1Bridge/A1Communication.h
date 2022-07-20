#pragma once 

#include <iostream>
#include <string> 
#include <variant> 
#include <map> 
#include <tango.h> 

#include "A1Bridge.h"
#include "A1Defines.h"

#include "Automation1.h"

namespace A1Bridge_ns {


// Helper functions

// Throws a TANGO error with the last error message from the A1 controller
void throwWithLastA1Error_origin(const std::string& reason, const std::string& origin);

// Macro that includes __func__ as location of error
#define throwWithLastA1Error(reason) throwWithLastA1Error_origin(reason, __func__)

// Macro to call an A1 function and report last A1 error if call returns an error code
#define A1_GENERIC_CALL_AND_THROW(A1F, ...) \
    if (!(A1F)(__VA_ARGS__)) \
    { \
        throwWithLastA1Error("ERROR: " #A1F " failed"); \
    } 


class A1PollConfig
{
    // RAII wrapper around Automation1StatusConfig_T 
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
    // The item will be retrieved and put in destination.
    double*  destination;
    unsigned index; 
    T        item;  
};
template<typename T> struct Automation1StatusItem
{
    // The item will be retrieved and put in destination.
    double*  destination;
    T        item;  
};


class A1PollManager
{
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
  protected:
    unsigned                m_programHaltTimeout; 
    unsigned                m_taskID; 

    Automation1Controller   m_controller_instance;
    Automation1Controller   *m_controller = &m_controller_instance; 
    
    // We have three sets of config: 
    // - one for common data like error status of each axis
    // - one for controller-only data
    // - one (per axis) for axis-only data
    A1PollManager           m_pollManagerCommon; 
    A1PollManager           m_pollManagerController; 
    A1PollManager           m_pollManagerAxis[MAX_AXES];

    PollClock m_lastCommonPoll; 
    
    virtual void connect_impl(const std::string& username, const std::string& password, const std::string& ip); 
    virtual void disconnect_impl(); 

    void onConnectController(); 
    void onConnectAxis(unsigned axis);

    virtual void initialiseController_impl(); 
    virtual void initialiseAxis_impl(unsigned axis); 
    
    virtual void readController_impl(); 
    virtual void readAxis_impl(unsigned axis); 
    
    virtual void deleteController_impl(); 
    virtual void deleteAxis_impl(unsigned axis); 

    void initialiseCommonPolling();
    void readCommon(); 

    void checkController();

  public: 
    A1Communication() : m_programHaltTimeout(100), m_taskID(1) {m_simulation = false;}; 
    virtual ~A1Communication() = default;
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
    virtual void axis_Abort(int32_t axis);
    virtual void axis_Home(int32_t axis, A1Axis_ns::_HomeTypeEnum homeType);
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
    virtual void axis_DataCollectionStart(int32_t axis);
    virtual void axis_DataCollectionStop(int32_t axis);
    virtual void axis_DataCollectionRefresh(int32_t axis);
    virtual void axis_DataCollectionGetResults(int32_t axis);
    
    virtual void axis_WriteRamp(unsigned axis, A1Axis_ns::RampTypeEnum type, A1Axis_ns::RampModeEnum mode, double value);
};

} // namespace A1Bridge_ns