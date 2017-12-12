#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "AwaitingSeatsQueue.h"
#include"Table.h"
#include"ReadInt.h"
#include "Chef.h"
#include "Hostess.h"
#include<algorithm>
#include<vector>

class Simulator
{
private:
	int totalRuntime;
	int clock;

	AwaitingSeatsQueue* awaitingSeatsQueue;
	Hostess* theHostess;
	Chef** chefArray;
	Table** nonSmokerTables;
	Table** smokerTables;
	int totalOrderWait;
	int numOfChefs;

public:

	//CONSTRUCTOR
	Simulator()
	{
		awaitingSeatsQueue = new AwaitingSeatsQueue();

		// Dynamically allocate all the nonsmoker tables
		nonSmokerTables = new Table*[7];

		for (int i = 0; i < 7; i++)
		{
			NonSmokerTable* tempNST = new NonSmokerTable();
			nonSmokerTables[i] = tempNST;
		}

		// Dynamically allocate all the smoker tables
		smokerTables = new Table*[3];

		for (int i = 0; i < 3; i++)
		{
			SmokerTable* tempST = new SmokerTable();
			smokerTables[i] = tempST;
		}
	}

	void enterData()
	{
		// INTRODUCTION

		std::cout << "Welcome to the Philly Cheese-Dequeues Simulator!\n";
		std::cout << "We are a small but happy restaurant with seating sections\n";
		std::cout << "for both smokers and non-smokers!\n";
		std::cout << std::endl;

		int rate = read_int("Please enter the arrival rate of parties per hour: ", 1, 59);
		double arrival_rate = rate / 60.0;

		numOfChefs = read_int("Please enter the number of chefs working: ", 0, INT_MAX);

		totalRuntime = read_int("Please enter the simulation time (hours): ", 1, INT_MAX);
		totalRuntime *= 60;

		// Set the arrival_rate for the landing queue
		awaitingSeatsQueue->setArrivalRate(arrival_rate);

		// Create an array of chefs (# numOfChefs)
		chefArray = new Chef*[numOfChefs];

		// Dynamically allocate each chef (a pointee to each pointer)
		for (int i = 0; i < numOfChefs; i++)
		{
			chefArray[i] = new Chef();
		}

		// Create a hostess
		theHostess = new Hostess();

		// Pass the hostess the awaiting seats queue
		theHostess->setQueue(awaitingSeatsQueue);
	}

	void runSimulation()
	{
		for (clock = 0; clock < totalRuntime; ++clock)
		{
			// Update the awaiting seats queue
			awaitingSeatsQueue->update(clock);

			// Update the hostess
			theHostess->update(clock, smokerTables, nonSmokerTables);

			// Update ALL the chefs
			for (int i = 0; i < numOfChefs; i++)
				chefArray[i]->update(clock, smokerTables, nonSmokerTables);

			// Update all the nonsmoker tables
			for (int i = 0; i < 7; i++)
				nonSmokerTables[i]->update(clock);

			// Update all the smoker tables
			for (int i = 0; i < 3; i++)
				smokerTables[i]->update(clock);
		}
	}

	void showStats()
	{
		std::cout << "Number of people served: " << awaitingSeatsQueue->getNumServed() << std::endl;
		std::cout << "Total wait time for all paries in awaiting seats queue: " << awaitingSeatsQueue->getTotalWait() << std::endl;
		
		// Calculate and display the average wait time for the awaiting seats queue
		int averageSeatingWait = awaitingSeatsQueue->getTotalWait() / awaitingSeatsQueue->getNumServed();
		std::cout << "Average wait time for each party in awaiting seats queue: " << averageSeatingWait << std::endl;

		std::cout << std::endl;

	}
};

#endif