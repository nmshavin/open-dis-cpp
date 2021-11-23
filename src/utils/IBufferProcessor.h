/// Copyright goes here
/// License goes here
/// @author John K. Grant

#pragma once

#include <utils/Endian.h>

namespace DIS
{
   /// the interface class for handling read operations.
   class IBufferProcessor
   {
   public:
      virtual ~IBufferProcessor() {}
      virtual void Process(const char* buf, unsigned int size, Endian e)=0;
   };
}

