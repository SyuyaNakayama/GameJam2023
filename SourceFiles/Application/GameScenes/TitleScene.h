#pragma once
#include "BaseScene.h"
#include "Stage.h"

class TitleScene : public BaseScene
{
	Stage stage;
	ViewProjection viewProjection;
	std::unique_ptr<Sprite> title;
	std::unique_ptr<Sprite> spaceBarUI;

	Audio audio;

	void Initialize();
	void Update();
	void Draw();
};