#pragma once 

#include <iostream>
#include <string> 
#include <tango.h> 
#include <thread>


#include "A1Bridge.h"
#include "A1SimulatedAxis.h"

namespace A1Bridge_ns {


#define SIM_AX_HOMED                           0  //Homed
#define SIM_AX_PROFILING                       1  //Profiling
#define SIM_AX_WAIT_DONE                       2  //WaitDone
#define SIM_AX_COMMAND_VALID                   3  //CommandValid
#define SIM_AX_HOMING                          4  //Homing
#define SIM_AX_ENABLING                        5  //Enabling
#define SIM_AX_JOG_GENERATING                  7  //JogGenerating
#define SIM_AX_JOGGING                         8  //Jogging
#define SIM_AX_DRIVE_PENDING                   9  //DrivePending
#define SIM_AX_DRIVE_ABORT_PENDING             10 //DriveAbortPending
#define SIM_AX_TRAJECTORY_FILTERING            11 //TrajectoryFiltering
#define SIM_AX_IFOV_ENABLED                    12 //IfovEnabled
#define SIM_AX_NOT_VIRTUAL                     13 //NotVirtual
#define SIM_AX_CAL_ENABLED1D                   14 //CalEnabled1D
#define SIM_AX_CAL_ENABLED2D                   15 //CalEnabled2D
#define SIM_AX_CAMMING_GEARING_CONTROL         16 //CammingGearingControl
#define SIM_AX_JOYSTICK_CONTROL                17 //JoystickControl
#define SIM_AX_BACKLASH_ACTIVE                 18 //BacklashActive
#define SIM_AX_GAIN_MAPPING_ENABLED            19 //GainMappingEnabled
#define SIM_AX_MOTION_DONE                     20 //MotionDone
#define SIM_AX_MOTION_CLAMPED                  21 //MotionClamped
#define SIM_AX_GANTRY_ALIGNED                  22 //GantryAligned
#define SIM_AX_GANTRY_DRIVE_CONTROL_REALIGNING 23 //GantryDriveControlRealigning
#define SIM_AX_THERMO_COMP_ENABLED             24 //ThermoCompEnabled

#define SIM_DRV_ENABLED                        0
#define SIM_DRV_IN_POSITION                    21

class A1Simulation: public A1Bridge
{
  protected:
    virtual void connect_impl(std::string username, std::string password, std::string ip); 
    virtual void disconnect_impl(); 
    virtual void initialiseController_impl();
    virtual void initialiseAxis_impl(unsigned axis);
    virtual bool readAxis_impl(unsigned axis);

  public:
    A1Simulation(); 
    virtual ~A1Simulation();
    void run();
    virtual void axis_HomeAsync(int32_t axis);
    virtual void axis_Home(int32_t axis);
    virtual void axis_Move(int32_t axis, A1Axis_ns::_MoveTypeEnum moveType, Tango::DevDouble position, Tango::DevDouble velocity);
    virtual void axis_Enable(int32_t axis);
    virtual void axis_Disable(int32_t axis);

  private:
    std::vector<A1SimulatedAxis> m_axes;
    std::thread *t_ptr;
    std::string m_motor_type;
};


} // namespace A1Bridge_ns
