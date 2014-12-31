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

/**
 * This following data assumes there are no citizens living in any city.
 * Kingdoms:
 * 		Capital | Cities
 * 			0	| 0, 2, 4, 8, 9, 11
 * 			3	| 3, 10, 14
 * 			1	| 1, 7, 12, 13
 * 			6	| 6
 * 			5	| 5
 */
static void setKingdoms(Planet& planet) {
	planet.JoinKingdoms(0, 2);
	planet.JoinKingdoms(0, 4);
	planet.JoinKingdoms(0, 8);
	planet.JoinKingdoms(0, 9);
	planet.JoinKingdoms(0, 11);
	planet.JoinKingdoms(3, 10);
	planet.JoinKingdoms(3, 14);
	planet.JoinKingdoms(1, 7);
	planet.JoinKingdoms(1, 12);
	planet.JoinKingdoms(1, 13);
}

/**
 * City:	| Citizens:
 * 		0	| 346, 740
 * 		1	| 274, 341
 * 		2	| 853
 * 		3	| 949
 * 		4	| 856, 143, 474
 * 		5	| 576
 * 		6	|
 * 		7	| 742
 * 		8	| 264
 * 		9	| 784, 889
 * 		10	| 697
 * 		11	|
 * 		12	|
 * 		13	| 390
 * 		14	| 481, 720, 710, 482
 *
 * If the function setKingdoms() is called after this function, then:
 * Kingdoms:
 * 		Capital | Cities
 * 			4	| 0, 2, 4, 8, 9, 11
 * 			14	| 3, 10, 14
 * 			1	| 1, 7, 12, 13
 * 			6	| 6
 * 			5	| 5
 */
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

	ASSERT_NO_THROW(planet.JoinKingdoms(6, 10));
	ASSERT_NO_THROW(planet.JoinKingdoms(6, 9));
	ASSERT_NO_THROW(planet.JoinKingdoms(6, 5));

	/**
	 * Kingdoms:
	 * Capital:	| Cities:
	 * 		0	| 0, 1, 7, 2, 4
	 * 		3	| 3
	 * 		5	| 5, 6, 10, 9
	 * 		8	| 8
	 * 		11	| 11
	 * 		12	| 12
	 * 		13	| 13
	 * 		14	| 14
	 */

	ASSERT_FAILURE(planet.JoinKingdoms(6, 4));
	ASSERT_FAILURE(planet.JoinKingdoms(6, 0));
	ASSERT_FAILURE(planet.JoinKingdoms(7, 0));

	placeCitizens(planet);

	/**
	 * Kingdoms:
	 * Capital:	| Cities:
	 * 		4	| 0, 1, 7, 2, 4
	 * 		3	| 3
	 * 		9	| 5, 6, 10, 9
	 * 		8	| 8
	 * 		11	| 11
	 * 		12	| 12
	 * 		13	| 13
	 * 		14	| 14
	 */

	ASSERT_FAILURE(planet.JoinKingdoms(6, 4));
	ASSERT_FAILURE(planet.JoinKingdoms(9, 1));
	ASSERT_FAILURE(planet.JoinKingdoms(5, 0));
	ASSERT_NO_THROW(planet.JoinKingdoms(4, 9));

	ASSERT_NO_THROW(planet.JoinKingdoms(8, 11));
	ASSERT_FAILURE(planet.JoinKingdoms(9, 13));
	ASSERT_FAILURE(planet.JoinKingdoms(11, 6));
	ASSERT_NO_THROW(planet.JoinKingdoms(8, 4));
	ASSERT_NO_THROW(planet.JoinKingdoms(4, 14));
	ASSERT_FAILURE(planet.JoinKingdoms(2, 13));
	ASSERT_NO_THROW(planet.JoinKingdoms(14, 13));

	/**
	 * Kingdoms:
	 * Capital:	| Cities:
	 * 		14	| 0, 1, 7, 2, 4, 8, 11, 14, 13, 5, 6, 10, 9
	 * 		3	| 3
	 * 		12	| 12
	 */

	return true;
}

static bool testGetCapital() {
	Planet planet(NUMBER_OF_CITIES);

	ASSERT_INVALID_INPUT(planet.GetCapital(-42));
	bringCitizens(planet);
	ASSERT_FAILURE(planet.GetCapital(10));
	ASSERT_FAILURE(planet.GetCapital(889));
	placeCitizens(planet);
	ASSERT_NO_THROW(planet.AddCitizen(42));
	ASSERT_FAILURE(planet.GetCapital(42));

	ASSERT_EQUALS(planet.GetCapital(346), 0);
	ASSERT_NO_THROW(planet.JoinKingdoms(0, 8));
	ASSERT_EQUALS(planet.GetCapital(346), 0);
	ASSERT_NO_THROW(planet.JoinKingdoms(5, 3));
	ASSERT_EQUALS(planet.GetCapital(576), 3);
	ASSERT_NO_THROW(planet.JoinKingdoms(0, 14));
	ASSERT_EQUALS(planet.GetCapital(264), 14);
	ASSERT_EQUALS(planet.GetCapital(740), 14);
	ASSERT_NO_THROW(planet.JoinKingdoms(9, 4));
	ASSERT_EQUALS(planet.GetCapital(784), 4);
	ASSERT_NO_THROW(planet.JoinKingdoms(14, 4));
	ASSERT_EQUALS(planet.GetCapital(143), 14);

	return true;
}

static bool testSelectCity() {
	Planet planet(NUMBER_OF_CITIES);

	ASSERT_INVALID_INPUT(planet.SelectCity(-42));
	ASSERT_FAILURE(planet.SelectCity(NUMBER_OF_CITIES));

	ASSERT_EQUALS(planet.SelectCity(3), 3);
	ASSERT_EQUALS(planet.SelectCity(14), 14);

	bringCitizens(planet);
	ASSERT_EQUALS(planet.SelectCity(0), 0);

	setKingdoms(planet);
	placeCitizens(planet);

	ASSERT_EQUALS(planet.SelectCity(3), 2);
	ASSERT_EQUALS(planet.SelectCity(9), 13);
	ASSERT_EQUALS(planet.SelectCity(14), 14);

	ASSERT_FAILURE(planet.SelectCity(NUMBER_OF_CITIES));

	return true;
}

static bool testGetCitiesBySize() {
	Planet planet(NUMBER_OF_CITIES);
	int *cities(new int[NUMBER_OF_CITIES]);

	planet.GetCitiesBySize(cities);
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		ASSERT_EQUALS(cities[i], i);
	}

	bringCitizens(planet);
	setKingdoms(planet);

	planet.GetCitiesBySize(cities);
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		ASSERT_EQUALS(cities[i], i);
	}

	placeCitizens(planet);

	planet.GetCitiesBySize(cities);
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		ASSERT_EQUALS(cities[i], planet.SelectCity(i));
	}

	delete[] cities;
	return true;
}

int main() {
	RUN_TEST(testAddCitizen());
	RUN_TEST(testMoveToCity());
	RUN_TEST(testJoinKingdoms());
	RUN_TEST(testGetCapital());
	RUN_TEST(testSelectCity());
	RUN_TEST(testGetCitiesBySize());

	return 0;
}
