#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int evenFibonacciNumbers(int n) {
    int runningSum = 2;

    int firstTerm = 1;
    int secondTerm  = 2;

    int nextTerm = 0;

    while (nextTerm < n) {
        nextTerm = firstTerm + secondTerm;
        if (nextTerm < n) {
            cout << nextTerm << endl;
            if (nextTerm % 2 == 0) {
                runningSum += nextTerm;
            }
            firstTerm = secondTerm;
            secondTerm = nextTerm;
        }
        else {
            break;
        }
    }

    return runningSum;

}

int main() {
    cout << evenFibonacciNumbers(4000000);
}