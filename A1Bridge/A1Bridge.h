#pragma once 

#include <iostream>
#include <string> 
#include <tango.h> 

#include "A1CommBase.h"
#include "A1Simulation.h"
#include "A1Communication.h"

#define DEFAULT_TO_SIMULATION false

namespace A1BridgeNS {

class A1Bridge
{
  private:
    static A1CommBase* A1CommInstance; 

  public: 
    A1Bridge(); 
    ~A1Bridge(); 
    static A1CommBase* getInstance();
    static A1CommBase* getInstance(bool simulation);
    static A1CommBase* setSimulation(bool simulation); 
};

} // namespace A1BridgeNS