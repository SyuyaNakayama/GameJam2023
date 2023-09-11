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
}

void ResultScene::Draw()
{
}
