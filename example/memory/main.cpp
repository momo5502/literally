#include <cstring>

#define LITERALLY_MEMORY_IMPLEMENTATION
#include <literally/memory.hpp>

using namespace literally::memory;

int main()
{
	auto memory = 4_kb; // Allocate 4kb of memory

	size_t size = memory; // Implicit conversion returns the size of the block
	void* ptr = memory;   // Implicit conversion returns a pointer to the allocated memory

	std::memset(ptr, 1, size);
	std::memset(memory, 0, memory); // This also works

	return 0;
}
