#include "utility.h"
#include "HammingCode.h"
#include <ctime>
#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    // Read message from standard input
    std::string message;
    std::cout << "Enter the message to encode: ";
    std::getline(std::cin, message);

    // Convert message to vector of booleans
    std::vector<bool> dataBits = stringToVecBool(message);
    int k = dataBits.size();                    // Number of data bits
    int r = calculateNumberParityBits(k);       // Number of parity bits
    int n = k + r;                              // Total number of bits after encoding
    double codeRate = static_cast<double>(k) / n;

    // Display code parameters
    std::cout << "\nThis is a Hamming(" << n << ", " << k << ") Code";
    std::cout << "\nCode Rate: " << codeRate << "\n";

    // Display original message in binary
    std::cout << "\nOriginal Message: " << message;
    std::cout << "\nOriginal Message in Binary: ";
    for (bool bit : dataBits) {
        std::cout << bit;
    }

    // Encode the data bits
    std::vector<bool> encodedMessage = encode(dataBits, n);
    std::cout << "\n\nEncoded Message in Binary:  ";
    for (bool bit : encodedMessage) {
        std::cout << bit;
    }

    // Introduce a single-bit error
    std::vector<bool> noisyMessage = flipBit(encodedMessage);
    std::cout << "\nNoisy Message in Binary:    ";
    for (bool bit : noisyMessage) {
        std::cout << bit;
    }

    // Calculate error syndrome and decode
    int errorSyndrome = calculateErrorSyndrome(noisyMessage);
    std::vector<bool> decodedMessage = decode(noisyMessage, errorSyndrome);
    std::cout << "\n\nError Syndrome: " << errorSyndrome;

    // Display decoded message in binary
    std::cout << "\nDecoded Message in Binary:  ";
    for (bool bit : decodedMessage) {
        std::cout << bit;
    }

    // Convert decoded bits back to string
    std::string decodedString = vecBoolToString(decodedMessage);
    std::cout << "\nDecoded Message: " << decodedString << "\n";

    return 0;
}
