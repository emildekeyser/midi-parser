/* #ifndef VLI_H */
/* #define VLI_H */

#include <memory>
/* #include <bitset> */
#include "io/vli.h"
#include "io/read.h"

namespace io
{
	uint64_t read_variable_length_integer(std::istream& in)
    {
        uint64_t accumulator = 0;
        uint8_t byte = 0;
        uint8_t seven_bits = 0;
        do {
            byte = read<uint8_t>(in);
            /* std::cout << "with msb: " << std::bitset<8>(byte) << std::endl; */
            seven_bits = byte & char(0b01111111);
            /* std::cout << "without msb: " << std::bitset<8>(seven_bits) << std::endl; */
            accumulator <<= 7;
            accumulator |= seven_bits;
            /* std::cout << "accumulator: " << std::bitset<64>(accumulator) << std::endl; */
        } while(byte >= 128);
        return accumulator;
    }
}

/* #endif */
