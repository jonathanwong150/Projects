#include <exception>
#include <stdexcept>
#include <vector>

template<class T>
class MinHeap {
public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
    This should work for any d >= 2,
    but doesn't have to do anything for smaller d.*/

    ~MinHeap();

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;
    /* returns the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */

    bool isEmpty();
    /* returns true iff there are no elements on the heap. */

private:
    // whatever you need to naturally store things.
    // You may also add helper functions here.
    void bubbleUp(int pos);
    void trickleDown(int pos);
    // void swap(int val1,int val2);
    void updatePriority(int pos, int priority);  // IMPLEMENT
    int numLeaves;
    std::vector<std::pair<T, int>> v;
};

template<class T>
MinHeap<T>::MinHeap(int d) {
    numLeaves = d;
}

template<class T>
MinHeap<T>::~MinHeap() {}

template<class T>
void MinHeap<T>::add(T item, int priority) {
    std::pair<T, int> myPair(item, priority);
    v.push_back(myPair);
    bubbleUp(v.size() - 1);
}

template<class T>
const T& MinHeap<T>::peek() const {
    if (v.empty()) {
        throw std::out_of_range("Empty Heap");
    }
    return v[0].first;
}

template<class T>
void MinHeap<T>::remove() {
    if (isEmpty()) {
        throw std::out_of_range("Empty Heap");
    }
    std::swap(v[0], v[v.size() - 1]);
    v.pop_back();
    trickleDown(0);
}

template<class T>
bool MinHeap<T>::isEmpty() {
    if (v.size() != 0) {
        return false;
    }
    return true;
}

template<class T>
void MinHeap<T>::bubbleUp(int pos) {
    if (pos > 0 && v[pos].second < v[(pos - 1) / numLeaves].second) {
        std::swap(v[pos], v[(pos - 1) / numLeaves]);
        bubbleUp((pos - 1) / numLeaves);
    } else if (
            pos > 0 && v[pos].second == v[(pos - 1) / numLeaves].second
            && v[pos].first < v[(pos - 1) / numLeaves].first) {
        std::swap(v[pos], v[(pos - 1) / numLeaves]);
    }
}

template<class T>
void MinHeap<T>::trickleDown(int pos) {
    int child = numLeaves * pos + 1;  // Gets first child
    int max = child;
    if (child < v.size()) {  // Check if child exists or is in bounds
        for (int i = 1; i <= numLeaves; i++) {
            if (child + i < v.size() && v[child + i].second < v[max].second) {  // Find smallest child
                max = child + i;
            }
        }
        if (v[max].second < v[pos].second) {  // Swap with smallest child
            std::swap(v[max], v[pos]);
            trickleDown(max);
        } else if (v[max].second == v[pos].second && v[max].first < v[pos].first) {
            std::swap(v[max], v[pos]);
        }
    }
}