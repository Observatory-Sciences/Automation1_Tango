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

    template<class T> void set(T value) 
    {
        switch (m_type)
        {
            case A1AttrVariantDevBoolean:
                m_DevBoolean = static_cast<Tango::DevBoolean*>(value); 
            case A1AttrVariantDevDouble:
                m_DevDouble  = static_cast<Tango::DevDouble*>(value); 
            case A1AttrVariantDevUShort:
                m_DevUShort  = static_cast<Tango::DevUShort*>(value); 
            case A1AttrVariantDevString:
                m_DevString  = static_cast<Tango::DevString*>(value); 
            case A1AttrVariantDevULong:
                m_DevULong   = static_cast<Tango::DevULong*>(value); 
        }
    };
} A1AttrVariant;


enum A1EnumVariantType 
{
    A1EnumVariantAutomation1AxisStatusItem, 
    A1EnumVariantAutomation1DriveStatus,
    A1EnumVariantAutomation1TaskState,
    A1EnumVariantAutomation1TaskStatus0,
    A1EnumVariantAutomation1TaskStatus1,
    A1EnumVariantAutomation1TaskStatus2
};

// Type *should be* inferred when called with Automation1 API. 
class A1EnumVariant 
{
  private:
    A1EnumVariantType      m_type;
    union
    {
        Automation1AxisStatusItem  m_Automation1AxisStatusItem;
        Automation1DriveStatus m_Automation1DriveStatus;
        Automation1TaskState   m_Automation1TaskState;
        Automation1TaskStatus0 m_Automation1TaskStatus0;
        Automation1TaskStatus1 m_Automation1TaskStatus1;
        Automation1TaskStatus2 m_Automation1TaskStatus2;
    };

  public:
    A1EnumVariant(Automation1AxisStatusItem  a): m_Automation1AxisStatusItem(a)  
        {m_type = A1EnumVariantAutomation1AxisStatusItem;};
    A1EnumVariant(Automation1DriveStatus a): m_Automation1DriveStatus(a) 
        {m_type = A1EnumVariantAutomation1DriveStatus;};
    A1EnumVariant(Automation1TaskState   a): m_Automation1TaskState(a)   
        {m_type = A1EnumVariantAutomation1TaskState;};
    A1EnumVariant(Automation1TaskStatus0 a): m_Automation1TaskStatus0(a) 
        {m_type = A1EnumVariantAutomation1TaskStatus0;};
    A1EnumVariant(Automation1TaskStatus1 a): m_Automation1TaskStatus1(a) 
        {m_type = A1EnumVariantAutomation1TaskStatus1;};
    A1EnumVariant(Automation1TaskStatus2 a): m_Automation1TaskStatus2(a) 
        {m_type = A1EnumVariantAutomation1TaskStatus2;};

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
                case A1EnumVariantAutomation1DriveStatus: 
                    return static_cast<T>(m_Automation1DriveStatus);
                case A1EnumVariantAutomation1TaskState: 
                    return static_cast<T>(m_Automation1TaskState);
                case A1EnumVariantAutomation1TaskStatus0: 
                    return static_cast<T>(m_Automation1TaskStatus0);
                case A1EnumVariantAutomation1TaskStatus1: 
                    return static_cast<T>(m_Automation1TaskStatus1);
                case A1EnumVariantAutomation1TaskStatus2: 
                    return static_cast<T>(m_Automation1TaskStatus2);
        }
    }
};


typedef struct A1Attribute
{
    A1AttrVariant attr;
    A1EnumVariant A1Enum; 
} A1Attribute; 
typedef std::pair<std::string, A1Attribute> A1AttributeContainer;


class A1Communication: public A1Bridge
{
  protected:
    unsigned errMessageLength=2048; 
    void connect_impl(std::string username, std::string password, std::string ip); 
    void disconnect_impl(); 
    void readHardware_impl(); 
    void readAxis_impl(); 
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

    void getAxisResult(unsigned axis, double *axisResults, A1AttributeContainer &attr, std::string origin);
    

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
    A1AttributeContainer attr_controllerContainer;
    A1AttributeContainer attr_axisContainer;
        
    // map<std::string, Tango::Attribute*, Automation1AxisStatus> attributes =
        // {{"AxisHomed", &attr_Homed_read, Automation1AxisStatus::Automation1AxisStatus_Homed}}; 


};

} // namespace A1Bridge_ns