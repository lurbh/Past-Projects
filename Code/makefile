# Change compiler path to match your system
CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++11
OBJECTS=greedyAlgo.obj Student.obj AdjacencyMatrix.obj
EXEFILE=greedyAlgo.exe 
ERASE=rm

# Targets ========================================

$(EXEFILE) : $(OBJECTS)
	$(CC) -o $(EXEFILE) $(OBJECTS)

Student.obj :Student.cpp Student.h
	$(CC) -c -o Student.obj $(CFLAGS) Student.cpp 

greedyAlgo.obj :greedyAlgo.cpp greedyAlgo.h
	$(CC) -c -o greedyAlgo.obj $(CFLAGS) greedyAlgo.cpp 

AdjacencyMatrix.obj :AdjacencyMatrix.cpp AdjacencyMatrix.h
	$(CC) -c -o AdjacencyMatrix.obj $(CFLAGS) AdjacencyMatrix.cpp 

all : 
	$(MAKE) $(EXEFILE)

rebuild : 
	$(MAKE) clean
	$(MAKE) all

clean :
	rm $(EXEFILE) $(OBJECTS)