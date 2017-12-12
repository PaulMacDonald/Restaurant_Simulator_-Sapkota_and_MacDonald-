#ifndef ORDER_H_
#define ORDER_H_

#include <ctime>
#include <cstdlib>

class Order
{
private:
	bool havingDessert;

public:

	// CONSTRUCTOR
	Order()
	{
		srand(time(0)); // Random seed
		int randomDessertNumber = rand() % 2;

		// 50% CHANCE OF HAVING DESSERT OR NOT
		if (randomDessertNumber == 0)
			havingDessert = true;

		else
			havingDessert = false;
	}

	bool isHavingDessert() { return havingDessert; }
};

#endif