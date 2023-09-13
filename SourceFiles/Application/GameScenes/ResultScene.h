#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include <map>

class ResultScene : public BaseScene
{
	std::map<std::string, std::unique_ptr<Sprite>> ui;
	std::unique_ptr<Sprite> numSpr[4];
	Audio audio;

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};