#pragma once
#include "Scene.h"

namespace GE
{
	class SampleScene : public Scene
	{
	private:
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
