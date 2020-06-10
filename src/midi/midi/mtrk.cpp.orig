#include "midi/midi.h"
/* #include "io/read.h" */
/* #include "io/endianness.h" */

namespace midi
{

    bool is_sysex_event(uint8_t id)
	{
        return id == 0xF0 || id == 0xF7;
	}

    bool is_meta_event(uint8_t id)
	{
        return id == 0xFF;
	}

    bool is_midi_event(uint8_t stat)
	{
        return stat >= 0x80 && stat <= 0xEF;
	}

    bool is_running_status(uint8_t stat)
	{
        return (stat & 0x80) == 0x00;
	}

    uint8_t extract_midi_event_type(uint8_t stat)
    {
        return (stat & 0xF0) >> 4;
    }

    Channel extract_midi_event_channel(uint8_t stat)
    {
        return Channel(stat & 0x0F);
    }

    bool is_note_off(uint8_t type)
    {
        return type == 0x08;
    }

    bool is_note_on(uint8_t type)
    {
        return type == 0x09;
    }

    bool is_polyphonic_key_pressure(uint8_t type)
    {
        return type == 0x0A;
    }

    bool is_control_change(uint8_t type)
    {
        return type == 0x0B;
    }

    bool is_program_change(uint8_t type)
    {
        return type == 0x0C;
    }

    bool is_channel_pressure(uint8_t type)
    {
        return type == 0x0D;
    }

    bool is_pitch_wheel_change(uint8_t type)
    {
        return type == 0x0E;
    }

}
