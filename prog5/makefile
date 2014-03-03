#Packet.o Grid.o Node.o
prog5: prog5.o Position.o Node.o Packet.o MuleNode.o SourceNode.o Grid.o Event.o ListNode.h LinkedList.h 
	g++ -o prog5 prog5.o Position.o Node.o Packet.o MuleNode.o SourceNode.o ReceiverNode.o Grid.o Event.o -I.

#Node.h Packet.h Grid.h prog5.h	
prog5.o: prog5.cpp ListNode.h LinkedList.h Node.h MuleNode.h SourceNode.o ReceiverNode.o Event.o Grid.h Packet.h prog5.h Position.h
	g++ -Wall -c prog5.cpp -I.

#ListNode.o:	ListNode.cpp ListNode.h prog5.h
#	g++ -Wall -c ListNode.cpp -I.
	
#LinkedList.o: LinkedList.cpp LinkedList.h ListNode.h Node.h prog5.h
#	g++ -Wall -c LinkedList.cpp -I.	
	
Packet.o: Packet.cpp Packet.h LinkedList.h Node.h SourceNode.h prog5.h
	g++ -Wall -c Packet.cpp -I.
	
Event.o: Event.cpp Event.h Packet.h prog5.h
	g++ -Wall -c Event.cpp -I.	
	
Position.o:	Position.cpp Position.h prog5.h
	g++ -Wall -c Position.cpp -I.
	
Grid.o: Grid.cpp Grid.h	prog5.h Node.h
	g++ -Wall -c Grid.cpp -I.	

Node.o: Node.cpp Node.h Packet.h Position.h prog5.h
	g++ -Wall -c Node.cpp -I.	
	
MuleNode.o: MuleNode.cpp MuleNode.h Node.h Position.h prog5.h
	g++ -Wall -c MuleNode.cpp -I.	

SourceNode.o: SourceNode.cpp SourceNode.h Node.h Position.h prog5.h
	g++ -Wall -c SourceNode.cpp -I.	

ReceiverNode.o: ReceiverNode.cpp ReceiverNode.h Node.h Position.h prog5.h
	g++ -Wall -c ReceiverNode.cpp -I.
	
clean:
	rm *.o
