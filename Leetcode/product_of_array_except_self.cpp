#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

 

Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]


Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]

*/


/*
1.) Create two iterators, one that will be used to iterator throught the numbers to the left of current intdex, and one for the right
2.) Create two variables that will hold the product of elements to the left, and element to the right
3.) Create a list that we will return at the end
4.) For each index, calculate the product of the numbers to the left and numbers to the right, multiply them together, and add them to the vector
that we will return at the end
5.) return the vector

*/

vector<int> productExceptSelf(vector<int>& nums) {
        // vector<int>::iterator leftSide;
        // vector<int>::iterator rightSide;
        // int leftProduct = 1;
        // int rightProduct = 1;

        vector<int> toReturn;

        for (int i = 0; i < nums.size(); i++) {

            int product = 1;

            for (int j = 0; j < nums.size(); j++) {
                if (j==i) {continue;}
                else {
                    product *= nums[j];
                }
            }
            toReturn.push_back(product);
            // leftSide = nums.begin();
            // rightSide = nums.end()-1;

            // leftProduct = 1;
            // rightProduct = 1;

            // int curIndex = 0;
            // while (curIndex != i) {
            //     leftProduct *= *leftSide;
            //     curIndex++;
            //     leftSide++;
            // }
            // curIndex = nums.size()-1;
            // while (curIndex != i) {
            //     rightProduct *= *rightSide;
            //     curIndex--;
            //     rightSide--;
            // }

            // //cout << "For: " << nums[i] << " Left Product is: " << leftProduct << " Right Product is: " << rightProduct << endl;

            // toReturn.push_back(leftProduct*rightProduct);
        }

        // cout << "[";
        // for (int each : toRetur ) {
        // cout << each << endl;
        // } cout << "]";

        return toReturn;

    }





int main() {

    vector<int> nums = {1,2,3,4};
    vector<int> result = productExceptSelf(nums);

    for (int each : result) {
        cout << each << endl;
    }
    
    return 0;
}