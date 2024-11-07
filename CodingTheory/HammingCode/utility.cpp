#include "utility.h"
#include <vector>
#include <string>
#include <bitset>
#include <cstdlib>


std::vector<bool> stringToVecBool(std::string code) {

    std::vector<bool> toReturn = {};

    std::bitset<8> curCharacter;

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


std::string vecBoolToString(std::vector<bool> vector_code) {
    std::string toReturn = "";

    char c = 0;

    for (int i = 0; i < vector_code.size() ; i+=8) {
        for (int j = 0; j < 8 ; j++) {
            c = c << 1 | vector_code[i+j];
        }
        toReturn += c;
    }

    return toReturn;
}


std::vector<bool> flipBit(std::vector<bool> encoded) {
    int min = 0;
    int max = encoded.size() - 1;
    int random_num = min + rand() % (max - min + 1);

    encoded[random_num] = encoded[random_num] ^ 1;

    return encoded;
}


int calculateNumberParityBits(int numDataBits) {
    int r = 0;
    while (!((1 << r) >= (numDataBits + r + 1))) {
        r++;
    }

    return r;
}