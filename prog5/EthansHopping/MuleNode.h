//Daniel Fitzgerald

#ifndef MULENODE_H
#define MULENODE_H

#include "Node.h"
#include "Position.h"

class MuleNode: public Node {
	private:
		Direction dir;
	public:
		char getType() const {return 'M';}
		MuleNode(unsigned int  newID);
		void hop();
};

#endif
