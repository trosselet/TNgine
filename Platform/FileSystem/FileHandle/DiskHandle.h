#ifndef DISK_HANDLE_H__INCLUDED
#define DISK_HANDLE_H__INCLUDED

#include <Core/include.h> 
#include "../FileHandle.h"

namespace TNgine
{
	namespace FileSystem
	{
		class DiskHandle : public FileHandle
		{
		public:
			DiskHandle(const Path& path, FileMode mode);
			~DiskHandle();
			uint64 Read(void* buffer, uint64 size) override;
			uint64 Write(const void* buffer, uint64 size) override;
			void Seek(int64 position, SeekMode seekMode = SeekMode::Begin) override;
			uint64 Tell() override;
			uint64 Size() override;
			void Flush() override;
			bool IsOpen() const override;
			void Close() override; 

		private:
			std::fstream m_FileStream; 
			FileMode m_Mode;
		};
	}
}


#endif // !DISK_HANDLE_H__INCLUDED
