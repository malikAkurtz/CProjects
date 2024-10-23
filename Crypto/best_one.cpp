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
using namespace std;

struct vNode {
    long long cumHammingDistance;
    int inputArrivalBit;
    int state;

    bool operator<(const vNode& other) const {
        return state < other.state;
    }
};

int calculateHammingDistance(string code1, string code2);
string generateOutput(string shiftregister, vector<vector<int>> genPolynomials);
string addNoise(string code, float prob_of_error);
void printTrellisStates(const vector<vector<vNode>> &trellis);
string getOriginalCode(const vector<vector<vNode>> &trellis);
void removeDuplicatePaths(vector<vector<vNode>> &trellis, int t);
vector<string> generateStates(int k);
string calculatePotentialInput(string curState, int zero_or_one);
string stringToBinary(string& message);
string binaryToString(string& binary);


int timeSteps = 0;
vector<vector<vNode>> trellis;

// Encode Method
string encode(string code, int k, vector<vector<int>> genPolynomials) { // k is the constraint length i.e length of the shift register we want to use
    string encodedVector = "";
    string sliding_window = "";
    // Follow this same procedure till every bit is processed
    for (int i = 0; i < code.size(); i++) {
        sliding_window = "";
        sliding_window += string(max((k-i-1), 0), '0'); // the registers that are still empty
        for (int j = 0; j < k - (max((k-i-1), 0));j++) {
            if (i >= k) {
                sliding_window += code[j-(k-i-1)];
            }
            else {
                sliding_window += code[j];
            }
            
        }
        encodedVector += generateOutput(sliding_window, genPolynomials);
        timeSteps += 1;
    }
    return encodedVector;
}


/*
index 0 will represent state (0,0)
index 1 will represent state (0,1)
index 2 will represent state (1,0)
index 3 will represent state (1,1)
*/


// IN PROGRESS
string viterbiDecode(string noisy_encoded_code, int k, vector<string> states, vector<vector<int>> genPolynomials) {

    string originalCode = "";
    
    int outputBits = genPolynomials.size();

    trellis.resize(timeSteps + 1);
    
    //initialize the only node at t = 0 (0,0)

    for (int t = 0; t < timeSteps+1; t++) {
        for (int s = 0; s < states.size(); s++) {
            vNode defaultNode;

            defaultNode.state = s;
            defaultNode.inputArrivalBit = -1;
            defaultNode.cumHammingDistance = INT_MAX;
            trellis[t].push_back(defaultNode);          
            
        }
    }

    trellis[0][0].cumHammingDistance = 0; // assuming out register will start at an intial state of State 0

    //printTrellisStates(trellis);



    for (int t = 1; t <= timeSteps; t++) {
        string observedInput = noisy_encoded_code.substr(outputBits*(t-1), outputBits);
        for (int s = 0; s < states.size(); s++) {
            // cout << "------------------------------------------------------------------------" << endl;
            // cout << "State is: " << s << endl;
            int transitionBit;
            if (s % 2 == 0) {
                // could only have gotten to this state s with a transition bit of 0
                transitionBit = 0;
                trellis[t][s].inputArrivalBit = transitionBit;
            }
            else {
                transitionBit = 1;
                trellis[t][s].inputArrivalBit = transitionBit;
            }

            // for each state we need to see what happens if the input is a 0 or a 1
            int firstPrevState = (std::stoi(states[s], nullptr, 2) >> 1);
            if (trellis[t-1][firstPrevState].cumHammingDistance != INT_MAX) {
                // cout << "Previous state for first input is: " << to_string(firstPrevState) << endl;
                string firstPotentialInput = calculatePotentialInput(states[firstPrevState], transitionBit);
                string firstExpected = generateOutput(firstPotentialInput, genPolynomials);
                // cout << "Our expected is:    " << firstExpected << endl;
                // cout << "Our observation is: " << observedInput << endl;
                int firstHammingDistance = trellis[t-1][firstPrevState].cumHammingDistance + calculateHammingDistance(observedInput, firstExpected);
                // cout << "So the cumulative hamming distance would be: " << firstHammingDistance << endl;
                if (firstHammingDistance < trellis[t][s].cumHammingDistance) {
                    trellis[t][s].cumHammingDistance = firstHammingDistance;
                    trellis[t][s].inputArrivalBit = transitionBit;
                }
            }
            

            int secondPrevState = ((std::stoi(states[s], nullptr, 2) >> 1) | (1 << (k-2)));
            if (trellis[t-1][secondPrevState].cumHammingDistance != INT_MAX) {
                // cout << "Previous state for second input is: " << to_string(secondPrevState) << endl;
                string secondPotentialInput = calculatePotentialInput(states[secondPrevState], transitionBit);
                string secondExpected = generateOutput(secondPotentialInput, genPolynomials);
                // cout << "Our expected is:    " << secondExpected << endl;
                // cout << "Our observation is: " << observedInput << endl;
                int secondHammingDistance = trellis[t-1][secondPrevState].cumHammingDistance + calculateHammingDistance(observedInput, secondExpected);
                // cout << "So the cumulative hamming distance would be: " << secondHammingDistance << endl;
                if (secondHammingDistance < trellis[t][s].cumHammingDistance) {
                    trellis[t][s].cumHammingDistance = secondHammingDistance;
                    trellis[t][s].inputArrivalBit = transitionBit;
                }
            }
        // cout << "------------------------------------------------------------------------" << endl;
        }
    }

    // printTrellisStates(trellis);

    return getOriginalCode(trellis);
}



