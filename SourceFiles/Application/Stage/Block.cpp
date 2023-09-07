#include "Block.h"

Input* Block::input = Input::GetInstance();

// ”‚ğ0‚©‚çˆê’è‚Ì”ÍˆÍ‚Ü‚Å‚Åƒ‹[ƒv‚³‚¹‚é
int Loop(int num, int max)
{
	num = num % max;
	// œ”‚ğ‘«‚µ‚Ä³‚Ì®”‚É‚·‚é
	if (num < 0) { num += max; }
	return num;
}

void Block::Initialize(float x, float y)
{
	object = ModelManager::Create("cube");
	object->worldTransform->scale *= 4.8f;
	object->worldTransform->translation = { -(x - 12 / 2) * 5 * 2, -(y - 22 / 2) * 5 * 2 };
}

void Block::Move()
{
}

void Block::Update()
{
	Move();
}