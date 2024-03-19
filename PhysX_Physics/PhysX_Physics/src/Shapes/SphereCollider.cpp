#include "SphereCollider.h"

#include "../PhysX_Engine.h"

void SphereCollider::InitializeGeometry(PhysX_Object* phyObj)
{
	BaseColliderShape::InitializeGeometry(phyObj);

	PxVec3 center = (mModelAABB.minimum + mModelAABB.maximum) * 0.5f;
	PxVec3 halfDiagonal = (mModelAABB.maximum - mModelAABB.minimum) * 0.5f;

	mRadius = PxMin(PxMin(halfDiagonal.x, halfDiagonal.y), halfDiagonal.z);

	mGeometry = new PxSphereGeometry();
	mSphereGeometry = ((PxSphereGeometry*)mGeometry);
	mSphereGeometry->radius = mRadius;

}

void SphereCollider::UpdateGeometry(const PxGeometry& geometry)
{
	//((PxSphereGeometry*)mGeometry)->radius = ((PxSphereGeometry&)geometry).radius;
}

void SphereCollider::DrawShape()
{
	Renderer::GetInstance().DrawSphere(mModelTransform->position, mSphereGeometry->radius, PhysX_Engine::GetInstance().gColliderColor);
}
