#include "PhysX_Object_ColliderShape.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

#include "../ShapeUtils.h"

SphereCollider* BaseColliderShape::AsSphere()
{
    return (SphereCollider*)this;
}

BoxCollider* BaseColliderShape::AsBox()
{
    return (BoxCollider*)this;
}

void BaseColliderShape::InitializeGeometry(Model* model)
{

    for (MeshAndMaterial* mesh : model->meshes)
    {
        UpdateAABBExtends(mModelAABB, CalcualteAABB(mesh->mesh->vertices));
    }

    mModelAABB.minimum.x *= model->transform.scale.x;
    mModelAABB.minimum.y *= model->transform.scale.y;
    mModelAABB.minimum.z *= model->transform.scale.z;

    mModelAABB.maximum.x *= model->transform.scale.x;
    mModelAABB.maximum.y *= model->transform.scale.y;
    mModelAABB.maximum.z *= model->transform.scale.z;
}
