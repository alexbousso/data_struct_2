/*
 * city.h
 *
 *  Created on: Dec 28, 2014
 *      Author: alex
 */

#ifndef CITY_H_
#define CITY_H_

#include <cassert>

class City {
	int population;
	const int cityID;
	static int CITY_ID_INITIALIZER = 0;

public:
	City() :
			population(0), cityID(CITY_ID_INITIALIZER++) {
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

	int getCityID() {
		return cityID;
	}
};

#endif /* CITY_H_ */
