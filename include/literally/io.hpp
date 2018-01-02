#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include <regex>
#include <filesystem>

namespace literally
{
	inline namespace io
	{
		class file
		{
		public:
			file(std::string name, int openmode = std::fstream::in | std::fstream::out | std::fstream::app | std::fstream::binary);

			template <class T>
			file& operator+=(T& t)
			{
				this->stream << t;
				return *this;
			}

			friend std::ostream& operator<<(std::ostream& os, const file& dt);
			operator std::string();
			operator bool();

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

		class files : private std::vector<std::string>
		{
		public:
			files(std::string path);

			std::vector<std::string> filter(std::regex regex);
			std::vector<std::string> filter(std::string regex);

			files::iterator begin();
			files::iterator end();
		};

		files operator"" _files(const char* str, size_t len);

		file operator"" _file(const char* str, size_t len);
		file operator"" _new_file(const char* str, size_t len);

#if defined(LITERALLY_IO_IMPLEMENTATION) || defined(LITERALLY_IMPLEMENTATION)

		file::file(std::string name, int openmode) : stream(name, openmode)
		{

		}

		file::operator bool()
		{
			return this->stream.is_open();
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

		file operator"" _file(const char* str, size_t len)
		{
			std::string filename(str, len);
			return file(filename);
		}

		file operator"" _new_file(const char* str, size_t len)
		{
			std::string filename(str, len);
			return file(filename, std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);
		}

		files::files(std::string path) : std::vector<std::string>()
		{
			for (auto& filename : std::experimental::filesystem::directory_iterator(path))
			{
				this->push_back(filename.path().generic_string());
			}
		}

		std::vector<std::string> files::filter(std::string regex)
		{
			return this->filter(std::regex(regex));
		}

		std::vector<std::string> files::filter(std::regex regex)
		{
			std::vector<std::string> filtered_filenames;

			for (auto& filename : *this)
			{
				if (std::regex_match(filename, regex))
				{
					filtered_filenames.push_back(filename);
				}
			}

			return filtered_filenames;
		}

		files::iterator files::begin()
		{
			return std::vector<std::string>::begin();
		}

		files::iterator files::end()
		{
			return std::vector<std::string>::end();
		}

		files operator"" _files(const char* str, size_t len)
		{
			std::string path(str, len);
			return files(path);
		}

#endif

	}
}