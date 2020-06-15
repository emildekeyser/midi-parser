#include "midi/midi.h"

midi::NoteCollector::NoteCollector(std::function<void(const NOTE&)> note_receiver)
{
    std::vector<std::shared_ptr<EventReceiver>> evrecs;
    for (int ch = 0; ch != 16; ch++)
    {
        auto er = std::make_shared<ChannelNoteCollector>(Channel(ch), note_receiver);
        evrecs.push_back(er);
    }
    this->_multicaster = EventMulticaster(evrecs);
}

void midi::NoteCollector::note_on(Duration dt, Channel channel, NoteNumber note, uint8_t velocity)
{
    this->_multicaster.note_on(dt, channel, note, velocity);
}

void midi::NoteCollector::note_off(Duration dt, Channel channel, NoteNumber note, uint8_t velocity)
{
    this->_multicaster.note_off(dt, channel, note, velocity);
}

void midi::NoteCollector::polyphonic_key_pressure(Duration dt, Channel channel, NoteNumber note, uint8_t pressure)
{
    this->_multicaster.polyphonic_key_pressure(dt, channel, note, pressure);
}

void midi::NoteCollector::control_change(Duration dt, Channel channel, uint8_t controller, uint8_t value)
{
    this->_multicaster.control_change(dt, channel, controller, value);
}

void midi::NoteCollector::program_change(Duration dt, Channel channel, Instrument program)
{
    this->_multicaster.program_change(dt, channel, program);
}

void midi::NoteCollector::channel_pressure(Duration dt, Channel channel, uint8_t pressure)
{
    this->_multicaster.channel_pressure(dt, channel, pressure);
}

void midi::NoteCollector::pitch_wheel_change(Duration dt, Channel channel, uint16_t value)
{
    this->_multicaster.pitch_wheel_change(dt, channel, value);
}

void midi::NoteCollector::meta(Duration dt, uint8_t type, std::unique_ptr<uint8_t[]> data, uint64_t data_size)
{
    this->_multicaster.meta(dt, type, std::move(data), data_size);
}

void midi::NoteCollector::sysex(Duration dt, std::unique_ptr<uint8_t[]> data, uint64_t data_size)
{
    this->_multicaster.sysex(dt, std::move(data), data_size);
}
