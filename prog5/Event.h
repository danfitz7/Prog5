//Daniel Fitzgerald

#ifndef EVENT_H
#define EVENT_H

#include "Packet.h"

enum EVENT_TYPE {ARRIVAL=0, TRANSMITTED=1};
ostream& operator<<(ostream& os, const EVENT_TYPE& type);

class Event{
	friend ostream& operator<<(ostream& os, const Event& event);
	friend ostream& operator<<(ostream& os, const Event* const eventPtr);
	
	private:
		unsigned int time;	//time the event occurs
		Packet* packetPtr;	//associated packet
		EVENT_TYPE type;	//type of event, either packet arrival or packet done transmitting (there is no packet done propagating because that is equivalent to arrival at the next node)
		
	public:
		Event(unsigned int , Packet*, EVENT_TYPE);	
		unsigned int getTime(){return time;}
		Packet* getPacket(){return packetPtr;}
		EVENT_TYPE getType(){return type;}
		bool operator<(Event other);	//comparison so events can be sorted in prioritized queue (see LinkedList)
};

#endif
