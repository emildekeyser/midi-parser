#ifndef RENDERING
#define RENDERING

#include <string>

struct Parameters 
{
    bool verbose;
    unsigned width;
    unsigned height;
    unsigned step;
    unsigned scale;
    std::string midifile;
    std::string pattern;
    Parameters() : verbose(false),
        width(500),
        height(500),
        step(5),
        scale(100),
        pattern("outimg/%d.bmp") {}
};

void render(Parameters);

#endif
