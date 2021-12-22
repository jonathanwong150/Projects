CXX = g++
CPPFLAGS = -Wall -g

all: rsa

doublet: rsa.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm *.o