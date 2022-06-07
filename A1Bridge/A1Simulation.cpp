#include "A1Simulation.h"


namespace A1Bridge_ns {


A1Simulation::A1Simulation()
{
    m_simulation = true;
    m_axes.resize(MAX_NO_OF_AXES);
}


A1Simulation::~A1Simulation()
{}


void A1Simulation::connect_impl(std::string username, std::string password, std::string ip)
{
    m_connected = true; 
    std::cout << "Connected to A1 controller in simulation" << std::endl; 
    attr_ControllerRunning_read = true; 
    std::cout << "Controller is running." << std::endl;
}


void A1Simulation::disconnect_impl()
{
    m_connected = false; 
}

void A1Simulation::axis_Home(int32_t axis) 
{
    // Check the axis number is within index limits
    if (axis < 0 || axis > MAX_NO_OF_AXES)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Home failed - axis out of range", 
                                       "A1Simulation::axis_Home");
    }
    // Check the axis is enabled
    if (!m_axes[axis].m_enabled)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Home failed - axis not enabled", 
                                       "A1Simulation::axis_Home");
    }

    // Set the homed flag for the particular axis
    m_axes[axis].m_homed = true;
} 

void A1Simulation::axis_Move(int32_t axis)
{
    // Check the axis number is within index limits
    if (axis < 0 || axis > MAX_NO_OF_AXES)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Move failed - axis out of range", 
                                       "A1Simulation::axis_Move");
    }
    // Check the axis is enabled
    if (!m_axes[axis].m_enabled)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Move failed - axis not enabled", 
                                       "A1Simulation::axis_Move");
    }

    // Set the internal moving flag true for the axis
    m_axes[axis].m_moving = true;
}

void A1Simulation::axis_Enable(int32_t axis)
{
    // Check the axis number is within index limits
    if (axis < 0 || axis > MAX_NO_OF_AXES)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Enable failed - axis out of range", 
                                       "A1Simulation::axis_Enable");
    }

    // Set the enabled flag for the particular axis
    m_axes[axis].m_enabled = true;
}

void A1Simulation::axis_Disable(int32_t axis)
{
    // Check the axis number is within index limits
    if (axis < 0 || axis > MAX_NO_OF_AXES)
    {
        Tango::Except::throw_exception("Tango_DEVICE_ERROR",
                                       "Automation1_Command_Disable failed - axis out of range", 
                                       "A1Simulation::axis_Disable");
    }

    // Set the enabled flag for the particular axis
    m_axes[axis].m_enabled = false;
}

} // namespace A1Bridge_ns