#include <catch2/catch_test_macros.hpp>
#include <iostream>

// uncomment and replace the following with your own headers
#include "geo.h"
// #include "AVL.h"

using namespace std;

// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
TEST_CASE("Test 1: Haversine = 0", "[haversine]")
{
	double const distance = haversineKm(0.0, 0.0, 0.0, 0.0);

	// all REQUIRE blocks must evaluate to true for the whole test to pass
	REQUIRE(distance == 0); // also fix me!
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

//TEST_CASE("Test 2", "[flag]"){
//	// you can also use "sections" to share setup code between tests, for example:
//	int one = 1;
//
//	SECTION("num is 2") {
//		int num = one + 1;
//		REQUIRE(num == 2);
//	};
//
//	SECTION("num is 3") {
//		int num = one + 2;
//		REQUIRE(num == 3);
//	};
//
//	// each section runs the setup code independently to ensure that they don't affect each other
//}
//
//// you must write 5 unique, meaningful tests for credit on the testing portion of this project!
//
//// the provided test from the template is below.
//
//TEST_CASE("Example BST Insert", "[flag]"){
//	/*
//		MyAVLTree tree;   // Create a Tree object
//		tree.insert(3);
//		tree.insert(2);
//		tree.insert(1);
//		std::vector<int> actualOutput = tree.inorder();
//		std::vector<int> expectedOutput = {1, 2, 3};
//		REQUIRE(expectedOutput.size() == actualOutput.size());
//		REQUIRE(actualOutput == expectedOutput);
//	*/
//}
