#pragma once
#include <PxPhysicsAPI.h>
#include <Mesh/Model.h>

using namespace physx;

extern PxBounds3 CalcualteAABB(std::vector<Vertex>& vertices);

extern void UpdateAABBExtends(PxBounds3& outAabb, PxBounds3 inAabb);