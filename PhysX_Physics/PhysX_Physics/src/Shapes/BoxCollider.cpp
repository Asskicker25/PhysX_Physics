#include "BoxCollider.h"

#include "../GLMToPhysX.h"
#include "../PhysX_Engine.h"

void BoxCollider::InitializeGeometry(PhysX_Object* phyObj)
{
	BaseColliderShape::InitializeGeometry(phyObj);

	mBoxGeometry = new PxBoxGeometry();

	mBoxGeometry->halfExtents.x = (mModelAABB.maximum.x - mModelAABB.minimum.x) * 0.5f;
	mBoxGeometry->halfExtents.y = (mModelAABB.maximum.y - mModelAABB.minimum.y) * 0.5f;
	mBoxGeometry->halfExtents.z = (mModelAABB.maximum.z - mModelAABB.minimum.z) * 0.5f;
}

PxGeometry* BoxCollider::GetGeometry()
{
	return mBoxGeometry;
}

void BoxCollider::UpdateGeometry(const PxGeometry& geometry)
{
}

void BoxCollider::DrawShape()
{
	modelAABB aabb;
	aabb.min = PxVec3ToGLM(mModelAABB.minimum);
	aabb.max = PxVec3ToGLM(mModelAABB.maximum);

	aabb.min += mModelTransform->position + mPositionOffset;
	aabb.max += mModelTransform->position + mPositionOffset;

	/*aabb.min = mModelTransform->GetTransformMatrix() * glm::vec4(aabb.min, 1.0f);
	aabb.max = mModelTransform->GetTransformMatrix() * glm::vec4(aabb.max, 1.0f);*/

	Renderer::GetInstance().DrawAABB(aabb, PhysX_Engine::gColliderColor, false, mModelTransform->rotation);
}
