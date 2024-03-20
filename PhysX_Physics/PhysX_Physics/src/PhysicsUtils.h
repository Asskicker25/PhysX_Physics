#pragma once
#include <glm/glm.hpp>
#include <Physx/PxPhysicsAPI.h>
#include <vector>

struct RayHitInfo
{

};

extern bool IsLayerExists(const int& layer, const std::vector<int> listOfLayers);
extern bool Raycast(glm::vec3 startPos, glm::vec3 rayDir, float maxDistance, RayHitInfo& hitInfo, std::vector<int> layers);