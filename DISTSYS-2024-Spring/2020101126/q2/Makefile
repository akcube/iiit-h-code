CXX := g++
CXXFLAGS := -O3

SOURCES := mapper0.cpp mapper1.cpp combiner0.cpp combiner1.cpp reducer0.cpp reducer1.cpp
EXECUTABLES := $(SOURCES:.cpp=.out)

.PHONY: all clean

build: $(EXECUTABLES)

%.out: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLES)

