#define LITERALLY_LIB_DELAY_IMPORT
#define LITERALLY_LIB_IMPLEMENTATION
#include <literally/lib.hpp>

using namespace literally::lib;

int main()
{
	auto kernel = "kernel32"_lib;

	void* memory = kernel.invoke_pascal<LPVOID>("VirtualAlloc", nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	kernel.invoke_pascal<BOOL>("VirtualFree",memory, 0, MEM_RELEASE);

	return 0;
}
