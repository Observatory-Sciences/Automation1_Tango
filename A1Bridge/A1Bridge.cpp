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


bool PollClock::checkAndUpdate(std::chrono::milliseconds interval)
{
    if (m_lastPoll < std::chrono::steady_clock::now() - interval)
    {
        m_lastPoll = std::chrono::steady_clock::now(); 
        return true; 
    }
    return false; 
}


A1Bridge* A1Bridge::m_instance = nullptr;


A1Bridge::A1Bridge() : 
    m_connected(false),
    m_initialised(false),
    m_pollInterval_ms(std::chrono::milliseconds(-1)) 
{
    attr_APIVersion_read         = Tango::string_dup("");
    attr_AeroScriptFilePath_read = Tango::string_dup("");

    for (unsigned i = 0; i < 32; i++)
    {
        attr_AeroScriptFiles_read[i] = Tango::string_dup(""); 
    }
    for (unsigned i = 0; i < MAX_AXES; i++)
    {
        attr_axes[i].attr_FirmwareVersion_read = Tango::string_dup("");
        attr_axes[i].attr_MotorType_read       = Tango::string_dup("");
    }
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


void A1Bridge::instanceReady()
{
    m_initialised = true; 
}


bool A1Bridge::checkInstanceReady()
{
    if (m_instance != nullptr)
    {
        return m_instance->m_initialised;
    }
    return false; 
}


A1Bridge* A1Bridge::setSimulation(bool simulation) 
{
    // This method is currently disallowed due to dangling pointer implications. 
    
    // if ((m_instance != nullptr) && (m_instance->isSimulation() != simulation))
    // {
    //     std::cout << "Halted bridge" << std::endl; 
    //     delete m_instance;
    // }

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
    std::cout << "Connected to A1 controller" << std::endl; 
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
    if (m_lastPoll.checkAndUpdate(m_pollInterval_ms))
    {
        this->readController_impl(); 
    }
}


void A1Bridge::readAxis(unsigned axis)
{
    if (m_lastAxisPoll[axis].checkAndUpdate(m_pollInterval_ms))
    {
        this->readAxis_impl(axis); 
    }
}


} // namespace A1Bridge_ns