#include "Path.h"

TNgine::FileSystem::Path::Path() : m_Path()
{
}

TNgine::FileSystem::Path::Path(const char* path) : m_Path(path)
{
}

TNgine::FileSystem::Path::Path(const std::string& path) : m_Path(path)
{
}

std::string TNgine::FileSystem::Path::String() const
{
	return m_Path.generic_string();
}

TNgine::FileSystem::Path TNgine::FileSystem::Path::Parent() const
{
	return Path(m_Path.parent_path().generic_string());
}

std::string TNgine::FileSystem::Path::Filename() const
{
	return m_Path.filename().generic_string();
}

std::string TNgine::FileSystem::Path::Extension() const
{
	return m_Path.extension().generic_string();
}

bool TNgine::FileSystem::Path::IsAbsolute() const
{
	return m_Path.is_absolute();
}

bool TNgine::FileSystem::Path::IsRelative() const
{
	return m_Path.is_relative();
}

TNgine::FileSystem::Path TNgine::FileSystem::Path::Normalize() const
{
	std::filesystem::path p(m_Path);

	p = p.lexically_normal();

	return Path(p.generic_string());
}

bool TNgine::FileSystem::Path::Exists() const
{
	return std::filesystem::exists(m_Path);
}

bool TNgine::FileSystem::Path::HasExtension() const
{
	return m_Path.has_extension();
}

bool TNgine::FileSystem::Path::Empty() const
{
	return m_Path.empty();
}

std::string TNgine::FileSystem::Path::Stem() const
{
	return m_Path.stem().generic_string();
}

TNgine::FileSystem::Path TNgine::FileSystem::Path::Absolute() const
{
	return Path(std::filesystem::absolute(m_Path).generic_string());
}

TNgine::FileSystem::Path TNgine::FileSystem::Path::Relative(const Path& base) const
{
	return Path(std::filesystem::relative(m_Path, base.m_Path).generic_string());
}