#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cstdint>
#include "util/tagged.h"

namespace midi
{
    struct Channel
        : tagged<uint8_t, Channel>, equality<Channel>, show_value<Channel, int>
        { using tagged::tagged; };
}

#endif
