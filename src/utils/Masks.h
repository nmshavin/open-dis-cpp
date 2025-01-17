/// Copyright goes here
/// License goes here
/// @author John K. Grant

#pragma once


#include <utils/msLibMacro.h>       // for library symbols

namespace DIS
{
   /// the mask that will leave only the typemetric
   /// from an integer representing the Articulation Parameter's parameter type.
   /// this mask is based on the IEEE Std 1278.1-1995
   const unsigned int ARTICULATION_PARAMETER_TYPE_METRIC_MASK = 0x001F;
}

