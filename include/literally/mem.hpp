#pragma once

#include <cstdlib>

namespace literally
{
	namespace mem
	{
		void* operator"" _bytes(unsigned long long int size);
	}
}

#ifdef LITERALLY_MEM_IMPLEMENTATION

namespace literally
{
	namespace mem
	{
		void* operator"" _bytes(unsigned long long int size)
		{
			return malloc(size_t(size));
		}
	}
}

#endif
