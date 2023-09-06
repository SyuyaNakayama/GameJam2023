#include "GamePlayScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 12,20 },200);
	viewProjection.Initialize();
	ModelManager::SetViewProjection(&debugCamera);

	//stage.Initialize();
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			blocks[y][x] = ModelManager::Create("cube");
			blocks[y][x]->worldTransform->translation = { -((float)x - 12 / 2) * 5 * 2, -((float)y - 22 / 2) * 5 * 2, 0.0f };
			
			if (map[y][x] == 0) {
				blocks[y][x]->worldTransform->scale *= 1.0f;
			}
			else {
				blocks[y][x]->worldTransform->scale *= 5.0f;
			}

		}
	}
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	//stage.Update();
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			ImGui::Text("%d,%d = %d", y, x, map[y][x]);
		}
	}
	
}

void GamePlayScene::Draw()
{
}