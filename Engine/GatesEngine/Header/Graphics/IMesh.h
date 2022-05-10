#pragma once


namespace GE
{
	class IMesh
	{
	public:
		virtual ~IMesh() {}
		virtual void Draw(unsigned int instanceCount = 1) = 0;
	};
}