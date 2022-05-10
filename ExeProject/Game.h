#pragma once
#include <GatesEngine/Header/Application/Application.h>
#include <GatesEngine/Header/Graphics/RenderTexture.h>
#include <GatesEngine/Header/Graphics/DepthTexture.h>

class Game : public GE::Application
{
private:
public:
	Game();
	Game(const GE::Math::Vector2& size, const std::string& title, GE::WindowMode mode = GE::WindowMode::POP_UP);
	~Game();
	bool LoadContents() override;
	bool Initialize() override;
	bool Update() override;
	bool Draw() override;
};

