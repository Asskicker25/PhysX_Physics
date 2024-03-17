#pragma once
#include <Graphics/Mesh/Model.h>
#include <PhysX/PxPhysicsAPI.h>

#include "PhysX_Object_RigidBody.h"
#include "Shapes/PhysX_Object_ColliderShape.h"

class PhysX_Engine;

using namespace physx;

class PhysX_Object : public Model
{
public:

	void Initialize(RigidBody::ePhysicsState physicsState = RigidBody::STATIC, BaseColliderShape::eColliderShape colliderShape = BaseColliderShape::SPHERE);

	PxRigidActor* mRigidActor = nullptr;

	RigidBody mRigidBody;
	BaseColliderShape* mColliderShape = nullptr;

private:

	void UpdatePhysicsState(RigidBody::ePhysicsState physicsState);
	void UpdateKinematic(bool isKinematic);
	void UpdateColliderShape(BaseColliderShape::eColliderShape colliderShape);
};

