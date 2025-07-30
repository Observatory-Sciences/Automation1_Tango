#include "A1Bridge.h"
#include "A1Communication.h"
#include "A1Simulation.h"
#if TANGO_VERSION_MAJOR < 10 && TANGO_VERSION_MINOR < 4
    // Maintain compatibility with cppTango 9.3-backports
    #include "log4tango.h"
#else
    #include <common/log4tango/Logger.h>
#endif
#include <mutex>


namespace A1Bridge_ns {


void NotImplemented(const std::string& feature)
{
    Tango::Except::throw_exception("DRIVER_FAILURE",
                                   feature + " not implemented",
                                   feature);
};


bool PeriodicClock::checkAndUpdate(std::chrono::milliseconds interval)
{
    if (m_lastPoll < std::chrono::steady_clock::now() - interval)
    {
        m_lastPoll = std::chrono::steady_clock::now(); 
        return true; 
    }
    return false; 
}


A1Bridge::A1Bridge() : 
    m_connected(false),
    m_simulation(false),
    m_verbose(false),
    attr_Automation1ProgramStopTimeout_read(100),
    attr_Automation1TaskID_read(1) 
{
    attr_APIVersion_read         = Tango::string_dup("");
    attr_AeroScriptFilePath_read = Tango::string_dup("");

    for (unsigned i = 0; i < MAX_AEROSCRIPTS; i++)
    {
        attr_AeroScriptFiles_read[i] = Tango::string_dup(""); 
    }

    attr_AeroScriptFilePath_read = Tango::string_dup("");

    for (unsigned i = 0; i < MAX_AXES; i++)
    {
        attr_axes[i].attr_FirmwareVersion_read = Tango::string_dup("");
        attr_axes[i].attr_MotorType_read       = Tango::string_dup("");
    }
}


std::shared_ptr<A1Bridge> startInstance(bool simulation) 
{
    std::lock_guard<std::mutex> instanceLock(instanceMutex);
    if (instance.get() == nullptr)
    {
        if (simulation)
        {
            std::cout << "Entering simulation mode" << std::endl; 
            instance = std::make_shared<A1Simulation>();
        }
        else
        {
            std::cout << "Entering communication mode" << std::endl; 
            instance = std::make_shared<A1Communication>();
        }
    }

    if(instance.get() == nullptr)
    {
        std::cout << "Failed to create instance (simulation = " << simulation << ")" << std::endl;
    }

    return instance;
}


std::shared_ptr<A1Bridge> getInstance()
{
    std::lock_guard<std::mutex> instanceLock(instanceMutex);
    if (instance.get() == nullptr)
    {
        Tango::Except::throw_exception("DRIVER_FAILURE",
                                   "Bridge not initialised",
                                   __func__);
    }
    return instance; 
}

bool checkInstance()
{
    std::lock_guard<std::mutex> instanceLock(instanceMutex);
    return instance.get() != nullptr;
}

void stopInstance()
{
    std::lock_guard<std::mutex> instanceLock(instanceMutex);
    // delete instance; 
    instance = nullptr; 
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
    this->reconnect_impl();
}


void A1Bridge::checkConnection()
{
    this->checkConnection_impl();
}


std::unique_lock<std::recursive_mutex> A1Bridge::checkConnectionWithLock() {
    auto guard = this->holdConnection_impl();
    this->checkConnection_impl();
    return guard;
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
    this->readController_impl(); 
}


bool A1Bridge::readAxis(unsigned axis)
{
    return this->readAxis_impl(axis); 
}


} // namespace A1Bridge_ns
