#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cstdint>
#include "util/tagged.h"

namespace midi
{
    struct Channel
        : tagged<uint8_t, Channel>,
        equality<Channel>,
        show_value<Channel, int>
        { using tagged::tagged; };

    struct Instrument
        : tagged<uint8_t, Instrument>,
        equality<Instrument>,
        show_value<Instrument, int>
        { using tagged::tagged; };

    struct NoteNumber
        : tagged<uint8_t, NoteNumber>,
        ordered<NoteNumber>,
        show_value<NoteNumber, int>
        { using tagged::tagged; };

    struct Duration
        : tagged<uint64_t, Duration>,
        ordered<Duration>,
        show_value<Duration, int>
        { using tagged::tagged; };

    struct Time
        : tagged<uint64_t, Time>,
        ordered<Time>,
        show_value<Time, int>
        { using tagged::tagged; };

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

#endif
