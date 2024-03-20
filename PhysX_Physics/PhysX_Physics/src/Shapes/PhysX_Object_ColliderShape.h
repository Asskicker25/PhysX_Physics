#pragma once
#include <PxPhysicsAPI.h>
#include <Graphics/Mesh/Model.h>
#include <Graphics/Renderer.h>

using namespace physx;

class SphereCollider;
class BoxCollider;
class CapsuleCollider;
class MeshCollider;

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

	SphereCollider* AsSphere();
	BoxCollider* AsBox();
	CapsuleCollider* AsCapsule();
	MeshCollider* AsMesh();

	virtual PxGeometry* GetGeometry() = 0;

	virtual void InitializeGeometry(PhysX_Object* phyObj);
	virtual void OnAddedToScene();
	virtual void UpdateGeometry(const PxGeometry& geometry) = 0;
	virtual void DrawShape();
	virtual void DrawShapeProperty() {};
	virtual glm::quat GetRotation();
	virtual glm::vec3 GetRotationOffset();
	void DrawProperty();
	void SetTriggerState(bool isTrigger = true);

protected:

	PxBounds3 mModelAABB;
	PhysX_Object* mPhyObj = nullptr;
	Transform* mModelTransform = nullptr;
};