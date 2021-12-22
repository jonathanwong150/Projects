CXX = g++
CPPFLAGS = -Wall -g

all: birthday proberate

birthday: birthday.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

proberate: proberate.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm *.o