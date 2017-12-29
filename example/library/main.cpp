#define LITERALLY_LIBRARY_DELAY_IMPORT
#define LITERALLY_LIBRARY_IMPLEMENTATION
#include <literally/library.hpp>

using namespace literally::library;

int main()
{
	// Search the kernel32 library or load it, if it's not yet loaded
	auto kernel = "kernel32"_lib;

	// Invoke the VirtualAlloc function
	// kernel32 functions use __stdcall, therefore invoke_pascal is needed
	void* memory = kernel.invoke_pascal<LPVOID>("VirtualAlloc", nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	// Free the allocated memory by invoking VirtualFree
	kernel.invoke_pascal<BOOL>("VirtualFree", memory, 0, MEM_RELEASE);

	// Free the entire library, as we don't need it anymore
	// This is unloads the module and is not necessarily needed, for some libraries this could even break
	"kernel32"_lib.free();

	return 0;
}
