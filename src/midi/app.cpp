#ifndef TEST_BUILD

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <numeric>

#include "imaging/bitmap.h"
#include "imaging/bmp-format.h"
#include "midi/midi.h"

#define NOTE_OFF_RS(note_index, velocity)                      char(note_index), char(velocity)
#define NOTE_OFF(channel, note_index, velocity)                char(0x80 | (channel)), NOTE_OFF_RS(note_index, velocity)
#define NOTE_ON_RS(note_index, velocity)                       char(note_index), char(velocity)
#define NOTE_ON(channel, note_index, velocity)                 char(0x90 | (channel)), NOTE_ON_RS(note_index, velocity)
#define PROGRAM_CHANGE_RS(program)                             char(program)
#define PROGRAM_CHANGE(channel, program)                       char(0xC0 | (channel)), PROGRAM_CHANGE_RS(program)

std::map<int, imaging::Color> gen_colors(std::vector<midi::NOTE> notes)
{
    imaging::Color available_colors[] = {
        imaging::Color(0, 0, 1),
        imaging::Color(0, 1, 0),
        imaging::Color(0, 1, 1),
        imaging::Color(1, 0, 0),
        imaging::Color(1, 0, 1),
        imaging::Color(1, 1, 0),
        imaging::Color(1, 1, 1)
    };
    std::map<int, imaging::Color> colors;
    int i = 0;
    for (midi::NOTE n : notes)
    {
        int ins = value(n.instrument);
        if (colors.count(ins) == 0) {
            colors[ins] = available_colors[i];
            if(i < 7) {
                i++;
            }
        }
    }
    return colors;
}

double gen_max_height(std::vector<midi::NOTE> notes)
{
    std::vector<double> note_ends;
    for (midi::NOTE n : notes) {
        note_ends.push_back(value(n.start) + value(n.duration));
    }
    double max = 0;
    for (double note_end : note_ends) {
        if (note_end > max) {
            max = note_end;
        }
    }
    return max;
}

std::pair<double, double> gen_low_high_notes(std::vector<midi::NOTE> notes)
{
    double max = 0;
    double min = 127;
    for (midi::NOTE n : notes) {
        if (value(n.note_number) > max) {
            max = value(n.note_number);
        }
        if (value(n.note_number) < min) {
            min = value(n.note_number);
        }
    }
    return std::pair<double, double>(min, max);
}

int main(int argn, char** argv)
{
    /* char buffer[] = { */
    /*     'M', 'T', 'h', 'd', */
    /*     0x00, 0x00, 0x00, 0x06, // MThd size */
    /*     0x00, 0x01, // Type */
    /*     0x00, 0x01, // Number of tracks */
    /*     0x01, 0x00, // Division */
    /*     'M', 'T', 'r', 'k', */
    /*     0x00, 0x00, 0x00, 26, // MTrk size */
    /*     0, PROGRAM_CHANGE(0, 1), */
    /*     0, NOTE_ON(0, 5, 120), */
    /*     100, NOTE_OFF(0, 5, 0), */
    /*     0, PROGRAM_CHANGE(0, 2), */
    /*     100, NOTE_ON(0, 8, 100), */
    /*     100, NOTE_ON(0, 8, 0), */
    /*     0, PROGRAM_CHANGE(0, 3), */
    /*     100, NOTE_ON(0, 9, 100), */
    /*     100, NOTE_ON(0, 9, 0), */
    /*     0, char(0xFF), 0x2F, 0x00 */
    /* }; */
    /* std::string data(buffer, sizeof(buffer)); */
    /* std::stringstream ss(data); */
    /* std::vector<midi::NOTE> notes = midi::read_notes(ss); */

    // min=35 max=85 total=45
    // colors 0,30,33
    std::ifstream ifs("dancemonkey.mid");
    std::vector<midi::NOTE> notes = midi::read_notes(ifs);

    auto color_init = [](Position p){return imaging::Color(0, 0, 0); };
    double max_heigth = gen_max_height(notes);
    auto bitmap = imaging::Bitmap(500, max_heigth + 1000, color_init);
    auto colors = gen_colors(notes);
    auto low_high_notes_pair = gen_low_high_notes(notes);
    double low = low_high_notes_pair.first;
    double high = low_high_notes_pair.second;
    for (midi::NOTE note : notes) {
        std::cout << note << "\n";
        double width = 500 / (high - low + 1);
        double height = value(note.duration);
        double x = (value(note.note_number) - low) * width;
        double y = value(note.start);
        auto color = colors[value(note.instrument)];
        auto slice = bitmap.slice(x, y, width, height);
        auto offset = Position(x, y);
        slice->for_each_position([&bitmap, &color, &offset](const Position& p) { bitmap[offset + p] = color; });
    }

    for (double y = 0; y <= max_heigth; y += 5) {
        auto slice = bitmap.slice(0, y, 500, 500);
        std::cout << "outimg/" + std::to_string((int)y) + ".bmp" << "\n";
        imaging::save_as_bmp("outimg/" + std::to_string((int)y) + ".bmp", *slice);
    }
}

#endif
