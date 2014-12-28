/*
 * planet.h
 *
 *  Created on: Dec 28, 2014
 *      Author: Miri
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "avl_tree.h"
#include "union_find.h"
#include "hash_table.h"
#include "city.h"
#include "citizen.h"

class CompareCities {
public:
	int operator()(City a, City b) const {
		if (a.getPopulation() != b.getPopulation()) {
			return a.getPopulation() - b.getPopulation();
		} else {
			return b.getCityID() - a.getCityID();
		}
	}
};

class ModuloCitizens {
	int n;

public:
	ModuloCitizens(int n) :
			n(n) {
	}

	int operator()(Citizen citizen) const {
		return (citizen.getLivingCity() % n);
	}
	int operator()(int num) const {
		return num % n;
	}
};

class Planet {
	UnionFind<City, CompareCities> kingdoms;
	AVLTree<City, CompareCities> cities;
	HashTable<Citizen, ModuloCitizens> citizens;
	int numberOfCities;

public:
	Planet(int cityNum) :
			kingdoms(cityNum), cities(), citizens(), numberOfCities(cityNum) {
	}

	/*
	 * adds a new citizen to the planet. not yet assigned to a city
	 */
	void AddCitizen(int citizenID);

	/*
	 * assigning a citizen to a specific city
	 */
	void MoveToCity(int citizenID, int city);

	/*
	 * uniting to kingdoms into one.
	 * only if the 2 cities sent are the capitals of their kingdom
	 */
	void JoinKingdoms(int, int);

	/*
	 * returns the city in which the given citizen is living
	 */
	void GetCapital(int, int*);

	/*
	 * returns the k-th city by size.
	 * if 2 cities are of the same size-them will return the one
	 * with the smaller id
	 */
	void SelectCity(int, int*);

	/*
	 * fills up an array with the cities organized by order
	 */
	void GetCitiesBySize(int*);

};

#endif /* PLANET_H_ */
