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
    uint8_t running_status = 0;
    while (!end_of_track_reached)
    {
        Duration event_duration = (Duration) io::read_variable_length_integer(in);
        uint8_t event_identifier = io::read<uint8_t>(in);
        if (is_midi_event(event_identifier))
        {
            running_status = event_identifier;
        }

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
        else if (is_midi_event(event_identifier) || is_running_status(event_identifier))
        {
            uint8_t status_byte;
            uint8_t next_byte;
            if (is_running_status(event_identifier))
            {
                status_byte = running_status;
                next_byte = event_identifier;
            }
            else
            {
                status_byte = event_identifier;
                next_byte = io::read<uint8_t>(in);
            }

            uint8_t type = extract_midi_event_type(status_byte);
            Channel channel = extract_midi_event_channel(status_byte);
            if (is_note_on(type))
            {
                NoteNumber note = (NoteNumber) next_byte;
                uint8_t velocity = io::read<uint8_t>(in);
                receiver.note_on(event_duration, channel, note, velocity);
            }
            else if(is_note_off(type))
            {
                NoteNumber note = (NoteNumber) next_byte;
                uint8_t velocity = io::read<uint8_t>(in);
                receiver.note_off(event_duration, channel, note, velocity);
            }
            else if (is_polyphonic_key_pressure(type))
            {
                NoteNumber note = (NoteNumber) next_byte;
                uint8_t pressure = io::read<uint8_t>(in);
                receiver.polyphonic_key_pressure(event_duration, channel, note, pressure);
            }
            else if (is_control_change(type))
            {
                uint8_t controller = next_byte;
                uint8_t value = io::read<uint8_t>(in);
                receiver.control_change(event_duration, channel, controller, value);
            }
            else if (is_program_change(type))
            {
                Instrument instrument = (Instrument) next_byte;
                receiver.program_change(event_duration, channel, instrument);
            }
            else if (is_channel_pressure(type))
            {
                uint8_t pressure = next_byte;
                receiver.channel_pressure(event_duration, channel, pressure);
            }
            else if (is_pitch_wheel_change(type))
            {
                uint8_t lower_bits_right = next_byte;
                uint16_t upper_bits_left = io::read<uint8_t>(in);
                uint16_t value = lower_bits_right;
                upper_bits_left = upper_bits_left << 7;
                value = value | upper_bits_left;
                receiver.pitch_wheel_change(event_duration, channel, value);
            }
        }
    }

}
