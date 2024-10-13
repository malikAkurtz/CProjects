#include <vector>
#include <string>
#include <iostream>
#include <sstream>

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

class Vector {
    private:
    vector<int> vectorElements;

    public:
    Vector() {
        vectorElements = {};
    }

    Vector(vector<int> elements) {
        vectorElements = elements;
    }

    string toString() const{
        stringstream ss;
        ss << "[ ";
        for (int element : vectorElements) {
            ss << element << " ";
        }  ss << "]";

        return ss.str();
    }

    int getSize() const {
        return vectorElements.size();
    }

    vector<int> getElements() const {
        return vectorElements;
    }
    
    void addElement(int elementToAdd) {
        vectorElements.push_back(elementToAdd);
    }

    int dot(Vector otherVector) const {
        int dotProduct = 0;
        for (int i = 0; i < otherVector.getSize(); i++) {
            dotProduct += getElements()[i] * otherVector.getElements()[i];
        }
        return dotProduct;
    }

    bool operator==(const Vector& otherVector) const {
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

    Vector operator + (const Vector& otherVector) const {
        Vector resultant;

        for (int i = 0; i < getSize(); i++) {
            resultant.addElement(getElements()[i] + otherVector.getElements()[i]);
        }

        return resultant;
    }

    Vector operator - (const Vector& otherVector) const {
        Vector resultant;

        for (int i = 0; i < getSize(); i++) {
            resultant.addElement(getElements()[i] - otherVector.getElements()[i]);
        }

        return resultant;
    }

    Vector cross(Vector otherVector) {
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


};

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

class Matrix {
    private:
    vector<Vector> matrixVectors;

    public:
    Matrix() {
        matrixVectors = {};
    }

    Matrix(vector<Vector> vectorOfVectors) {
        for (Vector v : vectorOfVectors) {
            matrixVectors.push_back(v);
        }
    }

    void addVector(Vector vectorToAdd) {
        matrixVectors.push_back(vectorToAdd);
    }

    vector<Vector> getVectors() {
        return matrixVectors;
    }


    string toString() {
        stringstream ss;
        for (Vector v : getVectors()) {
            ss << v.toString() << endl;
        }
        return ss.str();
    }
};


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

    return all_good;

}

int main() {

    int exitStatus = run_tests();

    cout << "Exit Status -> " << exitStatus;

    return 0;
}


