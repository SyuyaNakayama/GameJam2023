#include "ResultScene.h"
#include "SceneManager.h"
#include "ModelManager.h"

void ResultScene::Initialize()
{
	viewProjection.Initialize();
	ModelManager::SetViewProjection(&viewProjection);
}

void ResultScene::Update()
{
	if (input->IsTrigger(Key::Space))
	{
		sceneManager->ChangeScene(Scene::Title);
		ModelManager::ClearObjects();
	}

}

void ResultScene::Draw()
{
}
