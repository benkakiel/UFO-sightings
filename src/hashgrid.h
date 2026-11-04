#ifndef PROJECT2_HASHGRID_H
#define PROJECT2_HASHGRID_H
#include <string>
#include <vector>
#include <unordered_map>
#include "sighting.h"
#pragma once

class HashGrid
{
  double cellSize;
  std::unordered_map<std::string, std::vector<int>> cells; // Hash table
  std::string coordToCellHelper(double lat, double lon) const; // Convert coordinates to cells

public:
  HashGrid(double cellSize); // Hash table constructor
  void insertSighting(const Sighting& sighting, int index); // Insert sighting into table
  std::vector<int> findCell(double lat, double lon) const;
};

#endif //PROJECT2_HASHGRID_H
