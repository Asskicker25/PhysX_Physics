#pragma once
#include "PhysX_Object_ColliderShape.h"

class BoxCollider : public BaseColliderShape
{
public:

	PxBoxGeometry* mBoxGeometry = nullptr;

	// Inherited via BaseColliderShape
	void InitializeGeometry(PhysX_Object* phyObj) override;
	void UpdateGeometry(const PxGeometry& geometry) override;
	virtual void DrawShape();

};

