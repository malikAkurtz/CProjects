#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <bitset>
#include <cstdlib>
#include <time.h>
#include <cmath>

using namespace std;

struct vNode {
    int cumHammingDistance=0;
    int prevNodeState=-1;
    int inputArrivalBit=-1;
    int state;

    bool operator<(const vNode& other) const {
        return state < other.state;
    }
};

int calculateHammingDistance(string code1, string code2);
string calculateParities(string shiftregister);
string addNoise(string code, float prob_of_error);
void printTrellisStates(const vector<vector<vNode>> &trellis);
string getOriginalCode(const vector<vector<vNode>> &trellis);
void removeDuplicatePaths(vector<vector<vNode>> &trellis, int t);
void generateStates(vector<string>& statesVector, int k);
string calculatePotentialInput(string curState, int zero_or_one);

enum State {
    STATE_0,  // 0  -> representing (0,0)
    STATE_1, // 1 -> representing (0,1)
    STATE_2,  // 2 -> representing (1,0)
    STATE_3 // 3 -> representing (1,1)
};

int timeSteps = 0;
vector<string> states = {};


// Encode Method
string encode(string code, int k) { // k is the constraint length i.e length of the shift register we want to use
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
        encodedVector += calculateParities(sliding_window);
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
string viterbiDecode(string noisy_encoded_code, int k) {

    generateStates(states, k);

    string originalCode = "";
    

    vector<vector<vNode>> trellis(timeSteps+1);
    vNode initialNode;
    initialNode.state = 0;
    trellis[0].push_back(initialNode);
    //initialize the only node at t = 0 (0,0)


    string input0;
    string input1;
    string expectedOutput0;
    string expectedOutput1;
    vector<vNode> bestPathsAt_t;


    // index a node with trellis[t][s] which will return the node at time t with state s
    // now for every timestep
    for (int t = 1; t < (timeSteps+1); t++) {
        // save the input that corresponding to the bit that is read from the noisy message
        string observedInput = noisy_encoded_code.substr(k*(t-1), k);
        //cout << "Observed Input at t = " << t<< " is : " << observedInput << endl;
        // for every state
        for (int s = 0; s < states.size(); s++) { // THIS IS HARDCODED TO WORK FOR 4 STATES
        //******** DONT FORGET TO SKIP OVER T = 1 FOR S IS 0 ********************/
            input0 = "";
            input1 = "";
            expectedOutput0 = "";
            expectedOutput1 = "";
            vNode firstNode, secondNode, thirdNode, fourthNode, fifthNode, sixthNode, seventhNode, eigthNode;
            if (t == 1) {
                // case for input 0
                    //input0 = "000";
                    input0 = calculatePotentialInput(states[s], 0);
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    firstNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    firstNode.inputArrivalBit = 0;
                    firstNode.prevNodeState = s;
                    firstNode.state = 0;
                    trellis[t].push_back(firstNode);

                    // case for input 1;
                    input1 = calculatePotentialInput(states[s], 1);
                    expectedOutput1 = calculateParities(input1);

                    // cout << "Expected for input 1: " << expectedOutput1 << endl;
                    // cout << "Observed input is: " << observedInput << endl;
                    // cout << "Hamming distance is: " << calculateHammingDistance(expectedOutput1, observedInput) << endl;

                    secondNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    secondNode.inputArrivalBit = 1;
                    secondNode.prevNodeState = s;
                    secondNode.state = 1;
                    trellis[t].push_back(secondNode);
                    break;
            }
            else if (t == 2) {
                switch (s) {
                case 0: // state (0,0)
                    // case for input 0
                    input0 = calculatePotentialInput(states[s], 0);
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    firstNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    firstNode.inputArrivalBit = 0;
                    firstNode.prevNodeState = s;
                    firstNode.state = 0;
                    trellis[t].push_back(firstNode);

                    // case for input 1;
                    input1 = calculatePotentialInput(states[s], 1);
                    expectedOutput1 = calculateParities(input1);


                    // cout << "Expected for input 1: " << expectedOutput1 << endl;
                    // cout << "Observed input is: " << observedInput << endl;
                    // cout << "Hamming distance is: " << calculateHammingDistance(expectedOutput1, observedInput) << endl;

                    secondNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    secondNode.inputArrivalBit = 1;
                    secondNode.prevNodeState = s;
                    secondNode.state = 1;
                    trellis[t].push_back(secondNode);
                    break;
                case 1: // state (0,1)
                    // case for input 0
                    input0 = calculatePotentialInput(states[s], 0);
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    thirdNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    thirdNode.inputArrivalBit = 0;
                    thirdNode.prevNodeState = s;
                    thirdNode.state = 2;
                    trellis[t].push_back(thirdNode);

                    // case for input 1;
                    input1 = calculatePotentialInput(states[s], 1);
                    expectedOutput1 = calculateParities(input1);


                    fourthNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    fourthNode.inputArrivalBit = 1;
                    fourthNode.prevNodeState = s;
                    fourthNode.state = 3;
                                    
                    trellis[t].push_back(fourthNode);
                    break;

                }
            }
            else {
                switch (s) {
                case 0: // state (0,0)
                    // case for input 0
                    input0 = calculatePotentialInput(states[s], 0);
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    firstNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    firstNode.inputArrivalBit = 0;
                    firstNode.prevNodeState = s;
                    firstNode.state = 0;
                    trellis[t].push_back(firstNode);

                    // case for input 1;
                    input1 = calculatePotentialInput(states[s], 1);
                    expectedOutput1 = calculateParities(input1);


                    secondNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    secondNode.inputArrivalBit = 1;
                    secondNode.prevNodeState = s;
                    secondNode.state = 1;
                    trellis[t].push_back(secondNode);
                    
                    break;
                case 1: // state (0,1)
                    // case for input 0
                    input0 = calculatePotentialInput(states[s], 0);
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    thirdNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    thirdNode.inputArrivalBit = 0;
                    thirdNode.prevNodeState = s;
                    thirdNode.state = 2;
                    trellis[t].push_back(thirdNode);

                    // case for input 1;
                    input1 = calculatePotentialInput(states[s], 1);
                    expectedOutput1 = calculateParities(input1);


                    fourthNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    fourthNode.inputArrivalBit = 1;
                    fourthNode.prevNodeState = s;
                    fourthNode.state = 3;
                                    
                    trellis[t].push_back(fourthNode);


                    break;
                case 2: // state (1,0)
                    // case for input 0
                    input0 = calculatePotentialInput(states[s], 0);
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    fifthNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    fifthNode.inputArrivalBit = 0;
                    fifthNode.prevNodeState = s;
                    fifthNode.state = 0;
                    trellis[t].push_back(fifthNode);

                    // case for input 1;
                    input1 = calculatePotentialInput(states[s], 1);
                    expectedOutput1 = calculateParities(input1);


                    sixthNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    sixthNode.inputArrivalBit = 1;
                    sixthNode.prevNodeState = s;
                    sixthNode.state = 1;
                    trellis[t].push_back(sixthNode);


                    break;
                case 3: // state (1,1)
                    // case for input 0
                    input0 = calculatePotentialInput(states[s], 0);
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    seventhNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    seventhNode.inputArrivalBit = 0;
                    seventhNode.prevNodeState = s;
                    seventhNode.state = 2;
                    trellis[t].push_back(seventhNode);

                    // case for input 1;
                    input1 = calculatePotentialInput(states[s], 1);
                    expectedOutput1 = calculateParities(input1);


                    eigthNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    eigthNode.inputArrivalBit = 1;
                    eigthNode.prevNodeState = s;
                    eigthNode.state = 3;
                    trellis[t].push_back(eigthNode);

                    break;

                }
            }
        }

        //*** PERFORM A CHECK AT THE END OF EACH t AND GET RID OF DUPLICATE NOTES, GET RID OF THE ONE WITH THE HIGHER HAMMING DISTANCE
       if (t > 2) {
            removeDuplicatePaths(trellis, t);
       }
    }
    
    printTrellisStates(trellis);

    return getOriginalCode(trellis);
}



int main() {

    // used to get the random number between 0 and 1 when determining when to flip bits
    srand( (unsigned)time( NULL ) );

    // the code that we want to encode
    string code = "1010";
    int k = 3;


    // the probability of a single bit flipping after encoding the original code
    float p = 0.0;



    cout << "Original Code      -> " << code << endl;
    string encoded = encode(code, k);
    cout << "Encoded Code       -> " << encoded << endl;
    string noisy_encoded = addNoise(encoded, p);
    string s = ""; //debugging
    s += "1011";
    s += "1101";
    s += "0110";
    cout << "Code After Noise   -> " << s << endl;
    string originalCode = viterbiDecode(s, k);
    cout << "The original code is: " << originalCode << endl;



    for (string state : states) {
        cout << state << endl;
    }
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

string calculateParities(string shiftregister) {
    string parityBits = "";


    string registerSubstring;
    int registerParity=0;

    // (0,0,0)


    for (int i = shiftregister.length(); i > 0; i--) {
        registerSubstring = shiftregister.substr(0, i);
        registerParity=0;
        for (int j = 0; j < registerSubstring.length(); j++) {
            registerParity = (registerParity + (registerSubstring[j]-'0')) % 2;
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

void removeDuplicatePaths(vector<vector<vNode>> &trellis, int t) {
    vector<vNode> bestPathsAt_t;
    for (int i = 0; i < trellis[t].size()-1; i++) {
                sort(trellis[t].begin(), trellis[t].end()); 
                if (trellis[t][i].state == trellis[t][i+1].state) {
                    if (trellis[t][i].cumHammingDistance <= trellis[t][i+1].cumHammingDistance) {
                        bestPathsAt_t.push_back(trellis[t][i]);
                    }
                    else {
                        bestPathsAt_t.push_back(trellis[t][i+1]);
                    }
                }
            }

            trellis[t] = bestPathsAt_t;
}

void generateStates(vector<string>& statesVector, int k) {
    string curState;
    for (int i = 0; i < pow(2, k-1); i++) {
        curState = "";
        // Print each binary number of length `n`
        for (int bit = k - 2; bit >= 0; bit--) {
             curState += to_string(((i >> bit) & 1));
        }
        statesVector.push_back(curState);
    }
}

string calculatePotentialInput(string curState, int zero_or_one) {
    string input = curState;
    input += to_string(zero_or_one);
    return input;
}