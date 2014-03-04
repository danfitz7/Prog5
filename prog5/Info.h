//Ethan Coeytaux

#ifndef INFO_H
#define INFO_H

#include <vector>

class Info{
	private:
		unsigned int senderID;
		unsigned int totalPackets;
		std::vector<int> responseTimes;
	public:
		Info();
		void addPacket(int responseTime);
		void setSenderID(int newID);
		int getSenderID() {return senderID;}
		double getAverageResponseTime();
		double getVariance();
};

#endif
