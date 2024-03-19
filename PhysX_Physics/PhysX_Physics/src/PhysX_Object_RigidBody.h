#pragma once

class PhysX_Object;

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

	void Initialize(PhysX_Object* phyObj);
	void DrawProperty();
	void SetMass(float mass);

	float mMass = 1;
	ePhysicsState mPhysicsState = ePhysicsState::NONE;

	PhysX_Object* mPhyObj = nullptr;
};