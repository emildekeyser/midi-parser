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

    Time operator +(const Time&, const Duration&);
    Time operator +(const Duration&, const Time&);
    Time& operator +=(Time&, const Duration&);
    Duration operator +(const Duration&, const Duration&);
    Duration& operator +=(Duration&, const Duration&);
    Duration operator -(const Duration&, const Duration&);
    Duration& operator -=(Duration&, const Duration&);
    Duration operator -(const Time&, const Time&);

}

#endif
