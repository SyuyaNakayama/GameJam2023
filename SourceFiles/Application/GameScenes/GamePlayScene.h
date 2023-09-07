#pragma once
#include "BaseScene.h"
#include "Stage.h"

class GamePlayScene : public BaseScene
{
private:
	ViewProjection viewProjection;
	Stage stage;

	void Initialize();
	void Update();
	void Draw();
};