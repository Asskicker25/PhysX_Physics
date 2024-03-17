#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "PhysicsMaterial.h"

#include <PhysX/PxPhysicsAPI.h>

using namespace physx;

extern PxVec3 GLMVec3(const glm::vec3& value);
extern PxQuat GLMQuat(const glm::quat& value);

extern PxCombineMode::Enum LocalEnum(PhysicsMaterial::eCombineMode combineMode);