#ifndef READ_H
#define READ_H

#include <iostream>
#include <memory>
#include "logging.h"

namespace io
{
	template <typename T>
	void read_to(std::istream& in, T* buffer, size_t n=1)
	{
		in.read(reinterpret_cast<char*>(buffer), sizeof(T) * n);
		CHECK(!in.fail()) << "failed to read to buffer";
	}

 
	template<typename T, typename std::enable_if<std::is_fundamental<T>::value, T>::type* = nullptr>
	T read(std::istream& in)
	{
		T buffer;
		read_to(in, &buffer);
		return buffer;
	}

	template <typename T>
	std::unique_ptr<T[]> read_array(std::istream& in, size_t n)
	{
		T* buffer = new T[n];
		read_to(in, buffer, n);

		auto array = std::make_unique<T[]>(n);
		for(int i=0; i < n; i++)
		{
			array[i] = buffer[i];
		}
		return array;
	}
}

#endif 
