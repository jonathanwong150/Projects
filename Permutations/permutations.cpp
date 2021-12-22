#include <iostream>

// Swaps two characters in a string
void swap(std::string& x, int curr, int next) {
    char temp;
    temp = x[curr];
    x[curr] = x[next];
    x[next] = temp;
}
void helper(std::string& y, int start, int end) {
    if (start == end) {
        std::cout << y << std::endl;  // Once string is iterated through, print result
        return;
    }
    for (int i = start; i <= end; i++) {  // Loop from start to end
        swap(y, start, i);                // Swap starting index with i
        helper(y, start + 1, end);        // Call recursively with incremented starting index
        swap(y, start, i);                // Backtrace returns
    }
}

void permutations(std::string in) {
    int len = in.length();  // Find length
    if (len == 0) {         // Edge case
        std::cout << "" << std::endl;
        return;
    }
    helper(in, 0, len - 1);  // Call to helper
}