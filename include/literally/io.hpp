#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace literally
{
	namespace io
	{
		class file
		{
		public:
			file(std::string name);

			template <class T>
			file& operator+=(T& t)
			{
				this->stream << t;
				return *this;
			}

			friend std::ostream& operator<<(std::ostream& os, const file& dt);
			operator std::string();

			template <class T>
			void write(T& data)
			{
				this->stream << data;
			}

			size_t size();
			std::string read();

		private:
			std::fstream stream;
		};

		file operator"" _io(const char* str, size_t len);
	}
}

#ifdef LITERALLY_IO_IMPLEMENTATION

namespace literally
{
	namespace io
	{
		file::file(std::string name) : stream(name, std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary)
		{

		}

		file::operator std::string()
		{
			return this->read();
		}

		std::ostream& operator<<(std::ostream& stream, const file& f)
		{
			stream << const_cast<file*>(&f)->read();
			return stream;
		}

		size_t file::size()
		{
			this->stream.seekg(0, std::ios::end);
			size_t result = size_t(this->stream.tellg());
			this->stream.seekg(0, std::ios::beg);

			return result;
		}

		std::string file::read()
		{
			std::string data;
			data.reserve(this->size());
			data.assign((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

			return data;
		}

		file operator"" _io(const char* str, size_t len)
		{
			std::string filename(str, len);
			return file(filename);
		}
	}
}

#endif