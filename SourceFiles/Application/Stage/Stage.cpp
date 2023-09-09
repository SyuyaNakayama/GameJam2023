#include "Stage.h"
#include <imgui.h>
#include "Timer.h"

void Stage::Initialize()
{
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			blocks[y][x].Initialize((float)x, (float)y);
		}
	}
	Mtimer = 1;
	Mtimer.Start();
}

void Stage::Update()
{
	//block.Update();

	ImGui::Text("IsHit:%d", IsHit(minoX, minoY + 1, minoType, minoAngle));
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
	/*for (int i = 0; i < FIELD_HEIGHT; ++i)
	{
		field[i][0] = 1;
		field[i][FIELD_WIDTH - 1] = 1;
	}*/

	//óêêîê∂ê¨
	srand(time(nullptr));

	for (int i = 0; i < FIELD_WIDTH; ++i)
	{
		field[FIELD_HEIGHT - 1][i] = 1;
	}

	if (isflag == true)
	{
		if (input->IsInput(Key::S)) {
			if (input->IsTrigger(Key::S)) { fallTimer.Start(); }
			if (fallTimer.Update() && !IsHit(minoX, minoY + 1, minoType, minoAngle))
			{
				++minoY;
			}
		}

		if (input->IsInput(Key::A)) {
			holdTimeA++;

			if (holdTimeA <= 10)
			{
				if (input->IsTrigger(Key::A) && !IsHit(minoX + 1, minoY, minoType, minoAngle))
				{
					++minoX;
				}
			}
			else
			{
				if (!IsHit(minoX + 1, minoY, minoType, minoAngle))
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
				if (input->IsTrigger(Key::D) && !IsHit(minoX - 1, minoY, minoType, minoAngle))
				{
					--minoX;
				}
			}
			else
			{
				if (!IsHit(minoX - 1, minoY, minoType, minoAngle))
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
			while (!IsHit(minoX, minoY + 1, minoType, minoAngle))
			{
				++minoY;
			}
		}

		if (input->IsTrigger(Key::Space)) {
			if (!IsHit(minoX, minoY, minoType, (minoAngle + 1) % (int)MinoAngle::Max))
			{
				minoAngle = (minoAngle + 1) % (int)MinoAngle::Max;
			}
		}
		Display();

		if (Mtimer.Update()) {
			Mtimer.Start();

			//ìÆÇ©ÇµÇƒÇÈmino
			if (IsHit(minoX, minoY + 1, minoType, minoAngle)) {
				for (int i = 0; i < MINO_HEIGHT; ++i) {
					for (int j = 0; j < MINO_WIDTH; ++j) {
						field[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
					}
				}
				ResetMino();
			}
			else {
				++minoY;
			}

			Display();
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

void Stage::Display()
{
	displayBuffer = field;

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
				blocks[i][j].GetMainSprite()->color = {0.3f, 0.0f, 0.0f, 1.0f};
			}
			else
			{
				blocks[i][j].GetMainSprite()->color = { 0.3f, 0.3f, 0.3f, 1.0f };
			}
		}
	}
}

bool Stage::IsHit(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle)
{
	for (int i = 0; i < MINO_HEIGHT; ++i)
	{
		for (int j = 0; j < MINO_WIDTH; ++j)
		{
			if (argMinoY + i >= FIELD_HEIGHT || argMinoX + j >= FIELD_WIDTH) { return true; }
			if (minoShapes[argMinoType][argMinoAngle][i][j] && field[argMinoY + i][argMinoX + j])
			{
				return true;
			}
		}
	}
	return false;
}

void Stage::ResetMino()
{
	minoX = 5;
	minoY = 0;
	minoType = rand() % (int)MinoType::Max;
	minoAngle = rand() % (int)MinoAngle::Max;
}