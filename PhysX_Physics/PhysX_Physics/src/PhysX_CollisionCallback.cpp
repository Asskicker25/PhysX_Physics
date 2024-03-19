#include "PhysX_CollisionCallback.h"
#include "PhysX_Engine.h"
#include "PhysX_Object.h"

#include "GLMToPhysX.h"

void PhysX_CollisionCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
{
	printf("Constraint Break\n");
}

void PhysX_CollisionCallback::onWake(PxActor** actors, PxU32 count)
{
	printf("Wake\n");
}

void PhysX_CollisionCallback::onSleep(PxActor** actors, PxU32 count)
{
	printf("Sleep\n");
}

void PhysX_CollisionCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{

	PhysX_Object* collidedActor = (PhysX_Object*)pairHeader.actors[0]->userData;
	PhysX_Object* otherActor = (PhysX_Object*)pairHeader.actors[1]->userData;

	for (int i = 0; i < nbPairs; i++)
	{
		const PxContactPair& pair = pairs[i];

		if (pair.flags == PxContactPairFlag::eACTOR_PAIR_HAS_FIRST_TOUCH)
		{
			collidedActor->OnCollisionEnter(otherActor);
			otherActor->OnCollisionEnter(collidedActor);
		}
		else if (pair.flags == PxContactPairFlag::eACTOR_PAIR_LOST_TOUCH)
		{
			collidedActor->OnCollisionExit(otherActor);
			otherActor->OnCollisionExit(collidedActor);
		}

		std::vector<PxContactPairPoint> contactPoints;

		for (PxU32 i = 0; i < nbPairs; i++)
		{
			PxU32 contactCount = pairs[i].contactCount;
			if (contactCount)
			{
				contactPoints.resize(contactCount);
				pairs[i].extractContacts(&contactPoints[0], contactCount);

				for (PxU32 j = 0; j < contactCount; j++)
				{
					collidedActor->mListOfCollisionPoints.push_back(PxVec3ToGLM(contactPoints[j].position));
					otherActor->mListOfCollisionPoints.push_back(PxVec3ToGLM(contactPoints[j].position));
				}
			}
		}

	}


	//printf("Contact\n");
}

void PhysX_CollisionCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	PhysX_Object* triggerActor = nullptr;
	PhysX_Object* otherActor = nullptr;

	for (int i = 0; i < count; i++)
	{
		PxTriggerPair& pair = pairs[i];

		triggerActor = (PhysX_Object*)pair.triggerActor->userData;
		otherActor = (PhysX_Object*)pair.otherActor->userData;

		if (pair.status == PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			triggerActor->OnTriggerEnter(otherActor);
			otherActor->OnTriggerEnter(triggerActor);
		}
		else if (pair.status == PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			triggerActor->OnTriggerExit(otherActor);
			otherActor->OnTriggerExit(triggerActor);
		}
	}

}

void PhysX_CollisionCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
	printf("Advance\n");
}
