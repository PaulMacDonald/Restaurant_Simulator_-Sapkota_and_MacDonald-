#ifndef AWAITINGSEATSQUEUE_H_
#define AWAITINGSEATSQUEUE_H_

#include<queue>
#include"Party.h"

class AwaitingSeatsQueue
{
private:
	double arrivalRate;
	std::queue<Party*> theQueue;
	int totalWaitTime;
	int numServed;

public:

	// CONSTRUCTOR
	AwaitingSeatsQueue() : totalWaitTime(0), numServed(0)
	{
		Party* p1 = new Party(0);
		Party* p2 = new Party(0);
		Party* p3 = new Party(0);
		Party* p4 = new Party(0);
		Party* p5 = new Party(0);
	}

	void setArrivalRate(double theRate)
	{
		arrivalRate = theRate;
	}

	int getTotalWait() { return totalWaitTime; }

	int getNumServed() { return numServed; }

	void increaseNumServed(int partySize) { numServed += partySize; }


	void update(int clock)
	{
		if (clock >= 60.0 / arrivalRate) // Add new party if it's time to!
		{
			Party* arrival = new Party(clock);
			theQueue.push(arrival);
		}
	}


	friend class Hostess;
};

#endif