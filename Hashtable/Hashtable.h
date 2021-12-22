#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

template<class T>
class Hashtable {
public:
    // Constructor with default parameters
    Hashtable(bool debug = false, unsigned int size = 11);
    ~Hashtable() { delete[] data; };
    int add(std::string k, const T& val);
    const T& lookup(std::string k);
    void reportAll(std::ostream& stream) const;

private:
    int hash(std::string k) const;
    void resize();
    int size;
    int items;
    bool debug;
    std::pair<std::string, T>* data;
    long r[5];
    // Keeps track of our next resize
    int newSize = 0;
    int sizes[17]
            = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};
};

template<class T>
Hashtable<T>::Hashtable(bool debug, unsigned int size) {
    this->size = size;
    this->debug = debug;
    items = 0;
    // Finds the next biggest size in resize array
    while ((int)size > sizes[newSize]) {
        newSize++;
    }
    // Create array that will hold our data
    data = new std::pair<std::string, T>[size];
    // Add debug values into the r array
    if (debug == true) {
        r[4] = 983132572;
        r[3] = 1468777056;
        r[2] = 552714139;
        r[1] = 984953261;
        r[0] = 261934300;
    } else {
        r[0] = rand() % size;
        r[1] = rand() % size;
        r[2] = rand() % size;
        r[3] = rand() % size;
        r[4] = rand() % size;
    }
}

template<class T>
int Hashtable<T>::add(std::string k, const T& val) {
    // Resize if load factor is too big
    double load = (double)(items + 1) / size;
    if (load >= 0.5) {
        resize();
    }
    // Calculate hashKey and track index
    unsigned hashKey = hash(k) % size;
    int probes = 0;
    int index = hashKey;
    // While hashtable isn't empty at index
    while (data[index].first != "") {
        // Check if already in hashtable
        if (data[index].first == k) {
            return 0;
        } else {
            // Otherwise, increase number of probes and check again
            probes++;
            index = (hashKey + (int)pow(probes, 2)) % size;
        }
    }
    // Insert into hashtable and increment items
    data[index].first = k;
    data[index].second = val;
    items++;
    return probes;
}

template<class T>
const T& Hashtable<T>::lookup(std::string k) {
    // Calculate hashkey and track index
    unsigned hashKey = hash(k) % size;
    int probes = 0;
    int index = hashKey;
    // Same as add function
    while (data[index].first != "") {
        if (data[index].first == k) {
            // If its in the array, return value
            return data[index].second;
        } else {
            // Otherwise, increment probes and check again
            probes++;
            index = (hashKey + (int)pow(probes, 2)) % size;
        }
    }
    // Return junk value if not in table
    return data[0].second;
}

template<class T>
void Hashtable<T>::reportAll(std::ostream& stream) const {
    // Loop through the entire array
    for (int i = 0; i < size; i++) {
        // If there is a value at the index
        if (data[i].first != "") {
            // Output to the ostream
            stream << data[i].first << " " << data[i].second << std::endl;
        }
    }
}

template<class T>
void Hashtable<T>::resize() {
    // Approximately double the size or to the next in sequence
    // Track old size
    int temp = size;
    // Set size equal to the next biggest in sizes array
    size = sizes[newSize];
    // Increment for next resize
    newSize++;
    std::pair<std::string, T>* newHash = new std::pair<std::string, T>[size];
    // Rehash
    // Loop through entire old array
    for (int i = 0; i < temp; i++) {
        // If index isn't empty
        if (data[i].first != "") {
            // Create a new hashKey
            unsigned hashKey = hash(data[i].first);
            int probes = 0;
            int index = hashKey;
            // While newHash table isn't empty at index
            while (newHash[index].first != "") {
                // Quadratic probe
                probes++;
                index = (hashKey + (int)pow(probes, 2)) % size;
            }
            // Add to new hash table
            newHash[index].first = data[i].first;
            newHash[index].second = data[i].second;
        }
    }
    // Delete old hash table and set data equal to the new table
    delete[] data;
    data = newHash;
}

template<class T>
int Hashtable<T>::hash(std::string k) const {
    // Vector to store word sums
    std::vector<long long> w;
    // Index to track where we are in the string
    int index = k.length() - 1;
    long long sum;
    // Break the string into parts
    for (int i = k.length() / 6; i > 0; i--) {
        sum = 0;
        // Loop through each part, convert to numbers, and add
        for (int j = 0; j < 6; j++) {
            sum += (k[index] - 96) * pow(27, j);
            index--;
        }
        // Push to vector
        w.push_back(sum);
    }
    sum = 0;
    // Last part of string might not be perfectly 6 letters
    // Use modulo to find the loop bound
    for (int i = 0; i < (int)k.length() % 6; i++) {
        sum += (k[index] - 96) * pow(27, i);
        index--;
    }
    w.push_back(sum);
    long long totalSum = 0;
    // While w has values
    for (int i = 0; i < (int)w.size(); i++) {
        // Calculate the hash value using equation
        totalSum += w[i] * r[i];
    }
    // Modulo by size to wrap around
    totalSum = totalSum % size;
    return totalSum;
}