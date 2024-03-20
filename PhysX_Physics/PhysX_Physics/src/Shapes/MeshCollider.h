#pragma once

#include "PhysX_Object_ColliderShape.h"

class MeshCollider : public BaseColliderShape
{
public:

	PxTriangleMesh* mMeshTriangle = nullptr;
	PxTriangleMeshGeometry* mMeshGeometry = nullptr;

	PxU32 mNumTrisPerLeaf = 4;

	// Inherited via BaseColliderShape
	PxGeometry* GetGeometry() override;
	void InitializeGeometry(PhysX_Object* phyObj) override;
	void UpdateGeometry(const PxGeometry& geometry) override;
};

