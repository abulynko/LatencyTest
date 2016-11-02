CXX=clang++
CXXFLAGS=-pipe -std=c++11 -Wc++11-extension -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES) -I.
LIBS=-lstdc++ -lm -lpthread
SOURCES=application.cpp default_transport.cpp your_profiler.cpp your_transport.cpp 
HEADERS=default_transport.hpp your_profiler.hpp your_transport.hpp 

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

build: latency-test

clean:
	-rm *.o
	-rm latency-test

latency-test: $(OBJECTS)
	$(CXX) $(LFLAGS) -o $@ $(OBJECTS) $(LIBS)

%.o : %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) -o $@ $< 

.PHONY: build clean

