#include "Player.h"

#include <Graphics/InputManager/InputManager.h>
#include <Shapes/CapsuleCollider.h>

#include <PhysicsUtils.h>
#include <PhysX_Engine.h>

#include "AppSettings.h"

Player::Player()
{
	mRigidBody.mMaterial = new PhysicsMaterial();
	mRigidBody.mMaterial->mBounciness = 0.0f;

	PhysX_Engine::GetInstance().AddPhysicsMaterial(mRigidBody.mMaterial);

	name = "Player";
	LoadModel("Assets/Player.fbx");
	transform.SetPosition(glm::vec3(0, 2, 0));
	transform.SetRotation(glm::vec3(0, 0, 0));
	transform.SetScale(glm::vec3(0.05f));
	InitializePhysics(RigidBody::DYNAMIC, BaseColliderShape::CAPSULE);
	//mRigidBody.mRotationConstraints = RigidBody::AxisConstraints(true, true, true);
	mColliderShape->AsCapsule()->SetHeight(7);
	mColliderShape->AsCapsule()->SetRadius(1.5);
	mColliderShape->mPivotOffset.y = 5;
	//mRigidBody.mPositionConstraints = RigidBody::AxisConstraints(true, false, true);
	//mColliderShape->AsCapsule()->mHeight = 4;

	mColliderShape->SetTriggerState(false);

}

void Player::Update(float deltaTime)
{
	RayHitInfo info;
	if (Raycast(transform.position, transform.GetUp(), 10, info, { (int)Layer::Entity_Layer::RAYCAST }))
	{
		printf("Sphere Hit At : %.1f, %.1f, %.1f \n ", info.mPoint.x, info.mPoint.y, info.mPoint.z);
	}

	return;
	mMoveDir.x = InputManager::GetInstance().GetAxisX();
	mMoveDir.z = InputManager::GetInstance().GetAxisY();

	SetVelocity(mMoveDir * mSpeed);

}

void Player::OnTriggerEnter(PhysX_Object* other)
{
	printf("Player Trigger Enter With : %s\n", other->name.c_str());
}

void Player::OnTriggerExit(PhysX_Object* other)
{
	printf("Player Trigger Exit With : %s\n", other->name.c_str());
}

void Player::OnCollisionEnter(PhysX_Object* other, const CollisionInfo& collisionInfo)
{
	glm::vec3 point = collisionInfo.mListOfCollisionPoints[0];
	printf("Player Collision Enter With : %s at %.1f,%.1f,%.1f\n", other->name.c_str(), point.x, point.y, point.z);

}

void Player::OnCollisionExit(PhysX_Object* other)
{
	printf("Player Collision Exit With : %s\n", other->name.c_str());
}

