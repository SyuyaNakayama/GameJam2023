#include "Block.h"

void Block::Initialize(float x, float y)
{
	//平面にする(デバック用...残せ)
	object = ModelManager::Create("cube");
	object->worldTransform->scale *= 5.0f;
	object->worldTransform->translation =
	{ -((float)x - 22 / 2) * 10, -((float)y - 12 / 2) * 10, 0.0f };
	

	//円柱にする
	/*object = ModelManager::Create("block");
	object->worldTransform->scale *= 10.0f;
	object->worldTransform->translation = { 0.0f, -(float)y * 4.8f+55 , 0.0f };
	object->worldTransform->rotation.y = x * Angle(30);*/
}