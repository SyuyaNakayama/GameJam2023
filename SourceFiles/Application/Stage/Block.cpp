#include "Block.h"

void Block::Initialize(float x, float y)
{
	//���ʂɂ���(�f�o�b�N�p...�c��)
	object = ModelManager::Create("cube");
	object->worldTransform->scale *= 5.0f;
	object->worldTransform->translation =
	{ -((float)x - 22 / 2) * 10, -((float)y - 12 / 2) * 10, 0.0f };
	

	//�~���ɂ���
	/*object = ModelManager::Create("block");
	object->worldTransform->scale *= 10.0f;
	object->worldTransform->translation = { 0.0f, -(float)y * 4.8f+55 , 0.0f };
	object->worldTransform->rotation.y = x * Angle(30);*/
}