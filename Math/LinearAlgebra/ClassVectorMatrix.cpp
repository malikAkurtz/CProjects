#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "ClassVectorMatrix.h"

/*
Vector Class

Fields:
1.) vector<int> vectorElements

Constructors:
1.) Vector()
2.) Vector(vector<int> elements)

Methods:
1.) string                              toString()
2.) int                                 getSize()
3.) vector<int>                         getElements()
4.) void                                addElement()
5.) int                                 dot(Vector otherVector)
6.) Vector                              cross(Vector otherVector)

*/

using namespace std;


Vector::Vector() {
    vectorElements = {};
}

Vector::Vector(vector<int> elements) {
    vectorElements = elements;
}

string Vector::toString() const{
    stringstream ss;
    ss << "[ ";
    for (int element : vectorElements) {
        ss << element << " ";
    }  ss << "]";

    return ss.str();
}

int Vector::getSize() const {
    return vectorElements.size();
}

vector<int> Vector::getElements() const {
    return vectorElements;
}

void Vector::addElement(int elementToAdd) {
    vectorElements.push_back(elementToAdd);
}

int Vector::dot(Vector otherVector) const {
    int dotProduct = 0;
    for (int i = 0; i < otherVector.getSize(); i++) {
        dotProduct += getElements()[i] * otherVector.getElements()[i];
    }
    return dotProduct;
}

bool Vector::operator==(const Vector& otherVector) const {
    if (getSize() != otherVector.getSize()) {
        return false; // Vectors of different sizes are not equal
    }
    for (int i = 0; i < getSize(); i ++) {
        if (getElements()[i] != otherVector.getElements()[i]) {
            return false;
        }
    }
    return true;
}

Vector Vector::operator + (const Vector& otherVector) const {
    Vector resultant;

    for (int i = 0; i < getSize(); i++) {
        resultant.addElement(getElements()[i] + otherVector.getElements()[i]);
    }

    return resultant;
}

Vector Vector::operator - (const Vector& otherVector) const {
    Vector resultant;

    for (int i = 0; i < getSize(); i++) {
        resultant.addElement(getElements()[i] - otherVector.getElements()[i]);
    }

    return resultant;
}

Vector Vector::cross (Vector otherVector) const {
    vector<int> components = {};
    int componenti = (getElements()[1] * otherVector.getElements()[2]) - (getElements()[2] * otherVector.getElements()[1]);
    components.push_back(componenti);
    //cout << "Component i: " << componenti << endl;
    int componentj = ((getElements()[0] * otherVector.getElements()[2]) - (getElements()[2] * otherVector.getElements()[0])) * -1;
    components.push_back(componentj);
    //cout << "Component j: " << componentj << endl;
    // cout << (getElements()[0] * otherVector.getElements()[1]) << " - " << (getElements()[1] * otherVector.getElements()[0]) << endl;
    int componentk = (getElements()[0] * otherVector.getElements()[1]) - (getElements()[1] * otherVector.getElements()[0]);
    //cout << "Component k: " << componentk << endl;
    components.push_back(componentk);

    Vector normalVector(components);
    return normalVector;
}


/*
Matrix Class

Fields:
1.) vector<Vector> matrixVectors

Constructors:
1.) Matrix()
2.) Matrix(vector<Vector> vectorOfVectors)

Methods:
1.) void                                addVector(Vector vectorToAdd)
2.) vector<Vector>                      getVectors()
3.) string                              toString()
4.) void                                addElement()

TODO
- determinants
- eigenvalues

*/




Matrix::Matrix() {
    matrixVectors = {};
}

Matrix::Matrix(vector<Vector> vectorOfVectors) {
    for (Vector v : vectorOfVectors) {
        matrixVectors.push_back(v);
    }
}

void Matrix::addVector(Vector vectorToAdd) {
    matrixVectors.push_back(vectorToAdd);
}

vector<Vector> Matrix::getVectors() const {
    return matrixVectors;
}

int Matrix::getNumCols() const {
    return matrixVectors.size();
}

int Matrix::getNumRows() const {
    return getVectors()[0].getSize();
}


pair<int, int> Matrix::getShape(){
    dimension.first = getNumRows();
    dimension.second = getNumCols();
    return dimension;
}

string Matrix::toString() const{
    stringstream ss;
    for (Vector v : getVectors()) {
        ss << v.toString() << endl;
    }
    return ss.str();
}






