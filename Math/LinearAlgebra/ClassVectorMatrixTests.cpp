#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "ClassVectorMatrix.h"
#include "ClassVectorMatrixTests.h"
using namespace std;



bool test_matrixShape() {

    Matrix testMatrix;

    Vector testVector({1,2,3});

    //return 3 x 1

    testMatrix.addVector(testVector);

    pair<int,int> trueShape;
    trueShape.first = 3;
    trueShape.second = 1;

    return (testMatrix.getShape() == trueShape);

}

bool test_vectorAddition() {
    vector<int> first = {1,2,3};
    vector<int> second = {2,2,2};
    Vector v1(first);
    Vector v2(second);

    Vector resultant = v1 + v2;

    Vector trueResult({3,4,5});

    return (resultant == trueResult);
}

bool test_vectorSubtraction() {
    vector<int> first = {1,2,3};
    vector<int> second = {3,2,1};
    Vector v1(first);
    Vector v2(second);

    Vector resultant = v1 - v2;

    Vector trueResult({-2,0,2});

    return (resultant == trueResult);
}


bool test_vectorSize() {
    Vector testVector;
    return (testVector.getSize() == 0);
}

bool test_vectorAddElement() {
    Vector testVector;

    testVector.addElement(1);

    return (testVector.getSize() == 1);
}

bool test_vectorDot() {
    vector<int> v1 = {1,2,3};
    vector<int> v2 = {4,5,6};

    Vector V1(v1);
    Vector V2(v2);


    return (V1.dot(V2) == 32);
}

bool test_vectorCross() {

    vector<int> v1 = {1,2,3};
    vector<int> v2 = {4,5,6};

    Vector V1(v1);
    Vector V2(v2);

    Vector trueResult({-3,6,-3});

    // cout << V1.cross(V2).toString() << endl;
    // cout << trueResult.toString() << endl;


    return (V1.cross(V2) == trueResult);
}

bool run_tests() {
    bool all_good = 1;

    cout << "Testing vectorSize()..." << endl;
    all_good &= test_vectorSize();
    if (all_good != 1) {
        return all_good;
    }
    cout << "Testing vectorDot()..." << endl;
    all_good &= test_vectorDot();
    if (all_good != 1) {
        return all_good;
    }
    cout << "Testing vectorCross()..." << endl;
    all_good &= test_vectorCross();
    if (all_good != 1) {
        return all_good;
    }
    cout << "Testing vectorAddElement()..." << endl;
    all_good &= test_vectorAddElement();
    if (all_good != 1) {
        return all_good;
    }
    cout << "Testing vectorAddition()..." << endl;
    all_good &= test_vectorAddition();
    if (all_good != 1) {
        return all_good;
    }
    cout << "Testing vectorSubtraction()..." << endl;
    all_good &= test_vectorSubtraction();
    if (all_good != 1) {
        return all_good;
    }
    cout << "Testing matrixShape()..." << endl;
    all_good &= test_matrixShape();
    if (all_good != 1) {
        return all_good;
    }

    return all_good;

}