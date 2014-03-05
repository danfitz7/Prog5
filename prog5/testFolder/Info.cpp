//Ethan Coeytaux

#include "prog5.h"
#include "Info.h"
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

Info::Info():
	totalPackets(0)
{}

void Info::addPacket(int responseTime)
{
	totalPackets++;
	responseTimes.push_back(responseTime);
}

void Info::setSenderID(int newID)
{
	senderID = newID;
}

double Info::getVariance()
{
	double variance = 0;
	double averageResponseTime = getAverageResponseTime();
	for (unsigned int i = 0; i < totalPackets; i++) //calculates variance
	{
    	variance += (responseTimes[i] - averageResponseTime) * (responseTimes[i] - averageResponseTime);
    }
	return sqrt(variance / (totalPackets - 1));
}

double Info::getAverageResponseTime()
{
	unsigned int i, totalResponseTime = 0;
	for (i = 0; i < totalPackets; i++)
	{
		totalResponseTime += responseTimes[i];
	}
	return (double)totalResponseTime / totalPackets;
}

void Info::print()
{
	if (totalPackets)
	{
		cout << "\t  Average response time of S" << senderID << ": " << getAverageResponseTime() << endl;
		cout << "\t  Variance of S" << senderID << ": " << getVariance() << endl;
		cout << endl;
	}else{
		if (DEBUG) cout<<"\t\tReceived no packets from source "<<senderID<<endl;
	}
}
