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

class CompareCities; //TODO implement
class ModuluCitizens;


class Planet {
	UnionFind<City, CompareCities> kingdoms;
	AVLTree<City, CompareCities> cities;
	HashTable<Citizen, ModuluCitizens> citizens;

public:
	Planet(int cityNum): kingdoms(cityNum), cities(), citizens(){}

	/*
	 * adds a new citizen to the planet. not yet asigned to a city
	 */
	void PlanetAddCitizen(int);

	/*
	 * asigning a citizen to a specific city
	 */
	void PlanetMoveToCity(int, int);

	/*
	 * uniting to kingdoms into one.
	 * only if the 2 cities sent are the capitals of their kingdom
	 */
	void PlanetJoinKingdoms(int, int);

	/*
	 * returns the city in which the given citizen is living
	 */
	void PlanetGetCapital(int, int*);

	/*
	 * returns the k-th city by size.
	 * if 2 cities are of the same size-them will return the one
	 * with the smaller id
	 */
	void PlanetSelectCity(int, int*);

	/*
	 * fills up an array with te cities organized by order
	 */
	void PlanetGetCitiesBySize(int*);

};



#endif /* PLANET_H_ */
