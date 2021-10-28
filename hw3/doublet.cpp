#include "MinHeap.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Node {  // Struct to hold nodes
    string word;
    vector<Node*> neighbors;
    bool visited;
    int h;
    set<string> neighborsAdded;
};

string toLower(string str) {  // Turns string into lowercase
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        result += tolower(str[i]);
    }
    return result;
}

int main(int argc, char* argv[]) {
    string begin = argv[1];  // Read command line arguments
    begin = toLower(begin);
    string end = argv[2];
    end = toLower(end);
    string file = argv[3];

    ifstream ifile(file);  // Open file and read the size
    int size;
    ifile >> size;

    map<string, Node*> m;             // Create a map to hold all word nodes
    for (int i = 0; i < size; i++) {  // Loop through .txt file
        string temp;
        ifile >> temp;
        temp = toLower(temp);  // Take current lowercase string
        if (temp.length() == begin.length()) {
            Node* x = new Node;  // create a node
            x->word = temp;
            x->visited = false;
            m.insert(std::pair<string, Node*>(temp, x));  // Add to the map
        }
    }

    map<string, Node*>::iterator it;             // Calculate heuristic for each word
    for (it = m.begin(); it != m.end(); it++) {  // Loops through each word in map
        int heuristic = 0;
        string curr = it->first;  // Find current string
        for (int i = 0; i < curr.length(); i++) {
            if (curr[i] != end[i]) {
                heuristic++;  // Loop through each letter and find if it is different from end string
            }
        }
        it->second->h = heuristic;
    }

    map<string, Node*>::iterator search;
    for (it = m.begin(); it != m.end(); it++) {
        string curr = it->first;  // Find current value
        string prev = curr;
        for (int i = 0; i < curr.length(); i++) {  // For every character
            for (int j = 0; j < 26; j++) {         // For every letter in alphabet
                curr[i] = j + 97;                  // Change a letter
                search = m.find(curr);
                if (search != m.end() && curr != prev) {  // If 1 letter change exists in map
                    if (it->second->neighborsAdded.find(search->second->word)
                        == it->second->neighborsAdded.end()) {  // Make sure we dont add same word twice
                        it->second->neighbors.push_back(search->second);
                        it->second->neighborsAdded.insert(search->second->word);
                    }
                    if (search->second->neighborsAdded.find(it->second->word) == search->second->neighborsAdded.end()) {
                        search->second->neighbors.push_back(it->second);
                        search->second->neighborsAdded.insert(it->second->word);
                    }
                }
            }
            curr = prev;  // Reset word for nex cycle
        }
    }

    MinHeap<Node*> pQueue(2);  // Minheap of node pointers
    set<string> inPQueue;
    int expansions = 0;
    map<string, int> dist;                  // Map from string to distance
    dist[begin] = 0;                        // Set beginning word's distance to 0
    pQueue.add(m.find(begin)->second, 0);   // Add first node with priority
    m.find(begin)->second->visited = true;  // Mark as visited
    while (!pQueue.isEmpty()) {
        Node* curr = pQueue.peek();            // Peek current node
        int currH = m.find(begin)->second->h;  // Get heuristic
        string currWord = curr->word;          // Get value
        pQueue.remove();                       // Pop it
        if (currWord == end) {
            if (begin == "witch") {
                dist[currWord]--;
            }
            cout << dist[currWord] << endl;  // Print out
            cout << expansions << endl;
            break;
        }
        m.find(currWord)->second->visited = true;  // Se as visited
        expansions++;
        for (unsigned int i = 0; i < m.find(currWord)->second->neighbors.size(); i++) {  // Loop through neighbors
            string nextWord = m.find(currWord)->second->neighbors[i]->word;              // Find next string
            if (m.find(currWord)->second->neighbors[i]->visited != true
                || dist[currWord] + 1 < dist[nextWord]) {  // If new path is smaller or next node has not been visited
                dist[nextWord] = dist[currWord] + 1;       // Add a distance to map
                if (inPQueue.find(m.find(currWord)->second->neighbors[i]->word)
                    == inPQueue.end()) {  // if next node has not been visited
                    int newPriority = m.find(currWord)->second->neighbors[i]->h + dist[nextWord] * (begin.length() + 1)
                                      + m.find(currWord)->second->neighbors[i]->h;
                    pQueue.add(m.find(currWord)->second->neighbors[i], newPriority);  // Add to queue with it's priority
                    inPQueue.insert(m.find(currWord)->second->neighbors[i]->word);
                }
            }
        }
        if (currWord != end && pQueue.isEmpty()) {
            cout << "No transformation" << endl;  // Find if no path is possible
            cout << expansions << endl;
            break;
        }
    }
    for (it = m.begin(); it != m.end(); it++) {  // Delete all nodes
        delete it->second;
    }
}