#pragma once
#include "PhysX_Object_ColliderShape.h"

class BoxCollider : public BaseColliderShape
{
public:


	// Inherited via BaseColliderShape
	void InitializeGeometry(Model* model) override;

};

