#include "Block.h"

Input* Block::input = Input::GetInstance();

// ����0������͈̔͂܂łŃ��[�v������
int Loop(int num, int max)
{
	num = num % max;
	// �����𑫂��Đ��̐����ɂ���
	if (num < 0) { num += max; }
	return num;
}

void Block::Initialize(float x, float y)
{
	//����
	/*object = ModelManager::Create("cube");
	object->worldTransform->scale *= 5.0f;
	object->worldTransform->translation = { -((float)x - 12 / 2) * 5 * 2 ,-((float)y - 22 / 2) * 5 * 2, 0.0f };*/

	//�~���ɂ���
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