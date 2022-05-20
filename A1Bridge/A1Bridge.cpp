#include "A1Bridge.h"

namespace A1BridgeNS {


A1Bridge::A1Bridge()
{}


A1Bridge::~A1Bridge()
{
    if (A1CommInstance != NULL)
    {
        delete A1CommInstance;
    }
}


A1CommBase* A1Bridge::A1CommInstance = NULL;


A1CommBase* A1Bridge::getInstance() 
{
    getInstance(DEFAULT_TO_SIMULATION);
}


A1CommBase* A1Bridge::getInstance(bool simulation) 
{
    if (A1CommInstance == NULL)
    {
        if (simulation)
        {
            std::cout << "Entering simulation mode" << std::endl; 
            A1CommInstance = new A1Simulation();
        }
        else
        {
            std::cout << "Entering communication mode" << std::endl; 
            A1CommInstance = new A1Communication();
        }
    }

    return A1CommInstance;
};


A1CommBase* A1Bridge::setSimulation(bool simulation) 
{
    if ((A1CommInstance != NULL) && (A1CommInstance->isSimulation() != simulation))
    {
        std::cout << "Halted bridge" << std::endl; 
        delete A1CommInstance;
    }

    return getInstance(simulation);
};


} // namespace A1BridgeNS