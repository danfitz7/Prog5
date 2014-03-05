//Daniel Fitzgerald

#ifndef MULENODE_H
#define MULENODE_H

#include "Node.h"
#include "Position.h"

class MuleNode: public Node {
	private:
		Direction dir;	//direction the mule is currently travelling in (see Position.h)
	public:
		MuleNode(unsigned int  newID);
		void hop();						//same hop behavior as SmashBall players
		void print();
};

#endif
