#pragma once
#ifndef PROJECT2_QUADTREE_H
#define PROJECT2_QUADTREE_H

#include <vector>
#include "sighting.h"

// Axis aligned bounding box for a region of lat-lon space
struct BoundingBox
{
    double minLat, maxLat;
    double minLon, maxLon;

    BoundingBox(double minLat, double maxLat, double minLon, double maxLon)
        : minLat(minLat), maxLat(maxLat), minLon(minLon), maxLon(maxLon) {}

    bool contains(double lat, double lon) const;
    bool intersects(const BoundingBox& other) const;
};
