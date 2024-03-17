#pragma once

class SphereCollider;
class BoxCollider;

class BaseColliderShape
{
public:

	enum eColliderShape
	{
		SPHERE = 0,
		BOX = 1,
		CAPSULE = 2,
		MESH = 3,
	};

	bool mIsTrigger = false;
	eColliderShape mShape = eColliderShape::SPHERE;

	SphereCollider* AsSphere();
	BoxCollider* AsBox();
};