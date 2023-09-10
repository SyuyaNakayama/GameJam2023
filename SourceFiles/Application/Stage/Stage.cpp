#include "Stage.h"
#include <imgui.h>
#include "Timer.h"

// 数を0から一定の範囲まででループさせる
int Loop(int num, int max)
{
	num = num % max;
	// 除数を足して正の整数にする
	if (num < 0) { num += max; }
	return num;
}

void Stage::Initialize()
{
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			blocks[y][x].Initialize((float)x, (float)y);
		}
	}
	Mtimer.Start();
	//乱数生成
	srand(time(nullptr));
	//床
	for (int i = 0; i < FIELD_WIDTH; ++i) { field[FIELD_HEIGHT - 1][i] = 1; }
}

void Stage::Update()
{
	ShowImGui();
	MoveMino();

	shadowY = minoY;
	while (!IsHit(minoX, shadowY + 1, minoAngle)) { shadowY++; }

	Display();

	if (Mtimer.Update()) {
		Mtimer.Start();

		//動かしてるmino
		if (IsHit(Loop(minoX, 12), minoY + 1, minoAngle)) {
			for (int i = 0; i < MINO_HEIGHT; ++i) {
				for (int j = 0; j < MINO_WIDTH; ++j) {
					field[minoY + i][Loop(minoX + j, 12)] |= minoShapes[minoType][minoAngle][i][j];
				}
			}
			ResetMino();
		}
		else { ++minoY; }

		Display();
	}

	//揃っている行を探す
	for (int i = FIELD_HEIGHT - 2; i > 0; i--) { //一番下は枠のため
		//横一列の合計を求める
		sum[i] = std::accumulate(field[i].begin(), field[i].end(), 0);

		for (int j = 0; j < FIELD_WIDTH; ++j) {
			if (sum[i] != 12) { continue; }
			//揃ったら消す
			field[i][j] = 0;
			score += 100;
			for (int x = i; x > 0; x--) {
				field[x + 1][j] = field[x][j];
				field[x][j] = 0;
			}
			// ミノ加速
			if (Mtimer.GetInterval() >= 0.1f)
			{
				Mtimer = Mtimer.GetInterval() - (float)(score / 500) * 0.05;
			}
		}
	}

	//一番上まで積みあがったら終了
	if (sum[1] > 0) { isEnd = true; }
}

void Stage::Display()
{
	displayBuffer = field;

	for (int i = 0; i < MINO_HEIGHT; ++i)
	{
		for (int j = 0; j < MINO_WIDTH; ++j)
		{
			int minoFlag = minoShapes[minoType][minoAngle][i][j];
			displayBuffer[minoY + i][Loop(minoX + j, 12)] |= minoFlag;
			displayBuffer[shadowY + i][Loop(minoX + j, 12)] |= (minoFlag << 1);
		}
	}

	for (int i = 0; i < FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < FIELD_WIDTH; ++j)
		{
			if (displayBuffer[i][j] & 1)
			{
				blocks[i][j].GetMainSprite()->color = { 0.3f, 0.0f, 0.0f, 1.0f };
			}
			else if (displayBuffer[i][j] & 2)
			{
				blocks[i][j].GetMainSprite()->color = { 0.3f, 0.6f, 0.3f, 1.0f };
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
			if (minoShapes[minoType][argMinoAngle][i][j] && field[argMinoY + i][Loop(argMinoX + j, 12)])
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

void Stage::ShowImGui()
{
	ImGui::Text("isEnd:%d", isEnd);
	ImGui::Text("score:%d", score);
	ImGui::Text("IsHit:%d", IsHit(minoX, minoY + 1, minoAngle));
	ImGui::Text("deleteNum:%d", deleteNum);
	ImGui::Text("minoX:%d", minoX);
	ImGui::Text("Mtimer.GetInterval():%f", Mtimer.GetInterval());

	for (size_t i = 0; i < sum.size(); i++)
	{
		//ImGui::Text("sum[%d]:%d", i, sum[i]);
	}
	//for (int i = 0; i < 22; i++) {
	//	ImGui::Text("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
	//		field[i][0], field[i][1], field[i][2], field[i][3], field[i][4], field[i][5],
	//		field[i][6], field[i][7], field[i][8], field[i][9], field[i][10], field[i][11]);
	//}

	//ImGui::Text("----------------------------------");

	for (int i = 0; i < 22; i++) {
		ImGui::Text("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			displayBuffer[i][0], displayBuffer[i][1], displayBuffer[i][2], displayBuffer[i][3], displayBuffer[i][4], displayBuffer[i][5],
			displayBuffer[i][6], displayBuffer[i][7], displayBuffer[i][8], displayBuffer[i][9], displayBuffer[i][10], displayBuffer[i][11]);
	}
}

void Stage::MoveMino()
{
	// 落とす
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

	if (input->IsTrigger(Key::W)) {
		while (!IsHit(minoX, minoY + 1, minoAngle)) { ++minoY; }
		ResetMino();
	}

	if (input->IsTrigger(Key::Q)) {
		if (!IsHit(minoX, minoY, (minoAngle + 1) % (int)MinoAngle::Max))
		{
			minoAngle = (minoAngle + 1) % (int)MinoAngle::Max;
		}
	}
}