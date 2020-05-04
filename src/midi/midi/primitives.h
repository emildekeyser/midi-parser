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

}

#endif
