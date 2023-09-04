#include "Block.h"

// ”‚ğ0‚©‚çˆê’è‚Ì”ÍˆÍ‚Ü‚Å‚Åƒ‹[ƒv‚³‚¹‚é
int Loop(int num, int max)
{
	num = num % max;
	// œ”‚ğ‘«‚µ‚Ä³‚Ì®”‚É‚·‚é
	if (num < 0) { num += max; }
	return num;
}

void Block::Initialize()
{
	blockArr.push_back({ -1,1 });
	blockArr.push_back({ 1,0 });
	blockArr.push_back({ 0,1 });
	blockPos = { 6,15 };
	fallTimer = 60;
	input = Input::GetInstance();
	parent = ModelManager::Create("cube");
	parent->worldTransform->scale *= 3.0f;
	for (const auto& arr : blockArr)
	{
		Object3d* model = ModelManager::Create("cube");
		model->worldTransform->parent = parent->worldTransform.get();
		model->worldTransform->translation.x = 2 * arr.x * model->worldTransform->scale.x;
		model->worldTransform->translation.y = 2 * arr.y * model->worldTransform->scale.y;
		models.push_back(model);
	}
}

void Block::Move()
{
	// ˆÚ“®
	blockPos.x += input->IsTrigger(Key::D) - input->IsTrigger(Key::A);
	blockPos.x = Loop(blockPos.x, 12);
	// ‰ñ“]
	parent->worldTransform->rotation.z += Angle((input->IsTrigger(Key::Left) - input->IsTrigger(Key::Right)) * 90);
}

void Block::Update()
{
	Move();
	if (fallTimer.Update() && (int)blockPos.y > 0)
	{
		blockPos.y -= 1;
	}
	parent->worldTransform->translation.x = 2 * blockPos.x * parent->worldTransform->scale.x;
	parent->worldTransform->translation.y = 2 * blockPos.y * parent->worldTransform->scale.y;
}

std::vector<Vector2> Block::GetWorldPos()
{
	std::vector<Vector2> ret;
	for (auto& bArr : blockArr)
	{
		Vector2 pos = bArr + blockPos;
		int divisor = 12; // œ”
		pos.x = (int)pos.x % 12;
		// œ”‚ğ‘«‚µ‚Ä³‚Ì®”‚É‚·‚é
		if (pos.x < 0) { pos.x += divisor; }
		ret.push_back(pos);
	}
	return ret;
}
