#pragma once

namespace GE
{
	class ICBufferAllocater
	{
	public:
		virtual ~ICBufferAllocater() {}
		virtual void ResetCurrentUsedNumber() = 0;
		virtual int BindAndAttachData(int descIndex, const void* data, int size) = 0;
	};
}
