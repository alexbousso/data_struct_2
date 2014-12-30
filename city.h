/*
 * city.h
 *
 *  Created on: Dec 28, 2014
 *      Author: alex
 */

#ifndef CITY_H_
#define CITY_H_

#include <cassert>
#include <iostream>

class City {
	int population;
	int cityID;

public:
	City() :
			population(0), cityID(0) {
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

	int getPopulation() const {
		return population;
	}

	int getCityID() const {
		return cityID;
	}

	void setCityID(int ID) {
		cityID = ID;
	}

	// QUESTION: Why when removing this function from the class, it does not
	// compile?
	friend std::ostream& operator<<(std::ostream& os, const City& city) {
		os << "CityID: ";
		os.width(4);
		os << city.cityID << ", population: ";
		os.width(3);
		os << city.population;

		return os;
	}
};

#endif /* CITY_H_ */
