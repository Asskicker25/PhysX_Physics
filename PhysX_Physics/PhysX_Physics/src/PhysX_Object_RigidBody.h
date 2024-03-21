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

	struct AxisConstraints
	{
		AxisConstraints() = default;
		AxisConstraints(bool x, bool y, bool z)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
		}

		bool X = false;
		bool Y = false;
		bool Z = false;
	};

	void Initialize(PhysX_Object* phyObj);
	void DrawProperty();
	void SetMass(float mass);
	void SetGravityState(bool enabled);

	bool mUseGravity = true;

	AxisConstraints mPositionConstraints;
	AxisConstraints mRotationConstraints;

	float mMass = 1;

	ePhysicsState mPhysicsState = ePhysicsState::NONE;

	PhysX_Object* mPhyObj = nullptr;
};