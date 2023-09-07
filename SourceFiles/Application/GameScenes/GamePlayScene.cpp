#include "GamePlayScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include <imgui.h>
#include "Timer.h"

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 12,20 }, 300);
	viewProjection.Initialize();
	ModelManager::SetViewProjection(&debugCamera);

	//stage.Initialize();
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			blocks[y][x] = ModelManager::Create("block");
            blocks[y][x]->worldTransform->scale *= 10.0f;
			//blocks[y][x]->worldTransform->translation = { -((float)x - 12 / 2) * 5 * 2, -((float)y - 22 / 2) * 5 * 2, 0.0f };//ïΩñ 
            
            //â~íåÇ…Ç∑ÇÈ
            blocks[y][x]->worldTransform->translation = { 0.0f, -(float)y * 5.0f , 0.0f };
            blocks[y][x]->worldTransform->rotation.y = x * 30*PI/180;
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
    ImGui::Text("sam:%d", sam);
    /*for (int i = 0; i < 22; i++) {
        ImGui::Text("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
            field[i][0], field[i][1], field[i][2], field[i][3], field[i][4], field[i][5],
            field[i][6], field[i][7], field[i][8], field[i][9], field[i][10], field[i][11]);
    }

	ImGui::Text("----------------------------------");

    for (int i = 0; i < 22; i++) {
        ImGui::Text("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
            displayBuffer[i][0], displayBuffer[i][1], displayBuffer[i][2], displayBuffer[i][3], displayBuffer[i][4],  displayBuffer[i][5],
            displayBuffer[i][6], displayBuffer[i][7], displayBuffer[i][8], displayBuffer[i][9], displayBuffer[i][10], displayBuffer[i][11]);
    }*/
    
    

    //òg
	for (int i = 0; i < FIELD_WIDTH; ++i)
	{
		field[FIELD_HEIGHT - 1][i] = 1;
	}

	if (isflag == true)
	{
		if (input->IsInput(Key::S)) {
			if (input->IsTrigger(Key::S)) { fallTimer.Start(); }
			if (fallTimer.Update() && !isHit(minoX, minoY + 1, minoType, minoAngle))
			{
				++minoY;
			}
		}

		if (input->IsInput(Key::A)) {
			holdTimeA++;
			
			if (holdTimeA <= 10)
			{
				if (input->IsTrigger(Key::A)&&!isHit(minoX + 1, minoY, minoType, minoAngle))
				{
					++minoX;
				}
			}
			else
			{
				if (!isHit(minoX + 1, minoY, minoType, minoAngle))
				{
					++minoX;
				}
			}
		}
		else
		{
			holdTimeA = 0; 
		}

		if (input->IsInput(Key::D)) {
			holdTimeD++;

			if (holdTimeD <= 10)
			{
				if (input->IsTrigger(Key::D) && !isHit(minoX - 1, minoY, minoType, minoAngle))
				{
					--minoX;
				}
			}
			else
			{
				if (!isHit(minoX - 1, minoY, minoType, minoAngle))
				{
					--minoX;
				}
			}
		}
		else
		{
			holdTimeD = 0;
		}

		if (input->IsTrigger(Key::W))
		{
			while (!isHit(minoX, minoY + 1, minoType, minoAngle))
			{
				++minoY;
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

            //ìÆÇ©ÇµÇƒÇÈmino
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

    //ëµÇ¡ÇƒÇ¢ÇÈçsÇíTÇ∑
    for (int i = FIELD_HEIGHT - 2; i > 0; i--) {//àÍî‘â∫ÇÕògÇÃÇΩÇﬂ
        //â°àÍóÒÇÃçáåvÇãÅÇﬂÇÈ
        sam[i] = field[i][0] + field[i][1] + field[i][2] + field[i][3] + field[i][4] + field[i][5] +
            field[i][6] + field[i][7] + field[i][8] + field[i][9] + field[i][10] + field[i][11];


        

        for (int j = 0; j < FIELD_WIDTH; ++j) {
            if (sam[i] == 12) {//ëµÇ¡ÇΩÇÁè¡Ç∑
                field[i][j] = 0;
                
                for (int x = i; x > 0; x--) {
                    field[x + 1][j] = field[x][j];
                    field[x][j] = 0;
                }
            }
        }
    }
}

void GamePlayScene::Draw()
{
}


void GamePlayScene::display()
{
	memcpy(displayBuffer, field, sizeof(field));

    for (int i = 0; i < MINO_HEIGHT; ++i){
        for (int j = 0; j < MINO_WIDTH; ++j){
            displayBuffer[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
        }
    }

    //minoÇÃêFÇïœÇ¶ÇÈ
    for (int i = 0; i < FIELD_HEIGHT; ++i){
        for (int j = 0; j < FIELD_WIDTH; ++j){
            if (1 == displayBuffer[i][j]){
                blocks[i][j]->material.GetSprite(TexType::Main)->color = { 0.3f, 0.0f, 0.0f, 1.0f };
            }
            else{
                blocks[i][j]->material.GetSprite(TexType::Main)->color = { 0.3f, 0.3f, 0.3f, 1.0f };
            }
        }
    }
}

bool GamePlayScene::isHit(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle)
{
	for (int i = 0; i < MINO_HEIGHT; ++i){
		for (int j = 0; j < MINO_WIDTH; ++j){
			if (minoShapes[argMinoType][argMinoAngle][i][j] && field[argMinoY + i][argMinoX + j]){
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