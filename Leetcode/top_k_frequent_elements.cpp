#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

/*Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.


Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]

*/


/*
1.) Make a dictionary, with the keys being the integers and the value being the frequency
2.) sort the dictionary based on frequency
3.) add the k top elements to the list
4.) return the list
*/

vector<int> topKFrequent(vector<int>& nums, int k) {
    vector<int> kElements = {};
    map<int, int> integerFrequency;

    // create a dictionary of the ints with frequencies initialized to 0
    for (int i = 0; i < nums.size(); i++) {
        int Key = nums[i];
        integerFrequency.insert({Key, 0});
    }

    // map<int, int>::iterator it;
    // for (it = integerFrequency.begin() ; it != integerFrequency.end(); it++) {
    //     cout << it->first << ":" << it->second << endl;
    // }


    for (int i = 0; i < nums.size(); i++) {
        //cout << "For: " << nums[i] << " The current frequency is: " << integerFrequency.at(nums[i]) << endl;
        int prevFreq = integerFrequency.at(nums[i]);
        integerFrequency[nums[i]] = prevFreq+1;
        //cout << "After incrementing, " << nums[i] << " Frequency is now: " << integerFrequency.at(nums[i]) << endl;
    }

    // for (it = integerFrequency.begin() ; it != integerFrequency.end(); it++) {
    //     cout << it->first << ":" << it->second << endl;
    // }

    vector<pair<int, int>> pairs;

    for (auto& it : integerFrequency) {
        pairs.push_back(it);
    }

    sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    for (int i = 0 ; i < k ; i++) {
        kElements.push_back(pairs[i].first);
    }

    return kElements;
}




int main() {
    vector<int> nums = {4,1,-1,2,-1,2,3};
    int k = 2;

    vector<int> kfrequent;
    kfrequent = topKFrequent(nums, k);

    // for (int i = 0; i < kfrequent.size() ; i++) {
    //     cout << kfrequent[i] << endl;
    // }

    cout << "[";
    for (int i = 0; i < kfrequent.size() ; i++) {
        if (!(i == kfrequent.size() - 1)) {
            cout << kfrequent[i] << ",";
        }
        else {
            cout << kfrequent[i];
        }
    } cout << "]";

    return 0;
}