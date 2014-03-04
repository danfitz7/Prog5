//Ethan Coeytaux

#ifndef INFO_H
#define INFO_H

#include <vector>

class Info{
	private:
		int totalPackets;
		std::vector<int> responseTimes;
	public:
		Info();
		void addPacket(int responseTime);
		int getAverageResponseTime();
		int getVariance();
};

#endif