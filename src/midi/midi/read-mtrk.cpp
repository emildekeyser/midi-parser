#include "midi/midi.h"
#include "io/read.h"
#include "io/vli.h"
#include <cassert>

void midi::read_mtrk(std::istream& in, EventReceiver& receiver)
{
    midi::CHUNK_HEADER header;
    read_chunk_header(in, &header);
    assert(header_id(header) == "MTrk");

    bool end_of_track_reached = false;
    while (!end_of_track_reached)
    {
        Duration event_duration = (Duration) io::read_variable_length_integer(in);
        uint8_t event_identifier = io::read<uint8_t>(in);

        if (is_meta_event(event_identifier))
        {
            uint8_t type = io::read<uint8_t>(in);
            uint64_t len = io::read_variable_length_integer(in);
            auto data = io::read_array<uint8_t>(in, len);

            receiver.meta(event_duration, type, std::move(data), len);

            if (type == 0x2F) // = end of stream id
            {
                end_of_track_reached = true;
            }
        }
        else if (is_sysex_event(event_identifier))
        {
            uint64_t len = io::read_variable_length_integer(in);
            auto data = io::read_array<uint8_t>(in, len);
            receiver.sysex(event_duration, std::move(data), len);
        }
        /* else if ( event is note on ) */
        /* { */
        /*     data = read note on data */
        /*     receiver.note_on(data) */
        /* } */
        /* ... */
    }

}
