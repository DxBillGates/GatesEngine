#pragma once
#include "Header/Application/Application.h"

class Game : public GE::Application
{
private:
public:
	Game();
	Game(const GE::Math::Vector2& size, const std::string& title);
	~Game();
	bool LoadContents() override;
	bool Initialize() override;
	bool Update() override;
	bool Draw() override;
};

