#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <stdio.h>
#include <sstream>

using namespace std;

/* Cryptopals.com Set 1 Challenge 2

The string:
1c0111001f010100061a024b53535009181c

When decoded and XOR'd with:
686974207468652062756c6c277320657965

Should produce:
746865206b696420646f6e277420706c6179

*/

static char encoding_table[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

std::string hexToBinary(const std::string& hex_encoding) {
    string stringBinaryRepresentation = "";
    // for every character in the string
    for (int i = 0; i < hex_encoding.length(); i++){
        char curChar = hex_encoding[i];
        string binRep;
        // if the character at index i is an integer
        if (isdigit(curChar)) {
            // cout << "-----------------------------------------------------------" << endl;
            // cout << "Char is: " << curChar << endl;
            // cout << "ACII Value: " << (int) (curChar) << endl;
            // cout << "Decimal Value is: " << ((curChar) - 48) << endl;
            // cout << "As Binary is: " << bitset<4>((int) curChar) << endl;
            // cout << "-----------------------------------------------------------" << endl;
            binRep = bitset<4>((int) curChar).to_string();
        }
        else {
            // cout << "-----------------------------------------------------------" << endl;
            // cout << "Char is: " << curChar << endl;
            // cout << "ACII Value: " << (int) (curChar) << endl;
            // cout << "Decimal Value is: " << ((curChar) - 87) << endl;
            // cout << "As Binary is: " << bitset<4>((curChar) - 87) << endl;
            // cout << "-----------------------------------------------------------" << endl;
            binRep = bitset<4>((int) curChar - 87).to_string();
        }
        stringBinaryRepresentation += binRep;
    }

    return stringBinaryRepresentation;
}

string binaryToHex(const std::string& binary) {
    string stringHexRepresentation = "";

    string cur4Bits = "";


    for (int i = 0; i < binary.length() +1; i++) {
        if (cur4Bits.length() < 4) {

            if (i < binary.length()) {
                cout << "i is: " << i << endl;
                cur4Bits += binary[i];
                cout << cur4Bits << endl;
            }
            else {
                cout << "i is: " << i << endl;
                while (cur4Bits.length() < 4) {
                    cout << "Here?" << endl;
                    cur4Bits += "0";
                }
            }
        }

        else { // convert the 6 bits to base64 and append it to the base string
            // Ex. have "010101"
            cout << "The 4 bits are: " << bitset<4>(cur4Bits) << endl;
            unsigned long hexindex = bitset<4>(cur4Bits).to_ulong();
            stringHexRepresentation += encoding_table[hexindex];
            cout << hexindex << endl;
            cur4Bits = "";
            i = i - 1;
        }
    }

    return stringHexRepresentation;
}


string fixedXOR(string input1, string against) {
    string XORresult = "";

    
    string inputBinaryRep = hexToBinary(input1);

    string againstBinaryRep = hexToBinary(against);

    cout << "here";

    string cur4inputBits = "";
    string cur4againstBits = "";
    for (int i = 0; i < inputBinaryRep.length() ; i++) {
        if (cur4inputBits.length() < 4) {
            cur4inputBits += inputBinaryRep[i];
            cur4againstBits += againstBinaryRep[i];
        }
        if (cur4againstBits.length() == 4) {
            string toAppend = bitset<4>(bitset<4>(cur4inputBits).to_ulong() ^ bitset<4>(cur4againstBits).to_ulong()).to_string();
            XORresult += toAppend;
            cur4inputBits = "";
            cur4againstBits = "";
        }
    }

    cout << "XOR: " << XORresult << endl;



    return binaryToHex(XORresult);
}




int main() {
    string inputString = "1c0111001f010100061a024b53535009181c";

    string toXOR = "686974207468652062756c6c277320657965";

    cout << fixedXOR(inputString, toXOR);

}