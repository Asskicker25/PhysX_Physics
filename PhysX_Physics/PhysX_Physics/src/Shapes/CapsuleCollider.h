#pragma once

#include "PhysX_Object_ColliderShape.h"

class CapsuleCollider : public BaseColliderShape
{
public:


	glm::vec3 mRotationOffset = glm::vec3(0, 0, 0);

	PxCapsuleGeometry* mCapsuleGeometry = nullptr;

	// Inherited via BaseColliderShape
	void InitializeGeometry(PhysX_Object* phyObj) override;
	void UpdateGeometry(const PxGeometry& geometry) override;
	void DrawShape() override;
	PxTransform GetRelativePos() override;
	glm::vec3 GetRotationOffset() override;
	glm::quat GetRotation() override;
	
	void SetRadius(float radius);
	void SetHeight(float height);

	PxGeometry* GetGeometry() override;


	virtual void DrawShapeProperty();

private:
	float mHeight = 1.0f;
	float mRadius = 1.0f;
};

