#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
using namespace std;

/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.

*/


vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> toReturn = {};
    set<vector<int>> set;
    sort(nums.begin(), nums.end());
    vector<int> curSequence = {};

    

    

    vector<int>::iterator leftSide;
    vector<int>::iterator rightSide;

    std::set<int> aPositionSet = {};

    // for every number in nums
    for (int i = 0; i < nums.size(); i++) {
        // if it has already been processed in the first position, skip
        if (aPositionSet.contains(nums[i])) {
            //cout << "We have already processed: " << nums[i] << " at the first position, moving to next number" << endl;
            continue;
        }
        // otherwise call two sum on the remaining integers
        else {
            cout << "We have not processed: " << nums[i] << " at the first position, calling two sum on rest" << endl;
            leftSide = nums.begin() + (i+1);
            rightSide = nums.end() -1;
            while (leftSide < rightSide) {
                cout << "Left pointer points to: " << *leftSide << " Right Pointer points to: " << *rightSide << endl;
                if (nums[i] + *leftSide + *rightSide > 0) {
                    cout << "Result: " << *leftSide + *rightSide << " is greater than 0" << endl;
                    rightSide--;
                }
                else if (nums[i] + *leftSide + *rightSide < 0) {
                    cout << "Result: " << *leftSide + *rightSide << " is less than 0" << endl;
                    leftSide++;
                }
                else {
                    cout << "Result: " << nums[i] + *leftSide + *rightSide << " EQUALS 0" << endl;
                    curSequence.push_back(*leftSide);
                    curSequence.push_back(*rightSide);
                    curSequence.push_back(nums[i]);
                    sort(curSequence.begin(), curSequence.end());
                    set.insert(curSequence);
                    curSequence.clear();
                    rightSide--;
                    leftSide++;
                }
            }
            aPositionSet.insert(nums[i]);
        }
    }

    for (vector<int> triplet : set) {
        toReturn.push_back(triplet);
    }

    return toReturn;

}

int main() {

    vector<int> nums = {-1,0,1,2,-1,-4};
    vector<vector<int>> triplets = threeSum(nums);

    for (vector<int> group : triplets) {
        cout << "<";
        for (int num : group) {
            cout << num << " ";
        } cout << ">";
    }



    return 0;
}