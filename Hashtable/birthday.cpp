#include "Hashtable.h"

using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    // Create an array with every letter
    char alph[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    double count = 0;
    // Run birthday problem 10000 times
    for (int i = 0; i < 10000; i++) {
        // Create a new hashtable on each run
        Hashtable<int> days(false, 365);
        int items = 0;
        int collide = 0;
        // Keep adding
        while (true) {
            string random = "";
            // Generate random 28 length strings
            for (int i = 0; i < 28; i++) {
                random += alph[rand() % 26];
            }
            // Add to the hashtable and find how many collisions
            collide = days.add(random, 1);
            // Once we need to resize or we get a collision, stop
            if (collide > 0 || items > 365 / 2) {
                break;
            }
            items++;
        }
        // If the amount of inserts is less than 23, increment our counter
        if (items < 23) {
            count++;
        }
    }
    cout << "23 or less inserts happened " << (count / 10000) * 100 << "% of the time" << endl;
}