#include "Block.h"

void Block::Initialize()
{
	blockArr.push_back({ 0,0 });
	blockArr.push_back({ 0,1 });
	blockArr.push_back({ 0,-1 });
	blockPos = { 6,15 };
	fallTimer = 60;
	input = Input::GetInstance();
	model = ModelManager::Create("cube");
	model->worldTransform->scale *= 3.0f;
}

void Block::Update()
{
	blockPos.x += input->IsTrigger(Key::D);
	blockPos.x -= input->IsTrigger(Key::A);
	blockPos.x = NumberLoop(blockPos.x, 12);
	if (fallTimer.Update() && (int)blockPos.y > 0) { blockPos.y -= 1; }
	model->worldTransform->translation.x = 2 * blockPos.x * model->worldTransform->scale.x;
	model->worldTransform->translation.y = 2 * blockPos.y * model->worldTransform->scale.y;
}

std::vector<Vector2> Block::GetWorldPos()
{
	std::vector<Vector2> ret;
	for (auto& bArr : blockArr)
	{
		Vector2 pos = bArr + blockPos;
		pos.x = NumberLoop(pos.x, 12);
		//int divisor = 12; // œ”
		//pos.x = (int)pos.x % 12;
		//// œ”‚ğ‘«‚µ‚Ä³‚Ì®”‚É‚·‚é
		//if (pos.x < 0) { pos.x += divisor; }
		ret.push_back(pos);
	}
	return ret;
}
