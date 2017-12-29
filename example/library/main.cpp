#define LITERALLY_LIBRARY_DELAY_IMPORT
#define LITERALLY_LIBRARY_IMPLEMENTATION
#include <literally/library.hpp>

using namespace literally::library;

int main()
{
	auto kernel = "kernel32"_lib;

	void* memory = kernel.invoke_pascal<LPVOID>("VirtualAlloc", nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	kernel.invoke_pascal<BOOL>("VirtualFree", memory, 0, MEM_RELEASE);

	"kernel32"_lib.free();

	return 0;
}
