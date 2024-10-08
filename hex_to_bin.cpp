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
    std::string binary_string;
    
    for (char hex_char : hex_encoding) {
        unsigned int hexAsInt;
        
        if (hex_char >= '0' && hex_char <= '9') {
            hexAsInt = hex_char - '0';
        } else if (hex_char >= 'A' && hex_char <= 'F') {
            hexAsInt = hex_char - 'A' + 10;
        } else if (hex_char >= 'a' && hex_char <= 'f') {
            hexAsInt = hex_char - 'a' + 10;
        } else {
            std::cerr << "Invalid hex character: " << hex_char << std::endl;
            return ""; // Handle the error as appropriate for your use case
        }

        cout << hexAsInt << endl;
        binary_string += std::bitset<4>(hexAsInt).to_string();
    }
    
    return binary_string;
}

int main() {
    std::string s = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string binary_encoding = hexToBinary(s);
    std::cout << binary_encoding << std::endl;
    return 0;
}


std::string binaryToBase64(const std::string& binary_encoding) {

    vector<unsigned int> six_bit_vector(6, 0);

    int groupsOfSix = binary_encoding.length() / 6;

    int remainingBits = binary_encoding.length() % 6;

    for (int i = 0; i < groupsOfSix; i++) {
        six_bit_vector[0] = binary_encoding[i];
        six_bit_vector[1] = binary_encoding[i+1];
        six_bit_vector[2] = binary_encoding[i+2];
        six_bit_vector[3] = binary_encoding[i+3];
        six_bit_vector[4] = binary_encoding[i+4];
        six_bit_vector[5] = binary_encoding[i+5];


    }




}

    

