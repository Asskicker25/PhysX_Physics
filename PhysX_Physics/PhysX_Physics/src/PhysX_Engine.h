#pragma once
#include <iostream>

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

#include "PhysicsMaterial.h"

#define PVD_HOST "127.0.0.1"	

using namespace physx;

class PhysX_Engine
{
public:

	struct PhysicsProperties
	{
		float				mFixedStepTime = 0.01f;
		glm::vec3			mWorldGravity = glm::vec3(0, -9.8f, 0);
		PhysicsMaterial		mDefaultMaterial;

	};

	PhysX_Engine() = default;

	static PhysX_Engine& GetInstance();

	void Initialize();
	void Update();
	void Cleanup();

	static PxDefaultAllocator		gAllocator;
	static PxDefaultErrorCallback	gErrorCallback;
	static PxFoundation*			gFoundation;
	static PxPvd*					gPvd;
	static PxPhysics*				gPhysics;
	static PxDefaultCpuDispatcher*	gDispatcher;
	static PxScene*					gScene;
	static PxMaterial*				gDefaultMaterial;

	PhysicsProperties mPhysicsProperties;
};

