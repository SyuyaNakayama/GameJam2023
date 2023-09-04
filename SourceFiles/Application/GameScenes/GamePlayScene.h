#pragma once
#include "BaseScene.h"
#include "Stage.h"

class GamePlayScene : public BaseScene
{
	ViewProjection viewProjection;
	Stage stage;

	void Initialize();
	void Update();
	void Draw();
};