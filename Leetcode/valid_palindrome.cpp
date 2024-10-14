#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

/*
A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, 
it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.


Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.
*/

bool isPalindrome(string s) {
    string forward = "";
    string backward = "";

    for (char c: s){
        if ((48 <= (int) c && (int) c <= 57) || (65 <= ((int) c) && (int) c <= 90) || (97 <= ((int) c) && (int) c <= 122)) {
            if ((65 <= ((int) c) && (int) c <= 90)) {
                forward += (c + 32);
            }
            else {
                forward += c;
            }
        }
    }

    cout << forward << endl;

    for (int i = forward.length()-1; i >= 0; i--) {
        backward += forward[i];
    }
    cout << backward << endl;

    for (int i = 0; i < forward.length(); i++) {
        if (forward[i] != backward[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    string s = "A man, a plan, a canal: Panama";

    cout << isPalindrome(s);


    return 0;
}