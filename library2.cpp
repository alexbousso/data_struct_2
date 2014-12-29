#include "library2.h"

#include "planet.h"

void* Init(int n) {
	// TODO
}

StatusType AddCitizen(void* DS, int citizenID) {
	// TODO
	return SUCCESS;
}

StatusType MoveToCity(void* DS, int citizenID, int city) {
	// TODO
	return SUCCESS;
}

StatusType JoinKingdoms(void* DS, int city1, int city2) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	try {
		(static_cast<Planet*>(DS))->JoinKingdoms(city1, city2);
	} catch (InvalidInput& badinput) {
		return INVALID_INPUT;
	} catch (Failure& fail) {
		return FAILURE;
	}catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType GetCapital(void* DS, int citizenID, int* capital) {
	if(DS == NULL){
		return INVALID_INPUT;
	}
	try {
		(static_cast<Planet*>(DS))->GetCapital(citizenID, capital);
	} catch (InvalidInput& badInput) {
		return INVALID_INPUT;
	}catch (Failure& fail) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType SelectCity(void* DS, int k, int* city) {
	// TODO
}

StatusType GetCitiesBySize(void* DS, int results[]) {
	// TODO
}

void Quit(void** DS) {
	// TODO
}
