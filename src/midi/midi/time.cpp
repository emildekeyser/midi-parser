#include "midi/primitives.h"

namespace midi
{

    Time operator +(const Time& t, const Duration& d)
    {
        return Time(value(t) + value(d));
    }

    Time operator +(const Duration& d, const Time& t)
    {
        return Time(value(t) + value(d));
    }

    Time& operator +=(Time& t, const Duration& d)
    {
        t = t + d;
        return t;
    }

    Duration operator +(const Duration& d1, const Duration& d2)
    {
        return Duration(value(d1) + value(d2));
    }

    Duration& operator +=(Duration& d1, const Duration& d2)
    {
        d1 = d1 + d2;
        return d1;
    }

    Duration operator -(const Duration& d1, const Duration& d2)
    {
        return Duration(value(d1) - value(d2));
    }

    Duration& operator -=(Duration& d1, const Duration& d2)
    {
        d1 = d1 - d2;
        return d1;
    }

    Duration operator -(const Time& t1, const Time& t2)
    {
        /* auto tmp = value(t1) - value(t2); */
        /* if(tmp < 0) */
        /*     tmp = -tmp; */
        /* return Duration(tmp); */
        return Duration(value(t1) - value(t2));
    }

}
