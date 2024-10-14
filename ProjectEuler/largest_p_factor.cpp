#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

int largestPrimeFactor(int n){
    int largestPFactor = 1;

    for (int i = 0; i < sqrt(n); i++) {
        if (n % i != 0) {
            continue;
        }
        cout << i << " goes evenly into " << n << endl;
        if ((i % 2 != 0) && (i % 3 != 0) && (i % 5 != 0)) {
            cout << i << " is prime" << endl;
            largestPFactor = i;
        }
    }

    return largestPFactor;
}


int main() {

    cout << largestPrimeFactor(13195);

    return 0;
}