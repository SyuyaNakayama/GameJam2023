#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "Sprite.h"

class GamePlayScene : public BaseScene
{
private:
	ViewProjection viewProjection;
	Stage stage; 
	std::unique_ptr<Sprite> spr[5];
	std::unique_ptr<Sprite> numSpr[6];
	std::unique_ptr<Sprite> minoSpr;

	void Initialize();
	void Update();
	void Draw();

	void SpriteInitialize();
	void SpriteUpdate();
};