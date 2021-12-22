#include <array>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
const long e = 65537;

long log100(long num) {  // Log base 100 method
    return log(num) / log(100);
}

long gcd(long p, long q) {  // Finds the greatest common divisor between two parameters
    // Run euclidean algorithm
    long x = p;
    long y = q;
    while (y != 0) {
        long r = x % y;
        x = y;
        y = r;
    }
    return x;
}

long findD(long L) {  // Calculates decryption key
    // Run extended euclidean algorithm
    long s = 0;
    long old_s = 1;
    long t = 1;
    long old_t = 0;
    long r = e;
    long old_r = L;
    while (r != 0) {
        long quotient = floor(old_r / r);
        long temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = s;
        s = old_s - quotient * s;
        old_s = temp;
        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }
    return old_t;
}

string convertToBinary(long num) {  // Works
    string binary = "";
    while (num > 0) {  // Creates a backwards binary string
        binary += to_string(num % 2);
        num /= 2;
    }
    return binary;
}

long modExp(long b, string eBin, long m) {  // Takes a bool, binary array as an input
    long x = 1;                             // Runs modular exponentiation algorithm
    long power = b % m;
    for (unsigned int i = 0; i < eBin.length(); i++) {  // Loop through the binary string
        if (eBin[i] == '1') {
            x = (x * power) % m;
        }
        power = (power * power) % m;
    }
    return x;
}

int main(int argc, char* argv[]) {
    string temp = argv[1];  // Assume these are large primes
    long p = stol(temp);
    temp = argv[2];  // Cast these to ints
    long q = stol(temp);
    string command;
    cout << "Enter a command: ";  // Take in a command
    cin >> command;

    // Calculate decryption key
    long L = (p - 1) * (q - 1) / gcd(p - 1, q - 1);
    if (L <= e) {
        cout << "L is less than e!" << endl;  // Check for errors
        return 2;
    }
    if (gcd(e, L) != 1) {
        cout << "Unfortunate choice of p and q." << endl;
        return 3;
    }
    long d = findD(L);  // Calculate d
    if (d < 0) {        // Add if d is too small
        d += (p - 1) * (q - 1);
    }

    while (command != "EXIT") {  // Keep asking as long as user doesn't exit
        if (command != "EXIT" && command != "DECRYPT" && command != "ENCRYPT") {  // Exit gracefully
            return 0;
        }
        if (command == "ENCRYPT") {  // Create/override file at fileName, encrypt message, n is used in encryption
            string fileName;         // Read inputs
            long n;
            string message;
            cin >> fileName;
            cin >> n;  // N value we will use
            cin.ignore();
            getline(cin, message);                 // Take the entire message
            string eBinary = "10000000000000001";  // Hard Code Binary e value
            if (n < 27) {
                cout << "N value is too small." << endl;
                return 1;
            }
            long x = floor(1 + log100(n / 27));

            ofstream ofile;  // Open output file
            ofile.open(fileName, ios::trunc);

            unsigned int count = 0;
            unsigned int size = message.length();
            if (size % x != 0) {  // Add to the size for  trailing whitespace
                size += (size % x);
            }
            while (count < size) {
                string m = "";
                for (int i = count; i < x + count; i++) {  // Repeat this part
                    string temp = "";
                    if (message[i] == ' ') {  // Check if the character is a space
                        temp = "00";
                    } else {
                        temp = to_string((int)message[i] - 96);  // Turn it into numerical value
                        if ((int)message[i] - 96 < 10) {
                            temp = "0";
                            temp += to_string((int)message[i] - 96);
                        }
                    }
                    if (count >= message.length()) {
                        temp = "00";  // Add 00 for trailing whitespace
                    }
                    m += temp;  // Convert each char to an int and add to M
                }
                count += x;

                long M = stol(m);  // Calculate values and read into output file
                long C = modExp(M, eBinary, n);
                ofile << C;
                if (count != size) {
                    ofile << " ";
                }
            }
            ofile.close();
        }
        if (command == "DECRYPT") {  // Reads contents of input, decrypt, and override the output
            string input;
            string output;
            cin >> input;
            cin >> output;
            long n = p * q;
            long x = floor(1 + log100(n / 27));  // Calculate n and x

            ifstream ifile(input);  // Open input and output files
            ofstream ofile;
            ofile.open(output, ios::trunc);
            long C = 0;
            string dBinary = convertToBinary(d);  // Converts d to a reversesd binary string
            while (ifile >> C) {
                string word = "";
                string M = to_string(modExp(C, dBinary, n));  // Calculate M
                if (M.length() % 2 != 0) {                    // Add a 0 if the lengh of the message is odd
                    M = "0" + M;
                }
                for (unsigned int i = 0; i < x * 2;
                     i += 2) {  // Loop through the M, turn it into a char, and read to output
                    string temp = "";
                    temp += M[i];
                    temp += M[i + 1];
                    if (temp == "00") {
                        word += " ";
                    } else {
                        if (temp[i] == '0') {
                            temp = M[i + 1];
                        }
                        word += (char)(stoi(temp) + 96);
                    }
                    cout << word << endl;
                }
                ofile << word;
            }
            ofile.close();
        }

        cout << "Enter another command: ";
        cin >> command;
    }
    cout << "Exited Gracefully." << endl;
}