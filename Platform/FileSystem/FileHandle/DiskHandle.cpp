#include "DiskHandle.h"

TNgine::FileSystem::DiskHandle::DiskHandle(const Path& path, FileMode mode) : FileHandle(path), m_Mode(mode)
{
	std::ios::openmode openMode = std::ios::binary;

	switch (mode)
	{
		case FileMode::Read:
			openMode |= std::ios::in;
			break;

		case FileMode::Write:
			openMode |= std::ios::out;
			break;

		case FileMode::ReadWrite:
			openMode |= std::ios::in
				| std::ios::out;
			break;

		case FileMode::Append:
			openMode |= std::ios::app;
			break;
	}

	m_FileStream.open(path.String(), openMode);
}

TNgine::FileSystem::DiskHandle::~DiskHandle()
{
	Close();
}

uint64 TNgine::FileSystem::DiskHandle::Read(void* buffer, uint64 size)
{
	if (m_Mode == FileMode::Write || m_Mode == FileMode::Append)
	{
		return 0;
	}

	if (!IsOpen())
	{
		return 0;
	}

	m_FileStream.read(reinterpret_cast<char*>(buffer), static_cast<std::streamsize>(size));

	return static_cast<uint64>(m_FileStream.gcount());
}

uint64 TNgine::FileSystem::DiskHandle::Write(const void* buffer, uint64 size)
{
	if (m_Mode == FileMode::Read)
	{
		return 0;
	}

	if (!IsOpen())
	{
		return 0;
	}

	m_FileStream.write(reinterpret_cast<const char*>(buffer), static_cast<std::streamsize>(size));

	if (!m_FileStream.good())
	{
		return 0;
	}

	return size;
}

void TNgine::FileSystem::DiskHandle::Seek(int64 position, SeekMode seekMode)
{
	m_FileStream.seekg(position, static_cast<std::ios::seekdir>(seekMode));
	m_FileStream.seekp(position, static_cast<std::ios::seekdir>(seekMode));
}

uint64 TNgine::FileSystem::DiskHandle::Tell()
{
	auto pos = m_FileStream.tellg();

	if (pos == -1)
	{
		return 0;
	}

	return static_cast<uint64>(pos);
}

uint64 TNgine::FileSystem::DiskHandle::Size()
{
	if (!IsOpen())
	{
		return 0;
	}

	auto currentPos = m_FileStream.tellg();

	m_FileStream.seekg(0, std::ios::end);

	uint64 size = static_cast<uint64>(m_FileStream.tellg());

	m_FileStream.seekg(currentPos);

	return size;
}

void TNgine::FileSystem::DiskHandle::Flush()
{
	if (m_Mode == FileMode::Read)
	{
		return;
	}

	if (!IsOpen())
	{
		return;
	}

	m_FileStream.flush();
}

bool TNgine::FileSystem::DiskHandle::IsOpen() const
{
	return m_FileStream.is_open();
} 

void TNgine::FileSystem::DiskHandle::Close()
{
	if (m_FileStream.is_open())
	{
		m_FileStream.close();
	}
} 