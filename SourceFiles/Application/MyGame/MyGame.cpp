#include "MyGame.h"
#include "ModelManager.h"
#include "Audio.h"
#include "CollisionManager.h"

void MyGame::Initialize()
{
	Framework::Initialize();
	sceneManager->ChangeScene(Scene::Title, false);
	ModelManager::Initialize();
	ParticleManager::Initialize();
	Audio::StaticInitialize();
	postEffect = std::make_unique<PostEffect>();
	postEffect->Initialize();
}

void MyGame::Update()
{
	Framework::Update();
	ModelManager::Update();
	CollisionManager::CheckAllCollisions();
	Physics::ResetCollideList();
	ParticleManager::Update();
}

void MyGame::Draw()
{
	postEffect->PreDrawScene();
	// 3Dモデルの描画
	ModelManager::DrawObjects();
	// 2Dスプライトの描画
	Sprite::PreDraw();
	sceneManager->Draw();
	Sprite::PostDraw();
	ParticleManager::Draw();
	postEffect->PostDrawScene();
	
	dxCommon->PreDraw();
	postEffect->Draw();
	dxCommon->PostDraw();
}

void MyGame::Finalize()
{
	Audio::Finalize();
	Framework::Finalize();
}