#include "SphereCollider.h"
#include "../PhysX_Engine.h"
#include "../PhysX_Object.h"

#include <Graphics/Panels/ImguiDrawUtils.h>

void SphereCollider::InitializeGeometry(PhysX_Object* phyObj)
{
	BaseColliderShape::InitializeGeometry(phyObj);

	PxVec3 center = (mModelAABB.minimum + mModelAABB.maximum) * 0.5f;
	PxVec3 halfDiagonal = (mModelAABB.maximum - mModelAABB.minimum) * 0.5f;

	float radius = PxMin(PxMin(halfDiagonal.x, halfDiagonal.y), halfDiagonal.z);

	mSphereGeometry = new PxSphereGeometry();
	SetRadius(radius);
}

PxGeometry* SphereCollider::GetGeometry()
{
	return mSphereGeometry;
}

void SphereCollider::UpdateGeometry(const PxGeometry& geometry)
{
	//((PxSphereGeometry*)mGeometry)->radius = ((PxSphereGeometry&)geometry).radius;
}

void SphereCollider::DrawShape()
{
	Renderer::GetInstance().DrawSphere(mModelTransform->position, mRadius, PhysX_Engine::GetInstance().gColliderColor);
}



void SphereCollider::DrawShapeProperty()
{
	if (ImGuiUtils::DrawFloat("Radius", mRadius))
	{
		SetRadius(mRadius);
	}
}

void SphereCollider::SetRadius(float radius)
{
	mRadius = radius;
	mSphereGeometry->radius = radius;
}
