#include "midi/midi.h"
#include "io/read.h"
#include "io/endianness.h"

namespace midi
{

    void read_mthd(std::istream& is, MTHD* mthd)
    {
        read_chunk_header(is, &(mthd->header));
        mthd->type = io::read<uint16_t>(is);
        mthd->ntracks = io::read<uint16_t>(is);
        mthd->division = io::read<uint16_t>(is);
        io::switch_endianness(&(mthd->type));
        io::switch_endianness(&(mthd->ntracks));
        io::switch_endianness(&(mthd->division));
    }

}
