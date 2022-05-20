#pragma once 

#include <iostream>
#include <string> 
#include <tango.h> 

#include "A1CommBase.h"

namespace A1BridgeNS {

class A1Simulation: public A1CommBase
{
  protected:
    void connect_impl(std::string username, std::string password, std::string ip); 
    void disconnect_impl(); 
  public:
    A1Simulation(); 
    ~A1Simulation(); 
};

} // namespace A1BridgeNS