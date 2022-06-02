#include "A1Bridge.h"
#include "A1Simulation.h"
#include "A1Communication.h"


namespace A1Bridge_ns {


void NotImplemented(std::string feature)
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   feature + " not implemented",
                                   feature + " not implemented");
};



A1Bridge* A1Bridge::m_instance = NULL;


A1Bridge::A1Bridge()
{
    m_connected = false; 
    // TODO: 1000 hours is stupid
    m_lastPoll = std::chrono::steady_clock::now() - std::chrono::hours(1000); 
    m_pollInterval_ms = std::chrono::milliseconds(-1); 
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


void A1Bridge::readHardware()
{
    if (m_lastPoll < std::chrono::steady_clock::now() - m_pollInterval_ms)
    {
        std::cout << "Last poll " << m_lastPoll.time_since_epoch().count() << std::endl; 
        std::cout << "Interval  " << m_pollInterval_ms.count() << std::endl; 
        std::cout << "Now       " << std::chrono::steady_clock::now().time_since_epoch().count() << std::endl; 
        this->readHardware_impl(); 
        m_lastPoll = std::chrono::steady_clock::now(); 
    }
    else
    {
        std::cout << "Not polling" << std::endl; 
    }
}


} // namespace A1Bridge_ns