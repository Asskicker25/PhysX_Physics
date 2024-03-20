#pragma once
#include <glm/glm.hpp>
#include <Physx/PxPhysicsAPI.h>
#include <vector>

class PhysX_Object;

struct RayHitInfo
{
	//Distance from rayOrigin to rayhit
	float mDistance = 0;

	//Ray hit world point
	glm::vec3 mPoint = glm::vec3(0);

	//Surface normal of ray hit
	glm::vec3 mNormal = glm::vec3(0);

	//The physics obj hit
	PhysX_Object* mPhyObj = nullptr;
	
};

extern bool IsLayerExists(const int& layer, const std::vector<int> listOfLayers);
extern bool Raycast(glm::vec3 startPos, glm::vec3 rayDir, float maxDistance, RayHitInfo& hitInfo, std::vector<int> layers);