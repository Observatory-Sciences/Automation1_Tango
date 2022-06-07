#pragma once 

#include <iostream>
#include <string> 
#include <tango.h> 


#include "A1Bridge.h"
#include "A1SimulatedAxis.h"

namespace A1Bridge_ns {


/**
 * TODO:  Can the define be read from somewhere?
*/
#define MAX_NO_OF_AXES 32


class A1Simulation: public A1Bridge
{
  protected:
    void connect_impl(std::string username, std::string password, std::string ip); 
    void disconnect_impl(); 
  public:
    A1Simulation(); 
    ~A1Simulation();
    void axis_Home(int32_t axis);
    void axis_Move(int32_t axis);
    void axis_Enable(int32_t axis);
    void axis_Disable(int32_t axis);

  private:
    std::vector<A1SimulatedAxis> m_axes;
};


} // namespace A1Bridge_ns