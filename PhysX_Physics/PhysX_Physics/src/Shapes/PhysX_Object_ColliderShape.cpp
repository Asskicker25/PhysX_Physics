#include "PhysX_Object_ColliderShape.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "MeshCollider.h"

#include "../PhysX_Engine.h"
#include "../PhysX_Object.h"

#include "../GLMToPhysX.h"
#include "../ShapeUtils.h"

#include <Graphics/Panels/ImguiDrawUtils.h>

SphereCollider* BaseColliderShape::AsSphere()
{
	return (SphereCollider*)this;
}

BoxCollider* BaseColliderShape::AsBox()
{
	return (BoxCollider*)this;
}

CapsuleCollider* BaseColliderShape::AsCapsule()
{
	return (CapsuleCollider*)this;
}

MeshCollider* BaseColliderShape::AsMesh()
{
	return (MeshCollider*)this;
}

void BaseColliderShape::InitializeGeometry(PhysX_Object* phyObj)
{
	mPhyObj = phyObj;
	mModelTransform = &phyObj->transform;

	for (MeshAndMaterial* mesh : phyObj->meshes)
	{
		UpdateAABBExtends(mModelAABB, CalcualteAABB(mesh->mesh->vertices));
	}

	mModelAABB.minimum.x *= phyObj->transform.scale.x;
	mModelAABB.minimum.y *= phyObj->transform.scale.y;
	mModelAABB.minimum.z *= phyObj->transform.scale.z;

	mModelAABB.maximum.x *= phyObj->transform.scale.x;
	mModelAABB.maximum.y *= phyObj->transform.scale.y;
	mModelAABB.maximum.z *= phyObj->transform.scale.z;
}

void BaseColliderShape::OnAddedToScene()
{
	SetTriggerState(mIsTrigger);
}

void BaseColliderShape::DrawShape()
{
	modelAABB aabb;
	aabb.min = PxVec3ToGLM(mModelAABB.minimum);
	aabb.max = PxVec3ToGLM(mModelAABB.maximum);

	aabb.min += mModelTransform->position;
	aabb.max += mModelTransform->position;

	Renderer::GetInstance().DrawAABB(aabb, PhysX_Engine::gColliderColor, false);
}

glm::quat BaseColliderShape::GetRotation()
{
	return mModelTransform->quaternionRotation;
}

glm::vec3 BaseColliderShape::GetRotationOffset()
{
	return glm::vec3(0);
}

void BaseColliderShape::DrawProperty()
{
	if (!ImGui::TreeNodeEx("Collider", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	if (ImGuiUtils::DrawBool("IsTrigger", mIsTrigger))
	{
		SetTriggerState(mIsTrigger);
	}

	DrawShapeProperty();

	ImGui::TreePop();
}

void BaseColliderShape::SetTriggerState(bool isTrigger)
{
	mIsTrigger = isTrigger;

	if (mPhyObj->mRigidActor != nullptr)
	{
		mPhyObj->mRigidActor->detachShape(*mColliderShape);

		if (mIsTrigger)
		{
			mColliderShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, mIsTrigger);
			mColliderShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !mIsTrigger);
		}
		else
		{
			mColliderShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, mIsTrigger);
			mColliderShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !mIsTrigger);
		}

		mPhyObj->mRigidActor->attachShape(*mColliderShape);

		if (mPhyObj->mRigidBody.mPhysicsState == RigidBody::DYNAMIC)
		{
			((PxRigidDynamic*)mPhyObj->mRigidActor)->wakeUp();
		}
	}

}
