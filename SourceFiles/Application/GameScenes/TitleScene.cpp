#include "TitleScene.h"
#include "SceneManager.h"
#include "ModelManager.h"

void TitleScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	ModelManager::SetViewProjection(&debugCamera);
}

void TitleScene::Update()
{
	if (input->IsTrigger(Key::Space)) { sceneManager->ChangeScene(Scene::Play); }
}

void TitleScene::Draw()
{
}