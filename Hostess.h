#ifndef HOSTESS_H_
#define HOSTESS_H_

#include"AwaitingSeatsQueue.h"
#include "Party.h"
#include "Table.h"

class Hostess
{
private:
	AwaitingSeatsQueue* myQueue;

public:

	// CONSTRUCTOR
	Hostess()
	{

	}
	void setQueue(AwaitingSeatsQueue* theQueue) { myQueue = theQueue; }

	// She gonna seat some peeps!
	void update(int clock, Table* smokingSection[], Table* nonSmokingSection[])
	{
		if (!myQueue->theQueue.empty())
		{
			if (myQueue->theQueue.front()->isSmoker) // if they're a smoker party...
			{
				for (int i = 0; i < 3; i++) // look for an open smoker table...
				{
					if (smokingSection[i]->getIsEmpty())
					{
						smokingSection[i]->setParty(myQueue->theQueue.front()); // and seat them!
						myQueue->increaseNumServed(myQueue->theQueue.front()->numOfMembers); // add them to the numServed

						// Also, "stamp their time card"
						myQueue->theQueue.front()->seatedTime = clock;

						myQueue->theQueue.pop(); // and away they go!

						break;
					}

					else // if they're a non smoker party...
						for (int i = 0; i < 7; i++) // look for an open nonsmoker table... 
						{
							if (nonSmokingSection[i]->getIsEmpty())
							{
								nonSmokingSection[i]->setParty(myQueue->theQueue.front()); // and seat them!
								myQueue->increaseNumServed(myQueue->theQueue.front()->numOfMembers); // add them to the numServed

								// Also, "stamp their time card"
								myQueue->theQueue.front()->seatedTime = clock;

								myQueue->theQueue.pop(); // and away they go!
								break;
							}
						}
				}
			}
		}
	}

};


#endif