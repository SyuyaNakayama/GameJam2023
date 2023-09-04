#pragma once
#include "Timer.h"
#include "Input.h"
#include "Vector.h"
#include "ModelManager.h"
#include <vector>

class Block
{
private:
	FrameTimer fallTimer; // ��������C���^�[�o��
	Input* input = nullptr; // Input�̃|�C���^
	std::vector<Vector2> blockArr; // ���[�J�����W�ł̃u���b�N�z�u
	Vector2 blockPos; // ���S�̈ʒu
	Object3d* parent;
	std::vector<Object3d*> models{};

	void Move();

public:
	void Initialize();
	void Update();
	std::vector<Vector2> GetWorldPos();
};