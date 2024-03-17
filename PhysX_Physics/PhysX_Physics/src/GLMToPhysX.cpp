#include "GLMToPhysX.h"

PxVec3 GLMVec3(const glm::vec3& value)
{
    return PxVec3(value.x, value.y, value.z);
}

PxQuat GLMQuat(const glm::quat& value)
{
    return PxQuat(value.x, value.y, value.z, value.w);
}

PxMat33 PxMat3FromMat4(const PxMat44& value)
{
	PxMat33 rotationMatrix;

	rotationMatrix.column0 = value.column0.getXYZ();
	rotationMatrix.column1 = value.column1.getXYZ();
	rotationMatrix.column2 = value.column2.getXYZ();

	return rotationMatrix;
}

glm::vec3 PxVec3ToGLM(const PxVec3& value)
{
	return glm::vec3(value.x, value.y, value.z);
}

glm::quat PxQuatToGLM(const PxQuat& value)
{
	return glm::quat(value.w, value.x, value.y, value.z);
}

glm::mat4 PxMatToGLM(const PxMat44& value)
{
	return glm::mat4(
		value.column0.x, value.column0.y, value.column0.z, value.column0.w,
		value.column1.x, value.column1.y, value.column1.z, value.column1.w,
		value.column2.x, value.column2.y, value.column2.z, value.column2.w,
		value.column3.x, value.column3.y, value.column3.z, value.column3.w
	);
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
