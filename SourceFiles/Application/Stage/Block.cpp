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