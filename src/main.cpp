#include <iostream>
#include <vector>

#include "sighting.h"
#include "loader.h"
#include "hashgrid.h"
#include "geo.h"

using namespace std;

int main()
{
  auto sightings = loadSightings("data/close_encounters_simplified.csv"); // Load and parse CSV file of sightings, store all sightings

  HashGrid grid(1.0); // Initialize the hash table with cell size of 1 degree
  for (size_t i = 0; i < sightings.size(); i++)
  {
    grid.insertSighting(sightings[i], i); // Insert each sighting into the table
  }

  // Menu commands
  cout << endl;
  cout << "Welcome to the Close Encounters Library!" << endl;
  cout << "To get started, make a selection!" << endl;
  cout << endl;
  cout << "1. Search for a sighting using our hash grid" << endl;
  cout << "2. Search for a sighting using our quadtree" << endl;
  cout << "3. Search for all sightings reported in a state" << endl;
  cout << "4. Search for all sightings reported in a city" << endl;
  cout << "5. Search for all sightings reported in a country" << endl;
  cout << "6. Exit" << endl;
  cout << endl;
  cout << "Input selection: " << " ";

  int selection;
  cin >> selection;

  if (selection == 1)
  {
    double lat;
    double lon;
    double radius;

    cout << "Input latitude of viewpoint (Ex. 0.0): ";
    cin >> lat;
    cout << endl;

    cout << "Input longitude of viewpoint (Ex. 0.0): ";
    cin >> lon;

    cout << "Input radius (kilometers) of search (Ex. 120): ";
    cin >> radius;

    auto found = grid.radiusSearch(sightings, lat, lon, radius); // Create a vector of all sightings within radius of viewpoint
    for (size_t i = 0; i < found.size(); i++)
    {
      const auto &sighting = sightings[found[i]];
      cout << "Latitude of sighting: " << sighting.lat << endl;
      cout << "Longitude of sighting: " << sighting.lon << endl;
      cout << "Shape of sighting: " << sighting.shape << endl;
      cout << "Year of sighting: " << sighting.year << endl;
      cout << "Duration of sighting (seconds): " << sighting.duration << endl;
      cout << "City where sighting was reported: " << sighting.city << endl;
      cout << "State where sighting was reported: " << sighting.state << endl;
      cout << "Country where sighting was reported: " << sighting.country << endl;
      cout << endl;
    }
  }
}
