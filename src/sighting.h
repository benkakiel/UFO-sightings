//
// Created by Nicol on 11/2/2026.
//

#ifndef PROJECT1_SIGHTING_H
#define PROJECT1_SIGHTING_H
#include <string>
#include <vector>
#pragma once

struct Sighting // All data comprising a sighting
{
    double lat;
    double lon;
    std::string shape;
    int year;
    double duration;
    std::string city;
    std::string state;
    std::string country;
};

#endif //PROJECT1_SIGHTING_H
