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
		Citizen citizen = citizens.getData(citizenID);
		if (citizen.getLivingCity() != city && citizen.getLivingCity() >= 0) {
			throw Failure();
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
