#include "PhysX_Object.h"
#include "PhysX_Engine.h"

#include "GLMToPhysX.h"

#include "Shapes/SphereCollider.h"
#include "Shapes/BoxCollider.h"



void PhysX_Object::Initialize(RigidBody::ePhysicsState physicsState, BaseColliderShape::eColliderShape colliderShape)
{
	UpdateColliderShape(colliderShape);
	UpdatePhysicsState(physicsState);
}

void PhysX_Object::UpdatePhysicsState(RigidBody::ePhysicsState physicsState)
{
	//Return if no change in state
	if (mRigidBody.mPhysicsState == physicsState) return;

	RigidBody::ePhysicsState oldState = mRigidBody.mPhysicsState;

	mRigidBody.mPhysicsState = physicsState;

	if (physicsState == RigidBody::DYNAMIC && oldState == RigidBody::KINEMATIC ||
		physicsState == RigidBody::KINEMATIC && oldState == RigidBody::DYNAMIC)
	{
		UpdateKinematic(physicsState == RigidBody::KINEMATIC);
		return;
	}

	//Release the previous actor
	if (mRigidActor != nullptr)
	{
		mRigidActor->release();
	}

	PxTransform pxTranform(GLMVec3(transform.position), GLMQuat(transform.quaternionRotation));

	if (physicsState == RigidBody::STATIC)
	{
		mRigidActor = gPhysics->createRigidStatic(pxTranform);
	}
	else if (physicsState == RigidBody::DYNAMIC)
	{
		mRigidActor = gPhysics->createRigidDynamic(pxTranform);
	}
	else if (physicsState == RigidBody::KINEMATIC)
	{
		mRigidActor = gPhysics->createRigidDynamic(pxTranform);
		UpdateKinematic(true);
	}

}

void PhysX_Object::UpdateKinematic(bool isKinematic)
{
	((PxRigidDynamic*)mRigidActor)->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
}

void PhysX_Object::UpdateColliderShape(BaseColliderShape::eColliderShape colliderShape)
{
	if (mColliderShape != nullptr)
	{
		if (mColliderShape->mShape == colliderShape)
		{
			return;
		}
		else
		{
			delete mColliderShape;
		}
	}
	
	switch (mColliderShape->mShape)
	{
	case BaseColliderShape::SPHERE:
		mColliderShape = new SphereCollider();
		break;

	case BaseColliderShape::BOX:
		mColliderShape = new BoxCollider();
		break;
	}
}
