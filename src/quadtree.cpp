#include <cmath>
#include <stdexcept>
#include "quadtree.h"
#include "geo.h"

//BoundingBox
bool BoundingBox::contains(double lat, double lon) const
{
    return lat >= minLat && lat <= maxLat &&
           lon >= minLon && lon <= maxLon;
}

bool BoundingBox::intersects(const BoundingBox& other) const
{
    // Two boxes do NOT intersect if one is completely outside the other
    if (other.minLat > maxLat || other.maxLat < minLat) return false;
    if (other.minLon > maxLon || other.maxLon < minLon) return false;
    return true;
}

//Node
QuadTree::Node::Node(BoundingBox bounds)
    : bounds(bounds), divided(false)
{
    children[0] = children[1] = children[2] = children[3] = nullptr;
}

QuadTree::Node::~Node()
{
    for (int i = 0; i < 4; i++)
        delete children[i];
}