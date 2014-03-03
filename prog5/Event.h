//Daniel Fitzgerald

#ifndef EVENT_H
#define EVENT_H

#include "Packet.h"

enum EVENT_TYPE {ARRIVAL=0, TRANSMITTED=1, PROPAGATED=2};

class Event{
	private:
		unsigned int time;
		Packet* packetPtr;
		EVENT_TYPE type;
		
	public:
		Event(unsigned int , Packet*, EVENT_TYPE);
		unsigned int getTime(){return time;}
		const Packet* const getPacket(){return packetPtr;}
		EVENT_TYPE getType(){return type;}
		bool operator<(Event other){return time<other.time;}
};

#endif
