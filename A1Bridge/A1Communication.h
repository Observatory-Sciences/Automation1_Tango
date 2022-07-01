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


enum A1AttrVariantType 
{
    A1AttrVariantDevBoolean, 
    A1AttrVariantDevDouble,
    A1AttrVariantDevUShort,
    A1AttrVariantDevString,
    A1AttrVariantDevULong
};

// This class only holds a pointer to a Tango attribute. When the value is 
// retrieved from hardware, we set the value using the pointer. A C++17 variant
// would have done this job nicely for us. 
typedef struct A1AttrVariant
{
  private:
    A1AttrVariantType m_type; 
    union
    {
        Tango::DevBoolean *m_DevBoolean;
        Tango::DevDouble  *m_DevDouble;
        Tango::DevUShort  *m_DevUShort;
        Tango::DevString  *m_DevString;
        Tango::DevULong   *m_DevULong;
    };

  public: 
    A1AttrVariant(Tango::DevBoolean *arg): m_DevBoolean(arg) 
        {m_type = A1AttrVariantDevBoolean;};
    A1AttrVariant(Tango::DevDouble *arg):  m_DevDouble(arg) 
        {m_type = A1AttrVariantDevDouble;};
    A1AttrVariant(Tango::DevUShort *arg):  m_DevUShort(arg) 
        {m_type = A1AttrVariantDevUShort;};
    A1AttrVariant(Tango::DevString *arg):  m_DevString(arg) 
        {m_type = A1AttrVariantDevString;};
    A1AttrVariant(Tango::DevULong *arg):   m_DevULong(arg) 
        {m_type = A1AttrVariantDevULong;};

    template<typename T> void set(T value) 
    {
        switch (m_type)
        {
            case A1AttrVariantDevBoolean:
                *m_DevBoolean = static_cast<Tango::DevBoolean>(value); 
                break; 
            case A1AttrVariantDevDouble:
                *m_DevDouble  = static_cast<Tango::DevDouble>(value); 
                break; 
            case A1AttrVariantDevUShort:
                *m_DevUShort  = static_cast<Tango::DevUShort>(value); 
                break; 
            // case A1AttrVariantDevString:
            //     *m_DevString  = static_cast<Tango::DevString>(value); 
                break; 
            case A1AttrVariantDevULong:
                *m_DevULong   = static_cast<Tango::DevULong>(value); 
                break; 
            default:
                Tango::Except::throw_exception("DRIVER_FAILURE",
                                                "A1AttrVariant::set() fall through",
                                                __func__);
        }
    };
} A1AttrVariant;


enum A1EnumVariantType 
{
    A1EnumVariantAutomation1AxisStatusItem, 
    A1EnumVariantAutomation1TaskStatusItem
};

// Type *should be* inferred when called with Automation1 API. 
class A1EnumVariant 
{
  private:
    A1EnumVariantType      m_type;
    union
    {
        Automation1AxisStatusItem  m_Automation1AxisStatusItem;
        Automation1TaskStatusItem  m_Automation1TaskStatusItem;
        // Automation1DriveStatus m_Automation1DriveStatus;
        // Automation1TaskState   m_Automation1TaskState;
        // Automation1TaskStatus0 m_Automation1TaskStatus0;
        // Automation1TaskStatus1 m_Automation1TaskStatus1;
        // Automation1TaskStatus2 m_Automation1TaskStatus2;
    };

  public:
    A1EnumVariant(Automation1AxisStatusItem  a): m_Automation1AxisStatusItem(a)  
        {m_type = A1EnumVariantAutomation1AxisStatusItem;};
    A1EnumVariant(Automation1TaskStatusItem  a): m_Automation1TaskStatusItem(a)   
        {m_type = A1EnumVariantAutomation1TaskStatusItem;};
    // A1EnumVariant(Automation1DriveStatus a): m_Automation1DriveStatus(a) 
    //     {m_type = A1EnumVariantAutomation1DriveStatus;};
    // A1EnumVariant(Automation1TaskState   a): m_Automation1TaskState(a)   
    //     {m_type = A1EnumVariantAutomation1TaskState;};
    // A1EnumVariant(Automation1TaskStatus0 a): m_Automation1TaskStatus0(a) 
    //     {m_type = A1EnumVariantAutomation1TaskStatus0;};
    // A1EnumVariant(Automation1TaskStatus1 a): m_Automation1TaskStatus1(a) 
    //     {m_type = A1EnumVariantAutomation1TaskStatus1;};
    // A1EnumVariant(Automation1TaskStatus2 a): m_Automation1TaskStatus2(a) 
    //     {m_type = A1EnumVariantAutomation1TaskStatus2;};

