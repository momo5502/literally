#include <iostream>

#define LITERALLY_IO_IMPLEMENTATION
#include <literally/io.hpp>

using namespace literally::io;

int main()
{
	auto file = "test.txt"_io;
	file += "Hello World";

	std::cout << file << std::endl;
	return 0;
}
