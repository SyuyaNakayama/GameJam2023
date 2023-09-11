#include "GamePlayScene.h"
#include "SceneManager.h"
#include "ModelManager.h"

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 55,-55 }, 300);
	viewProjection.Initialize();
	ModelManager::SetViewProjection(&debugCamera);
	stage.Initialize();
	SpriteInitialize();
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	stage.Update();
	SpriteUpdate();

	if (stage.IsEnd()) 
	{
		sceneManager->ChangeScene(Scene::Result); 
		ModelManager::ClearObjects();
	}
}

void GamePlayScene::Draw()
{
	for (int i = 0; i < 5; i++) {
		spr[i]->Draw();
	}
	for (int i = 0; i < 6; i++) {
		numSpr[i]->Draw();
	}
	minoSpr->Draw();
}

void GamePlayScene::SpriteInitialize()
{
	//テクスチャの読み込み
	spr[0] = Sprite::Create("operation.png");//操作説明 WASD
	spr[1] = Sprite::Create("operation.png");//操作説明 SPACE
	spr[2] = Sprite::Create("level.png");//"LEVEL"
	spr[3] = Sprite::Create("score.png");//"SCORE"
	spr[4] = Sprite::Create("next.png"); //"NEXT"

	spr[0]->textureLeftTop = { 0.0f,0.0f };
	spr[0]->textureSize = { 430.0f,250.0f };
	spr[0]->size = { 430.0f,250.0f };
	spr[0]->position = { 0,150 };

	spr[1]->textureLeftTop = { 0.0f,250.0f };
	spr[1]->textureSize = { 430.0f,136.0f };
	spr[1]->size = { 430.0f,136.0f };
	spr[1]->position = { 0,550 };

	spr[2]->position = { 900.0f,150.0f };
	spr[3]->position = { 900.0f,200.0f };
	spr[4]->position = { 900.0f,400.0f };

	//更新
	for (int i = 0; i < 5; i++) {
		spr[i]->Update();
	}

	//数字のスプライト
	for (int i = 0; i < 6; i++) {
		numSpr[i] = Sprite::Create("num.png");
		numSpr[i]->textureSize = { 30.0f,30.0f };
		numSpr[i]->size = { 30.0f,30.0f };
	}
	//配置
	numSpr[0]->position = { 1110.0f,160.0f };
	numSpr[1]->position = { 1140.0f,160.0f };
	numSpr[2]->position = { 1050.0f,210.0f };
	numSpr[3]->position = { 1080.0f,210.0f };
	numSpr[4]->position = { 1110.0f,210.0f };
	numSpr[5]->position = { 1140.0f,210.0f };

	//nextミノのスプライト
	minoSpr = Sprite::Create("mino.png");
	minoSpr->textureSize = { 20.0f,10.0f };
	minoSpr->size = { 200.0f,100.0f };
	minoSpr->position = { 950.0f,500.0f };
}

void GamePlayScene::SpriteUpdate()
{
	int level = stage.GetLevel();
	int level_10 = floor(level / 10);
	int level_1 = level - level_10 * 10;
	
	//LEVELの十桁
	numSpr[0]->textureLeftTop = { level_10 * 30.0f,0.0f };
	
	//LEVELの一桁
	numSpr[1]->textureLeftTop = { level_1 * 30.0f,0.0f };
	

	int score = stage.GetScore();
	int score_1000 = floor(score / 1000);
	int score_100 = floor((score - score_1000 * 1000) / 100);
	
	//SCOREの千桁
	numSpr[2]->textureLeftTop = { score_1000 * 30.0f,0.0f };

	//SCOREの百桁
	numSpr[3]->textureLeftTop = { score_100 * 30.0f,0.0f };

	//SCOREの十桁
	numSpr[4]->textureLeftTop = { 0.0f,0.0f };

	//SCOREの一桁
	numSpr[5]->textureLeftTop = { 0.0f,0.0f };


	//nextミノ
	int nextMino = stage.GetNextMinoType();
	minoSpr->textureLeftTop = { nextMino * 20.0f,0.0f };

	for (int i = 0; i < 6; i++) {
		numSpr[i]->Update();
	}
	minoSpr->Update();
}
