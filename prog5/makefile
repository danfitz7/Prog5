main: main.o packet.o queue.o
	g++ -o main main.o packet.o queue.o -I.
	
main.o: main.cpp packet.h queue.h
	g++ -Wall -c main.cpp -I.

packet.o: packet.cpp packet.h queue.h
	g++ -Wall -c packet.cpp -I.

queue.o: queue.cpp packet.h queue.h
	g++ -Wall -c queue.cpp -I.	

clean:
	rm *.o
