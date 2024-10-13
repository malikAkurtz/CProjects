#ifndef CLASSVECTORMATRIXTESTS_H
#define CLASSVECTORMATRIXTESTS_H

#include <vector>
#include <string>
#include <iostream>
#include "ClassVectorMatrix.h" // Ensure this is included to access Vector and Matrix

// Function Declarations
bool test_matrixShape();
bool test_vectorAddition();
bool test_vectorSubtraction();
bool test_vectorSize();
bool test_vectorAddElement();
bool test_vectorDot();
bool test_vectorCross();
bool run_tests(); // Add this line to declare run_tests

#endif
