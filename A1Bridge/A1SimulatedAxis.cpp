#include "A1SimulatedAxis.h"


namespace A1Bridge_ns {


A1SimulatedAxis::A1SimulatedAxis():
  m_homed(false),
  m_enabled(false),
  m_moving(false),
  m_in_position(true),
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
  double delta_t = 0.1;
  double delta_s = 0.0;
  // 100ms update
  if (m_moving){
    // If we will hit the position within 100ms
    // Then simply set velocity to 0, position to demand
    // and moving to false
    delta_s = m_current_velocity / 2.0 * delta_t;

    if (sqrt((m_demand_position - m_position)*(m_demand_position - m_position)) < delta_s){
      m_position = m_demand_position;
      m_current_velocity = 0.0;
      m_moving = false;
      m_in_position = true;
    } else {
      // If we will reach the destination by slowing down then
      // begin to decelerate
      delta_s = (m_current_velocity * m_current_velocity) / 2.0 / m_acceleration;
      if (sqrt((m_demand_position - m_position)*(m_demand_position - m_position)) < delta_s){
        m_current_velocity -= (m_acceleration * delta_t);
      } else {
        // If we are not at max velocity accelerate
        if (m_current_velocity < m_max_velocity){
          m_current_velocity += (m_acceleration * delta_t);
          if (m_current_velocity > m_max_velocity){
            m_current_velocity = m_max_velocity;
          }
        }
      }
      // Update our position
      if (m_demand_position < m_position){
        m_position -= (m_current_velocity * delta_t);
      } else {
        m_position += (m_current_velocity * delta_t);
      }
    }
  }
}

} // namespace A1Bridge_ns
