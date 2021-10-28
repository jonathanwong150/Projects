CXX = g++
CPPFLAGS = -Wall -g

all: doublet

doublet: doublet.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm *.o