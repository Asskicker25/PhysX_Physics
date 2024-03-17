#pragma once

struct PhysicsMaterial
{
	enum class eCombineMode
	{
		AVERAGE		= 0,
		MINIMUM		= 1,
		MULTIPLY	= 2,
		MAXIMUM		= 3
	};

	float mDynamicFriction	= 0.5f;
	float mStaticFriction	= 0.5f;
	float mBounciness		= 0.6f;

	eCombineMode mFrictionCombineMode	= eCombineMode::AVERAGE;
	eCombineMode mBounceCombineMode		= eCombineMode::AVERAGE;

};