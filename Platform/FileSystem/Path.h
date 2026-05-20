#ifndef PATH_H__INCLUDED
#define PATH_H__INCLUDED

#include <Core/include.h>
#include <Filesystem>
#include <string>

namespace TNgine
{
	class Path
	{
	public:

		Path();
		Path(const char* path);
		Path(const std::string& path);

		std::string String() const;

		Path Parent() const;

		Path Filename() const;

		Path Extension() const;

		Path Normalize() const;

		Path Stem() const;

		Path Absolute() const;

		Path Relative(const Path& base) const;

		bool IsAbsolute() const;

		bool Exists() const;

		bool HasExtension() const; 

		Path& operator=(const char* path)
		{
			m_Path = path;
			return *this;
		}

		Path operator/(const Path& other) const
		{
			return Path((m_Path / other.m_Path).generic_string());
		}

		bool operator==(const Path& other) const
		{
			return Normalize().String() == other.Normalize().String();
		}

		bool operator!=(const Path& other) const
		{
			return !(*this == other);
		}

	private:

		std::filesystem::path m_Path;
	};
}

#endif // !PATH_H__INCLUDED
