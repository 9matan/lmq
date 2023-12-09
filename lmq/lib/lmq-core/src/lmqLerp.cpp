#include "lmq/core/lmqLerp.h"

long lmqMapValue( const long val
                , const long inMin
                , const long inMax
                , const long outMin
                , const long outMax)
{
    if(val == inMin) return outMin;

    return ((val - inMin) * (outMax - outMin)) / (inMax - inMin) + outMin;
}