#pragma once
#include "Scene.h"
#include "..\..\..\Header\GameFramework\Collision\ICollider.h"

namespace GE
{
	class SampleScene : public Scene
	{
	private:
		ICollider* col1,*col2;
	public:
		SampleScene();
		SampleScene(const std::string& sceneName);
		~SampleScene();
		void Initialize() override;
		void Update(float deltaTime) override;
		void Draw() override;
		void LateDraw() override;
	};
}
