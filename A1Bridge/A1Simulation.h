#pragma once 

#include <iostream>
#include <string> 
#include <tango.h> 

#include "A1Bridge.h"

namespace A1Bridge_ns {

class A1Simulation: public A1Bridge
{
  protected:
    void connect_impl(std::string username, std::string password, std::string ip); 
    void disconnect_impl(); 
  public:
    A1Simulation(); 
    ~A1Simulation(); 
};

} // namespace A1Bridge_ns