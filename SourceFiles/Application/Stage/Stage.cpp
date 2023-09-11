#include "Stage.h"
#include <imgui.h>
#include "Timer.h"
#include "Quaternion.h"

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
	//乱数生成
	srand(time(nullptr));
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			blocks[y][x].Initialize((float)x, (float)y);
		}
	}
	Mtimer.Start();
	mino.Reset(nextMinoType);
	nextMinoType = rand() % (int)MinoType::Max;
	//床
	for (int i = 0; i < FIELD_WIDTH; ++i) { field[FIELD_HEIGHT - 1][i] = 1; }
}

void Stage::Update()
{
	ShowImGui();
	MoveMino();

	mino.shadowY = mino.posY;
	while (!IsHit(mino.posX, mino.shadowY + 1, mino.angle)) { mino.shadowY++; }

	Display();

	// 地面に接地したら少し動かせる
	if (IsHit(mino.posX, mino.posY + 1, mino.angle) && !mino.isEarth) { Mtimer.Start(); mino.isEarth = true; }

	if (Mtimer.Update()) {
		Mtimer.Start();

		//動かしてるmino
		if (IsHit(mino.posX, mino.posY + 1, mino.angle)) {
			MinoSet();
			mino.Reset(nextMinoType);
			nextMinoType = rand() % (int)MinoType::Max;
		}
		else { ++mino.posY; }

		Display();
	}

	// 揃っている行を探す
	for (int i = FIELD_HEIGHT - 2; i > 0; i--) { // 一番下は枠のため
		// 横一列の合計を求める
		sum[i] = std::accumulate(field[i].begin(), field[i].end(), 0);

		if (sum[i] != 12) { continue; } // 揃った時
		score += 100;
		// ミノ加速
		if (Mtimer.GetInterval() >= 0.1f)
		{
			level = score / 500;
			Mtimer = 1.0f - (float)level * 0.05;
		}
		// ミノを消す
		for (int j = 0; j < FIELD_WIDTH; ++j) {
			field[i][j] = 0;
			for (int x = i - 1; x > 0; x--) {
				field[x + 1][j] = field[x][j];
				field[x][j] = 0;
			}
		}
		//床
		for (int i = 0; i < FIELD_WIDTH; ++i) { field[FIELD_HEIGHT - 1][i] = 1; }
	}

	// 一番上まで積みあがったら終了
	if (sum[1] > 0) { isEnd = true; }
}

void Stage::MinoSet()
{
	for (int i = 0; i < MINO_HEIGHT; ++i) {
		for (int j = 0; j < MINO_WIDTH; ++j) {
			field[mino.posY + i][Loop(mino.posX + j, 12)] |= minoShapes[mino.type][mino.angle][i][j];
		}
	}
	mino.Reset(nextMinoType);
}

void Stage::Display()
{
	displayBuffer = field;

	for (int i = 0; i < MINO_HEIGHT; ++i)
	{
		for (int j = 0; j < MINO_WIDTH; ++j)
		{
			int minoFlag = minoShapes[mino.type][mino.angle][i][j];
			displayBuffer[mino.posY + i][Loop(mino.posX + j, 12)] |= minoFlag;
			displayBuffer[mino.shadowY + i][Loop(mino.posX + j, 12)] |= (minoFlag << 1);
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
			if (minoShapes[mino.type][argMinoAngle][i][j] && field[argMinoY + i][Loop(argMinoX + j, 12)])
			{
				return true;
			}
		}
	}
	return false;
}

void Stage::ShowImGui()
{
	ImGui::Text("nextMinoType:%d", nextMinoType);
	ImGui::Text("minoType:%d", mino.type);
	ImGui::Text("isEnd:%d", isEnd);
	ImGui::Text("score:%d", score);
	ImGui::Text("IsHit:%d", IsHit(mino.posX, mino.posY + 1, mino.angle));
	ImGui::Text("deleteNum:%d", deleteNum);
	ImGui::Text("mino.posX:%d", mino.posX);
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
	isMinoMoveY = fallTimer.Update() && !IsHit(mino.posX, mino.posY + 1, mino.angle) && input->IsInput(Key::S);
	if (isMinoMoveY) { ++mino.posY; }

	int minoMoveX = 0;
	bool isMinoMoveX = false;
	if (input->IsInput(Key::A)) { holdTimeA++; }
	else { holdTimeA = 0; }
	isMinoMoveX = !IsHit(Loop(mino.posX + 1, 12), mino.posY, mino.angle);
	isMinoMoveX &= (holdTimeA <= TO_MOVE_TIME && input->IsTrigger(Key::A)) || (holdTimeA > TO_MOVE_TIME && holdTimeA % 3 == 0);
	if (isMinoMoveX) { minoMoveX++; }

	if (input->IsInput(Key::D)) { holdTimeD++; }
	else { holdTimeD = 0; }
	isMinoMoveX = !IsHit(Loop(mino.posX - 1, 12), mino.posY, mino.angle);
	isMinoMoveX &= (holdTimeD <= TO_MOVE_TIME && input->IsTrigger(Key::D)) || (holdTimeD > TO_MOVE_TIME && holdTimeD % 3 == 0);
	if (isMinoMoveX) { minoMoveX--; }

	mino.posX = Loop(mino.posX + minoMoveX, 12);

	//	ハードドロップ
	if (input->IsTrigger(Key::W)) {
		while (!IsHit(mino.posX, mino.posY + 1, mino.angle)) { ++mino.posY; }
		MinoSet();
		mino.Reset(nextMinoType);
		nextMinoType = rand() % (int)MinoType::Max;
	}

	if (input->IsTrigger(Key::Space)) {
		if (!IsHit(mino.posX, mino.posY, (mino.angle + 1) % (int)MinoAngle::Max))
		{
			mino.angle = (mino.angle + 1) % (int)MinoAngle::Max;
		}
	}

	//ViewProjection* pCamera = ModelManager::GetViewProjection();
	//pCamera->eye = Quaternion::RotateVector(
	//	{ 0,0,-150 }, Quaternion::MakeAxisAngle(
	//		Vector3::MakeAxis(Axis::Y), (mino.posX - 1) * Angle(30)));
}

void Mino::Reset(int nextMinoType)
{
	posX = 5;
	posY = 0;
	type = nextMinoType;
	angle = 0;
	isEarth = false;
}