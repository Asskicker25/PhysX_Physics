#include "PhysicsUtils.h"
#include "PhysX_Engine.h"
#include "PhysX_Object.h"
#include "GLMToPhysX.h"

using namespace physx;

bool IsLayerExists(const int& layer, const std::vector<int> listOfLayers)
{
	for (const int& it : listOfLayers)
	{
		if (layer == it) return true;
	}

	return false;
}

bool Raycast(glm::vec3 startPos, glm::vec3 rayDir, float maxDistance, RayHitInfo& hitInfo, std::vector<int> layers)
{
	for (PhysX_Object* phyObj : PhysX_Engine::GetInstance().mListOfPhysicObjects)
	{
		if (!IsLayerExists(phyObj->layer, layers)) continue;

		PxTransform pxTranform(GLMVec3(phyObj->transform.position), GLMQuat(phyObj->mColliderShape->GetRotation()));

		PxGeomRaycastHit rayHit;
		if (PxGeometryQuery::raycast(GLMVec3(startPos), GLMVec3(rayDir), *phyObj->mColliderShape->GetGeometry(), pxTranform, maxDistance,
			PxHitFlag::eDEFAULT | PxHitFlag::eNORMAL | PxHitFlag::eANY_HIT | PxHitFlag::ePOSITION,
			100, &rayHit))
		{
			return true;
		}

	}


	return false;
}
