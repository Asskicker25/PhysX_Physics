#include "PhysX_Engine.h"
#include "GLMToPhysX.h"

using namespace physx;

PxDefaultAllocator		PhysX_Engine::gAllocator;
PxDefaultErrorCallback	PhysX_Engine::gErrorCallback;
PxFoundation*			PhysX_Engine::gFoundation		= NULL;
PxPvd*					PhysX_Engine::gPvd				= NULL;
PxPhysics*				PhysX_Engine::gPhysics			= NULL;
PxDefaultCpuDispatcher* PhysX_Engine::gDispatcher		= NULL;
PxScene*				PhysX_Engine::gScene			= NULL;
PxMaterial*				PhysX_Engine::gDefaultMaterial	= NULL;


PhysX_Engine& PhysX_Engine::GetInstance()
{
	static PhysX_Engine instance;
	return instance;
}

void PhysX_Engine::Initialize()
{
#pragma region Foundation Initialize

	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	if (!gFoundation)
	{
		std::cout << "PhysX Foundation Creation Failed!!!" << std::endl;

	}
#pragma endregion

#pragma region PVD Connect

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

#pragma endregion

#pragma region Create Global Physics

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

#pragma endregion

#pragma region Default Material

	gDefaultMaterial = gPhysics->createMaterial(
		mPhysicsProperties.mDefaultMaterial.mStaticFriction,
		mPhysicsProperties.mDefaultMaterial.mDynamicFriction,
		mPhysicsProperties.mDefaultMaterial.mBounciness
	);

	gDefaultMaterial->setFrictionCombineMode(LocalEnum(mPhysicsProperties.mDefaultMaterial.mFrictionCombineMode));
	gDefaultMaterial->setRestitutionCombineMode(LocalEnum(mPhysicsProperties.mDefaultMaterial.mBounceCombineMode));

#pragma endregion

#pragma region Create Physics Scene

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(mPhysicsProperties.mWorldGravity.x, mPhysicsProperties.mWorldGravity.y, mPhysicsProperties.mWorldGravity.z);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);


	PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

#pragma endregion

}

void PhysX_Engine::Update()
{
	gScene->simulate(mPhysicsProperties.mFixedStepTime);
	gScene->fetchResults(true);
}

void PhysX_Engine::Cleanup()
{
	PX_RELEASE(gScene);
	PX_RELEASE(gDispatcher);
	PX_RELEASE(gPhysics);
	if (gPvd)
	{
		PxPvdTransport* transport = gPvd->getTransport();
		gPvd->release();	gPvd = NULL;
		PX_RELEASE(transport);
	}
	PX_RELEASE(gFoundation);


	std::cout << "Physics Cleanup" << std::endl;
}

