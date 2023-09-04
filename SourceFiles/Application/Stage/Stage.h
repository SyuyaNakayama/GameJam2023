#pragma once
#include <array>
#include "Block.h"

class Stage
{
private:
	std::array<std::array<bool, 12>, 15> stage; // �c15 * ��12�}�X
	Block block; // ���ݗ����Ă���u���b�N

public:
	void Initialize();
	void Update();
};