#include "A1CommBase.h"

namespace A1BridgeNS {


A1CommBase::A1CommBase()
{
    m_connected = false; 
}


A1CommBase::~A1CommBase()
{}


bool A1CommBase::isSimulation()
{
    return m_simulation;
}


bool A1CommBase::isConnected()
{
    return m_connected;
}


void A1CommBase::connect(std::string username, std::string password, std::string ip)
{
    m_username = username; 
    m_password = password; 
    m_ip = ip; 
    this->connect_impl(username, password, ip); 
    m_connected = true; 
}


void A1CommBase::disconnect()
{
    this->disconnect_impl(); 
    m_connected = false; 
}


void A1CommBase::reconnect()
{
    this->disconnect_impl();
    this->connect_impl(m_username, m_password, m_ip);
}


}