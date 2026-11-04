#include <iostream>
#include <vector>
#include <cmath>

#include "sighting.h"

double toRadians(double deg)
{
    return deg * M_PI / 180.0;
}

double haversineKm(double const lat1, double const lon1, double const lat2, double const lon2)
// Codex told me I needed a "haversine" function, but I wrote it
// Codex did tell me what some of the formulae were (such as angle using asin and the inters)
{
    // Constant for Earth radius
    int constexpr radius = 6371;

    // Compute latitude and longitude change
    double const latChange = lat2 - lat1;
    double const lonChange = lon2 - lon1;

    // Compute the intermediates for North-South, East-West, and then overall
    double const interNS = sin(toRadians(latChange / 2)) * sin(toRadians(latChange / 2));
    double const interEW = cos(toRadians(lat1)) * cos(toRadians(lat2)) * sin(toRadians(lonChange / 2)) * sin(toRadians(lonChange / 2));
    double inter = interNS + interEW;

    // Clamp values for the intermediate
    if (inter > 1)
        inter = 1.0;
    else if (inter < 0)
        return 0;

    // Calculate the angle
    double const angle = 2 * asin(sqrt(inter));

    // Calculate the distance for the sighting radius
    double const distance = radius * angle;

    // Return the radius we're checking in
    return distance;
}

std::vector<int> sightingsInDistance(const std::vector<Sighting>& sightings, double searchLat, double searchLon, double radius)
// Linear search through a vector of sightings and return those found inside the radius from a search point
{
    std::vector<int> foundSightings;

    for (std::size_t i = 0; i < sightings.size(); i++)
    {
      double currentLat = sightings[i].lat;
      double currentLon = sightings[i].lon;
      if (haversineKm(currentLat, currentLon, searchLat, searchLon) <= radius)
      {
        foundSightings.push_back(i);
      }
    }

  return foundSightings;
}
