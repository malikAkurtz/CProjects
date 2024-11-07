#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <bitset>
#include <cstdlib>
#include <time.h>
#include <cmath>


std::vector<bool> encode(std::vector<bool> input, int totalBits) {

    //initialize a vector that will hold our data bits plus our redundant bits
    std::vector<bool> toReturn(totalBits);

    
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



int calculateErrorSyndrome(std::vector<bool> noisy_encoded) {
    std::vector<bool> correctEncoding = noisy_encoded;

    std::vector<bool> decoded = {};

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

std::vector<bool> decode(std::vector<bool> noisy_encoded, int error_syndrome) {

    std::vector<bool> decoded = {};
    std::vector<bool> correctEncoding = noisy_encoded;

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
