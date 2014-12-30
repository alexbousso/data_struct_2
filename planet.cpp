#include "planet.h"
#include <cassert>
#include "exceptions.h"
#include <iostream>

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

int Planet::GetCapital(int citizenID) {
	if (citizenID < 0) {
		throw InvalidInput();
	}
	try {
		int livingCity = (citizens.getData(citizenID)).getLivingCity();
		if (!citizens.find(citizenID) || livingCity < 0) {
			throw Failure();
		}

		return kingdoms.getMaxIndex(kingdoms.find(livingCity));
	} catch (DataDoesNotExist& noData) {
		throw Failure();
	}

}

int Planet::SelectCity(int k) {
	if (k < 0) {
		throw InvalidInput();
	}
	if (k >= numberOfCities) {
		throw Failure();
	}
	return (cities.select(k + 1)).getCityID();
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

void Planet::print() {
	std::cout << std::endl;
	for (int i = 0; i < 80; i++) {
		std::cout << "*";
	}
	std::cout << std::endl;

	std::cout << "\t*** Printing the current status of the planet: ***"
			<< std::endl;
	std::cout << "\nCitizens on the planet (printing the hash table):"
			<< std::endl;
	citizens.print();

	std::cout << "\nPrinting the tree of cities:" << std::endl;
	cities.printTree();

	std::cout
			<< "\nPrinting all the kingdoms (printing the union-find content):"
			<< std::endl;
	kingdoms.printUF();

	std::cout << std::endl;
	for (int i = 0; i < 80; i++) {
		std::cout << "*";
	}
	std::cout << std::endl;
}

