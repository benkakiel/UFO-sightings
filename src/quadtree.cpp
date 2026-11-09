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
//QuadTree
    }

    // Need to split if not already divided
    if (!node->divided)
    {
        subdivide(node);
        // Insert back the existing indices into children
        for (int i : node->indices)
            for (int c = 0; c < 4; c++)
                insert(node->children[c], i);
        node->indices.clear();
    }

    // Insert new index into the appropriate child
    for (int c = 0; c < 4; c++)
        insert(node->children[c], index);
}

void QuadTree::radiusSearch(const Node* node, double lat, double lon,
                             double radius, std::vector<int>& results) const
{
    // Estimate bounding box of the search circle in degrees
    // Same  approach as the hash grid
    double latChange = (radius / 6371.0) * (180.0 / M_PI);
    double minLat = lat - latChange;
    double maxLat = lat + latChange;

    // Approximate longitude extent at the given latitude
    double lonChange;
    double val = sin(radius / 6371.0) / cos(lat * M_PI / 180.0);
    if (val >= 1.0)       lonChange = 180.0;
    else if (val <= -1.0) lonChange = 180.0;
    else                  lonChange = asin(val) * 180.0 / M_PI;

    double minLon = lon - lonChange;
    double maxLon = lon + lonChange;

    BoundingBox searchBox(minLat, maxLat, minLon, maxLon);

    // Prune: if this node's region doesn't overlap the search box, skip it
    if (!node->bounds.intersects(searchBox))
        return;

    if (!node->divided)
    {
        // Leaf node — check each stored sighting precisely with haversine
        for (int idx : node->indices)
        {
            double dist = haversineKm((*sightings)[idx].lat,
                                      (*sightings)[idx].lon,
                                      lat, lon);
            if (dist <= radius)
                results.push_back(idx);
        }
        return;
    }

    // Recurse into all four children
    for (int c = 0; c < 4; c++)
        radiusSearch(node->children[c], lat, lon, radius, results);
}

std::vector<int> QuadTree::radiusSearch(const std::vector<Sighting>& sightingsRef,
                                         double lat, double lon, double radius) const
{
    if (radius < 0)
        throw std::invalid_argument("Radius must be greater than or equal to 0.");
    if (lat < -90 || lat > 90)
        throw std::invalid_argument("Latitude out of bounds.");
    if (lon < -180 || lon > 180)
        throw std::invalid_argument("Longitude out of bounds.");

    std::vector<int> results;
    radiusSearch(root, lat, lon, radius, results);
    return results;
}