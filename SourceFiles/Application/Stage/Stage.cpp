#include "Stage.h"
#include "Timer.h"
#include "Quaternion.h"

int Stage::scoreMem = 0;

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
	minoTypeRan = new Random_Int(0, (int)MinoType::Max-1);
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			blocks[y][x].Initialize((float)x, (float)y);
		}
	}

	Mtimer.Start();
	nextMinoType = (*minoTypeRan)();
	mino.Reset(nextMinoType);

	//床
	for (int i = 0; i < FIELD_WIDTH; ++i) { field[FIELD_HEIGHT - 1][i] = 1; }

	// SE
	se["Rotate"].Initialize(L"rotate.mp3");
	se["Harddrop"].Initialize(L"harddrop.mp3");
	se["Delete"].Initialize(L"delete.mp3");
}

void Stage::Update()
{
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
			nextMinoType = (*minoTypeRan)();
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
		se["Delete"].Play();
	}

	// 一番上まで積みあがったら終了
	if (sum[1] > 0) { isEnd = true; scoreMem = score; }
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
	for (int i = 0; i < FIELD_WIDTH; ++i)
	{
		displayBuffer[0][i] |= 4;
		displayBuffer[1][i] |= 4;
	}

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
				blocks[i][j].GetMainSprite()->color = { 0.9f, 0.0f, 0.0f };
			}
			else if (displayBuffer[i][j] & 2)
			{
				blocks[i][j].GetMainSprite()->color = { 0.3f, 0.6f, 0.3f };
			}
			else if (displayBuffer[i][j] & 4)
			{
				blocks[i][j].GetMainSprite()->color = { 0.6f, 0.3f, 0.3f };
			}
			else
			{
				blocks[i][j].GetMainSprite()->color = { 0.6f, 0.6f, 0.6f };
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

	if (minoMoveX) { se["Rotate"].Play(); }
	mino.posX = Loop(mino.posX + minoMoveX, 12);

	//	ハードドロップ
	if (input->IsTrigger(Key::W)) {
		while (!IsHit(mino.posX, mino.posY + 1, mino.angle)) { ++mino.posY; }
		MinoSet();
		mino.Reset(nextMinoType);
		nextMinoType = (*minoTypeRan)();
		se["Harddrop"].Play();
	}

	if (input->IsTrigger(Key::Space)) {
		if (!IsHit(mino.posX, mino.posY, (mino.angle + 1) % (int)MinoAngle::Max))
		{
			mino.angle = (mino.angle + 1) % (int)MinoAngle::Max;
			se["Rotate"].Play();
		}
	}

	ViewProjection* pCamera = ModelManager::GetViewProjection();
	pCamera->eye = Quaternion::RotateVector(
		{ 0,0,-150 }, Quaternion::MakeAxisAngle(
			Vector3::MakeAxis(Axis::Y), (mino.posX - 1) * Angle(30)));
}

void Mino::Reset(int nextMinoType)
{
	posX = 5;
	posY = 0;
	type = nextMinoType;
	angle = 0;
	isEarth = false;
}