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

enum State {
    STATE_0,  // 0  -> representing (0,0)
    STATE_1, // 1 -> representing (0,1)
    STATE_2,  // 2 -> representing (1,0)
    STATE_3 // 3 -> representing (1,1)
};

int timeSteps = 0;


// Encode Method
// Takes in a 16 bit code and return its encoded version after applying function C1, and C2 over the rolling window
string encode(string code, int k) { // k is the constraint length i.e length of the shift register we want to use

    string encodedVector = "";
    string sliding_window = "";

    // Initializing the slides window that we will use for our C1, C2, C3 parity calculations

    for (int i =0; i < k; i++) {
        sliding_window += "0";
    }

    
    // This is where our sliding window will start from the left of the code, moving to the right, and calculating
    // the parities using C1, C2, C3 and outputting the results of this calculations to an encoded version of the code

    // In the first iteration of the window, we start with only the most significant bit from the code in the right most register
    // of the sliding window, with the first two registers initialized to 0
    // this is what it would look like:
    // code -> 1010
    // register starts at [0,0,1] (since 1 is the most significant bit and registers 1 and 2 are still empty)

    // *** FOR C1 FUNCTION ***
    sliding_window[0] = 0;
    sliding_window[1] = 0;
    sliding_window[2] = code[0];

    // add the result of the parity calculation from C1, C2, C3 to the encoded vector
    encodedVector += calculateParities(sliding_window);

    //cout << "Time Steps was: " << timeSteps << endl;
    timeSteps += 1;
    //cout << "Time Steps is now: " << timeSteps << endl;



    // In the second iteration of the window, we start with  the most significant bit from the code in the second register
    // of the sliding window, and the bit after the most significant bit in the third register, with the first still being empty
    // this is what it would look like building off the previous:
    // register is now [0,1,0] (just shifting the register over now, but notice the first register is still empty since weve only
    // processed two bits thus far)
    sliding_window[0] = 0;
    sliding_window[1] = code[0];
    sliding_window[2] = code[1];

    // add the result of the parity calculation from C1 to the encoded vector
    encodedVector += calculateParities(sliding_window);

    //cout << "Time Steps was: " << timeSteps << endl;
    timeSteps += 1;
    //cout << "Time Steps is now: " << timeSteps << endl;
    
    // encoded_vector.push_back(calculateParityC2(sliding_window));

    // Follow this same procedure till every bit is processed
    for (int i = 2; i < code.size(); i++) {
        sliding_window[0] = code[i-2];
        sliding_window[1] = code[i+1-2];
        sliding_window[2] = code[i+2-2];
        encodedVector += calculateParities(sliding_window);
        // cout << "Time Steps was: " << timeSteps << endl;
        timeSteps += 1;
        // cout << "Time Steps is now: " << timeSteps << endl;

    }

    // so essentially, if our original code was: 1010
    // Register @ t=0 -> [0,0,1] -> C1 = 1 -> C2 = 0 -> C3 = 0 -> Encoded vector: <1,0,0>
    // Register @ t=1 -> [0,1,0] -> C1 = 1 -> C2 = 1 -> C3 = 0 -> Encoded vector: <1,0,0,1,1,0>
    // Register @ t=3 -> [1,0,1] -> C1 = 0 -> C2 = 1 -> C3 = 1 -> Encoded vector: <1,0,0,1,1,0,0,1,1>
    // Register @ t=3 -> [0,1,0] -> C1 = 1 -> C2 = 1 -> C3 = 0 -> Encoded vector: <1,0,0,1,1,0,0,1,1,1,1,0>
    // So out final encoding is 100110011110 or <1,0,0,1,1,0,0,1,1,1,1,0>


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
    int numStates = pow(2, k-1); 

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
        //bestPathsAt_t.clear();
        // for every state
        for (int s = 0; s < numStates; s++) { // THIS IS HARDCODED TO WORK FOR 4 STATES
        //******** DONT FORGET TO SKIP OVER T = 1 FOR S IS 0 ********************/
            input0 = "";
            input1 = "";
            expectedOutput0 = "";
            expectedOutput1 = "";
            vNode firstNode, secondNode, thirdNode, fourthNode, fifthNode, sixthNode, seventhNode, eigthNode;
            if (t == 1) {
                // case for input 0
                    input0 = "000";
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    firstNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    firstNode.inputArrivalBit = 0;
                    firstNode.prevNodeState = s;
                    firstNode.state = 0;
                    trellis[t].push_back(firstNode);

                    // case for input 1;
                    input1 = "001";
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
                    input0 = "000";
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    firstNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    firstNode.inputArrivalBit = 0;
                    firstNode.prevNodeState = s;
                    firstNode.state = 0;
                    trellis[t].push_back(firstNode);

                    // case for input 1;
                    input1 = "001";
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
                    input0 = "010";
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    thirdNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    thirdNode.inputArrivalBit = 0;
                    thirdNode.prevNodeState = s;
                    thirdNode.state = 2;
                    trellis[t].push_back(thirdNode);

                    // case for input 1;
                    input1 = "011";
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
                    input0 = "000";
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    firstNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    firstNode.inputArrivalBit = 0;
                    firstNode.prevNodeState = s;
                    firstNode.state = 0;
                    trellis[t].push_back(firstNode);

                    // case for input 1;
                    input1 = "001";
                    expectedOutput1 = calculateParities(input1);


                    secondNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    secondNode.inputArrivalBit = 1;
                    secondNode.prevNodeState = s;
                    secondNode.state = 1;
                    trellis[t].push_back(secondNode);
                    
                    break;
                case 1: // state (0,1)
                    // case for input 0
                    input0 = "010";
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    thirdNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    thirdNode.inputArrivalBit = 0;
                    thirdNode.prevNodeState = s;
                    thirdNode.state = 2;
                    trellis[t].push_back(thirdNode);

                    // case for input 1;
                    input1 = "011";
                    expectedOutput1 = calculateParities(input1);


                    fourthNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    fourthNode.inputArrivalBit = 1;
                    fourthNode.prevNodeState = s;
                    fourthNode.state = 3;
                                    
                    trellis[t].push_back(fourthNode);


                    break;
                case 2: // state (1,0)
                    // case for input 0
                    input0 = "100";
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    fifthNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    fifthNode.inputArrivalBit = 0;
                    fifthNode.prevNodeState = s;
                    fifthNode.state = 0;
                    trellis[t].push_back(fifthNode);

                    // case for input 1;
                    input1 = "101";
                    expectedOutput1 = calculateParities(input1);


                    sixthNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput1, observedInput);
                    sixthNode.inputArrivalBit = 1;
                    sixthNode.prevNodeState = s;
                    sixthNode.state = 1;
                    trellis[t].push_back(sixthNode);


                    break;
                case 3: // state (1,1)
                    // case for input 0
                    input0 = "110";
                    expectedOutput0 = calculateParities(input0);


                    // now need to compare this with the observedInput and calculate the hamming distance
                    seventhNode.cumHammingDistance += trellis[t-1][s].cumHammingDistance + calculateHammingDistance(expectedOutput0, observedInput);
                    seventhNode.inputArrivalBit = 0;
                    seventhNode.prevNodeState = s;
                    seventhNode.state = 2;
                    trellis[t].push_back(seventhNode);

                    // case for input 1;
                    input1 = "111";
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
    //string noisy_encoded = addNoise(encoded, p);
    // string s = ""; //debugging
    // s += "1011";
    // s += "1101";
    // s += "0110";
    //cout << "Code After Noise   -> " << noisy_encoded << endl;
    string originalCode = viterbiDecode("101110011110", k);
    cout << "The original code is: " << originalCode;

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