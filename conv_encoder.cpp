#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <bitset>
#include <cstdlib>
#include <time.h>

using namespace std;

// Calculate Parity C1 Method
// This method takes a veector of 3 bits, calculates it parity, and returns it
uint32_t calculateParityC1(std::vector<uint32_t> three_bit_window) {
    uint32_t parityBitC1 = 0;

    // for each bit in each of the three registers, add them all up mod 2
    for (int i = 0; i < three_bit_window.size(); i++) {
        parityBitC1 = (parityBitC1 + three_bit_window[i]) % 2;
    }

    return parityBitC1;
}



// Calculate Parity C2 Method
// This method takes a veector of 2 bits, calculates it parity, and returns it
uint32_t calculateParityC2(std::vector<uint32_t> three_bit_window) {
    uint32_t parityBitC2 = 0;

    // for each bit in each of the 2 registers, add them all up mod 2
    for (int i = 0; i < three_bit_window.size()-1; i++) {
        parityBitC2 = (parityBitC2 + three_bit_window[i]) % 2;
    }

    return parityBitC2;
}


// Encode Method
// Takes in a 16 bit code and return its encoded version after applying function C1, and C2 over the rolling window
int32_t encode(uint16_t code) {

    // To store the 16-bit code as a vector of bits
    std::vector<uint32_t> raw_code_as_vector(16, 0);

    // Need to get the code as a string so we can add each  bit to the code vector
    std::string code_as_string = std::bitset<16>(code).to_string();
    // "0000000010101010"

    
    // for each bit in the now string version of the code, 
    // turn the char version of the bit into an int and assign it in its spot in the code vector
    for (int i = 0; i < code_as_string.length(); i++) {
        raw_code_as_vector[i] = code_as_string[i] - '0';
    }

    //raw_code_as_vector = [0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0]

    // This is encoded code as a vector of bits
    std::vector<uint32_t> encoded_vector;
    encoded_vector.reserve(1000);

    // Initializing the slides window that we will use for our C1 and C2 parity calculations
    std::vector<uint32_t> sliding_window(3, 0);

    
    // This is where our sliding window will start from the left of the code, moving to the right, and calculating
    // the parities using C1 (and C2) and outputting the results of this calculations to an encoded version of the code

    // In the first iteration of the window, we start with only the most significant bit from the code in the right most register
    // of the sliding window, with the first two registers initialized to 0
    // this is what it would look like:
    // code -> 1010
    // register starts at [0,0,1] (since 1 is the most significant bit and registers 1 and 2 are still empty)
    sliding_window[0] = 0;
    sliding_window[1] = 0;
    sliding_window[2] = raw_code_as_vector[0];

    // add the result of the parity calculation from C1 to the encoded vector
    encoded_vector.push_back(calculateParityC1(sliding_window));

    // For debugging, Ill be using only C1 for now
    // encoded_vector.push_back(calculateParityC2(sliding_window));


    // In the second iteration of the window, we start with  the most significant bit from the code in the second register
    // of the sliding window, and the bit after the most significant bit in the third register, with the first still being empty
    // this is what it would look like building off the previous:
    // register is now [0,1,0] (just shifting the register over now, but notice the first register is still empty since weve only
    // processed two bits thus far)
    sliding_window[0] = 0;
    sliding_window[1] = raw_code_as_vector[0];
    sliding_window[2] = raw_code_as_vector[1];

    // add the result of the parity calculation from C1 to the encoded vector
    encoded_vector.push_back(calculateParityC1(sliding_window));
    
    // encoded_vector.push_back(calculateParityC2(sliding_window));

    // Follow this same procedure till every bit is processed
    for (int i = 2; i < raw_code_as_vector.size(); i++) {
        sliding_window[0] = raw_code_as_vector[i-2];
        sliding_window[1] = raw_code_as_vector[i+1-2];
        sliding_window[2] = raw_code_as_vector[i+2-2];
        encoded_vector.push_back(calculateParityC1(sliding_window));
        // encoded_vector.push_back(calculateParityC2(sliding_window));
        // encoded_vector.push_back(calculateParityC3(sliding_window));
    }

    // so essentially, if our original code was: 1010
    // Register @ t=0 -> [0,0,1] -> C1 = 1 -> Encoded vector: <1>
    // Register @ t=1 -> [0,1,0] -> C1 = 1 -> Encoded vector: <1,1>
    // Register @ t=3 -> [1,0,1] -> C1 = 0 -> Encoded vector: <1,1,0>
    // Register @ t=3 -> [0,1,0] -> C1 = 1 -> Encoded vector: <1,1,0,1> -> This is our encoding

    uint32_t encoded_code = 0;

    // Convert the binary vector to a uint32_t value
    for (size_t i = 0; i < encoded_vector.size(); ++i) {  
        encoded_code = (encoded_code << 1) | encoded_vector[i];  // Shift result and add the current bit
    }

    return encoded_code;
}



