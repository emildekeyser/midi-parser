#include "midi/midi.h"
#include "io/read.h"
#include "io/endianness.h"

namespace midi
{

    void read_chunk_header(std::istream& ss, midi::CHUNK_HEADER* header)
    {
        auto buf = io::read_array<char>(ss, 4);
        header->id[0] = buf[0];
        header->id[1] = buf[1];
        header->id[2] = buf[2];
        header->id[3] = buf[3];
        header->size = io::read<uint32_t>(ss);
        io::switch_endianness(&(header->size));
    }

    std::string header_id(midi::CHUNK_HEADER header)
    {
        return std::string(header.id, sizeof(header.id));
    }

}
