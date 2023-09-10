#include "GamePlayScene.h"
#include "SceneManager.h"
#include "ModelManager.h"

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 12,20 }, 300);
	viewProjection.Initialize();
	ModelManager::SetViewProjection(&debugCamera);
	stage.Initialize();
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	stage.Update();

	if (stage.IsEnd()) 
	{
		sceneManager->ChangeScene(Scene::Result); 
		ModelManager::ClearObjects();
	}
}

void GamePlayScene::Draw()
{
}