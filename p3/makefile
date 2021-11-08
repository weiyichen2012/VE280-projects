all: p3

pack: p3.cpp
	rm p3.zip
	zip p3.zip p3.cpp

clean:
	rm p3 p3.o simulation.o

run: p3
	./p3

p3: p3.o simulation.o
	g++ -Wall -o p3 p3.o simulation.o

p3.o: p3.cpp simulation.h world_type.h
	g++ -Wall -c p3.cpp

simulation.o: simulation.cpp simulation.h world_type.h
	g++ -Wall -c simulation.cpp