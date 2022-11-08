#include "A1SimulatedAxis.h"


namespace A1Bridge_ns {


A1SimulatedAxis::A1SimulatedAxis():
  m_homed(false),
  m_braking(false),
  m_freeRunning(false),
  m_enabled(false),
  m_moving(false),
  m_in_position(true),
  m_position(0.0),
  m_demand_position(0.0),
  m_max_velocity(SIM_V_MAX_DEFAULT),
  m_current_velocity(0.0),
  m_demand_velocity(0.0),
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
    int direction = (m_demand_position > m_position) - (m_demand_position < m_position); //1 if need to increase position, -1 if need to decrease position, 0 if in position
    if (std::abs(m_demand_position - m_position) < std::abs(delta_s)){
      m_position = m_demand_position;
      m_current_velocity = 0.0;
      m_moving = false;
      m_in_position = true;
    } else {
      // If we will reach the destination by slowing down then
      // begin to decelerate
      delta_s = (m_current_velocity * m_current_velocity) / 2.0 / m_acceleration;
      if (std::abs(m_demand_position - m_position) < std::abs(delta_s)){
        m_current_velocity -= direction*(m_acceleration * delta_t);
      } else {
        // If we are not at max velocity accelerate
        double delta_v = direction * m_acceleration * delta_t;
        m_current_velocity += delta_v;
        if (std::abs(m_current_velocity) > std::abs(m_max_velocity))
        {
          m_current_velocity = m_max_velocity * ((m_current_velocity > 0) - (m_current_velocity < 0));
        }
      }
      m_position += (m_current_velocity * delta_t);
    }
  }
  else if (m_freeRunning)
  {
    m_in_position = false;
    int direction = (m_demand_velocity > m_current_velocity) - (m_demand_velocity < m_current_velocity); //1 if need to increase velocity, -1 if need to decrease velocity, 0 if at correct velocity
    double delta_v = direction * m_acceleration * delta_t;
    m_current_velocity += delta_v;
    if (std::abs(m_current_velocity) > std::abs(m_demand_velocity) && (m_current_velocity<0)==(m_demand_velocity<0))
    {
      m_current_velocity = m_demand_velocity;
    }
    if (std::abs(m_current_velocity) > std::abs(m_max_velocity))
    {
      m_current_velocity = m_max_velocity * ((m_current_velocity > 0) - (m_current_velocity < 0));
    }
    m_position += (m_current_velocity * delta_t);
  }
  else
  {
    m_current_velocity = 0;
  }
}

} // namespace A1Bridge_ns
