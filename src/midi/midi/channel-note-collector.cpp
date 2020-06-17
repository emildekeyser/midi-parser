#include "midi/midi.h"

midi::ChannelNoteCollector::ChannelNoteCollector(Channel channel, std::function<void(const NOTE&)> note_receiver)
    : _channel(channel), _note_receiver(note_receiver){}

void midi::ChannelNoteCollector::note_on(Duration duration, Channel channel, NoteNumber note_number, uint8_t velocity)
{
    if (velocity == 0) {
        this->note_off(duration, channel, note_number, velocity);
        return;
    }

    this->_current_time += duration;
    if (channel == this->_channel)
    {
        if (this->_notes[note_number].velocity != 0){
            this->note_off(Duration(0), channel, note_number, 0);
        }
        this->_notes[note_number].instrument = this->_current_instrument;
        this->_notes[note_number].duration = Duration(0);
        this->_notes[note_number].start = this->_current_time;
        this->_notes[note_number].note_number = note_number;
        this->_notes[note_number].velocity = velocity;
    }
}

void midi::ChannelNoteCollector::note_off(Duration duration, Channel channel, NoteNumber note_number, uint8_t velocity)
{
    if (channel == this->_channel && (_notes.empty() || this->_notes[note_number].velocity == 0))
        return;

    this->_current_time += duration;
    if (channel == this->_channel)
    {
        _notes[note_number].duration = this->_current_time - this->_notes[note_number].start;
        this->_note_receiver(_notes[note_number]);
        this->_notes[note_number].velocity = 0;
    }
}

void midi::ChannelNoteCollector::program_change(Duration duration, Channel channel, Instrument instrument)
{
    this->_current_time += duration;
    if (channel == this->_channel)
    {
        this->_current_instrument = instrument;
    }
}

void midi::ChannelNoteCollector::polyphonic_key_pressure(Duration duration, Channel channel, NoteNumber note, uint8_t pressure)
	{this->_current_time += duration; }
void midi::ChannelNoteCollector::control_change(Duration duration, Channel channel, uint8_t controller, uint8_t value)
	{this->_current_time += duration; }
void midi::ChannelNoteCollector::channel_pressure(Duration duration, Channel channel, uint8_t pressure)
	{this->_current_time += duration; }
void midi::ChannelNoteCollector::pitch_wheel_change(Duration duration, Channel channel, uint16_t value)
	{this->_current_time += duration; }
void midi::ChannelNoteCollector::meta(Duration duration, uint8_t type, std::unique_ptr<uint8_t[]> data, uint64_t data_size)
	{this->_current_time += duration; }
void midi::ChannelNoteCollector::sysex(Duration duration, std::unique_ptr<uint8_t[]> data, uint64_t data_size)
	{this->_current_time += duration; }
