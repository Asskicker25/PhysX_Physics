#pragma once

#include "PhysX_Object_ColliderShape.h"

class CapsuleCollider : public BaseColliderShape
{
public:
	float mHeight = 1.0f;
	float mRadius = 1.0f;

	glm::vec3 mRotationOffset = glm::vec3(0, 0, 90);

	PxCapsuleGeometry* mCapsuleGeometry = nullptr;

	// Inherited via BaseColliderShape
	void InitializeGeometry(PhysX_Object* phyObj) override;
	void UpdateGeometry(const PxGeometry& geometry) override;
	void DrawShape() override;
	glm::vec3 GetRotationOffset() override;
	glm::quat GetRotation() override;

	PxGeometry* GetGeometry() override;


	virtual void DrawShapeProperty();

};

