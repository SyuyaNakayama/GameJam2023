#pragma once
#include "ModelManager.h"

class Block
{
private:
	Object3d* object = nullptr;

public:
	void Initialize(float x, float y);
	Sprite* GetMainSprite() { return object->material.GetSprite(TexType::Main); }
};