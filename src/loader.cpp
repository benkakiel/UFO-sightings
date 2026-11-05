#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <direct.h>
#include "loader.h"

#include <iostream>

std::vector<Sighting> loadSightings(const std::string& filepath)
{
  std::ifstream file(filepath); // Load the CSV file

  std::vector<Sighting> sightings; // Create a vector to store all of the sightings

  if (file.is_open())
  {
    std::string line; // Define each line of the CSV file
    std::getline(file, line); // Get the header of the file (lat, lon, shape, year, duration, city, state, country)

    while (std::getline(file, line)) // While there is a line and the file is open
    {
      std::string lat = line.substr(0, line.find(',')); // Extract latitude
      double latitude = std::stod(lat); // Change latitude to double

      // Move comma positions so for parsing we can start one past the previous comma and end at the next comma
      auto comma1 = line.find(',');
      auto comma2 = line.find(',', comma1 + 1);

      std::string lon = line.substr(comma1 + 1, comma2 - comma1 - 1); // Extract longitude
      double longitude = std::stod(lon); // Change longitude to double

      comma1 = line.find(',', comma1 + 1);
      comma2 = line.find(',', comma2 + 1);

      std::string shape = line.substr(comma1 + 1, comma2 - comma1 - 1); // Extract shape

      comma1 = line.find(',', comma1 + 1);
      comma2 = line.find(',', comma2 + 1);

      std::string year = line.substr(comma1 + 1, comma2 - comma1 - 1); // Extract year
      int yearSeen = std::stoi(year); // Convert year to int

      comma1 = line.find(',', comma1 + 1);
      comma2 = line.find(',', comma2 + 1);

      std::string duration = line.substr(comma1 + 1, comma2 - comma1 - 1); // Extract duration of sighting
      double durationSeen = std::stod(duration); // Convert duration to double

      comma1 = line.find(',', comma1 + 1);
      comma2 = line.find(',', comma2 + 1);

      std::string city = line.substr(comma1 + 1, comma2 - comma1 - 1); // Extract city of sighting

      comma1 = line.find(',', comma1 + 1);
      comma2 = line.find(',', comma2 + 1);

      std::string state = line.substr(comma1 + 1, comma2 - comma1 - 1); // Extract state of sighting

      comma1 = line.find(',', comma1 + 1);

      std::string country = line.substr(comma1 + 1); // Extract country of sighting

      // Create a Sighting object and insert it into the sightings vector
      auto newSighting = Sighting{latitude, longitude, shape, yearSeen, durationSeen, city, state, country};
      sightings.push_back(newSighting);
    }
  }

  else
  {
    char path[4096];
    if (_getcwd(path, sizeof(path)) != nullptr)
      std::cout << path << std::endl;
    throw std::invalid_argument("File was not opened properly"); // If file doesn't open, throw an error
  }
  return sightings; // Return the vector of all Sightings
}
