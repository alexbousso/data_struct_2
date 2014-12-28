/*
 * city.h
 *
 *  Created on: Dec 28, 2014
 *      Author: alex
 */

#ifndef CITY_H_
#define CITY_H_

#include <cassert>

static int CITY_ID_INITIALIZER = 0;

class City {
	int population;
	int cityID;

public:
	City() :
			population(0), cityID(CITY_ID_INITIALIZER++) {
	}

	City(const City& copy) :
			population(copy.population), cityID(copy.cityID) {
	}

	City(int population, int cityID) :
			population(population), cityID(cityID) {
		if (population < 0 || cityID < 0) {
			throw InvalidInput();
		}
	}

	void increasePopulation() {
		++population;
	}

	void decreasePopulation() {
		if (population == 0) {
			throw CityIsEmpty();
		}
		assert(population > 0);
		--population;
	}

	int getPopulation() {
		return population;
	}

	int getCityID() {
		return cityID;
	}
};

#endif /* CITY_H_ */
