#ifndef FILE_HANDLE_H__INCLUDED
#define FILE_HANDLE_H__INCLUDED

#include <fstream>

#include <Core/include.h>
#include "Path.h"

namespace TNgine
{
	namespace FileSystem
	{
		enum class SeekMode
		{
			Begin = std::ios::beg,
			Current = std::ios::cur,
			End = std::ios::end
		};

		enum class FileMode
		{
			Read,
			Write,
			ReadWrite,
			Append
		};

		class FileHandle
		{
		public:
			virtual ~FileHandle() = default;
			virtual uint64 Read(void* buffer, uint64 size) = 0;
			virtual uint64 Write(const void* buffer, uint64 size) = 0;
			virtual void Seek(int64 position, SeekMode seekMode = SeekMode::Begin) = 0;
			virtual uint64 Tell() = 0;
			virtual uint64 Size() = 0;
			virtual void Flush() = 0;
			virtual bool IsOpen() const = 0;
			virtual void Close() = 0; 
			const Path& GetPath() const;

		protected:
			FileHandle() = default;
			FileHandle(const Path& path);

		protected:
			TNgine::FileSystem::Path m_Path;
		};
	}
}


#endif // !FILE_HANDLE_H__INCLUDED