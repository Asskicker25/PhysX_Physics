#include "PhysX_Object.h"
#include "PhysX_Engine.h"

#include "GLMToPhysX.h"

#include "Shapes/SphereCollider.h"
#include "Shapes/BoxCollider.h"
#include "Shapes/CapsuleCollider.h"



void PhysX_Object::Initialize(RigidBody::ePhysicsState physicsState, BaseColliderShape::eColliderShape colliderShape)
{

	UpdateColliderShape(colliderShape);
	//UpdatePhysicsState(physicsState);
	//PhysX_Engine::gScene->addActor(*mRigidActor);

	mRigidBody.mPhysicsState = physicsState;

	PhysX_Engine::GetInstance().AddPhysicsObject(this);
}

void PhysX_Object::Render()
{
	if (mColliderShape == nullptr) return;

	mColliderShape->DrawShape();
}

void PhysX_Object::InitializeRigidActor()
{
	//Return if no change in state
	PxTransform pxTranform(GLMVec3(transform.position), GLMQuat(mColliderShape->GetRotation()));

	if (mRigidBody.mPhysicsState == RigidBody::STATIC)
	{
		mRigidActor = PhysX_Engine::gPhysics->createRigidStatic(pxTranform);
	}
	else if (mRigidBody.mPhysicsState == RigidBody::DYNAMIC)
	{
		mRigidActor = PhysX_Engine::gPhysics->createRigidDynamic(pxTranform);

	}
	else if (mRigidBody.mPhysicsState == RigidBody::KINEMATIC)
	{
		mRigidActor = PhysX_Engine::gPhysics->createRigidDynamic(pxTranform);
		UpdateKinematic(true);
	}


	PxShape* shape = PhysX_Engine::gPhysics->createShape(*mColliderShape->GetGeometry(), *PhysX_Engine::gDefaultMaterial);
	mRigidActor->attachShape(*shape);
	mColliderShape->mColliderShape = &(*shape);

	PhysX_Engine::gScene->addActor(*mRigidActor);
	mRigidActor->userData = this;
	mRigidBody.Initialize(this);

	mColliderShape->OnAddedToScene();

	mRigidActor->setGlobalPose(pxTranform,true);

	//((PxRigidDynamic*)mRigidActor)->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);
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

	switch (colliderShape)
	{
	case BaseColliderShape::SPHERE:
		mColliderShape = new SphereCollider();
		break;

	case BaseColliderShape::BOX:
		mColliderShape = new BoxCollider();
		break;
	case BaseColliderShape::CAPSULE:
		mColliderShape = new CapsuleCollider();
		break;
	default: 
		mColliderShape = new SphereCollider();
		break;
	}

	mColliderShape->InitializeGeometry(this);

	//shape->release();

}

void PhysX_Object::SetVelocity(glm::vec3 velocity)
{
	if (mRigidBody.mPhysicsState == RigidBody::DYNAMIC)
	{
		((PxRigidDynamic*)mRigidActor)->setLinearVelocity(GLMVec3(velocity), true);
	}
}

void PhysX_Object::OnPropertyDraw()
{
	Model::OnPropertyDraw();

	mRigidBody.DrawProperty();
	mColliderShape->DrawProperty();
}


glm::vec3 PhysX_Object::GetVelocity()
{
	if (mRigidBody.mPhysicsState == RigidBody::DYNAMIC)
	{
		return PxVec3ToGLM(((PxRigidDynamic*)mRigidActor)->getLinearVelocity());
	}

	return glm::vec3(0);
}

void PhysX_Object::OnCollisionEnter(PhysX_Object* other, const CollisionInfo& collisionInfo)
{
	printf("Collision Enter\n");
}

void PhysX_Object::OnCollisionExit(PhysX_Object* other)
{
	printf("Collision Exit\n");
}