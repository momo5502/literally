#include <iostream>

#define LITERALLY_IO_IMPLEMENTATION
#include <literally/io.hpp>

using namespace literally::io;

int main()
{
	{
		// Access the file called test.txt and create it if it doesn't exist
		auto file = "test.txt"_file;

		// Check if the file is valid
		if (!file) return 1;

		// Write to it (or append, if it already existed)
		file += "Hello World #1\n";

		// Print its content to the console
		std::cout << file;
	}

	{
		// Create the file called test.txt or overwrite it, if it already exists
		auto file = "test.txt"_new_file;

		// Check if the file is valid
		if (!file) return 1;

		// Write to it
		file += "Hello World #2\n";

		// Print its content to the console
		std::cout << file;
	}

	std::cout << std::endl;

	// List all files in the current directory
	for (auto& file : "./"_files)
	{
		std::cout << file << std::endl;
	}

	std::cout << std::endl;

	// List all executable files in the current directory
	// The filter is a regular expression
	for (auto& file : "./"_files.filter(".*\\.exe"))
	{
		std::cout << file << std::endl;
	}

	return 0;
}
