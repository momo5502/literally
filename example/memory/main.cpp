#include <cstring>

#define LITERALLY_MEMORY_IMPLEMENTATION
#include <literally/memory.hpp>

using namespace literally::memory;

int main()
{
	// Allocate 4kb of memory
	// This block is movable, copyable and fully thread-safe
	auto memory = 4_kb;

	// Allocate 1337 bytes and free the previous block
	memory = 1337_b;

	// Check if the block is valid
	if (!memory) return 1;

	size_t size = memory; // Implicit conversion returns the size of the block
	void* ptr = memory;   // Implicit conversion returns a pointer to the allocated memory

	std::memset(ptr, 1, size);
	std::memset(memory, 0, memory); // This works as well

	return 0;
}
