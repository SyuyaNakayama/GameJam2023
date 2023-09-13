#include "TitleScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ImGuiManager.h"
#include <imgui.h>

void TitleScene::Initialize()
{
	stage.Initialize();
	viewProjection.Initialize();
	viewProjection.target = { 50,3 };
	viewProjection.eye = { 50,3,-150 };
	ModelManager::SetViewProjection(&viewProjection);
	title = Sprite::Create("title.png");
	title->position = { 600,115 };
	title->size *= 3;
	title->Update();

	spaceBarUI = Sprite::Create("operation.png");
	spaceBarUI->textureLeftTop = { 0.0f,250.0f };
	spaceBarUI->textureSize = { 430.0f, 100.0f };
	spaceBarUI->size = spaceBarUI->textureSize * 1.5f;
	spaceBarUI->position = { 540,310 };
	spaceBarUI->Update();

	audio.Initialize(L"delete.mp3");
}

void TitleScene::Update()
{
	if (input->IsTrigger(Key::Space))
	{
		audio.Play();
		sceneManager->ChangeScene(Scene::Play);
		ModelManager::ClearObjects();
	}
}

void TitleScene::Draw()
{
	title->Draw();
	spaceBarUI->Draw();
}