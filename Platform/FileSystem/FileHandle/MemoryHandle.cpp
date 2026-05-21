#include "MemoryHandle.h"

TNgine::FileSystem::MemoryHandle::MemoryHandle(const DynArray<byte>& data) : FileHandle(), m_Buffer(data), m_Position(0), m_IsOpen(true)
{
}

TNgine::FileSystem::MemoryHandle::~MemoryHandle()
{
	Close();
}

uint64 TNgine::FileSystem::MemoryHandle::Read(void* buffer, uint64 size)
{
	if (size == 0 || buffer == nullptr || m_Position >= m_Buffer.Size() || !m_IsOpen)
	{
		return 0;
	}

	uint64 bytesRead = static_cast<uint64>(std::min(size, m_Buffer.Size() - m_Position));

	memcpy(buffer, m_Buffer.Data() + m_Position, static_cast<uint64>(std::min(size, m_Buffer.Size() - m_Position)));

	m_Position += bytesRead;


	return std::min(size, m_Buffer.Size() - m_Position);
}

uint64 TNgine::FileSystem::MemoryHandle::Write(const void* buffer, uint64 size)
{
	if (size == 0 || buffer == nullptr || !m_IsOpen)
	{
		return 0;
	}

	uint64 requiredSize = m_Position + size;

	if (requiredSize > m_Buffer.Size())
	{
		m_Buffer.Resize(requiredSize);
	}

	memcpy(m_Buffer.Data() + m_Position, buffer, size);

	m_Position += size;

	return size;
}

void TNgine::FileSystem::MemoryHandle::Seek(int64 position, SeekMode seekMode)
{
	if (!m_IsOpen)
	{
		return;
	}

	int64 newPosition = std::clamp<int64>(position, 0, static_cast<int64>(m_Buffer.Size()));

	switch (seekMode)
	{
	case SeekMode::Begin:
		m_Position = static_cast<uint64>(newPosition);
		break;

	case SeekMode::Current:
		m_Position += static_cast<uint64>(newPosition);
		break;

	case SeekMode::End:
		m_Position = m_Buffer.Size() + static_cast<uint64>(newPosition);
	}
}

uint64 TNgine::FileSystem::MemoryHandle::Tell()
{
	return m_Position;
}

uint64 TNgine::FileSystem::MemoryHandle::Size()
{
	return m_Buffer.Size();
}

void TNgine::FileSystem::MemoryHandle::Flush()
{ 
}

bool TNgine::FileSystem::MemoryHandle::IsOpen() const
{
	return m_IsOpen;
} 

void TNgine::FileSystem::MemoryHandle::Close()
{
	m_IsOpen = false;
} 