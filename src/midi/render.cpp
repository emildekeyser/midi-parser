#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <numeric>
#include <iomanip>

#include "imaging/bitmap.h"
#include "imaging/bmp-format.h"
#include "midi/midi.h"
#include "render.h"

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

double gen_total_height(std::vector<midi::NOTE> notes)
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

std::string indexed_filename(int index, std::string pattern)
{
    std::string filename = pattern;
    std::stringstream formatted_index;
    formatted_index << std::setfill('0') << std::setw(5) << index;
    size_t pos = filename.find("%d");
    filename.replace(pos, 2, formatted_index.str());
    return filename;
}

void render(Parameters params)
{
    std::ifstream ifs(params.midifile);
    std::vector<midi::NOTE> notes = midi::read_notes(ifs);

    auto   color_init          = [](Position p){return imaging::Color(0, 0, 0); };
    double total_heigth        = gen_total_height(notes);
    auto   bitmap              = imaging::Bitmap(params.width, total_heigth + params.height, color_init);
    auto   colors              = gen_colors(notes);
    auto   low_high_notes_pair = gen_low_high_notes(notes);
    double low                 = low_high_notes_pair.first;
    double high                = low_high_notes_pair.second;
    double width               = params.width / (high - low + 1);

    for (midi::NOTE note : notes) {

        if (params.verbose)
            std::cout << note << "\n";

        double height = value(note.duration);
        double x      = (value(note.note_number) - low) * width;
        double y      = value(note.start);
        auto   color  = colors[value(note.instrument)];
        auto   slice  = bitmap.slice(x, y, width, height);
        auto   offset = Position(x, y);

        slice->for_each_position([&bitmap, &color, &offset](const Position& p) {
                bitmap[offset + p] = color;
            });
    }

    for (double y = 0; y <= total_heigth; y += params.step) {
        auto slice = bitmap.slice(0, y, params.width, params.height);
        auto filename = indexed_filename(y / params.step, params.pattern);
        if (params.verbose)
            std::cout << filename << "\n";
        imaging::save_as_bmp(filename, *slice);
    }
}
