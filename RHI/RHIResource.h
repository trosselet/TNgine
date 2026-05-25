#ifndef RHI_RESOURCE_H__INCLUDED
#define RHI_RESOURCE_H__INCLUDED

#include <Core/include.h>
#include <string>

namespace TNgine
{
	class RHIResource
	{
	public:

		virtual ~RHIResource() = default;

		void SetDebugName(std::string name)
		{
			m_DebugName = name;
		}

		const std::string& GetDebugName() const
		{
			return m_DebugName;
		}

	protected:
		std::string m_DebugName;
	};
}

#endif // !RHI_RESOURCE_H__INCLUDED