#include "SphereCollider.h"

void SphereCollider::InitializeGeometry(Model* model)
{
	BaseColliderShape::InitializeGeometry(model);

	PxVec3 center = (mModelAABB.minimum + mModelAABB.maximum) * 0.5f;
	PxVec3 halfDiagonal = (mModelAABB.maximum - mModelAABB.minimum) * 0.5f;

	mRadius = PxMin(PxMin(halfDiagonal.x, halfDiagonal.y), halfDiagonal.z);

	mGeometry = new PxSphereGeometry();

	((PxSphereGeometry*)mGeometry)->radius = mRadius;
}
