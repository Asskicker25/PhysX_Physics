#pragma once



class RigidBody
{
public:

	enum  ePhysicsState
	{
		NONE = -1,
		STATIC = 0,
		DYNAMIC = 1,
		KINEMATIC = 2
	};

	float mMass = 1;
	ePhysicsState mPhysicsState = ePhysicsState::NONE;
};