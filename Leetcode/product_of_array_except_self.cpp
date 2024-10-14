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

Prefix shoud be [1, 2, 6, 24]

postfix should be [24, 24, 12, 4]

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
    vector<int> output ={};
    vector<int> prefix = {};
    vector<int> postfix= {};

    int leftProduct = 1;
    int rightProduct = 1;


    // Making Prefix vector
    for (int i = 0; i < nums.size(); i++) {
        //cout << nums[i] << endl;
        if (i == 0) {
            prefix.push_back(nums[i]);
        }
        else {
            prefix.push_back(nums[i]*prefix[i-1]);
        }
        
    }
    int separateCounter = 0;
    for (int i = nums.size()-1; i >= 0; i--) {
        if (i == nums.size()-1) {
            postfix.push_back(nums[nums.size()-1]);
        }
        else {
            //cout << nums[i] << " * " <<postfix[i-1];
            postfix.push_back(nums[i] * postfix[separateCounter]);
            separateCounter++;
        }
        
    }

    reverse(postfix.begin(), postfix.end());

    // cout << "Prefix : " << endl;

    // for (int i = 0; i < prefix.size(); i++) {
    //     cout << prefix[i] << endl;
    // }

    // cout << "postfix : " << endl;
    // for (int i = 0; i < postfix.size(); i++) {
    //     cout <<  postfix[i] << endl;
    // }
    
    // cout << "Done";


    for (int i = 0; i < nums.size(); i++) {
        if (i == 0) {
            output.push_back(postfix[i+1]);
        }
        else if (i == nums.size()-1) {
            output.push_back(prefix[i-1]);
        }
        else {
            leftProduct = prefix[i-1];
            rightProduct = postfix[i+1];
            output.push_back(leftProduct*rightProduct);
        }
    }
            
    return output;     
}







int main() {

    vector<int> nums = {1,2,3,4};
    vector<int> result = productExceptSelf(nums);

    for (int each : result) {
        cout << each << endl;
    }
    
    return 0;
}