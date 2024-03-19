#pragma once

#include <PhysX_Object.h>

class Player : public PhysX_Object
{
public:

	Player();

	virtual void Update(float deltaTime) override;
	virtual void OnTriggerEnter(PhysX_Object* other);
	virtual void OnTriggerExit(PhysX_Object* other);

	virtual void OnCollisionEnter(PhysX_Object* other, CollisionInfo collisionInfo);
	virtual void OnCollisionExit(PhysX_Object* other);

private:

	float mSpeed = 5;

	glm::vec3 mMoveDir = glm::vec3(0);

};

