#pragma once
#include "BaseScene.h"

class ResultScene : public BaseScene
{
	ViewProjection viewProjection;
	
	void Initialize();
	void Update();
	void Draw();
};