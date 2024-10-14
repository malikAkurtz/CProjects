#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

/*
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

*/

/*
1.) First go through each row and check if there are any repeats
2.) Go through each column and check for repeats
3.) go through each box and check for repeats

*/

bool isValidSudoku(vector<vector<char>>& board) {
    bool valid = true;


    std::cout << "-----------------------------------------------------------------------------------------------------" << endl;
    std::cout << "Checking Rows" << endl;
    // check each row
    for (int i = 0; i < board.size();i++){
        //std::cout << "Checking row: " << i << endl;
        // i = row number
        // check each number in the row
        for (int j = 0; j < board[i].size();j++) {
            //std::cout << "we are here" << endl;
            if (board[i][j] == '.') {
                //std::cout << "j is " << j << endl;
                continue;
            }
            // std::cout << "and here" << endl;
            // std::cout << "Row: " << i << " Column: " << j << endl;
            std::cout << "Looking at char: " << board[i][j] << endl;
            for (int k = 0; k < board[i].size(); k++) {
                //std::cout << "K is: " << k <<endl;
                //std::cout << "Here1" << endl;
                std::cout << "Comparing to char: " << board[i][k] << endl;
                if (j==k) {
                    //std::cout << "Here2" << endl;
                    continue;
                }
                else if (board[i][k] == '.') {
                    //std::cout << "Here3" << endl;
                    continue;
                }
                else if (board[i][j] == board[i][k]) {
                    //std::cout << "Here5" << endl;
                    std::cout << "Element: " << board[i][j] << " is equal to: " << board[i][k] << endl;
                    valid = false;
                    return valid;
                }
                //std::cout << "Made it here" << endl;
            }
        }
    }
    std::cout << "-----------------------------------------------------------------------------------------------------" << endl;
    //std::cout << "Here" << endl;

    std::cout << "Checking Columns" << endl;
    // check each column
    for (int j = 0; j < board[0].size() ; j++) {
        // j represents column
        // for each row
        for (int i = 0; i < board.size(); i++) {
            //i represents row
            std::cout << "Looking at char: " << board[i][j] << endl;
            for (int k = 0; k < board.size(); k++) {
                //std::cout << "Comparing to char: " << board[k][j] << endl;
                if (i == k) {
                    continue;
                }
                else if (board[k][j] == '.') {
                    continue;
                }
                else if (board[i][j] == board[k][j]) {
                    std::cout << "Element: " << board[i][j] << " is equal to: " << board[i][k] << endl;
                    valid = false;
                    return valid;
                }
            }
        }
    }

    std::cout << "-----------------------------------------------------------------------------------------------------" << endl;

   
    //std::cout << "And Here" << endl;
    // check each 3x3 box

    vector<char> box = {};
    char curChar;

    for (int boxRow = 0; boxRow < 3; boxRow++) {
        for (int boxCol = 0; boxCol < 3; boxCol++) {
            

            for (int i = 0;i<3;i++) {
                for (int j = 0;j<3;j++) {
                curChar = board[boxRow*3+i][boxCol*3+j];
                if (curChar != '.') {
                    box.push_back(curChar);
                    }
                }
            }

            for (int i = 0; i < box.size(); i++) {
                for (int j = 0; j < box.size(); j++) {
                    if (i == j) {
                        continue;
                    }
                    else {
                        if (box[i] == box[j]) {
                            valid = false;
                            return valid;
                        }
                    }
                }
            }
        }
    }

    return valid;
}

int main() {

std::vector<std::vector<char>> board3 = {
    {'.', '8', '7', '6', '5', '4', '3', '2', '1'},
    {'2', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'3', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'4', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'5', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'6', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'8', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'9', '.', '.', '.', '.', '.', '.', '.', '.'}
};

std::vector<std::vector<char>> board = {
    {'.', '.', '.', '.', '5', '.', '.', '1', '.'},
    {'.', '4', '.', '3', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '3', '.', '.', '1'},
    {'8', '.', '.', '.', '.', '.', '.', '2', '.'},
    {'.', '.', '2', '.', '7', '.', '.', '.', '.'},
    {'.', '1', '5', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '2', '.', '.', '.'},
    {'.', '2', '.', '9', '.', '.', '.', '.', '.'},
    {'.', '.', '4', '.', '.', '.', '.', '.', '.'}
};
    std::cout << isValidSudoku(board);

    return 0;

}