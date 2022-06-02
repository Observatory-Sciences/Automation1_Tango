#include "A1Simulation.h"


namespace A1Bridge_ns {


A1Simulation::A1Simulation()
{
    m_simulation = true;
}


A1Simulation::~A1Simulation()
{}


void A1Simulation::connect_impl(std::string username, std::string password, std::string ip)
{
    m_connected = true; 
}


void A1Simulation::disconnect_impl()
{
    m_connected = false; 
}


} // namespace A1Bridge_ns