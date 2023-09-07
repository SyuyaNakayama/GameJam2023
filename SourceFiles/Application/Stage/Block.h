#pragma once
#include "Timer.h"
#include "Input.h"
#include "Vector.h"
#include "ModelManager.h"
#include <vector>

class Block
{
private:
	static Input* input; // Input‚Ìƒ|ƒCƒ“ƒ^
	Object3d* object = nullptr;

	void Move();

public:
	void Initialize(float x, float y);
	void Update();
	Sprite* GetMainSprite() { return object->material.GetSprite(TexType::Main); }
};