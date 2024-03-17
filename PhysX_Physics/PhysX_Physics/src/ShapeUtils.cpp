#include "ShapeUtils.h"
#include "GLMToPhysX.h"

PxBounds3 CalcualteAABB(std::vector<Vertex>& vertices)
{
    glm::vec3 minExtents = vertices[0].positions;
    glm::vec3 maxExtents = vertices[0].positions;

    for (const Vertex& vertex : vertices)
    {
        minExtents.x = PxMin(minExtents.x, vertex.positions.x);
        minExtents.y = PxMin(minExtents.y, vertex.positions.y);
        minExtents.z = PxMin(minExtents.z, vertex.positions.z);

        maxExtents.x = PxMax(maxExtents.x, vertex.positions.x);
        maxExtents.y = PxMax(maxExtents.y, vertex.positions.y);
        maxExtents.z = PxMax(maxExtents.z, vertex.positions.z);
    }

    return PxBounds3(GLMVec3(minExtents), GLMVec3(maxExtents));
}

void UpdateAABBExtends(PxBounds3& outAabb, PxBounds3 inAabb)
{
    outAabb.minimum.x = PxMin(outAabb.minimum.x, inAabb.minimum.x);
    outAabb.minimum.y = PxMin(outAabb.minimum.y, inAabb.minimum.y);
    outAabb.minimum.z = PxMin(outAabb.minimum.z, inAabb.minimum.z);

    outAabb.maximum.x = PxMax(outAabb.maximum.x, inAabb.maximum.x);
    outAabb.maximum.y = PxMax(outAabb.maximum.y, inAabb.maximum.y);
    outAabb.maximum.z = PxMax(outAabb.maximum.z, inAabb.maximum.z);
}
