#ifndef VLI_H
#define VLI_H

#include <cstdint>
#include <iostream>

namespace io
{
	uint64_t read_variable_length_integer(std::istream& in);
}

#endif
