#Packet.o Grid.o Node.o
prog5: prog5.o LinkedList.o ListNode.o 
	g++ -o prog5 prog5.o LinkedList.o ListNode.o -I.

#Node.h Packet.h Grid.h prog5.h	
prog5.o: prog5.cpp 
	g++ -Wall -c prog5.cpp -I.

ListNode.o:	ListNode.cpp ListNode.h prog5.h
	g++ -Wall -c ListNode.cpp -I.
	
LinkedList.o: LinkedList.cpp LinkedList.h ListNode.h prog5.h
	g++ -Wall -c LinkedList.cpp -I.	
	
#Packet.o: Packet.cpp Packet.h prog5.h
#	g++ -Wall -c Packet.cpp -I.
	
#Grid.o: Grid.cpp Grid.h	prog5.h Node.h
#	g++ -Wall -c Grid.cpp -I.	

#Node.o: Node.cpp Node.h Packet.h prog5.h
#	g++ -Wall -c Node.cpp -I.	
	
clean:
	rm *.o
