#pragma once
#include "PhysX_Object_ColliderShape.h"


class SphereCollider : public BaseColliderShape
{
public:

	float mRadius = 0;

	// Inherited via BaseColliderShape
	void InitializeGeometry(Model* model) override;

};

