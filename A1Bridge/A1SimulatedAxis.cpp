#include "A1SimulatedAxis.h"


namespace A1Bridge_ns {


A1SimulatedAxis::A1SimulatedAxis():
  m_homed(false),
  m_enabled(false),
  m_moving(true),
  m_in_position(false),
  m_position(0.0),
  m_demand_position(0.0),
  m_max_velocity(SIM_V_MAX_DEFAULT),
  m_current_velocity(0.0),
  m_acceleration(SIM_ACCEL_DEFAULT)
{

}

A1SimulatedAxis::~A1SimulatedAxis()
{

}

void A1SimulatedAxis::update()
{
  // 100ms update
  if (m_moving){
    
  }
  m_position += 0.1;
}

} // namespace A1Bridge_ns
