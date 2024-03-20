#pragma once

#include "../Object.h"
#include "../Transform.h"

#include <functional>

class EntityManager;

class Entity : public Object
{

public:

	virtual ~Entity() {};
	virtual void InitializeEntity(Entity* entity);
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void OnDestroy() = 0;

	virtual void OnPropertyDraw();
	virtual void OnSceneDraw();
	virtual void OnLayerChanged() {};

	virtual void Destroy();

	Transform transform;

	std::string entityId;
	std::string tag = "Untagged";
	std::string name = "UnNamed";

	int layer = 0;

	bool isStartInvoked = false;

	static std::function<void(Entity*)> OnLayerDraw;

};