// IN PROGRESS
uint16_t viterbiDecode(uint32_t encoded_code) {
    std::vector<uint32_t> raw_code_as_vector(32, 0);

    std::string code_as_string = std::bitset<32>(encoded_code).to_string();

    for (int i = 0; i < code_as_string.length(); i++) {
        raw_code_as_vector[i] = code_as_string[i] - '0';
    }

    std::vector<uint32_t> decoded_vector;
    decoded_vector.reserve(1000);
    std::vector<uint32_t> sliding_window(3, 0);

    //calculate first bit in decoded message
    sliding_window[0] = 0;
    sliding_window[1] = 0;  
    sliding_window[2] = raw_code_as_vector[0];
    decoded_vector.push_back(calculateParityC1(sliding_window));


    //calculate second bit in decoded message
    sliding_window[0] = 0;
    sliding_window[1] = raw_code_as_vector[0]; 
    sliding_window[2] = raw_code_as_vector[1];
    decoded_vector.push_back(calculateParityC1(sliding_window));

}



uint32_t addNoise(uint32_t code, float prob_of_error) {

    // This will store the encoded code as a vector of bits
    std::vector<uint32_t> raw_code_as_vector(32, 0);

    // Turn the encoded code into a string
    std::string code_as_string = std::bitset<32>(code).to_string();
    // "0000000010101010"

    
    // For every char bit in the string code
    for (int i = 0; i < code_as_string.length(); i++) {
        // turn the char back to an int
        int bit = code_as_string[i] - '0';
        // calculate a random number between 0 and 1 and if its less than the p value passed in, flip the bit
        if ((float) rand()/RAND_MAX < prob_of_error) {
            switch (bit) {
                case 0:
                    raw_code_as_vector[i] = 1;
                    break;
                case 1:
                    //cout << "Flipping 1 to 0" << endl;
                    raw_code_as_vector[i] = 0;
                    //cout << std::bitset<64>(raw_code_as_vector[i]).to_string() << endl;
                    break;
            }
        }
        // if the random number generated isn't less than p, dont flip the bit
        else {
            raw_code_as_vector[i] = bit;
        }
        
    }

    uint32_t noisy_code = 0;

    // Convert the binary vector to a uint32_t value
    for (size_t i = 0; i < raw_code_as_vector.size(); ++i) {
        noisy_code = (noisy_code << 1) | raw_code_as_vector[i];  // Shift result and add the current bit
    }

    return noisy_code;

}


int main() {

    // used to get the random number between 0 and 1 when determining when to flip bits
    srand( (unsigned)time( NULL ) );

    // the code that we want to encode
    uint16_t code = 0b1010;

    // the probability of a single bit flipping after encoding the original code
    float p = 0.1;


    

    cout << "Original Code -> " << std::bitset<16>(code).to_string() << endl;
    uint32_t encoded = encode(code);
    cout << "Encoded Code -> " << std::bitset<16>(encoded).to_string() << endl;
    uint32_t noisy_encoded = addNoise(encoded, p);
    cout << "Code After Noise -> " << std::bitset<16>(noisy_encoded).to_string() << endl;

    return 0;

}