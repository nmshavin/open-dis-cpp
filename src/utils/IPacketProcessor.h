/// Copyright goes here
/// License goes here
/// @author John K. Grant

#pragma once


namespace DIS
{
   class Pdu;

   /// it is the responsibility of the processor to use the packet
   /// because it will be deleted after this call.
   class IPacketProcessor
   {
   public:
      virtual ~IPacketProcessor() {}
      virtual void Process(const Pdu& p)=0;
   };

}
