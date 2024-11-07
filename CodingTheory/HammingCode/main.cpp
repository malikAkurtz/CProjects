#include "utility.h"
#include "HammingCode.h"
#include <time.h>
#include <string>
#include <vector>
#include <iostream>

int main() {

    srand(time(0)); // Seed with the current time

    std::string message;
    std::getline(std::cin, message);
    std::vector<bool> asVecBool = stringToVecBool(message);
    //asVecBool = {1,0,1,0};

    int k = asVecBool.size();               // Total # of Data Bits
    int r = calculateNumberParityBits(k);   // Total # of Redundant Bits
    int n = k+r;                            // Total # of Bits

    double codeRate = (double) k / n;       // The ratio of Data Bits to Total Bits (Higher = Better)

    printf("This is a Hamming(%d, %d) Code\n", n, k);
    printf("The Code Rate is: %f\n", codeRate);

    std::cout << "Original Message: " << message << std::endl;
    std::cout << "Original Message in Binary: ";
    for (bool b : asVecBool) {
        std::cout << b;
    } std::cout << std::endl;


    std::vector<bool> encoded = encode(asVecBool, n);
    std::cout << "Encoded Message in Binary:  ";
    for (bool b : encoded) {
       std::cout << b;
    } std::cout << std::endl;
    

    std::vector<bool> noisy_encoded = flipBit(encoded);
    std::cout << "Noisy Message in Binary:    ";
    for (bool b : noisy_encoded) {
        std::cout << b;
    } std::cout << std::endl;

    int errorSyndrome = calculateErrorSyndrome(noisy_encoded);
    std::vector<bool> decoded = decode(noisy_encoded, errorSyndrome);
    std::cout << "Decoded Message in Binary:  ";
    for (bool b : decoded) {
        std::cout << b;
    } std::cout << std::endl;

    std::cout << "Decoded Message: " << vecBoolToString(decoded);
    

    return 0;
}