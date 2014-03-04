//Daniel Fitzgerald
#include "prog5.h"

#include "Event.h"
#include "Packet.h"

#include <sstream>

Event::Event(unsigned int TIME, Packet* pktPtr, EVENT_TYPE evntType):
	time(TIME),
	packetPtr(pktPtr),
	type(evntType)
{}

bool Event::operator<(Event other){
	if (time<other.time){
		return true;
	}else if (time == other.time){	//if two events arrive at the same time
		return ((int)type > (int)other.type);//this a TRANSMITTED and other is an ARRIVAL - finish transmitting events before getting new arrival events
	}
	return false;
}

ostream& operator<<(ostream& os, const EVENT_TYPE& type){
	switch(type){
		case ARRIVAL:
			os<<"ARRIVAL";
			break;
		case TRANSMITTED:
			os<<"TRANSMITTED";
			break;
		default:
			os<<"INVALID EVENT TYPE";
			break;
	}
	return os;
}

//for printing source nodes
ostream& operator<<(ostream& os, const Event& event){
	os<<"EVENT{t="<<event.time<<" type="<<event.type<<" packet="<<event.packetPtr<<"}";
	return os;	
}

ostream& operator<<(ostream& os, const Event* const eventPtr){
	os<<"*"<<*eventPtr;
	return os;	
}
