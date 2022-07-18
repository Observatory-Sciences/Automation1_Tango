#include "A1Bridge.h"
#include "A1Communication.h"
#include "A1Simulation.h"


namespace A1Bridge_ns {


void NotImplemented(const std::string& feature)
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   feature + " not implemented",
                                   feature);
};


A1Bridge* A1Bridge::m_instance = nullptr;


A1Bridge::A1Bridge():
    m_connected(false)
{
    // TODO: 1000 hours is stupid here
    m_lastPoll = std::chrono::steady_clock::now() - std::chrono::hours(1000); 
    
    for (unsigned idx = 0; idx < MAX_AXES; idx++)
    {
        m_lastAxisPoll[idx] = m_lastPoll; 
    }

    m_pollInterval_ms = std::chrono::milliseconds(-1); 
}


A1Bridge::~A1Bridge()
{
    if (m_instance != nullptr)
    {
        delete m_instance;
        m_instance = nullptr; 
    }
}


A1Bridge* A1Bridge::getInstance() 
{
    getInstance(DEFAULT_TO_SIMULATION);
}


A1Bridge* A1Bridge::getInstance(bool simulation) 
{
    if (m_instance == nullptr)
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


bool A1Bridge::instanceReady()
{
    return (m_instance != nullptr);
}


A1Bridge* A1Bridge::setSimulation(bool simulation) 
{
    if ((m_instance != nullptr) && (m_instance->isSimulation() != simulation))
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


void A1Bridge::connect(const std::string& username, const std::string& password, const std::string& ip)
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


void A1Bridge::initialiseController()
{
    this->initialiseController_impl(); 
}


void A1Bridge::initialiseAxis(unsigned axis)
{
    this->initialiseAxis_impl(axis); 
}


void A1Bridge::deleteController()
{
    this->deleteController_impl(); 
}


void A1Bridge::deleteAxis(unsigned axis)
{
    this->deleteAxis_impl(axis); 
}


void A1Bridge::readController()
{
    if (m_lastPoll < std::chrono::steady_clock::now() - m_pollInterval_ms)
    {
        this->readController_impl(); 
        m_lastPoll = std::chrono::steady_clock::now(); 
    }
}


void A1Bridge::readAxis(unsigned axis)
{
    if (m_lastAxisPoll[axis] < std::chrono::steady_clock::now() - m_pollInterval_ms)
    {
        this->readAxis_impl(axis); 
        m_lastAxisPoll[axis] = std::chrono::steady_clock::now(); 
    }
}


} // namespace A1Bridge_ns