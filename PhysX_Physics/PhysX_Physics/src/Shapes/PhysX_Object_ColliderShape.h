#pragma once
#include <PxPhysicsAPI.h>
#include <Graphics/Mesh/Model.h>

using namespace physx;

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

	PxGeometry* mGeometry = nullptr;

	virtual void InitializeGeometry(Model* model);

	SphereCollider* AsSphere();
	BoxCollider* AsBox();

protected:

	PxBounds3 mModelAABB;
};