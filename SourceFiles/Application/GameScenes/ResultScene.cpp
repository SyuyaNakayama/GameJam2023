#include "ResultScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "Stage.h"

void ResultScene::Initialize()
{
	ui["Score"] = Sprite::Create("score.png");
	ui["Score"]->position = { 100.0f,200.0f };
	ui["Score"]->size *= 3.0f;
	ui["Score"]->Update();

	ui["Space"] = Sprite::Create("operation.png");
	ui["Space"]->textureLeftTop = { 0.0f,250.0f };
	ui["Space"]->textureSize = { 430.0f, 100.0f };
	ui["Space"]->size = ui["Space"]->textureSize * 1.5f;
	ui["Space"]->position = { 650,300 };
	ui["Space"]->Update();

	ui["titlehe"] = Sprite::Create("titlehe.png");
	ui["titlehe"]->position = { 840,250 };
	ui["titlehe"]->size *= 1.0f;
	ui["titlehe"]->Update();

	//数字のスプライト
	for (auto& spr : numSpr) {
		spr = Sprite::Create("num.png");
		spr->textureSize = { 30.0f,30.0f };
		spr->size = { 90.0f,90.0f };
	}
	//配置
	for (size_t i = 0; i < 4; i++)
	{
		numSpr[i]->position = { 85 + numSpr[0]->size.x * i,350.0f };
	}

	int score = Stage::GetScoreMem();
	int score_1000 = floor(score / 1000);
	int score_100 = floor((score - score_1000 * 1000) / 100);

	//SCOREの千桁
	numSpr[0]->textureLeftTop = { score_1000 * 30.0f,0.0f };

	//SCOREの百桁
	numSpr[1]->textureLeftTop = { score_100 * 30.0f,0.0f };

	//SCOREの十桁
	numSpr[2]->textureLeftTop = { 0.0f,0.0f };

	//SCOREの一桁
	numSpr[3]->textureLeftTop = { 0.0f,0.0f };

	for (auto& spr : numSpr) { spr->Update(); }
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
	for (auto& spr : ui) { spr.second->Draw(); }
	for (auto& spr : numSpr) { spr->Draw(); }
}

void ResultScene::Finalize()
{
	delete ModelManager::GetViewProjection();
}