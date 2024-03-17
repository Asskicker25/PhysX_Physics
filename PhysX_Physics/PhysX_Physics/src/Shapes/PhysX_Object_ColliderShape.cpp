#include "PhysX_Object_ColliderShape.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

SphereCollider* BaseColliderShape::AsSphere()
{
    return (SphereCollider*)this;
}

BoxCollider* BaseColliderShape::AsBox()
{
    return (BoxCollider*)this;
}