int main() {
    float p;
    int lowerKlimit;
    int upperKlimit;
    // degree of any gen polynomial should always be less than or equal to k-1
    vector<string> possibleStates;

    // used to get the random number between 0 and 1 when determining when to flip bits
    unsigned int seed = 12345;  // Replace 12345 with any specific seed you want
    srand(seed);
    // srand( (unsigned)time( NULL ) );

    // the code that we want to encode
    string message;
    getline(cin, message);
    string code = stringToBinary(message);

    // string code = "1010";

    // string code = "1010";
    
    // the probability of ax single bit flipping after encoding the original code
    p = 0.1; // LOL
    p = 0.01; // Poor channel conditions, severe interference, or far-from-optimal signal quality.
    // p = 0.001; // Moderate noise, common in low-quality wireless connections or basic wired links with interference.
    p = 0.1;
    int numIterations = 50;

    if (code.length() < 10) {
        lowerKlimit = 2;
        upperKlimit = 3;
    }
    else if (code.length() < 50) {
        lowerKlimit = 3;
        upperKlimit = 5;
    }
    else if (code.length() < 100) {
        lowerKlimit = 5;
        upperKlimit = 7;
    }
    else {
        lowerKlimit = 7;
        upperKlimit = 8; // going above 8 will destroy your computer :)
    }


    // lowerKlimit = 8;
    // upperKlimit = 8;
    map<int, float> k_averages;  // Adjusted to store averages for all possible_k values

    // Loop over possible values of k
    for (int possible_k = lowerKlimit; possible_k <= upperKlimit; possible_k++) {
        float average_success = 0.0;
        int total_successes = 0;

        cout << "===============================================================" << endl;
        cout << "Processing for k = " << possible_k << " (" << numIterations << " iterations)" << endl;
        cout << "===============================================================" << endl;

        // Perform multiple iterations for each k value
        for (int i = 0; i < numIterations; i++) {
            // Reset the environment for each iteration
            vector<vector<int>> generatorPolynomials(10); // hardcoding generator polynomials i.e 3 output bits that will be autofilled later
            possibleStates = generateStates(possible_k);
            timeSteps = 0;
            trellis.clear();
            
            // Default generator polynomial for every iteration will just be the polynomial 1 + x^1 + ... + x^k-1
            for (int i = 0; i < generatorPolynomials.size(); i++) {
                generatorPolynomials[i].clear();
                for (int j = 0; j < possible_k; j++) {
                    generatorPolynomials[i].push_back(1);
                }
            }



            // Encoding, adding noise, and decoding
            string encoded = encode(code, possible_k, generatorPolynomials);
            string noisy_encoded = addNoise(encoded, p);
            string originalCode = viterbiDecode(noisy_encoded, possible_k, possibleStates, generatorPolynomials);
            string originalMessage = binaryToString(originalCode);
            // string originalMessage = originalCode;

            // Displaying results for each iteration
            cout << "---------------------------------------------------------------" << endl;
            cout << "Iteration #" << i + 1 << ":" << endl;
            cout << "K = " << possible_k << endl;
            cout << "Generator Polynomials: [ ";
            // for every generator polynomial
            for (int i = 0; i < generatorPolynomials.size(); i++) {
                // print the opening bracket for each polynomial
                cout << "[ ";
                
                // for every term in the polynomial
                for (int j = 0; j < generatorPolynomials[i].size(); j++) {
                    // print the term
                    cout << generatorPolynomials[i][j];
                    
                    // if this is not the last term in the polynomial, print a comma and space
                    if (j != generatorPolynomials[i].size() - 1) {
                        cout << ", ";
                    }
                }
                
                // close the bracket for the current polynomial
                cout << " ]";
            }

            // print a newline after all polynomials have been printed
            cout << endl;
            cout << "Original Message : " << message << endl;
            cout << "Original Code  : " << code << endl;
            cout << "Encoded Code   : " << encoded << endl;
            cout << "Noisy Code     : " << noisy_encoded << endl;
            cout << "Noise Added?   : " << (noisy_encoded == encoded ? "No" : "Yes") << endl;
            cout << "Number of bits flipped: " << calculateHammingDistance(encoded,noisy_encoded) << endl;
            cout << "Decoded Code   : " << originalCode << endl;
            cout << "Decoded Message: " << originalMessage << endl;

            bool success = (code == originalCode);
            if (success) {
                cout << "Result         : SUCCESS" << endl;
                total_successes += 1;
            } else {
                cout << "Result         : FAIL" << endl;
            }
            cout << "---------------------------------------------------------------" << endl;

            average_success += success;
        }

        // Calculate and display the success rate for this k value
        float success_rate = (average_success / numIterations);
        k_averages[possible_k] = success_rate;

        cout << "===============================================================" << endl;
        cout << "Summary for k = " << possible_k << ":" << endl;
        cout << "Total Successes: " << total_successes << " / " << numIterations << endl;
        cout << "Average Success: " << success_rate * 100 << "% success rate" << endl;
        cout << "===============================================================" << endl << endl;
    }

    // Final summary of all k values
    cout << "===================== Overall Results =====================" << endl;
    cout << "Noise was: " << p << endl;
    cout << "Message length was: " << code.length() << endl;
    for (int i = lowerKlimit; i <= upperKlimit; i++) {
        cout << "For k = " << i << " -> Average Success = " << k_averages[i] * 100 << "%" << endl;
    }
    cout << "===========================================================" << endl;

    return 0;
}


