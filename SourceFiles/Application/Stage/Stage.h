#pragma once
#include <array>
#include "Block.h"

class Stage
{
private:
	std::array<std::array<bool, 12>, 15> stage; // 縦15 * 横12マス
	Block block; // 現在落ちているブロック

public:
	void Initialize();
	void Update();
};