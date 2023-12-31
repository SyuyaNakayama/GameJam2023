#pragma once
#include <json.hpp>
#include "Object3d.h"

struct ColliderData
{
	std::string type;
	Vector3 center, size, normal;
};

struct ObjectData
{
	std::string fileName;
	ColliderData collider;
	WorldTransform* worldTransform;
};

struct LevelData
{
	std::list<ObjectData> objects;

	void LoadJsonRecursive(nlohmann::json& object, WorldTransform* parent = nullptr);
};

class JsonLoader
{
private:
	const static std::string DEFAULT_BASE_DIRECTORY;

public:
	/// <param name = "fileName">拡張子なし文字列</param>
	static LevelData* LoadJson(const std::string& fileName);
};