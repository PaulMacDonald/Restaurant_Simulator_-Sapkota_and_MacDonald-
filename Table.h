#ifndef TABLE_H_
#define TABLE_H_

#include "Party.h"
#include "Order.h"
#include <ctime>
#include <cstdlib>

class Table
{
protected:
	Party* theParty;
	bool isEmpty;
	bool hasBeenServed;
	Order* ourOrder;
	int eatTime;

public:

	//CONSTRUCTOR
	Table()
	{
		isEmpty = true;
		hasBeenServed = false;
	}

	bool getIsEmpty() { return isEmpty; }

	void setIsEmpty(bool emptyBool) { isEmpty = emptyBool; }

	Order* getOrder() { return ourOrder; }

	void setOrder(Order* theOrder) { ourOrder = theOrder; }

	Party* getParty() { return theParty; }

	void setParty(Party* newParty) { theParty = newParty; }

	bool getHasBeenServed() { return hasBeenServed; }

	int chooseCookingTime()
	{
		if (theParty->numOfMembers > 0 && theParty->numOfMembers <= 5 && !ourOrder->isHavingDessert())
			return 10;

		else if (theParty->numOfMembers > 5 && theParty->numOfMembers <= 10 && !ourOrder->isHavingDessert())
			return 15;

		else if (theParty->numOfMembers > 0 && theParty->numOfMembers <= 5 && ourOrder->isHavingDessert())
			return 20;

		else if (theParty->numOfMembers > 5 && theParty->numOfMembers <= 10 && ourOrder->isHavingDessert())
			return 25;
	}

	void pickRandomEatingTime()
	{
		srand(time(0)); // Random seed
		int randomNumberForChoosingTime = rand() % 10;

		// 10% CHANCE FOR 20 MINUTES EATING TIME
		// 40% CHANCE FOR 40 MINUTES
		// 50% CHANCE FOR 60 MINUTES
		if (randomNumberForChoosingTime == 0)
			eatTime = 20;

		else if (randomNumberForChoosingTime > 0 && randomNumberForChoosingTime < 5)
			eatTime = 40;

		else
			eatTime = 60;

	}

	void update(int clock)
	{
		if (!this->isEmpty) // If this table is NOT empty...
		{
			if (clock - theParty->servedTime >= eatTime) // ... and they've had their fill...
				this->isEmpty = true; // ... they outta here.
		}
	}
};

class NonSmokerTable : public Table {};

class SmokerTable : public Table {};

#endif