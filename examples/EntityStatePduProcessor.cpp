#include "EntityStatePduProcessor.h"

#include <iostream>

using namespace Example;

void EntityStatePduProcessor::Process(const DIS::Pdu& packet)
{
   const DIS::EntityStatePdu& espdu = static_cast<const DIS::EntityStatePdu&>( packet );
   if( espdu.getTimestamp() % 10 )
   {
       std::cout << "id: " << espdu.getEntityID().getEntityNumber();
      const DIS::Vector3Double& position = espdu.getEntityLocation();
      std::cout << "\tx:" << position.getX()
                << "\ty:" << position.getY()
                << "\tz:" << position.getZ()
                << std::endl;
   }
}
