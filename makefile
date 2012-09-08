CC = g++
CFLAGS = -c -O3 -I /usr/include/jsoncpp
LDFLAGS = /usr/lib/libjsoncpp.a

debug: clean Particle.o System.o
	$(CC) -O3 -o FancySimulation FancySimulation.cpp Particle.o System.o $(LDFLAGS)

Particle.o:
	$(CC) $(CFLAGS) Particle.cpp

System.o:
	$(CC) $(CFLAGS) System.cpp

all: Particle.o System.o

clean:
	rm *.o || echo "Nothing to clean."