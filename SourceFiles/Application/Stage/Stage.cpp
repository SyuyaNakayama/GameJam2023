#include "Stage.h"
#include <imgui.h>
#include "Timer.h"

int Loop(int num, int max);

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

	ImGui::Text("IsHit:%d", IsHit(minoX, minoY + 1, minoAngle));
	ImGui::Text("deleteNum:%d", deleteNum);
	ImGui::Text("minoX:%d", minoX);

	for (size_t i = 0; i < sum.size(); i++)
	{
		ImGui::Text("sum[%d]:%d", i, sum[i]);
	}
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
		// óéÇ∆Ç∑
		bool isMinoMoveY = false;
		if (input->IsTrigger(Key::S)) { fallTimer.Start(); }
		isMinoMoveY = fallTimer.Update() && !IsHit(minoX, minoY + 1, minoAngle) && input->IsInput(Key::S);
		if (isMinoMoveY) { ++minoY; }

		int minoMoveX = 0;
		bool isMinoMoveX = false;
		if (input->IsInput(Key::A)) { holdTimeA++; }
		else { holdTimeA = 0; }
		isMinoMoveX = !IsHit(Loop(minoX + 1, 12), minoY, minoAngle);
		isMinoMoveX &= (holdTimeA <= 30 && input->IsTrigger(Key::A)) || (holdTimeA > 30 && holdTimeA % 4 == 0);
		if (isMinoMoveX) { minoMoveX++; }

		if (input->IsInput(Key::D)) { holdTimeD++; }
		else { holdTimeD = 0; }
		isMinoMoveX = !IsHit(Loop(minoX + 1, 12), minoY, minoAngle);
		isMinoMoveX &= (holdTimeD <= 30 && input->IsTrigger(Key::D)) || (holdTimeD > 30 && holdTimeD % 4 == 0);
		if (isMinoMoveX) { minoMoveX--; }

		minoX = Loop(minoX + minoMoveX, 12);

		if (input->IsTrigger(Key::W))
		{
			while (!IsHit(minoX, minoY + 1, minoAngle))
			{
				++minoY;
			}
		}

		if (input->IsTrigger(Key::Space)) {
			if (!IsHit(minoX, minoY, (minoAngle + 1) % (int)MinoAngle::Max))
			{
				minoAngle = (minoAngle + 1) % (int)MinoAngle::Max;
			}
		}
		Display();

		if (Mtimer.Update()) {
			Mtimer.Start();

			//ìÆÇ©ÇµÇƒÇÈmino
			if (IsHit(Loop(minoX, 12), minoY + 1, minoAngle)) {
				for (int i = 0; i < MINO_HEIGHT; ++i) {
					for (int j = 0; j < MINO_WIDTH; ++j) {
						field[minoY + i][Loop(minoX + j, 12)] |= minoShapes[minoType][minoAngle][i][j];
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
	for (int i = FIELD_HEIGHT - 2; i > 0; i--) { //àÍî‘â∫ÇÕògÇÃÇΩÇﬂ
		//â°àÍóÒÇÃçáåvÇãÅÇﬂÇÈ
		sum[i] = std::accumulate(field[i].begin(), field[i].end(), 0);

		for (int j = 0; j < FIELD_WIDTH; ++j) {
			if (sum[i] != 12) { continue; }
			//ëµÇ¡ÇΩÇÁè¡Ç∑
			field[i][j] = 0;

			for (int x = i; x > 0; x--) {
				field[x + 1][j] = field[x][j];
				field[x][j] = 0;
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
			displayBuffer[minoY + i][Loop(minoX + j, 12)] |= minoShapes[minoType][minoAngle][i][j];
		}
	}

	for (int i = 0; i < FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < FIELD_WIDTH; ++j)
		{
			if (1 == displayBuffer[i][j])
			{
				blocks[i][j].GetMainSprite()->color = { 0.3f, 0.0f, 0.0f, 1.0f };
			}
			else
			{
				blocks[i][j].GetMainSprite()->color = { 0.3f, 0.3f, 0.3f, 1.0f };
			}
		}
	}
}

bool Stage::IsHit(int argMinoX, int argMinoY, int argMinoAngle)
{
	for (int i = 0; i < MINO_HEIGHT; ++i)
	{
		for (int j = 0; j < MINO_WIDTH; ++j)
		{
			if (argMinoY + i >= FIELD_HEIGHT || argMinoX + j >= FIELD_WIDTH) { return true; }
			if (minoShapes[minoType][argMinoAngle][i][j] && field[argMinoY + i][argMinoX + j])
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