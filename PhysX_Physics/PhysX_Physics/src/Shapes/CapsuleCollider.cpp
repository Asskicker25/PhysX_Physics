#include "CapsuleCollider.h"
#include "../GLMToPhysX.h"
#include "../PhysX_Engine.h"

#include <Graphics/Panels/ImguiDrawUtils.h>

void CapsuleCollider::InitializeGeometry(PhysX_Object* phyObj)
{
	BaseColliderShape::InitializeGeometry(phyObj);

	mCapsuleGeometry = new PxCapsuleGeometry();

	float xExtend = (mModelAABB.maximum.x - mModelAABB.minimum.x) * 0.5f;
	float zExtend = (mModelAABB.maximum.z - mModelAABB.minimum.z) * 0.5f;

	mRadius = PxMax(zExtend, xExtend);
	mHeight = (mModelAABB.maximum.y - mModelAABB.minimum.y);
	mHeight -= mRadius * 2.0f;

	mCapsuleGeometry->halfHeight = mHeight * 0.5f;
	mCapsuleGeometry->radius = mRadius;
}


PxGeometry* CapsuleCollider::GetGeometry()
{
	return mCapsuleGeometry;
}

void CapsuleCollider::UpdateGeometry(const PxGeometry& geometry)
{
}

void CapsuleCollider::DrawShape()
{
	Renderer::GetInstance().DrawCube(mModelTransform->position, mModelTransform->rotation, glm::vec3(mRadius, mHeight * 0.5f, mRadius), PhysX_Engine::gColliderColor, false);
	
	glm::vec3 upCenter = mModelTransform->position + mModelTransform->GetUp() * mHeight * 0.5f;
	glm::vec3 downCenter = mModelTransform->position - mModelTransform->GetUp() * mHeight * 0.5f;
	Renderer::GetInstance().DrawSphere(upCenter, mRadius, PhysX_Engine::gColliderColor);
	Renderer::GetInstance().DrawSphere(downCenter, mRadius, PhysX_Engine::gColliderColor);
}

glm::vec3 CapsuleCollider::GetRotationOffset()
{
	return mRotationOffset;
}

glm::quat CapsuleCollider::GetRotation()
{
	glm::vec3 eulerAnglesRadians = glm::radians(mModelTransform->rotation + mRotationOffset);
	return  glm::quat(eulerAnglesRadians);
}

void CapsuleCollider::DrawShapeProperty()
{
	if (ImGuiUtils::DrawFloat("Height", mHeight))
	{
		mCapsuleGeometry->halfHeight = mHeight * 0.5f;
	}

	if (ImGuiUtils::DrawFloat("Radius", mRadius))
	{
		mCapsuleGeometry->radius = mRadius;
	}
}
