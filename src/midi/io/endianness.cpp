#include "io/endianness.h"
#include <cstdint>

namespace io
{
	void switch_endianness(uint16_t* n)
	{
		uint16_t right_byte = *n & 0x00FF;
		uint16_t left_byte = *n & 0xFF00;
		uint16_t byte_to_become_right = left_byte >> 8;
		uint16_t byte_to_become_left = right_byte << 8;
		*n = byte_to_become_left | byte_to_become_right;
	}

	void switch_endianness(uint32_t* n)
	{
		uint32_t bytes[4] = {};
		bytes[0] = *n & 0x000000FF;
		bytes[1] = *n & 0x0000FF00;
		bytes[2] = *n & 0x00FF0000;
		bytes[3] = *n & 0xFF000000;

		bytes[0] <<= 24;
		bytes[1] <<= 8;
		bytes[2] >>= 8;
		bytes[3] >>= 24;

		*n = bytes[0] |
                     bytes[1] |
                     bytes[2] |
                     bytes[3]; 
	}

	void switch_endianness(uint64_t* n)
	{
		uint64_t bytes[8] = {};
		bytes[0] = *n & 0x00000000000000FF;
		bytes[1] = *n & 0x000000000000FF00;
		bytes[2] = *n & 0x0000000000FF0000;
		bytes[3] = *n & 0x00000000FF000000;
		bytes[4] = *n & 0x000000FF00000000;
		bytes[5] = *n & 0x0000FF0000000000;
		bytes[6] = *n & 0x00FF000000000000;
		bytes[7] = *n & 0xFF00000000000000;

		bytes[0] <<= 56;
		bytes[1] <<= 40;
		bytes[2] <<= 24;
		bytes[3] <<= 8;
		bytes[4] >>= 8;
		bytes[5] >>= 24;
		bytes[6] >>= 40;
		bytes[7] >>= 56;

		*n = bytes[0] |
                     bytes[1] |
                     bytes[2] |
                     bytes[3] |
                     bytes[4] |
                     bytes[5] |
                     bytes[6] |
                     bytes[7]; 
	}
}
