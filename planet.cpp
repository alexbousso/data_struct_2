#include "planet.h"
#include <cassert>
#include "exceptions.h"

void Planet::AddCitizen(int citizenID) {
	if (citizenID < 0) {
		throw InvalidInput();
	}
	Citizen citizen(citizenID);
	if (citizens.find(citizen)) {
		throw Failure();
	}
	citizens.insert(citizen);
}

class UpdateCity {
public:
	void operator()(City& city) {
		city.increasePopulation();
	}
};

void Planet::MoveToCity(int citizenID, int city) {
	if (citizenID < 0 || city < 0 || city >= numberOfCities) {
		throw InvalidInput();
	}
	try {
		Citizen& citizen = citizens.getData(citizenID);
		if (citizen.getLivingCity() != city && citizen.getLivingCity() >= 0) {
			throw Failure();
		}
		if (citizen.getLivingCity() == city) {
			return;
		}
		citizen.setLivingCity(city);
		City dest(kingdoms.getData(city));
		kingdoms.updateElement(city, UpdateCity());
		cities.remove(dest);
		dest.increasePopulation();
		cities.insert(dest);
	} catch (DataDoesNotExist& e) {
		throw Failure();
	}
}

void Planet::JoinKingdoms(int city1, int city2) {
	kingdoms.unite(city1, city2);
}

//TODO make sure the logics are fine
void Planet::GetCapital(int citizenID, int* capital) {
	if (citizenID < 0 || capital == NULL) {
		throw InvalidInput();
	}
	try {
		int livingCity = (citizens.getData(citizenID)).getLivingCity();
		if (!citizens.find(citizenID) || livingCity < 0) {
			throw Failure();
		}

		*capital = kingdoms.find(livingCity);
	} catch (DataDoesNotExist& noData) {
		throw Failure();
	}

}

void Planet::SelectCity(int k, int* city) {
	if (k < 0 || city == NULL) {
		throw InvalidInput();
	}
	if (k >= numberOfCities) {
		throw Failure();
	}
	*city = (cities.select(k)).getCityID();
}

class FillCitiesArray {
	int* cities;
	int index;
public:
	FillCitiesArray(int* cities) :
			cities(cities), index(0) {
	}
	void operator()(City c) {
		cities[index++] = c.getCityID();
	}
};

void Planet::GetCitiesBySize(int citiesArr[]) {
	FillCitiesArray functor(citiesArr);
	cities.inOrder(functor);
}
