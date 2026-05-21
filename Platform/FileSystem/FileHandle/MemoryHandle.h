#ifndef MEMORY_HANDLE_H__INCLUDED
#define MEMORY_HANDLE_H__INCLUDED

#include <Core/include.h> 
#include "../FileHandle.h"

namespace TNgine
{
	namespace FileSystem
	{
		class MemoryHandle : public FileHandle
		{
		public:
			MemoryHandle(const DynArray<byte>& data);
			~MemoryHandle();
			uint64 Read(void* buffer, uint64 size) override;
			uint64 Write(const void* buffer, uint64 size) override;
			void Seek(int64 position, SeekMode seekMode = SeekMode::Begin) override;
			uint64 Tell() override;
			uint64 Size() override;
			void Flush() override;
			bool IsOpen() const override; 
			void Close() override; 

		private:
			DynArray<byte> m_Buffer;
			uint64 m_Position; 
			bool m_IsOpen;
		};
	}
}


#endif // !MEMORY_HANDLE_H__INCLUDED
