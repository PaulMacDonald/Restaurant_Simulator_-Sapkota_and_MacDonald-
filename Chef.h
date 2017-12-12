#ifndef CHEF_H_
#define CHEF_H_

#include "Table.h"

class Chef
{
private:
	Table* myTable;
	bool stillCooking = false;
	int startedCooking;
	int cookingTime;

public:

	// CONSTRUCTOR
	Chef() 
	{
		myTable = new Table();
		myTable->setIsEmpty(true);
	}

	// GETTERS AND SETTERS
	Table* getTable() { return myTable; }
	bool isStillCooking() { return stillCooking; }
	int getCookingTime() { return cookingTime; }

	void setTable(Table* table) { myTable = table; }

	void setStillCooking(bool cooking) { stillCooking = cooking; }
	void setNewCookingTime(int time) { cookingTime = time; }

	void update(int clock, Table* smokingSection[], Table* nonSmokingSection[])
	{
		if (stillCooking)
		{

			if (clock - startedCooking >= cookingTime) // If he's cooked it long enough (it's ready)...
			{
				myTable->getParty()->servedTime = clock; // ... Dinner is served!
				stillCooking = false; // and he's ready to take on another table.
			}
		}

		else if (!stillCooking)
		{
			// Look for a new table in the nonsmoking section
			for (int i = 0; i < 7; i++)
			{
				if (!nonSmokingSection[i]->getHasBeenServed())
				{
					this->myTable = nonSmokingSection[i];
					startedCooking = clock;
					stillCooking = true;
					break;
				}
			}
		}

		if (!stillCooking)
		{

			// Look for a new table in the smoking section
			for (int i = 0; i < 3; i++)
			{
				if (!smokingSection[i]->getHasBeenServed())
				{
					this->myTable = smokingSection[i];
					startedCooking = clock;
					stillCooking = true;
					break;
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