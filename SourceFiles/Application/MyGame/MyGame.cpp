#include "MyGame.h"
#include "ModelManager.h"
#include "Audio.h"

void MyGame::Initialize()
{
	Framework::Initialize();
	sceneManager->ChangeScene(Scene::Title, false);
	ModelManager::Initialize();
	Audio::StaticInitialize();
}

void MyGame::Update()
{
	Framework::Update();
	ModelManager::Update();
}

void MyGame::Draw()
{
	dxCommon->PreDraw();
	// 3Dモデルの描画
	ModelManager::DrawObjects();
	// 2Dスプライトの描画
	Sprite::PreDraw();
	sceneManager->Draw();
	Sprite::PostDraw();
	dxCommon->PostDraw();
}

void MyGame::Finalize()
{
	Audio::Finalize();
	Framework::Finalize();
}