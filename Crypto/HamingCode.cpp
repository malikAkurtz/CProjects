#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <bitset>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <map>
#include <bitset>
#include <fstream>

using namespace std;

vector<bool> stringToVecBool(string code) {

    vector<bool> toReturn = {};

    bitset<8> curCharacter;

    // for every character in the string
    for (char c : code) {
        curCharacter = c;
        // for every bit in the character
        for (int i = 7; i >= 0; i--) {
            toReturn.push_back(curCharacter[i]);
        }
    }

    return toReturn;
}

string vecBoolToString(vector<bool> vector_code) {
    string toReturn = "";

    char c = 0;

    for (int i = 0; i < vector_code.size() ; i+=8) {
        for (int j = 0; j < 8 ; j++) {
            c = c << 1 | vector_code[i+j];
        }
        toReturn += c;
    }

    return toReturn;
}


// number of redundancy bits = log2()


int calculateNumParityBits(vector<bool> input) {
    int numParityBits = ceil(log(input.size())) + 1;

    return numParityBits;
}


int main() {
    string message = "a";
    vector<bool> encoded = stringToVecBool(message);

    for (bool b : encoded) {
        cout << b;
    } cout << endl;

    string decoded = vecBoolToString(encoded);

    cout << decoded << endl;
    cout << calculateNumParityBits(encoded);

    

    return 0;
}