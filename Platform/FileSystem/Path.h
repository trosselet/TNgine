#ifndef PATH_H__INCLUDED
#define PATH_H__INCLUDED

#include <Core/include.h>
#include <Filesystem>
#include <string>

namespace TNgine
{
	namespace FileSystem
	{
		class Path
		{
		public:

			Path() = default;
			Path(const char* path);
			Path(const std::string& path);

			std::string String() const;

			Path Parent() const;

			std::string Filename() const;

			std::string Extension() const;

			Path Normalize() const;

			std::string Stem() const;

			Path Absolute() const;

			Path Relative(const Path& base) const;

			Path LexicallyRelative(const Path& base) const;

			bool IsAbsolute() const;

			bool IsRelative() const;

			bool Exists() const;

			bool HasExtension() const;

			bool Empty() const;

			bool StartsWith(const Path& prefix) const;

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
}

namespace std
{
	template<>
	struct hash<TNgine::FileSystem::Path>
	{
		size_t operator()(const TNgine::FileSystem::Path& path) const
		{
			return hash<std::string>{}(path.Normalize().String());
		}
	};
}

#endif // !PATH_H__INCLUDED
