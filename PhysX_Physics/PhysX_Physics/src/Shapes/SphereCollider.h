#pragma once
#include "PhysX_Object_ColliderShape.h"


class SphereCollider : public BaseColliderShape
{
public:

	float mRadius = 0;

	PxSphereGeometry* mSphereGeometry = nullptr;

	// Inherited via BaseColliderShape
	void InitializeGeometry(PhysX_Object* phyObj) override;
	void UpdateGeometry(const PxGeometry& geometry) override;
	void DrawShape() override;
	PxGeometry* GetGeometry() override;
	virtual void DrawShapeProperty();

	void SetRadius(float radius);

};

