#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> resultIndices = {};
        vector<int>::iterator leftSide = numbers.begin();
        vector<int>::iterator rightSide = numbers.end()-1;

        int leftindex = 0;
        int rightindex = numbers.size() -1;

        cout << *leftSide << " " << *rightSide << endl;
        while ((*leftSide + *rightSide) != target ) {
            if ((*leftSide + *rightSide) > target) {
                cout << *leftSide << " " << *rightSide << endl;
                rightSide--;
                rightindex--;
            }
            else if ((*leftSide + *rightSide) < target) {
                cout << *leftSide << " " << *rightSide << endl;
                leftSide++;
                leftindex++;
            }
        }

        resultIndices.push_back(leftindex+1);
        resultIndices.push_back(rightindex+1);

        return resultIndices;
        
}


int main() {
    vector<int> nums = {2,7,11,15};
    vector<int> nums1 = {-10,-8,-2,1,2,5,6};

    vector<int> result = twoSum(nums, 9);
    for (int i : result) {
        cout << i << endl;
    }

    return 0;
}