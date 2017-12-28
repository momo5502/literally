#define LITERALLY_MEM_IMPLEMENTATION
#include <literally/mem.hpp>

using namespace literally::mem;

int main()
{
	void* memory = 100_bytes;
	free(memory);

	return 0;
}
