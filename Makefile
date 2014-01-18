OBJS = minHeap.o City.o Route.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Project4 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Project4

minHeap.o : minHeap.h minHeap.cpp
	$(CC) $(CFLAGS) minHeap.cpp

City.o : City.h City.cpp Route.h Route.cpp
	$(CC) $(CFLAGS) City.cpp

Route.o : Route.h Route.cpp City.h City.cpp
	$(CC) $(CFLAGS) Route.cpp

main.o : main.cpp City.h City.cpp Route.h Route.cpp minHeap.h minHeap.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	\rm *.o *~ Project4