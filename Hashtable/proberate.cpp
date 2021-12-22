#include "Hashtable.h"

using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    // Create an array with every letter
    char alph[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    // Track the amount of probes that are needed
    double probes = 0;
    Hashtable<int> map;
    // Insert into the hashtable 10000 times
    for (int i = 0; i < 10000; i++) {
        string random = "";
        // Generate a random 28 length string
        for (int i = 0; i < 28; i++) {
            random += alph[rand() % 26];
        }
        // Add to map and sum up the amount of probes on each  add
        probes += map.add(random, 1);
    }
    // Calculate the avergae amount of probes
    cout << "Average number of probes is " << (double)probes / 10000 << endl;
}