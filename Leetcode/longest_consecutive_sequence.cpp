#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

/*
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

 

Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
Example 2:

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
*/

int longestConsecutive(vector<int>& nums) {
    if (nums.size() == 0) {
        return 0;
    }

    int longestSequence = 1;
    int tempSequence = 1;
    sort(nums.begin(), nums.end());

    // For each number
    for (int i = 1; i < nums.size(); i++) {
        

        if (nums[i] == nums[i-1]) {
            continue;
        }
        else if (nums[i] == nums[i-1]+1) {
            tempSequence += 1;
        }
        else {
            if (tempSequence > longestSequence) {
                longestSequence = tempSequence;
            }
            tempSequence = 1;
        }
    }
    longestSequence = std::max(longestSequence, tempSequence);
    return longestSequence;
}

int main() {

    vector<int> nums = {100,4,200,1,3,2};

    cout << longestConsecutive(nums);

    return 0;
}