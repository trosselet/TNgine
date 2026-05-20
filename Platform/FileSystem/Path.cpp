#include "Path.h"

TNgine::Path::Path() : m_Path()
{
}

TNgine::Path::Path(const char* path) : m_Path(path)
{
}

TNgine::Path::Path(const std::string& path) : m_Path(path)
{
}

std::string TNgine::Path::String() const
{
	return m_Path.generic_string();
}

TNgine::Path TNgine::Path::Parent() const
{
	return Path(m_Path.parent_path().generic_string());
}

std::string TNgine::Path::Filename() const
{
	return m_Path.filename().generic_string();
}

std::string TNgine::Path::Extension() const
{
	return m_Path.extension().generic_string();
}

bool TNgine::Path::IsAbsolute() const
{
	return m_Path.is_absolute();
}

bool TNgine::Path::IsRelative() const
{
	return m_Path.is_relative();
}

TNgine::Path TNgine::Path::Normalize() const
{
	std::filesystem::path p(m_Path);

	p = p.lexically_normal();

	return Path(p.generic_string());
}

bool TNgine::Path::Exists() const
{
	return std::filesystem::exists(m_Path);
}

bool TNgine::Path::HasExtension() const
{
	return m_Path.has_extension();
}

bool TNgine::Path::Empty() const
{
	return m_Path.empty();
}

std::string TNgine::Path::Stem() const
{
	return m_Path.stem().generic_string();
}

TNgine::Path TNgine::Path::Absolute() const
{
	return Path(std::filesystem::absolute(m_Path).generic_string());
}

TNgine::Path TNgine::Path::Relative(const Path& base) const
{
	return Path(std::filesystem::relative(m_Path, base.m_Path).generic_string());
}