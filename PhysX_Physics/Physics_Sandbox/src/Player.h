#pragma once

#include <PhysX_Object.h>

class Player : public PhysX_Object
{
public:

	Player();

	virtual void Update(float deltaTime) override;

private:

	float mSpeed = 5;

	glm::vec3 mMoveDir = glm::vec3(0);

};

