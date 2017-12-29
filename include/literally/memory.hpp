#pragma once

#include <cstdlib>

namespace literally
{
	namespace memory
	{
		class block
		{
		public:
			block(size_t size);
			~block();

			operator void*();
			operator size_t();

		private:
			void* memory;
			size_t size;
		};

		inline block operator"" _b(unsigned long long int size);
		inline block operator"" _kb(unsigned long long int size);
		inline block operator"" _Mb(unsigned long long int size);
		inline block operator"" _Gb(unsigned long long int size);
	}
}

#ifdef LITERALLY_MEMORY_IMPLEMENTATION

namespace literally
{
	namespace memory
	{
		block::block(size_t _size) : size(_size)
		{
			this->memory = calloc(this->size, 1);
		}

		block::~block()
		{
			free(this->memory);
		}

		block::operator void*()
		{
			return this->memory;
		}

		block::operator size_t()
		{
			return this->size;
		}

		inline block operator"" _b(unsigned long long int size)
		{
			return block(size_t(size));
		}

		inline block operator"" _kb(unsigned long long int size)
		{
			return operator"" _b(size * 1024);
		}

		inline block operator"" _Mb(unsigned long long int size)
		{
			return operator"" _kb(size * 1024);
		}

		inline block operator"" _Gb(unsigned long long int size)
		{
			return operator"" _Mb(size * 1024);
		}
	}
}

#endif
