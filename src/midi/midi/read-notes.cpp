#include "midi/midi.h"

std::vector<midi::NOTE> midi::read_notes(std::istream& in)
{
    std::vector<midi::NOTE> notes;
    midi::MTHD mthd;
    read_mthd(in, &mthd);
    auto collector_func = [&notes](const midi::NOTE& note) { notes.push_back(note); };
    for (int track = 0; track != mthd.ntracks; track++){
        auto note_collector = NoteCollector(collector_func);
        read_mtrk(in, note_collector);
    }

    return notes;
}
