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
	object = ModelManager::Create("block");
	object->worldTransform->scale *= 10.0f;

	//‰~’Œ‚É‚·‚é
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