#ifndef CHEF_H_
#define CHEF_H_

#include "Table.h"

class Chef
{
private:
	Table* myTable;
	bool stillCooking;
	int startedCooking;
	int cookingTime;

public:

	// CONSTRUCTOR
	Chef() {}

	// GETTERS AND SETTERS
	Table* getTable() { return myTable; }
	bool isStillCooking() { return stillCooking; }
	int getCookingTime() { return cookingTime; }

	void setTable(Table* table) { myTable = table; }

	void setStillCooking(bool cooking) { stillCooking = cooking; }
	void setNewCookingTime(int time) { cookingTime = time; }

	void update(int clock, Table* smokingSection[], Table* nonSmokingSection[])
	{
		if (clock - startedCooking >= cookingTime) // If he's cooked it long enough (it's ready)...
		{
			myTable->getParty()->servedTime = clock; // ... Dinner is served!
			stillCooking = false; // and he's ready to take on another table.

			// If the last table was a smoker table, look for a nonsmoker table to serve next (for variety)
			if (myTable->getParty()->isSmoker)
			{
				for (int i = 0; i < 7; i++)
				{
					if (!nonSmokingSection[i]->getHasBeenServed())
					{
						this->myTable = nonSmokingSection[i];
						startedCooking = clock;
					}
				}
			}

			// If the last table was a nonsmoker table, look for a smoker table to serve next (for variety)
			if (!myTable->getParty()->isSmoker)
			{
				for (int i = 0; i < 3; i++)
				{
					if (!smokingSection[i]->getHasBeenServed())
						this->myTable = smokingSection[i];
				}
			}
		}
	}

	// OPERATOR OVERLOADS FOR ORGANIZING HEAP

	/*bool operator >(const Chef &otherChef) const
	{
		if (!this->stillCooking && otherChef.stillCooking)
			return true;

		else
			return false;
	}

	bool operator <(const Chef &otherChef) const
	{
		if (this->stillCooking && !otherChef.stillCooking)
			return true;

		else
			return false;
	}

	bool operator =(const Chef &otherChef) const
	{
		if (this->stillCooking && otherChef.stillCooking)
			return true;

		else if (!this->stillCooking && !otherChef.stillCooking)
			return true;

		else
			return false;
	}*/

};
#endif