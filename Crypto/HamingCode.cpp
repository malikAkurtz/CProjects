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

vector<bool> stringToVecBool(string code);
string vecBoolToString(vector<bool> vector_code);
int calculateNumberParityBits(int numDataBits);
vector<bool> flipBit(vector<bool> encoded);


vector<bool> encode(vector<bool> input, int totalBits) {

    //initialize a vector that will hold our data bits plus our redundant bits
    vector<bool> toReturn(totalBits);

    
    int dataIndex = 0;
    // For every position in our output vector
    for (int i = 1; i <= toReturn.size(); i++) {
        // check if this is a position for a reserved bit
        if ((i & (i-1)) == 0) {
            // if it is, do nothing
            continue;
        }
        // if its not reserved for a parity bit
        else {
            toReturn[i-1] = input[dataIndex];
            dataIndex++;
        }
    }

    int parity = 0;
    // for every position in our output vector
    for (int i = 1; i <= toReturn.size(); i <<= 1) { 
        parity = 0;
        for (int j = 1; j <= toReturn.size(); j++) {
            if (j & i) { 
                parity ^= toReturn[j - 1];
            }
        }
        toReturn[i - 1] = parity; 
    }
    

    return toReturn;
}



int calculateErrorSyndrome(vector<bool> noisy_encoded) {
    vector<bool> correctEncoding = noisy_encoded;

    vector<bool> decoded = {};

    int errorSyndrome = 0;

    for (int i = 1; i <= noisy_encoded.size(); i <<= 1) { 

        int actualParity = 0;
        for (int j = 1; j <= noisy_encoded.size(); j++) {
            if (j & i) { 
                actualParity ^= noisy_encoded[j - 1];
            }
        }

        if (actualParity != 0) {
            errorSyndrome += i;
        }
    }

    return errorSyndrome;
}

vector<bool> decode(vector<bool> noisy_encoded, int error_syndrome) {

    vector<bool> decoded = {};
    vector<bool> correctEncoding = noisy_encoded;

    if (error_syndrome != 0) {
        int errorIndex = error_syndrome - 1;
        correctEncoding[errorIndex] = correctEncoding[errorIndex] ^ 1;
    }

    // For every position in our output vector
    for (int i = 1; i <= correctEncoding.size(); i++) {
        // check if this is a position for a reserved bit
        if ((i & (i-1)) == 0) {
            // if it is, do nothing
            continue;
        }
        // if its not reserved for a parity bit
        else {
            decoded.push_back(correctEncoding[i-1]);
        }
    }

    return decoded;
    
}


int main() {

    srand(time(0)); // Seed with the current time

    string message;
    getline(cin, message);
    vector<bool> asVecBool = stringToVecBool(message);
    //asVecBool = {1,0,1,0};

    int k = asVecBool.size();               // Total # of Data Bits
    int r = calculateNumberParityBits(k);   // Total # of Redundant Bits
    int n = k+r;                            // Total # of Bits

    double codeRate = (double) k / n;       // The ratio of Data Bits to Total Bits (Higher = Better)

    printf("This is a Hamming(%d, %d) Code\n", n, k);
    printf("The Code Rate is: %f\n", codeRate);

    cout << "Original Message: " << message << endl;
    cout << "Original Message in Binary: ";
    for (bool b : asVecBool) {
        cout << b;
    } cout << endl;


    vector<bool> encoded = encode(asVecBool, n);
    cout << "Encoded Message in Binary:  ";
    for (bool b : encoded) {
        cout << b;
    } cout << endl;
    

    vector<bool> noisy_encoded = flipBit(encoded);
    cout << "Noisy Message in Binary:    ";
    for (bool b : noisy_encoded) {
        cout << b;
    } cout << endl;

    int errorSyndrome = calculateErrorSyndrome(noisy_encoded);
    vector<bool> decoded = decode(noisy_encoded, errorSyndrome);
    cout << "Decoded Message in Binary:  ";
    for (bool b : decoded) {
        cout << b;
    } cout << endl;

    cout << "Decoded Message: " << vecBoolToString(decoded);
    

    return 0;
}



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


int calculateNumberParityBits(int numDataBits) {
    int r = 0;
    while (!((1 << r) >= (numDataBits + r + 1))) {
        r++;
    }

    return r;
}


vector<bool> flipBit(vector<bool> encoded) {
    int min = 0;
    int max = encoded.size() - 1;
    int random_num = min + rand() % (max - min + 1);

    encoded[random_num] = encoded[random_num] ^ 1;

    return encoded;
}