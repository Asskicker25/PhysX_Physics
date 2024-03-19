#pragma once
#include <iostream>
#include <vector>

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

#include "PhysicsMaterial.h"
#include "PhysX_CollisionCallback.h"

#define PVD_HOST				"127.0.0.1"	
#define MAX_NUM_ACTOR_SHAPES	128

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

	static glm::vec4				gColliderColor;


	static PxFilterFlags ContactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize);

	PhysicsProperties mPhysicsProperties;
	PhysX_CollisionCallback mCollisionCallback;

private:

	void UpdateRender();
};

