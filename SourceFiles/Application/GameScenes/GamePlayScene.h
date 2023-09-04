#pragma once
#include "BaseScene.h"
#include "Object3d.h"

class GamePlayScene : public BaseScene
{
	ViewProjection viewProjection;
	std::unique_ptr<Sprite> sprite;

	void Initialize();
	void Update();
	void Draw();
};