#include "GamePlayScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 55,-55 }, 300);
	viewProjection.Initialize();
	viewProjection.eye.z = -150;
	//ModelManager::SetViewProjection(&debugCamera);
	ModelManager::SetViewProjection(&viewProjection);
	stage.Initialize();
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	stage.Update();

	ImGui::InputFloat("viewProjection.eye.z", &viewProjection.eye.z);

	if (stage.IsEnd()) 
	{
		sceneManager->ChangeScene(Scene::Result); 
		ModelManager::ClearObjects();
	}
}

void GamePlayScene::Draw()
{
}