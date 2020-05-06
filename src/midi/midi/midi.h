#ifndef MIDI_H
#define MIDI_H

#include <cstdint>

namespace midi
{

#pragma pack(push, 1)

    struct CHUNK_HEADER
    {
        char id[4];
        uint32_t size;
    };

#pragma pack(pop)

}

#endif
