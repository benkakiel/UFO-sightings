#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "geo.h"
#include "hashgrid.h"
using namespace std;

TEST_CASE("Test 1: Haversine = 0", "[haversine]")
{
  double const distance = haversineKm(0.0, 0.0, 0.0, 0.0);
  REQUIRE(distance == 0);
}

TEST_CASE("Test 2: Haversine != 0" "[haversine]")
{
  double const distance = haversineKm(0.0, 0.0, 1.0, 0.0);
  REQUIRE(std::abs(distance - 111.195) < 0.01); // Codex helped with the approximation because I wasn't sure
}

TEST_CASE("Test 3: Haversine != 0", "[haversine]")
{
  double const distance = haversineKm(1.0, 0.0, 0.0, 0.0);
  REQUIRE(std::abs(distance - 111.195) < 0.01);
}

namespace
{
  std::vector<Sighting> makeTestSightings()
  {

    std::vector<Sighting> sightings;

    Sighting A{0.0, 1.0, "Circle", 2020, 2.1, "Jacksonville", "NC", "US"};
    Sighting B{1.0, 0.0, "Square", 2021, 2.2, "Gainesville", "FL", "US"};
    Sighting C{2.0, 0.0, "Oval", 2026, 2.3, "Myrtle Beach", "SC", "US"};
    Sighting D{0.0, 2.0,};
    Sighting E{5.0, 1.0};
    Sighting F{2.0, 2.0};
    Sighting G{1.5, 2.5};
    Sighting H{1.1, 1.1};

    sightings.push_back(A);
    sightings.push_back(B);
    sightings.push_back(C);
    sightings.push_back(D);
    sightings.push_back(E);
    sightings.push_back(F);
    sightings.push_back(G);
    sightings.push_back(H);

    return sightings;
  }
}

TEST_CASE("Test 4: No sightings in radius", "[sightings]")
{
  auto sightings = makeTestSightings();
  auto results = sightingsInDistance(sightings, 0.0, 0.0, 0);

  REQUIRE(results.empty());
}

TEST_CASE("Test 5: Some sightings in radius", "[sightings]")
{
  auto sightings = makeTestSightings();
  auto results = sightingsInDistance(sightings, 0.0, 0.0, 120);
  std::vector<int> expectedResults{0, 1};

  REQUIRE(results == expectedResults);
}

TEST_CASE("Test 6: All sightings in radius", "[sightings]")
{
  auto sightings = makeTestSightings();
  auto results = sightingsInDistance(sightings, 0.0, 0.0, 1000000);
  std::vector<int> expectedResults{0, 1, 2, 3, 4, 5, 6, 7};

  REQUIRE(results == expectedResults);
}

TEST_CASE("Test 7: Empty Vector", "[sightings]")
{
  std::vector<Sighting> sightings;
  auto results = sightingsInDistance(sightings, 0.0, 0.0, 1000000);
  std::vector<int> expectedResults{};

  REQUIRE(results == expectedResults);
}

TEST_CASE("Test 8: Search centered on a sighting", "[sightings]")
{
  auto sightings = makeTestSightings();
  auto results = sightingsInDistance(sightings, 0.0, 1.0, 0);
  std::vector<int> expectedResults{0};

  REQUIRE(results == expectedResults);
}

TEST_CASE("Test 9: 1 sighting inserted into cell", "[insertion]")
{
  auto sightings = makeTestSightings();

  HashGrid hash(10);
  hash.insertSighting(sightings[0], 0);

  auto contents = hash.findCell(sightings[0].lat, sightings[0].lon);
  std::vector<int> expectedContents{0};

  REQUIRE(contents == expectedContents);
}

TEST_CASE("Test 10: 2 sightings inserted into cell", "[insertion]")
{
  auto sightings = makeTestSightings();

  HashGrid hash(10);
  hash.insertSighting(sightings[0], 0);
  hash.insertSighting(sightings[1], 0);

  auto contents = hash.findCell(sightings[0].lat, sightings[0].lon);
  std::vector<int> expectedContents{0, 0};

  REQUIRE(contents == expectedContents);
}

TEST_CASE("Test 11: 2 sightings inserted into different cells", "[insertion]")
{
  auto sightings = makeTestSightings();

  HashGrid hash(10);
  hash.insertSighting(sightings[0], 0);
  hash.insertSighting(sightings[1], 1);

  auto contents = hash.findCell(sightings[0].lat, sightings[0].lon);
  std::vector<int> expectedContents{0, 1};

  REQUIRE(contents == expectedContents);
}

TEST_CASE("Test 12: 0 insertions", "[insertion]")
{
  std::vector<Sighting> sightings;

  HashGrid hash(10);

  std::vector<int> expectedContents{};

  REQUIRE(expectedContents.size() == 0);
}



