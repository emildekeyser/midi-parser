#ifndef TEST_BUILD

#include <iostream>
#include "render.h"
#include "shell/command-line-parser.h"

int main(int argc, char** argv)
{
    Parameters params;
    auto cliparser = shell::CommandLineParser();
    cliparser.add_argument("-v", &params.verbose);
    cliparser.add_argument("-w", &params.width);
    cliparser.add_argument("-h", &params.height);
    cliparser.add_argument("-s", &params.scale);
    cliparser.add_argument("-d", &params.step);
    cliparser.process(argc, argv);
    auto posargs = cliparser.positional_arguments();
    if (posargs.empty()){
        std::cout << "Must at least provide a midi file!" << "\n";
        return 1;
    }
    params.midifile = posargs[0];
    if (posargs.size() == 2){
        params.pattern = posargs[1];
    }

    if (params.verbose) {
        std::cout << "w: " << params.width << "\n"
            << "h: " << params.height << "\n"
            << "s: " << params.scale << "\n"
            << "d: " << params.step << "\n"
            << "midi: " << params.midifile << "\n"
            << "pat: " << params.pattern << "\n";
    }

    render(params);
}
#endif
