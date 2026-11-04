//
// Created by Nicol on 11/2/2026.
//

#ifndef PROJECT2_GEO_H
#define PROJECT2_GEO_H
#include <sighting.h>
#pragma once

double haversineKm(double lat1, double lon1, double lat2, double lon2); // Distance from viewpoint
std::vector<int> sightingsInDistance(const std::vector<Sighting>& sightings, double searchLat, double searchLon, double radius);


#endif //PROJECT2_GEO_H
