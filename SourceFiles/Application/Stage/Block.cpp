#include "Block.h"

void Block::Initialize(float x, float y)
{
	//‰~’Œ‚É‚·‚é
	object = ModelManager::Create("block");
	object->worldTransform->scale *= 10.0f;
	object->worldTransform->translation = { 0.0f, -(float)y * 4.8f+55 , 0.0f };
	object->worldTransform->rotation.y = x * Angle(30);
}