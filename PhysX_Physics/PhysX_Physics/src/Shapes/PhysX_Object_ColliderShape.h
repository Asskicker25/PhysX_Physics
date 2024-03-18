#pragma once
#include <PxPhysicsAPI.h>
#include <Graphics/Mesh/Model.h>
#include <Graphics/Renderer.h>

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

	SphereCollider* AsSphere();
	BoxCollider* AsBox();

	virtual void InitializeGeometry(Model* model);
	virtual void UpdateGeometry(const PxGeometry& geometry) = 0;
	virtual void DrawShape();

protected:

	PxBounds3 mModelAABB;
	Transform* mModelTransform = nullptr;
};