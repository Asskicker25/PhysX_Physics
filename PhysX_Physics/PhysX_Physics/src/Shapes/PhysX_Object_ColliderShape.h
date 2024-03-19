#pragma once
#include <PxPhysicsAPI.h>
#include <Graphics/Mesh/Model.h>
#include <Graphics/Renderer.h>

using namespace physx;

class SphereCollider;
class BoxCollider;
class PhysX_Object;

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

	PxShape* mColliderShape = nullptr;
	PxGeometry* mGeometry = nullptr;

	SphereCollider* AsSphere();
	BoxCollider* AsBox();

	virtual void InitializeGeometry(PhysX_Object* phyObj);
	virtual void UpdateGeometry(const PxGeometry& geometry) = 0;
	virtual void DrawShape();

	void DrawProperty();
	void SetTriggerState(bool isTrigger = true);

protected:

	PxBounds3 mModelAABB;
	PhysX_Object* mPhyObj = nullptr;
	Transform* mModelTransform = nullptr;
};