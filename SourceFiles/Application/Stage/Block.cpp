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
	//•½–Ê
	/*object = ModelManager::Create("cube");
	object->worldTransform->scale *= 5.0f;
	object->worldTransform->translation = { -((float)x - 12 / 2) * 5 * 2 ,-((float)y - 22 / 2) * 5 * 2, 0.0f };*/

	//‰~’Œ‚É‚·‚é
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