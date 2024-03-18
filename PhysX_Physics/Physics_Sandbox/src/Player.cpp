#include "Player.h"

#include <Graphics/InputManager/InputManager.h>

Player::Player()
{
	LoadModel("res/Models/DefaultCube.fbx");
	transform.SetPosition(glm::vec3(0, 1, 0));
	transform.SetRotation(glm::vec3(0, 0, 0));
	Initialize(RigidBody::KINEMATIC, BaseColliderShape::BOX);
}

void Player::Update(float deltaTime)
{
	mMoveDir.x = InputManager::GetInstance().GetAxisX();
	mMoveDir.z = InputManager::GetInstance().GetAxisY();

	SetVelocity(mMoveDir * mSpeed );

}
