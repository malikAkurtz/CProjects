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
#include <fstream>

using namespace std;

struct vNode {
    long long cumHammingDistance;
    int inputArrivalBit;
    int state;

    bool operator<(const vNode& other) const {
        return state < other.state;
    }
};

int calculateHammingDistance(string& code1, string& code2);
string generateOutput(string& shiftregister, vector<unsigned int>& genPolynomials);
string addNoise(string& code, float prob_of_error);
void printTrellisStates(const vector<vector<vNode>> &trellis);
string getOriginalCode(const vector<vector<vNode>> &trellis);
void removeDuplicatePaths(vector<vector<vNode>> &trellis, int t);
vector<string> generateStates(int k);
string calculatePotentialInput(string& curState, int zero_or_one);
string stringToBinary(string& message);
string binaryToString(string& binary);
void exportData(map<int, float>& k_data_points, string& filename);


int timeSteps = 0;
vector<vector<vNode>> trellis;

// // Encode Method
string encode(string code, int k, vector<unsigned int> genPolynomials) { // k is the constraint length i.e length of the shift register we want to use
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


// // IN PROGRESS
string viterbiDecode(string noisy_encoded_code, int k, vector<string> states, vector<unsigned int> genPolynomials) {

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
    string exportFile = "results.csv";
    vector<unsigned int> generatorPolynomials;

    // degree of any gen polynomial should always be less than or equal to k-1
    vector<string> possibleStates;

    // used to get the random number between 0 and 1 when determining when to flip bits
    // unsigned int seed = 12345;  // Replace 12345 with any specific seed you want
    // srand(seed);
    srand( (unsigned)time( NULL ) );

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
    p = 0.05;
    int numIterations = 100;


    // if (code.length() < 50) {
    //     lowerKlimit = 4;
    //     upperKlimit = 5;
    // }
    // else if (code.length() < 100) {
    //     lowerKlimit = 5;
    //     upperKlimit = 7;
    // }
    // else {
    //     lowerKlimit = 7;
    //     upperKlimit = 8; // going above 8 will destroy your computer :)
    //}


    lowerKlimit = 4;
    upperKlimit = 12;
    
    map<int, float> k_averages;  // Adjusted to store averages for all possible_k values

    // Loop over possible values of k
    for (int possible_k = lowerKlimit; possible_k <= upperKlimit; possible_k++) {
        generatorPolynomials.clear();
        if (possible_k == 4) {
            generatorPolynomials.push_back(0x5);
            generatorPolynomials.push_back(0x5);
            generatorPolynomials.push_back(0x5);
            generatorPolynomials.push_back(0x5);
            generatorPolynomials.push_back(0x5);
        }
        else if (possible_k == 5) {
            generatorPolynomials.push_back(0x9);
            generatorPolynomials.push_back(0x9);
            generatorPolynomials.push_back(0x9);
            generatorPolynomials.push_back(0x9);
            generatorPolynomials.push_back(0x9);
        }
        else if (possible_k == 6) {
            generatorPolynomials.push_back(0x15);
            generatorPolynomials.push_back(0x15);
            generatorPolynomials.push_back(0x15);
            generatorPolynomials.push_back(0x15);
            generatorPolynomials.push_back(0x15);
        }
        else if (possible_k == 7) {
            generatorPolynomials.push_back(0x23);
            generatorPolynomials.push_back(0x23);
            generatorPolynomials.push_back(0x23);
            generatorPolynomials.push_back(0x23);
            generatorPolynomials.push_back(0x23);
        }
        else if (possible_k == 8) {
            generatorPolynomials.push_back(0x72);
            generatorPolynomials.push_back(0x72);
            generatorPolynomials.push_back(0x72);
            generatorPolynomials.push_back(0x72);
            generatorPolynomials.push_back(0x72);
        }
        else if (possible_k == 9) {
            generatorPolynomials.push_back(0x9b);
            generatorPolynomials.push_back(0x9b);
            generatorPolynomials.push_back(0x9b);
            generatorPolynomials.push_back(0x9b);
            generatorPolynomials.push_back(0x9b);
        }
        else if (possible_k == 10) {
            generatorPolynomials.push_back(0x13c);
            generatorPolynomials.push_back(0x13c);
            generatorPolynomials.push_back(0x13c);
            generatorPolynomials.push_back(0x13c);
            generatorPolynomials.push_back(0x13c);
        }
        else if (possible_k == 11) {
            generatorPolynomials.push_back(0x29b);
            generatorPolynomials.push_back(0x29b);
            generatorPolynomials.push_back(0x29b);
            generatorPolynomials.push_back(0x29b);
            generatorPolynomials.push_back(0x29b);
        }
        else if (possible_k == 12) {
            generatorPolynomials.push_back(0x4f5);
            generatorPolynomials.push_back(0x4f5);
            generatorPolynomials.push_back(0x4f5);
            generatorPolynomials.push_back(0x4f5);
            generatorPolynomials.push_back(0x4f5);
        }
        float average_success = 0.0;
        int total_successes = 0;

        possibleStates = generateStates(possible_k);

        cout << "===============================================================" << endl;
        cout << "Processing for k = " << possible_k << " (" << numIterations << " iterations)" << endl;
        cout << "===============================================================" << endl;

        // Perform multiple iterations for each k value
        for (int i = 0; i < numIterations; i++) {
            // Reset the environment for each iteration
            timeSteps = 0;
            trellis.clear();
 
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

            // print a newline after all polynomials have been printed
            cout << endl;
            cout << "Original Message : " << message << endl;
            cout << "Original Code  : " << code << endl;
            cout << "Encoded Code   : " << encoded << endl;
            cout << "Noisy Code     : " << noisy_encoded << endl;
            cout << "Noise Added?   : " << (noisy_encoded == encoded ? "No" : "Yes") << endl;
            cout << "# bits flipped: " << calculateHammingDistance(encoded,noisy_encoded) << endl;
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
    cout << "Original message was: " << message << endl;
    cout << "Message length was: " << code.length() << endl;
    // cout << "Output Bits per input: " << outputBits << endl;
    for (int i = lowerKlimit; i <= upperKlimit; i++) {
        cout << "For k = " << i << " -> Average Success = " << k_averages[i] * 100 << "%" << endl;
    }
    cout << "===========================================================" << endl;

    exportData(k_averages, exportFile);
    return 0;
}



int calculateHammingDistance(string& code1, string& code2) {
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

string generateOutput(string& shiftregister, vector<unsigned int>& genPolynomials) {
    int k = shiftregister.length();

    string parityBits = "";


    int registerParity=0;

    for (unsigned int genPoly : genPolynomials) {
        genPoly = genPoly << 1 | 1; // just need to add another 1 at the end
        registerParity = 0;
        // cout << "Current genPoly: " << bitset<8>(genPoly) << endl; // Print binary of genPoly for clarity
        // cout << "Shift Register: " << shiftregister << endl;
        // gen poly = 1011
        // k = 4
        //j = 0
        for (int j = 0; j <k; j++) {
            if (((genPoly >> j) & 1) == 1) {
                // cout << "  - XOR with shiftregister[" << k - 1 - j << "] (" << shiftregister[k - 1 - j] << ")" << endl;
                registerParity ^= shiftregister[k - 1 - j] -'0';
            } 
            else {}
        }
        // cout << "Intermediate registerParity: " << registerParity << endl;
        parityBits += to_string(registerParity);
    }
// cout << "Final Output is: " << parityBits << endl;
    return parityBits; 

}

string addNoise(string& code, float prob_of_error) {

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

string calculatePotentialInput(string& curState, int next_input) {
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

void exportData(map<int, float>& k_data_points, string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "K, Success Rate\n";
        for (auto& entry : k_data_points) {
            file << entry.first << "," << entry.second * 100 << "\n";
        }
        file.close();
    }

}
