#include "A1Bridge.h"
#include "A1Simulation.h"
#include "A1Communication.h"


namespace A1Bridge_ns {


A1Bridge* A1Bridge::m_instance = NULL;


A1Bridge::A1Bridge()
{
    m_connected = false; 
}


A1Bridge::~A1Bridge()
{
    if (m_instance != NULL)
    {
        delete m_instance;
    }
}


A1Bridge* A1Bridge::getInstance() 
{
    getInstance(DEFAULT_TO_SIMULATION);
}


A1Bridge* A1Bridge::getInstance(bool simulation) 
{
    if (m_instance == NULL)
    {
        if (simulation)
        {
            std::cout << "Entering simulation mode" << std::endl; 
            m_instance = new A1Simulation();
        }
        else
        {
            std::cout << "Entering communication mode" << std::endl; 
            m_instance = new A1Communication();
        }
    }

    return m_instance;
}


A1Bridge* A1Bridge::setSimulation(bool simulation) 
{
    if ((m_instance != NULL) && (m_instance->isSimulation() != simulation))
    {
        std::cout << "Halted bridge" << std::endl; 
        delete m_instance;
    }

    return getInstance(simulation);
}


bool A1Bridge::isSimulation()
{
    return m_simulation;
}


bool A1Bridge::isConnected()
{
    return m_connected;
}


void A1Bridge::connect(std::string username, std::string password, std::string ip)
{
    m_username = username; 
    m_password = password; 
    m_ip = ip; 
    this->connect_impl(username, password, ip); 
    m_connected = true; 
}


void A1Bridge::disconnect()
{
    this->disconnect_impl(); 
    m_connected = false; 
}


void A1Bridge::reconnect()
{
    this->disconnect();
    this->connect(m_username, m_password, m_ip);
}


} // namespace A1Bridge_ns