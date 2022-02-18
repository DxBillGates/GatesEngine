#pragma once
#include "ICollider.h"
#include "..\..\Util\Manager.h"

#include <vector>

namespace GE
{
	class CollisionManager
	{
	private:
	public:
		static bool CheckHit(ICollider* col1, ICollider* col2);
		static bool CheckSphere(ICollider* col1, ICollider* col2);
		static bool CheckAABB(ICollider* col1, ICollider* col2);
		static bool CheckOBB(ICollider* col1, ICollider* col2);
	};
}