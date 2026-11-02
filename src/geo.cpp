#include <iostream>
#include <algorithm>
#include <cmath>

static double toRadians(double deg)
{
    return deg * M_PI/180.0;
}

double haversineKm(double const lat1, double const lon1, double const lat2, double const lon2)
{
    // Constant for Earth radius
    int constexpr radius = 6371;

    // Compute latitude and longitude change
    double const latChange = lat2 - lat1;
    double const lonChange = lon2 - lon1;

    // Compute the intermediates for North-South, East-West, and then overall
    double const interNS = sin(toRadians(latChange/2)) * sin(toRadians(latChange/2));
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
};
