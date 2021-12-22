Jonathan Wong
Email: jzwong@usc.edu

A hashtable is a data structure that uses a hash (random) function to map keys to values and allows for constant adding and lookup. To create my own hashtable, I implemented a universal hash function as well as a class that supports add, lookup, resize, and printall. I also implemented two test programs that use the hashtable.

To compile my program, run "make" in the terminal and which will compile two test programs. To run these programs, run ./birthday and 
./proberate

birthday.cpp will show the birthday problem using the hashtable which will result in around a 50% that our first collision happens within the first 23 inserts

proberate.cpp will show the average amount of probes given a set number of inserts.
