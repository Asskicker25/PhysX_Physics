#include "PhysX_Object_ColliderShape.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "../PhysX_Engine.h"

#include "../GLMToPhysX.h"
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
    mModelTransform = &model->transform;

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

void BaseColliderShape::DrawShape()
{
    modelAABB aabb;
    aabb.min = PxVec3ToGLM( mModelAABB.minimum);
    aabb.max = PxVec3ToGLM( mModelAABB.maximum);

    aabb.min += mModelTransform->position;
    aabb.max += mModelTransform->position;

    Renderer::GetInstance().DrawAABB(aabb, PhysX_Engine::gColliderColor,false);
}
