#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

#include "PhysicsMaterial.h"

#include <PhysX/PxPhysicsAPI.h>

using namespace physx;

extern PxVec3 GLMVec3(const glm::vec3& value);
extern PxQuat GLMQuat(const glm::quat& value);

extern PxMat33 PxMat3FromMat4(const PxMat44& value);

extern glm::vec3 PxVec3ToGLM(const PxVec3& value);
extern glm::quat PxQuatToGLM(const PxQuat& value);
extern glm::mat4 PxMatToGLM(const PxMat44& value);

extern PxCombineMode::Enum LocalEnum(PhysicsMaterial::eCombineMode combineMode);
