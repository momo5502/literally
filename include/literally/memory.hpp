#pragma once

#include <cstdlib>
#include <mutex>

namespace literally
{
	inline namespace memory
	{
		class block
		{
		public:
			block(size_t size);
			~block();

			block(block &&) noexcept;
			block(const block&);
			block& operator=(block &&);

			operator bool();
			operator void*();
			operator size_t();
			void* operator*();

		private:
			std::mutex* mutex;
			size_t* count;

			void* memory;
			size_t size;
		};

		inline block operator"" _b(unsigned long long int size);
		inline block operator"" _kb(unsigned long long int size);
		inline block operator"" _Mb(unsigned long long int size);
		inline block operator"" _Gb(unsigned long long int size);

#if defined(LITERALLY_MEMORY_IMPLEMENTATION) || defined(LITERALLY_IMPLEMENTATION)

		block::block(size_t _size) : size(_size)
		{
			this->mutex = new std::mutex;
			std::lock_guard<std::mutex> _(*this->mutex);

			this->count = new size_t(1);
			this->memory = calloc(this->size, 1);
		}

		block::block(block&& obj) noexcept
		{
			this->mutex = nullptr;
			this->count = nullptr;
			this->memory = nullptr;

			this->operator=(std::move(obj));
		}

		block::block(const block& obj)
		{
			std::lock_guard<std::mutex> _(*obj.mutex);
			++*obj.count;
			this->count = obj.count;
			this->mutex = obj.mutex;
			this->memory = obj.memory;
			this->size = obj.size;
		}

		block& block::operator=(block && obj)
		{
			std::lock_guard<std::mutex> _(*obj.mutex);
			this->~block(); // Call the destructor, without destroying the object

			this->count = obj.count;
			this->mutex = obj.mutex;
			this->memory = obj.memory;
			this->size = obj.size;

			obj.mutex = nullptr;
			obj.memory = nullptr;
			obj.count = nullptr;

			return *this;
		}

		block::~block()
		{
			if (!this->mutex) return;

			std::unique_lock<std::mutex> lock(*this->mutex);
			if (!this->count || !this->memory) return;

			if (--*this->count == 0)
			{
				if (this->memory)
				{
					free(this->memory);
				}

				delete this->count;

				lock.unlock();
				delete this->mutex;
			}
		}

		block::operator bool()
		{
			return this->memory != nullptr;
		}

		block::operator void*()
		{
			return this->memory;
		}

		block::operator size_t()
		{
			return this->size;
		}

		void* block::operator*()
		{
			return this->memory;
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

#endif

	}
}
