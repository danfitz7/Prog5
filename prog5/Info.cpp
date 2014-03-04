//Ethan Coeytaux

#include "Info.h"
#include <vector>

using namespace std;

Info::Info():
	totalPackets(0)
{}

void Info::addPacket(int responseTime)
{
	totalPackets++;
	responseTimes.push_back(responseTime);
}

int Info::getVariance()
{
	int i, variance = 0;
	int averageResponseTime = getAverageResponseTime();
	for (i = 0; i < totalPackets; i++) //calculates variance
	{
    	variance += (responseTimes[i] - averageResponseTime) * (responseTimes[i] - averageResponseTime);
    }
	return variance / (totalPackets - 1);
}

int Info::getAverageResponseTime()
{
	int i, totalResponseTime = 0;
	for (i = 0; i < totalPackets; i++)
	{
		totalResponseTime += responseTimes[i];
	}
	return totalResponseTime / totalPackets;
}
