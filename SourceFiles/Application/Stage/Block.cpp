#include "Block.h"

Input* Block::input = Input::GetInstance();

// 数を0から一定の範囲まででループさせる
int Loop(int num, int max)
{
	num = num % max;
	// 除数を足して正の整数にする
	if (num < 0) { num += max; }
	return num;
}

void Block::Initialize(float x, float y)
{
	//平面
	/*object = ModelManager::Create("cube");
	object->worldTransform->scale *= 5.0f;
	object->worldTransform->translation = { -((float)x - 12 / 2) * 5 * 2 ,-((float)y - 22 / 2) * 5 * 2, 0.0f };*/

	//円柱にする
	object = ModelManager::Create("block");
	object->worldTransform->scale *= 10.0f;
	object->worldTransform->translation = { 0.0f, -(float)y * 5.0f , 0.0f };
	object->worldTransform->rotation.y = x * Angle(30);
}

void Block::Move()
{
}

void Block::Update()
{
	Move();
}