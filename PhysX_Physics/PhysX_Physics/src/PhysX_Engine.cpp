#include "PhysX_Engine.h"
#include "GLMToPhysX.h"

#include "PhysX_Object.h"

using namespace physx;

PxDefaultAllocator		PhysX_Engine::gAllocator;
PxDefaultErrorCallback	PhysX_Engine::gErrorCallback;
PxFoundation* PhysX_Engine::gFoundation = NULL;
PxPvd* PhysX_Engine::gPvd = NULL;
PxPhysics* PhysX_Engine::gPhysics = NULL;
PxDefaultCpuDispatcher* PhysX_Engine::gDispatcher = NULL;
PxScene* PhysX_Engine::gScene = NULL;
PxMaterial* PhysX_Engine::gDefaultMaterial = NULL;


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


	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gDefaultMaterial);
	gScene->addActor(*groundPlane);
}

void PhysX_Engine::Update()
{
	gScene->simulate(mPhysicsProperties.mFixedStepTime);
	gScene->fetchResults(true);

	UpdateRender();
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

void PhysX_Engine::UpdateRender()
{
	PxU32 nbActors = gScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);

	if (!nbActors) return;

	std::vector<PxRigidActor*> actors(nbActors);
	gScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);

	PxShape* shapes[MAX_NUM_ACTOR_SHAPES];

	glm::vec3 actorPos;
	glm::quat actorRot;

	for (PxRigidActor* actor : actors)
	{
		if (actor->userData == NULL) continue;

		actorPos = glm::vec3(0);
		actorRot = glm::quat(0,0,0,0);

		const PxU32 nbShapes = actor->getNbShapes();
		PX_ASSERT(nbShapes <= MAX_NUM_ACTOR_SHAPES);

		actor->getShapes(shapes, nbShapes);

		for (PxU32 index = 0; index < nbShapes; index++)
		{
			const PxMat44 shapePose(PxShapeExt::getGlobalPose(*shapes[index], *actor));
			const PxGeometry& geom = shapes[index]->getGeometry();

			actorPos += PxVec3ToGLM(shapePose.getPosition());
			actorRot += PxQuatToGLM(PxQuat(PxMat3FromMat4(shapePose)));
		}

		actorPos /= nbShapes;
		actorRot /= nbShapes;


		PhysX_Object* phyObj = (PhysX_Object*)actor->userData;
		phyObj->transform.SetPosition(actorPos);
		phyObj->transform.SetQuatRotation(actorRot);
	}

}

