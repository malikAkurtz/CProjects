#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <stdio.h>
#include <sstream>

using namespace std;

/* Cryptopals.com Set 1 Challenge 1

The string:
49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d

Should produce:
SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

*/

// Hex (base 16) will use 4 bits (2^4) , so base 64 will use 6 (2^6)

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

std::string hexToBinary(const std::string& hex_encoding) {
    string stringBinaryRepresentation = "";
    // for every character in the string
    for (int i = 0; i < hex_encoding.length(); i++){
        char curChar = hex_encoding[i];
        string binRep;
        // if the character at index i is an integer
        if (isdigit(curChar)) {
            cout << "-----------------------------------------------------------" << endl;
            cout << "Char is: " << curChar << endl;
            cout << "ACII Value: " << (int) (curChar) << endl;
            cout << "Decimal Value is: " << ((curChar) - 48) << endl;
            cout << "As Binary is: " << bitset<4>((int) curChar) << endl;
            cout << "-----------------------------------------------------------" << endl;
            binRep = bitset<4>((int) curChar).to_string();
        }
        else {
            cout << "-----------------------------------------------------------" << endl;
            cout << "Char is: " << curChar << endl;
            cout << "ACII Value: " << (int) (curChar) << endl;
            cout << "Decimal Value is: " << ((curChar) - 87) << endl;
            cout << "As Binary is: " << bitset<4>((curChar) - 87) << endl;
            cout << "-----------------------------------------------------------" << endl;
            binRep = bitset<4>((int) curChar - 87).to_string();
        }
        stringBinaryRepresentation += binRep;
    }

    return stringBinaryRepresentation;
}

string binaryToBase64(const std::string& binary) {
    string stringBase64Representation = "";

    string cur6Bits = "";

    int leftoverBits = binary.length() % 6;

    for (int i = 0; i < binary.length() +1; i++) {
        if (cur6Bits.length() < 6) {

            if (i < binary.length()) {
                cout << "i is: " << i << endl;
                cur6Bits += binary[i];
                cout << cur6Bits << endl;
            }
            else {
                while (cur6Bits.length() < 6) {
                    cout << "Here?" << endl;
                    cur6Bits += "0";
                }
            }
        }

        else { // convert the 6 bits to base64 and append it to the base string
            // Ex. have "010101"
            cout << "The 6 bits are: " << bitset<6>(cur6Bits) << endl;
            unsigned long base64index = bitset<6>(cur6Bits).to_ulong();
            stringBase64Representation += encoding_table[base64index];
            cout << base64index << endl;
            cur6Bits = "";
            i = i - 1;
        }
    }

    return stringBase64Representation;
}


int main() {
    string s = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

    string binaryRep = hexToBinary(s);

    cout << binaryRep << endl;

    string base64 = binaryToBase64(binaryRep);

    cout << base64;
}