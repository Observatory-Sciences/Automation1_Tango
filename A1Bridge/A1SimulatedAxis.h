#pragma once 

#include <iostream>
#include <string> 
#include <tango.h> 


namespace A1Bridge_ns {

#define SIM_V_MAX_DEFAULT 2.0
#define SIM_ACCEL_DEFAULT 1.0

/**
 * @brief Simple class to store simulated axis information
 */
class A1SimulatedAxis
{
  public:
    bool m_homed;
    bool m_enabled;
    bool m_moving;
    double m_position;
    double m_demand_position;
    double m_max_velocity;
    double m_current_velocity;
    double m_acceleration;

    A1SimulatedAxis();
    ~A1SimulatedAxis();
};


} // namespace A1Bridge_ns
