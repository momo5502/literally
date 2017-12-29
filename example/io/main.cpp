#include <iostream>

#define LITERALLY_IO_IMPLEMENTATION
#include <literally/io.hpp>

using namespace literally::io;

int main()
{
	{
		auto file = "test.txt"_file;
		file += "Hello World #1";

		std::cout << file << std::endl;
	}

	{
		auto file = "test.txt"_new_file;
		file += "Hello World #2";

		std::cout << file << std::endl;
	}

	return 0;
}
