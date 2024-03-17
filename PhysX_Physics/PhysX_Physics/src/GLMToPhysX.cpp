#include "GLMToPhysX.h"

PxVec3 GLMVec3(const glm::vec3& value)
{
    return PxVec3(value.x, value.y, value.z);
}

PxQuat GLMQuat(const glm::quat& value)
{
    return PxQuat(value.x, value.y, value.z, value.w);
}

PxCombineMode::Enum LocalEnum(PhysicsMaterial::eCombineMode combineMode)
{
	switch (combineMode)
	{
	case PhysicsMaterial::eCombineMode::AVERAGE:	return PxCombineMode::eAVERAGE;
		
	case PhysicsMaterial::eCombineMode::MINIMUM:	return PxCombineMode::eMIN;
		
	case PhysicsMaterial::eCombineMode::MULTIPLY:	return PxCombineMode::eMULTIPLY;

	case PhysicsMaterial::eCombineMode::MAXIMUM:	return PxCombineMode::eMAX;
	};
}
