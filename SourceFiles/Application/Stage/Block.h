#pragma once
#include "Timer.h"
#include "Input.h"
#include "Vector.h"
#include "ModelManager.h"
#include <vector>

class Block
{
private:
	FrameTimer fallTimer; // 落下するインターバル
	Input* input = nullptr; // Inputのポインタ
	std::vector<Vector2> blockArr; // ローカル座標でのブロック配置
	Vector2 blockPos; // 中心の位置
	Object3d* parent;
	std::vector<Object3d*> models{};

	void Move();

public:
	void Initialize();
	void Update();
	std::vector<Vector2> GetWorldPos();
};