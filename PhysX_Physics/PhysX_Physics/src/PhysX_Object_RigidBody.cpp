#include "PhysX_Object_RigidBody.h"
#include "PhysX_Object.h"

#include <Graphics/Panels/ImguiDrawUtils.h>


void RigidBody::Initialize(PhysX_Object* phyObj)
{
	mPhyObj = phyObj;

	SetMass(mMass);
}

void RigidBody::DrawProperty()
{

	if (!ImGui::TreeNodeEx("RigidBody", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
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
