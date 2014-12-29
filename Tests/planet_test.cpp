#include "../planet.h"
#include "assert.h"
#include <string>

std::string location;

static const int NUMBER_OF_CITIES = 15;

static void bringCitizens(Planet& planet) {
	planet.AddCitizen(856);
	planet.AddCitizen(274);
	planet.AddCitizen(784);
	planet.AddCitizen(346);
	planet.AddCitizen(576);
	planet.AddCitizen(143);
	planet.AddCitizen(481);
	planet.AddCitizen(720);
	planet.AddCitizen(949);
	planet.AddCitizen(474);
	planet.AddCitizen(264);
	planet.AddCitizen(740);
	planet.AddCitizen(853);
	planet.AddCitizen(742);
	planet.AddCitizen(697);
	planet.AddCitizen(710);
	planet.AddCitizen(482);
	planet.AddCitizen(390);
	planet.AddCitizen(341);
	planet.AddCitizen(889);
}

static void placeCitizens(Planet& planet) {
	planet.MoveToCity(856, 4);
	planet.MoveToCity(274, 1);
	planet.MoveToCity(784, 9);
	planet.MoveToCity(346, 0);
	planet.MoveToCity(576, 5);
	planet.MoveToCity(143, 4);
	planet.MoveToCity(481, 14);
	planet.MoveToCity(720, 14);
	planet.MoveToCity(949, 3);
	planet.MoveToCity(474, 4);
	planet.MoveToCity(264, 8);
	planet.MoveToCity(740, 0);
	planet.MoveToCity(853, 2);
	planet.MoveToCity(742, 7);
	planet.MoveToCity(697, 10);
	planet.MoveToCity(710, 14);
	planet.MoveToCity(482, 14);
	planet.MoveToCity(390, 13);
	planet.MoveToCity(341, 1);
	planet.MoveToCity(889, 9);
}

static bool testAddCitizen() {
	Planet planet(NUMBER_OF_CITIES);

	ASSERT_INVALID_INPUT(planet.AddCitizen(-10));

	ASSERT_NO_THROW(planet.AddCitizen(42));
	ASSERT_NO_THROW(planet.AddCitizen(33));
	ASSERT_NO_THROW(planet.AddCitizen(1002));

	ASSERT_FAILURE(planet.AddCitizen(42));

	return true;
}

static bool testMoveToCity() {
	Planet planet(NUMBER_OF_CITIES);

	ASSERT_INVALID_INPUT(planet.MoveToCity(-3, 17));
	ASSERT_INVALID_INPUT(planet.MoveToCity(10, 42));
	ASSERT_FAILURE(planet.MoveToCity(10, 11));

	bringCitizens(planet);

	ASSERT_INVALID_INPUT(planet.MoveToCity(710, NUMBER_OF_CITIES));
	ASSERT_INVALID_INPUT(planet.MoveToCity(889, -12));
	ASSERT_FAILURE(planet.MoveToCity(17, 3));

	ASSERT_NO_THROW(planet.MoveToCity(710, 8));
	ASSERT_FAILURE(planet.MoveToCity(710, 4));
	ASSERT_NO_THROW(planet.MoveToCity(710, 8));

	return true;
}

static bool testJoinKingdoms() {
	Planet planet(NUMBER_OF_CITIES);

	ASSERT_INVALID_INPUT(planet.JoinKingdoms(12, 17));
	ASSERT_INVALID_INPUT(planet.JoinKingdoms(42, 11));
	ASSERT_INVALID_INPUT(planet.JoinKingdoms(12, -3));
	ASSERT_INVALID_INPUT(planet.JoinKingdoms(-10, 17));

	ASSERT_NO_THROW(planet.JoinKingdoms(1, 0));
	ASSERT_FAILURE(planet.JoinKingdoms(0, 1));
	ASSERT_FAILURE(planet.JoinKingdoms(1, 2));
	ASSERT_NO_THROW(planet.JoinKingdoms(0, 7));
	ASSERT_NO_THROW(planet.JoinKingdoms(2, 4));
	ASSERT_FAILURE(planet.JoinKingdoms(2, 7));
	ASSERT_FAILURE(planet.JoinKingdoms(4, 0));
	ASSERT_NO_THROW(planet.JoinKingdoms(2, 0));

	bringCitizens(planet);

	return true;
}

int main() {
	RUN_TEST(testAddCitizen());
	RUN_TEST(testMoveToCity());
	RUN_TEST(testJoinKingdoms());

	return 0;
}
