#include "GamePlayScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include <imgui.h>
#include "Timer.h"

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 12,20 },200);
	viewProjection.Initialize();
	ModelManager::SetViewProjection(&debugCamera);

	//stage.Initialize();
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			blocks[y][x] = ModelManager::Create("cube");
            blocks[y][x]->worldTransform->scale *= 4.8f;
			blocks[y][x]->worldTransform->translation = { -((float)x - 12 / 2) * 5 * 2, -((float)y - 22 / 2) * 5 * 2, 0.0f };
		}
	}
    Mtimer = 1;
    Mtimer.Start();
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	//stage.Update();

    ImGui::Text("isHit:%d", isHit(minoX, minoY + 1, minoType, minoAngle));
    ImGui::Text("deleteNum:%d", deleteNum);
    for (int i = 0; i < 22; i++) {
        ImGui::Text("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
            field[i][0], field[i][1], field[i][2], field[i][3], field[i][4], field[i][5],
            field[i][6], field[i][7], field[i][8], field[i][9], field[i][10], field[i][11]);
    }

    ImGui::Text("----------------------------------");

    for (int i = 0; i < 22; i++) {
        ImGui::Text("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
            displayBuffer[i][0], displayBuffer[i][1], displayBuffer[i][2], displayBuffer[i][3], displayBuffer[i][4],  displayBuffer[i][5],
            displayBuffer[i][6], displayBuffer[i][7], displayBuffer[i][8], displayBuffer[i][9], displayBuffer[i][10], displayBuffer[i][11]);
    }
    
    

    //枠
	/*for (int i = 0; i < FIELD_HEIGHT; ++i)
	{
		field[i][0] = 1;
		field[i][FIELD_WIDTH - 1] = 1;
	}*/

	for (int i = 0; i < FIELD_WIDTH; ++i)
	{
		field[FIELD_HEIGHT - 1][i] = 1;
	}

    //minoを動かす
    if(isflag == true)
    {
        if (input->IsTrigger(Key::S)) {
            if (!isHit(minoX, minoY + 1, minoType, minoAngle))
            {
                ++minoY;
            }
        }

        if (input->IsTrigger(Key::A)) {
            if (!isHit(minoX + 1, minoY, minoType, minoAngle))
            {
                ++minoX;
            }
        }

        if (input->IsTrigger(Key::D)) {
            if (!isHit(minoX - 1, minoY, minoType, minoAngle))
            {
                --minoX;
            }
        }

        if (input->IsTrigger(Key::Space)) {
            if (!isHit(minoX, minoY, minoType, (minoAngle + 1) % MINO_ANGLE_MAX))
            {
                minoAngle = (minoAngle + 1) % MINO_ANGLE_MAX;
            }
        }
        display();
        
        if (Mtimer.Update()){
            Mtimer.Start();

            //動かしてるmino
            if (isHit(minoX, minoY + 1, minoType, minoAngle)){
                for (int i = 0; i < MINO_HEIGHT; ++i){
                    for (int j = 0; j < MINO_WIDTH; ++j){
                        field[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
                    }
                }

                
                resetMino();
            }
            else{
                ++minoY;
            }

            display();
        }
    }
    // 揃ったらけす
    memcpy(fall, field, sizeof(field));
    for (int i = 0; i < FIELD_HEIGHT - 1; ++i) {//一番下は枠のため
        for (int j = 0; j < FIELD_WIDTH; ++j) {

            sam += fall[i][j];
            if (sam >= 12) {//揃った行を探す
                deleteNum = i;
            }

            //揃った列を消す
            fall[deleteNum][j] = 0;

            if (j == FIELD_WIDTH - 1) {//一行やったら戻す
                sam = 0;

            }
        }
        //deleteNum = 0;
    }

    //下げる
    for (int i = 0; i < FIELD_HEIGHT - 1; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {

            if (fall[i][j] == 1 && fall[i + 1][j] == 0) {//もし1のとき,下が0なら

                //置き換える
                fall[i + 1][j] = 1;
                fall[i][j] = 0;
            }

        }
    }

    memcpy(field, fall, sizeof(field));
}

void GamePlayScene::Draw()
{
}


void GamePlayScene::display()
{
    memcpy(displayBuffer, field, sizeof(field));

    


    //揃ったら消す
    for (int i = 0; i < FIELD_HEIGHT - 1; ++i) {//一番下は枠のため
        for (int j = 0; j < FIELD_WIDTH; ++j) {

            sam += displayBuffer[i][j];
            if (sam >= 12) {//揃った行を探す
                deleteNum = i;
            }

            //揃った列を消す
            displayBuffer[deleteNum][j] = 0;
            field[deleteNum][j] = 0;
            if (j == FIELD_WIDTH - 1) {//一行やったら戻す
                sam = 0;
                
            }
        }
        deleteNum = 0;
    }

    for (int i = 0; i < FIELD_HEIGHT - 1; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {

            if (displayBuffer[i][j] == 1 && displayBuffer[i + 1][j] == 0) {//もし1のとき,下が0なら
                
                //置き換える
                displayBuffer[i + 1][j] = 1;
                displayBuffer[i][j] = 0;
                field[i + 1][j] = 1;
                field[i][j] = 0;
            }

        }
    }


    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            displayBuffer[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
        }
    }

    for (int i = 0; i < FIELD_HEIGHT; ++i)
    {
        for (int j = 0; j < FIELD_WIDTH; ++j)
        {
            if (1 == displayBuffer[i][j])
            {
                blocks[i][j]->material.GetSprite(TexType::Main)->color = { 0.3f, 0.0f, 0.0f, 1.0f };
            }
            else
            {
                blocks[i][j]->material.GetSprite(TexType::Main)->color = { 0.3f, 0.3f, 0.3f, 1.0f };
            }
        }
    }
}

bool GamePlayScene::isHit(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle)
{
	for (int i = 0; i < MINO_HEIGHT; ++i)
	{
		for (int j = 0; j < MINO_WIDTH; ++j)
		{
			if (minoShapes[argMinoType][argMinoAngle][i][j] && field[argMinoY + i][argMinoX + j])
			{
				return true;
			}
		}
	}
	return false;
}

void GamePlayScene::resetMino()
{
    minoX = 5;
    minoY = 0;
    minoType = rand() % MINO_TYPE_MAX;
    minoAngle = rand() % MINO_ANGLE_MAX;
}