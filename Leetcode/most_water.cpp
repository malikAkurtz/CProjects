#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

/*
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

 

Example 1:


Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
*/


int maxArea(vector<int>& height) {
        int largestArea = 0;
        int area = 0;
        int w;
        int h;

        int L = 0;

        int R = height.size() - 1;

        //while the left pointer is less than the right pointer
        while (L < R) {
            // calculate the area formed by the two pointers
            w = R-L;
            h = min(height[L], height[R]);
            area = w * h;
            cout << "Left Pointer is: " << L << " Right Pointer is: " << R << " Width is: " << area << endl;
            if (area > largestArea) {
                largestArea = area;
            }
            cout << "Left Pointer height is: " << height[L] << " Right Pointer height is: " << height[R] << endl;
            if (height[L] < height[R]) {
                cout << "Moving left pointer to the right" << endl;
                L++;
            }
            else {
                cout << "Moving right pointer to the right" << endl;
                R--;
            }
        }

        return largestArea;

    }


int main() {
    vector<int> nums = {1,8,6,2,5,4,8,3,7};
    cout << maxArea(nums);
}