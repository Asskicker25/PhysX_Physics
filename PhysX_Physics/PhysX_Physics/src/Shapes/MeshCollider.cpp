#include "MeshCollider.h"
#include "../PhysX_Engine.h"
#include "../PhysX_Object.h"
#include "../GLMToPhysX.h"

PxGeometry* MeshCollider::GetGeometry()
{
	return mMeshGeometry;
}


void MeshCollider::UpdateGeometry(const PxGeometry& geometry)
{
}


void MeshCollider::InitializeGeometry(PhysX_Object* phyObj)
{
	BaseColliderShape::InitializeGeometry(phyObj);

	PxU32 verticesCount = 0;
	PxU32 triangleCount = 0;
	PxU32 indexCount = 0;

	for (MeshAndMaterial* mesh : phyObj->meshes)
	{
		verticesCount += mesh->mesh->vertices.size();
		triangleCount += mesh->mesh->triangles.size();
		indexCount += mesh->mesh->indices.size();
	}

	PxVec3* listOfVertices = new PxVec3[verticesCount];
	PxU32* listOfIndices = new PxU32[indexCount];

	int vertIndex = 0;
	int indicesIndex = 0;
	int prevSizeOfVerts = 0;
	for (MeshAndMaterial* mesh : phyObj->meshes)
	{
		prevSizeOfVerts = vertIndex;
		for (const Vertex& vert : mesh->mesh->vertices)
		{
			listOfVertices[vertIndex] = GLMVec3(vert.positions);
			vertIndex++;
		}

		for (const unsigned int& index : mesh->mesh->indices)
		{
			listOfIndices[indicesIndex] = index + prevSizeOfVerts;
			indicesIndex++;
		}
	}


	PxTriangleMeshDesc meshDesc;
	meshDesc.points.count = verticesCount;
	meshDesc.points.data = listOfVertices;
	meshDesc.points.stride = sizeof(PxVec3);
	meshDesc.triangles.count = triangleCount;
	meshDesc.triangles.data = listOfIndices;
	meshDesc.triangles.stride = 3 * sizeof(PxU32);

	PxTolerancesScale scale;
	PxCookingParams params(scale);

	params.midphaseDesc = PxMeshMidPhase::eBVH34;
	params.suppressTriangleMeshRemapTable = true;
	params.meshPreprocessParams &= ~static_cast<PxMeshPreprocessingFlags>(PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH);
	params.meshPreprocessParams &= ~static_cast<PxMeshPreprocessingFlags>(PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE);
	params.midphaseDesc.mBVH34Desc.numPrimsPerLeaf = mNumTrisPerLeaf;

	PxDefaultMemoryOutputStream outBuffer;
	PxCookTriangleMesh(params, meshDesc, outBuffer);

	PxDefaultMemoryInputData stream(outBuffer.getData(), outBuffer.getSize());
	mMeshTriangle = PhysX_Engine::gPhysics->createTriangleMesh(stream);

	PxU32 meshSize = outBuffer.getSize();

	mMeshGeometry = new PxTriangleMeshGeometry();
	mMeshGeometry->scale = PxMeshScale(GLMVec3(mModelTransform->scale));
	mMeshGeometry->triangleMesh = mMeshTriangle;
}
