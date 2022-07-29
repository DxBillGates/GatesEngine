#pragma once
#include <GatesEngine/Header/Application/Application.h>
#include <GatesEngine/Header/Graphics/RenderTexture.h>
#include <GatesEngine/Header/Graphics/DepthTexture.h>

class Game : public GE::Application
{
private:
public:
	Game();
	Game(const GE::WindowData& windowData, const GE::Math::Vector2& resolution);
	Game(const GE::Math::Vector2& size, const GE::Math::Vector2& resolution = {1920,1080},const std::string & title = "no title", GE::WindowMode mode = GE::WindowMode::POP_UP);
	~Game();
	bool LoadContents() override;
	bool Initialize() override;
	bool Update() override;
	bool Draw() override;
};

