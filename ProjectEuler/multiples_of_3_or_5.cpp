#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

// get the sum of all the multiples of 3 or 5 below n
int multiplesOf3or5(int n) {
    int runningSum = 0;
    int curInt = 0;

    while (curInt != n) {
        if (curInt % 3 == 0 or curInt % 5 == 0) {
            runningSum += curInt;
        }
        curInt += 1;
        cout << curInt << endl;
    }

    return runningSum;

}

int main() {
    cout << multiplesOf3or5(1000);
}