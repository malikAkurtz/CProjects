#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <stack>
using namespace std;
/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.

Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "()[]{}"
Output: true

Example 3:
Input: s = "(]"
Output: false

Example 4:
Input: s = "([])"
Output: true
*/

bool isValid(string s) {
    stack<int> stack = {};
    map<char, char> map;
    map.insert({')', '('});
    map.insert({']', '['});
    map.insert({'}', '{'});

    // for ever char in the set
    for (int i = 0; i < s.length(); i++) {
        // if the char is a closing type
        if (map.contains(s[i])) {
            if (!stack.empty() && stack.top() == map.at(s[i])) {
                stack.pop();
                continue;
            }
            else {
                return false;
            }
        }
        stack.push(s[i]);
   }

   return (stack.empty());
}


int main() {

    // string s = "()";
    // cout << s << " " << isValid(s) << endl;

    // string s1 = "()[]{}";
    // cout << s1 << " " << isValid(s1) << endl;

    string s3 = "([])";
    cout << s3 << " " << isValid(s3) << endl;

    // string s4 = "){";
    // cout << s4 << " " << isValid(s4) << endl;


    // string s5 = "(([]){})";
    // //cout << s5 << " " << isValid(s5) << endl;
}