    // Automation1AxisStatusItem  get() {return m_Automation1AxisStatusItem;};
    // Automation1DriveStatus get() {return m_Automation1DriveStatus;};
    // Automation1TaskState   get() {return m_Automation1TaskState;};
    // Automation1TaskStatus0 get() {return m_Automation1TaskStatus0;};
    // Automation1TaskStatus1 get() {return m_Automation1TaskStatus1;};
    // Automation1TaskStatus2 get() {return m_Automation1TaskStatus2;};

    template<class T> T get()
    {
        switch (m_type)
        {
                case A1EnumVariantAutomation1AxisStatusItem: 
                    return static_cast<T>(m_Automation1AxisStatusItem);
                case A1EnumVariantAutomation1TaskStatusItem: 
                    return static_cast<T>(m_Automation1TaskStatusItem);

                // case A1EnumVariantAutomation1DriveStatus: 
                //     return static_cast<T>(m_Automation1DriveStatus);
                // case A1EnumVariantAutomation1TaskState: 
                //     return static_cast<T>(m_Automation1TaskState);
                // case A1EnumVariantAutomation1TaskStatus0: 
                //     return static_cast<T>(m_Automation1TaskStatus0);
                // case A1EnumVariantAutomation1TaskStatus1: 
                //     return static_cast<T>(m_Automation1TaskStatus1);
                // case A1EnumVariantAutomation1TaskStatus2: 
                //     return static_cast<T>(m_Automation1TaskStatus2);
        }
    }
};


typedef struct A1Attribute
{
    A1AttrVariant attr;
    A1EnumVariant A1Enum; 
} A1Attribute; 
typedef std::pair<std::string, A1Attribute> A1AttributeContainer;
typedef std::vector<A1AttributeContainer> A1AttributeVector;


class A1Communication: public A1Bridge
{
  protected:
    unsigned                    errMessageLength=2048; 
    Automation1Controller      *m_controller;
	Automation1StatusConfig_T  *m_statusControllerPollConfigOnce; 
    Automation1StatusConfig_T  *m_statusControllerPollConfig;
    Automation1StatusConfig_T  *m_statusAxisPollConfig[MAX_AXES];
    unsigned                    m_statusContollerPollLength; 
    unsigned                    m_statusAxisPollLength; 

    virtual void connect_impl(std::string username, std::string password, std::string ip); 
    virtual void disconnect_impl(); 

    virtual void readController_impl(); 
    virtual void readAxis_impl(unsigned axis); 
    
    virtual void deleteController_impl(); 
    virtual void deleteAxis_impl(unsigned axis); 

    virtual void initialiseController_impl(); 
    virtual void initialiseAxis_impl(unsigned axis); 

    void createPollConfig(Automation1StatusConfig_T **config); 
    void deletePollConfig(Automation1StatusConfig_T **config); 

    void createControllerPollConfig(); 
    void createAxisPollConfig(unsigned axis); 
    void deleteControllerPollConfig(); 
    void deleteAxisPollConfig(unsigned axis); 

    void getAxisResult(unsigned axis, double *axisResults, A1AttributeContainer &attr, std::string origin);
    void getTaskResult(unsigned task, double *controllerResults, A1AttributeContainer &attr, std::string origin);
    void getSystemResult(double *controllerResults, A1AttributeContainer &attr, std::string origin);

    void checkController();

    void throwWithLastA1Error(std::string reason, std::string origin);
    void return_checker(bool ret, std::string strTrue="", std::string strFalse="");

    A1AttributeVector attr_controllerContainer;
    A1AttributeVector attr_axisContainer[MAX_AXES];

  public: 
    A1Communication(); 
    virtual ~A1Communication();
    virtual void controller_Reset();
    virtual void controller_Start();
    virtual void controller_Stop();
    virtual void controller_Enable();
    virtual void controller_Disable();
    virtual void controller_ClearErrors();
    virtual void controller_AeroScriptProgramRun();
    virtual void controller_AeroScriptProgramLoad();
    virtual void controller_AeroScriptProgramStart();
    virtual void controller_AeroScriptProgramStop();
    virtual void controller_AeroScriptProgramPause();
    virtual void axis_Abort(int32_t axis);
    virtual void axis_Home(int32_t axis);
    virtual void axis_Move(int32_t axis);
    virtual void axis_Enable(int32_t axis);
    virtual void axis_Disable(int32_t axis);
    virtual void axis_BrakeOn(int32_t axis);
    virtual void axis_BrakeOff(int32_t axis);
    virtual void axis_MoveFromLimit(int32_t axis);
    virtual void axis_FreeRun(int32_t axis, double vel);
    virtual void axis_FreeRunStop(int32_t axis);
    virtual void axis_ThrowAllFaults(int32_t axis);
    virtual void axis_AcknowledgeFaults(int32_t axis);
    virtual void axis_DataCollectionStart(int32_t axis);
    virtual void axis_DataCollectionStop(int32_t axis);
    virtual void axis_DataCollectionRefresh(int32_t axis);
    virtual void axis_DataCollectionGetResults(int32_t axis);
};

} // namespace A1Bridge_ns