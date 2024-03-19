#include "Player.h"

#include <Graphics/InputManager/InputManager.h>

Player::Player()
{
	name = "Player";
	LoadModel("res/Models/DefaultCube.fbx");
	transform.SetPosition(glm::vec3(0, 1, 0));
	transform.SetRotation(glm::vec3(0, 0, 0));
	Initialize(RigidBody::KINEMATIC, BaseColliderShape::BOX);

	mColliderShape->SetTriggerState(false);

}

void Player::Update(float deltaTime)
{
	return;

	mMoveDir.x = InputManager::GetInstance().GetAxisX();
	mMoveDir.z = InputManager::GetInstance().GetAxisY();

	SetVelocity(mMoveDir * mSpeed );

}

void Player::OnTriggerEnter(PhysX_Object* other)
{
	printf("Player Trigger Enter With : %s\n", other->name.c_str());
}

void Player::OnTriggerExit(PhysX_Object* other)
{
	printf("Player Trigger Exit With : %s\n", other->name.c_str());
}

void Player::OnCollisionEnter(PhysX_Object* other)
{
	printf("Player Collision Enter With : %s\n", other->name.c_str());
}

void Player::OnCollisionExit(PhysX_Object* other)
{
	printf("Player Collision Exit With : %s\n", other->name.c_str());
}

