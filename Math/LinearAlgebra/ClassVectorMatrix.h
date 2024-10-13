#ifndef CLASSVECTORMATRIX_H
#define CLASSVECTORMATRIX_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// Vector Class Declaration
class Vector {
private:
    vector<int> vectorElements;

public:
    // Constructors
    Vector();
    Vector(vector<int> elements);

    // Methods
    string toString() const;
    int getSize() const;
    vector<int> getElements() const;
    void addElement(int elementToAdd);
    int dot(Vector otherVector) const;
    Vector cross(Vector otherVector) const;

    // Operator Overloads
    bool operator==(const Vector& otherVector) const;
    Vector operator+(const Vector& otherVector) const;
    Vector operator-(const Vector& otherVector) const;
};

// Matrix Class Declaration
class Matrix {
private:
    vector<Vector> matrixVectors;
    pair<int, int> dimension;

public:
    // Constructors
    Matrix();
    Matrix(vector<Vector> vectorOfVectors);

    // Methods
    void addVector(Vector vectorToAdd);
    vector<Vector> getVectors() const;
    int getNumCols() const;
    int getNumRows() const;
    pair<int, int> getShape();
    string toString() const;
};



#endif
