#ifndef PARTY_H_
#define PARTY_H_

#include <ctime>
#include <cstdlib>

struct Party
{
	// CONSTRUCTOR
	Party(int clock) :
		arrivalTime(clock)
	{

		srand(time(0)); // Random seed

		numOfMembers = rand() % 10 + 1;

		int randomSmokerNumber = rand() % 2;
		
		// 50% CHANCE OF BEING SMOKER OR NONSMOKER
		if (randomSmokerNumber == 0)
			isSmoker = false;

		else
			isSmoker = true;
	}

	int numOfMembers;
	bool isSmoker;
	int arrivalTime;
	int seatedTime;
	int servedTime;
};

#endif