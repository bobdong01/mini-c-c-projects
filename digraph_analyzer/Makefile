CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -g

digraph_analyzer: digraph_analyzer.o digraph_functions.o
	$(CC) -o digraph_analyzer digraph_analyzer.o digraph_functions.o

diagraph_analyzer.o: digraph_analyzer.cpp digraph_functions.h
	$(CC) $(CFLAGS) -c digraph_analyzer.cpp

diagraph_functions.o: digraph_functions.cpp digraph_functions.h
	$(CC) $(CFLAGS) -c digraph_functions.cpp

clean:
	rm -f *.o digraph_analyzer
