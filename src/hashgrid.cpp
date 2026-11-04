#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

#include "hashgrid.h"
#pragma once

HashGrid::HashGrid(double cellSize) : cellSize(cellSize) // Initialize cell size, ensure greater than 0
{
  if (cellSize <= 0)
  {
    throw std::invalid_argument("Cell size must be greater than 0.");
  }
}

std::string HashGrid::coordToCellHelper(const double lat, const double lon) const // Calculate the cell a coordinate is in
{
  int x = static_cast<int>(std::floor(lat / cellSize)); // So string is one number without decimals
  int y = static_cast<int>(std::floor(lon / cellSize));

  const std::string xCoordinate = std::to_string(x);
  const std::string yCoordinate = std::to_string(y);

  return xCoordinate + "," + yCoordinate;
}