int calculateHammingDistance(string code1, string code2) {
    if (code1.length() != code2.length()) {
        return -1;
    }

    int hammingDistance = 0;
    for (int i = 0; i < code1.length(); i++) {
        if (code1[i] != code2[i]) {
            hammingDistance++;
        }
    }

    return hammingDistance;
}



string generateOutput(string shiftregister, vector<vector<int>> genPolynomials) {

    string parityBits = "";


    string registerSubstring;
    int registerParity=0;

    // (0,0,0)


    for (vector<int> polynomial : genPolynomials) {
        registerParity = 0;

        for (int i = 0; i < polynomial.size(); i++) {
            if (polynomial[i] == 1) {
                registerParity ^= shiftregister[i]-'0';
            }
        }
        parityBits += to_string(registerParity);
    }

    return parityBits; 
}

string addNoise(string code, float prob_of_error) {

    string noisyEncoded = "";
    
    // For every char bit in the string code
    for (int i = 0; i < code.length(); i++) {
        // turn the char back to an int
        int bit = code[i] - '0';
        // calculate a random number between 0 and 1 and if its less than the p value passed in, flip the bit
        if ((float) rand()/RAND_MAX < prob_of_error) {
            switch (bit) {
                case 0:
                    noisyEncoded += to_string(1);
                    break;
                case 1:
                    //cout << "Flipping 1 to 0" << endl;
                    noisyEncoded += to_string(0);
                    //cout << std::bitset<64>(raw_code_as_vector[i]).to_string() << endl;
                    break;
            }
        }
        // if the random number generated isn't less than p, dont flip the bit
        else {
            noisyEncoded += code[i];
        }
        
    }
    return noisyEncoded;
}

void printTrellisStates(const vector<vector<vNode>> &trellis) {
    for (int i = 0; i < trellis.size(); i++) {
        cout << "For t = " << i << endl;
        for (int j = 0; j < trellis[i].size(); j++) {
            cout << "Node State: " << trellis[i][j].state 
                << " Cumulative Hamming Distance: " << trellis[i][j].cumHammingDistance << endl;
        }
    }
}

string getOriginalCode(const vector<vector<vNode>> &trellis) {
    string originalCode = "";
    for (int t = timeSteps;t > 0; t--) {
        //cout << "t is: " << t << endl;
        vNode bestPathNode = trellis[t][0];
        for (int i = 1; i < trellis[t].size();i++) {
            if (trellis[t][i].cumHammingDistance < bestPathNode.cumHammingDistance) {
                bestPathNode = trellis[t][i];
            }
        }
        originalCode += to_string(bestPathNode.inputArrivalBit);
    }

    reverse(originalCode.begin(), originalCode.end());

    return originalCode;
}



vector<string> generateStates(int k) {
    vector<string> statesVector = {};

    string curState;
    //Ex. k = 4
    // this loop will run 8 times to generate all 8 possible states
    // i goes from 0-7
    // for i = 0
    for (int i = 0; i < pow(2, k-1); i++) {
        curState = "";
        // bit = 4 - 2 = 2
        // so bit goes from 2-0
        for (int bit = k - 2; bit >= 0; bit--) {
            // i = 0
            // bit = 2
            // 0 >> 2 = 0, & 1 = 0, 0 gets appended
            // bit = 1
            // 0 >> 1 = 0, & 1 = 0, 0 gets appended
            // bit = 0
            // 0 >> 0 = 0, & 1 = 0, 0 gets appended
             curState += to_string(((i >> bit) & 1));
        }
        statesVector.push_back(curState);
    }

    return statesVector;
}

string calculatePotentialInput(string curState, int next_input) {
    string input = curState;
    input += to_string(next_input);
    return input;
}

string stringToBinary(string& message) {
    string binaryString = "";
    for (char c : message) {
        binaryString += std::bitset<8>(c).to_string();
    }
    return binaryString;
}

string binaryToString(string& binary) {
    string stringBinary = "";

    for (int i = 0; i < binary.length(); i+=8) {
        bitset<8> charBits(binary.substr(i,8));
        stringBinary += char(charBits.to_ulong());
    }

    return stringBinary;
}