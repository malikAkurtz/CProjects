#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <stdio.h>
#include <sstream>

using namespace std;
/*
The string:
49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d

Should produce:
SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

*/

// Hex (base 16) will use 4 bits (2^4) , so base 64 will use 6 (2^6)


#include <iostream>
#include <string>
#include <bitset>

std::string hexToBinary(const std::string& hex_encoding) {
    string stringBinaryRepresentation = "";
    // for every character in the string
    for (int i = 0; i < hex_encoding.length(); i++){
        char curChar = hex_encoding[i];
        // if the character at index i is an integer
        if (isdigit(curChar)) {
            cout << "-----------------------------------------------------------" << endl;
            cout << "Char is: " << curChar << endl;
            cout << "ACII Value: " << (int) (curChar) << endl;
            cout << "Decimal Value is: " << ((curChar) - 48) << endl;
            cout << "As Binary is: " << bitset<4>((int) curChar) << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }
}


int main() {
    string s = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

    string binaryRep = hexToBinary(s);

    cout << binaryRep;
}