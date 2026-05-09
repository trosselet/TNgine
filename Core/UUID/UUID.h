#ifndef UUID_H__INCLUDED
#define UUID_H__INCLUDED

#include "../define.h"

namespace TNgine
{
	namespace Core
	{
		class UUID
		{
		public:
			UUID();
			explicit UUID(uint64 id);
			virtual ~UUID() = default;

			uint64 GetID() const;

			bool operator==(const UUID& other) const;
			bool operator!=(const UUID& other) const;
			explicit operator uint64() const;

		private:
			uint64 m_ID;
		};
	}
}


#endif // !UUID_H__INCLUDED
