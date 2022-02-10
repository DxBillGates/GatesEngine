#pragma once

namespace GE
{
	class ICBufferAllocater
	{
	public:
		virtual ~ICBufferAllocater() {}
		virtual void ResetCurrentUsedNumber() = 0;
		virtual void BindAndAttachData(int descIndex, const void* data, int size) = 0;
	};
}
