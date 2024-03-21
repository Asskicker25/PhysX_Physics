#include "PhysX_Object_RigidBody.h"
#include "PhysX_Object.h"

#include <Graphics/Panels/ImguiDrawUtils.h>


void RigidBody::Initialize(PhysX_Object* phyObj)
{
	mPhyObj = phyObj;

	SetMass(mMass);
	SetGravityState(mUseGravity);
}

void RigidBody::DrawProperty()
{

	if (!ImGui::TreeNodeEx("RigidBody", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	if (ImGuiUtils::DrawBool("UseGravity", mUseGravity))
	{
		SetGravityState(mUseGravity);
	}

	if (ImGuiUtils::DrawFloat("Mass", mMass))
	{
		SetMass(mMass);
	}


	ImGui::TreePop();
}

void RigidBody::SetMass(float mass)
{
	mMass = mass;
	if (mPhysicsState == DYNAMIC && mPhyObj != nullptr)
	{
		((PxRigidDynamic*)mPhyObj->mRigidActor)->setMass(mMass);
	}
}

void RigidBody::SetGravityState(bool enabled)
{
	mUseGravity = enabled;

	if (mPhysicsState == DYNAMIC && mPhyObj != nullptr)
	{
		mPhyObj->mRigidActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, (!mUseGravity));
		((PxRigidDynamic*)mPhyObj->mRigidActor)->wakeUp();
	}
}

