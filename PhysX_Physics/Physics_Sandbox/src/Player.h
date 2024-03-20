#pragma once

#include <PhysX_Object.h>

class Player : public PhysX_Object
{
public:

	Player();

	virtual void Update(float deltaTime) override;
	virtual void OnTriggerEnter(PhysX_Object* other);
	virtual void OnTriggerExit(PhysX_Object* other);

	void OnCollisionEnter(PhysX_Object* other, const CollisionInfo& collisionInfo) override;
	void OnCollisionExit(PhysX_Object* other) override;

private:

	float mSpeed = 5;

	glm::vec3 mMoveDir = glm::vec3(0);

};

