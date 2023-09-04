#include "GamePlayScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	viewProjection.Initialize();
	ModelManager::SetViewProjection(&debugCamera);
	sprite = Sprite::Create("64670481_p0_master1200.jpg");
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	sprite->Update();
}

void GamePlayScene::Draw()
{
	sprite->Draw();
}