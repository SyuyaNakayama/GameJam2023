#include "GamePlayScene.h"
#include "SceneManager.h"
#include "ModelManager.h"

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 12,20 }, 300);
	viewProjection.Initialize();
	ModelManager::SetViewProjection(&debugCamera);
	stage.Initialize();
	SpriteInitialize();
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	stage.Update();
}

void GamePlayScene::Draw()
{
	for (int i = 0; i < 5; i++) {
		spr[i]->Draw();
	}
}

void GamePlayScene::SpriteInitialize()
{
	//�e�N�X�`���̓ǂݍ���
	spr[0] = Sprite::Create("operation.png");//������� WASD
	spr[1] = Sprite::Create("operation.png");//������� SPACE
	spr[2] = Sprite::Create("level.png");//"LEVEL"
	spr[3] = Sprite::Create("score.png");//"SCORE"
	spr[4] = Sprite::Create("next.png"); //"NEXT"

	//spr->textureLeftTop = { 0.0f,15.0f };
	//spr->textureSize = { 177.0f,15.0f };
	//spr->size = { 177.0f,15.0f };
	//spr->position = { 10,10 };

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
}
