#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

#include "hashgrid.h"

HashGrid::HashGrid(double cellSize) : cellSize(cellSize) // Initialize cell size, ensure greater than 0
{
  if (cellSize <= 0)
  {
    throw std::invalid_argument("Cell size must be greater than 0.");
  }
}

std::string HashGrid::coordToCellHelper(const double lat, const double lon) const // Calculate the cell a coordinate is in
{

  if (lat < -90 || lat > 90) // Check latitude bounds
    throw std::invalid_argument("Latitude out of bounds.");
  if (lon < -180 || lon > 180) // Check longitude bounds
    throw std::invalid_argument("Longitude out of bounds.");

  int x = static_cast<int>(std::floor(lat / cellSize)); // So string is one number without decimals
  int y = static_cast<int>(std::floor(lon / cellSize));

  const std::string xCoordinate = std::to_string(x); // Coordinates stores as strings
  const std::string yCoordinate = std::to_string(y);

  return xCoordinate + "," + yCoordinate;
}

void HashGrid::insertSighting(const Sighting &sighting, const int index) // Insert sighting into table
{
  std::string coord = coordToCellHelper(sighting.lat, sighting.lon); // Get coordinates of sighting
  cells[coord].push_back(index); // Append index of sighting
}

std::vector<int> HashGrid::findCell(const double lat, const double lon) const // See if a sighting exists in the table in a specified coordinate
{
  std::string coord = coordToCellHelper(lat, lon);

  auto doesExist = cells.find(coord);

  if (doesExist == cells.end())
    return {};
  else
  {
    return doesExist->second;
  }
}