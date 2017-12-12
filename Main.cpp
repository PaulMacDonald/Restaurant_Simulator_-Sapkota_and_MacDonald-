#include "Simulator.h"

Simulator PhillyCheeseDeques;

int main()
{

	PhillyCheeseDeques.enterData();
	PhillyCheeseDeques.runSimulation();
	PhillyCheeseDeques.showStats();

	system("pause");
	return 0;
}