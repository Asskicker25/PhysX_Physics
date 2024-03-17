#pragma once
#include <iostream>

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

#include "PhysicsMaterial.h"

#define PVD_HOST "127.0.0.1"	

using namespace physx;

static PxDefaultAllocator		gAllocator;
static PxDefaultErrorCallback	gErrorCallback;
static PxFoundation*			gFoundation			= NULL;
static PxPvd*					gPvd				= NULL;
static PxPhysics*				gPhysics			= NULL;
static PxDefaultCpuDispatcher*	gDispatcher			= NULL;
static PxScene*					gScene				= NULL;
static PxMaterial*				gDefaultMaterial	= NULL;
	
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

	PhysicsProperties mPhysicsProperties;
};

