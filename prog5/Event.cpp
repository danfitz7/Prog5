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

