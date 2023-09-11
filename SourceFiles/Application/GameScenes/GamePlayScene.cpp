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
	//�e�N�X�`���̓ǂݍ���
	spr[0] = Sprite::Create("operation.png");//������� WASD
	spr[1] = Sprite::Create("operation.png");//������� SPACE
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

	//�X�V
	for (int i = 0; i < 5; i++) {
		spr[i]->Update();
	}

	//�����̃X�v���C�g
	for (int i = 0; i < 6; i++) {
		numSpr[i] = Sprite::Create("num.png");
		numSpr[i]->textureSize = { 30.0f,30.0f };
		numSpr[i]->size = { 30.0f,30.0f };
	}
	//�z�u
	numSpr[0]->position = { 1110.0f,160.0f };
	numSpr[1]->position = { 1140.0f,160.0f };
	numSpr[2]->position = { 1050.0f,210.0f };
	numSpr[3]->position = { 1080.0f,210.0f };
	numSpr[4]->position = { 1110.0f,210.0f };
	numSpr[5]->position = { 1140.0f,210.0f };

	//next�~�m�̃X�v���C�g
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
	
	//LEVEL�̏\��
	numSpr[0]->textureLeftTop = { level_10 * 30.0f,0.0f };
	
	//LEVEL�̈ꌅ
	numSpr[1]->textureLeftTop = { level_1 * 30.0f,0.0f };
	

	int score = stage.GetScore();
	int score_1000 = floor(score / 1000);
	int score_100 = floor((score - score_1000 * 1000) / 100);
	
	//SCORE�̐猅
	numSpr[2]->textureLeftTop = { score_1000 * 30.0f,0.0f };

	//SCORE�̕S��
	numSpr[3]->textureLeftTop = { score_100 * 30.0f,0.0f };

	//SCORE�̏\��
	numSpr[4]->textureLeftTop = { 0.0f,0.0f };

	//SCORE�̈ꌅ
	numSpr[5]->textureLeftTop = { 0.0f,0.0f };


	//next�~�m
	int nextMino = stage.GetNextMinoType();
	minoSpr->textureLeftTop = { nextMino * 20.0f,0.0f };

	for (int i = 0; i < 6; i++) {
		numSpr[i]->Update();
	}
	minoSpr->Update();
}
