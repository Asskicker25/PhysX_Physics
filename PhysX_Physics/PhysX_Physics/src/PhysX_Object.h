#pragma once
#include <Graphics/Mesh/Model.h>
#include <PhysX/PxPhysicsAPI.h>

#include "PhysX_Object_RigidBody.h"
#include "Shapes/PhysX_Object_ColliderShape.h"

#include "CollisionInfo.h"


class PhysX_Engine;

using namespace physx;


class PhysX_Object : public Model
{
public:

	void Initialize(RigidBody::ePhysicsState physicsState = RigidBody::STATIC, BaseColliderShape::eColliderShape colliderShape = BaseColliderShape::SPHERE);
	
	virtual void Render() override;
	virtual void OnPropertyDraw() override;

	virtual void OnTriggerEnter(PhysX_Object* other) {};
	virtual void OnTriggerExit(PhysX_Object* other) {};

	virtual void OnCollisionEnter(PhysX_Object* other, CollisionInfo collisionInfo) {};
	virtual void OnCollisionExit(PhysX_Object* other) {};

	void SetVelocity(glm::vec3 velocity);

	glm::vec3 GetVelocity();

	PxRigidActor* mRigidActor = nullptr;

	RigidBody mRigidBody;
	BaseColliderShape* mColliderShape = nullptr;

	std::vector<glm::vec3> mListOfCollisionPoints;


private:

	void UpdatePhysicsState(RigidBody::ePhysicsState physicsState);
	void UpdateKinematic(bool isKinematic);
	void UpdateColliderShape(BaseColliderShape::eColliderShape colliderShape);

};

