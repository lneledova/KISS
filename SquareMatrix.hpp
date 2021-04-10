#ifndef HELLOWORLD_SQUAREMATRIX_HPP
#define HELLOWORLD_SQUAREMATRIX_HPP

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class SquareMatrix {
private:
    int** array;
    int size;


    void initialization(int num) {
        size = num;
        array = new int*[size];
        for (int i = 0; i < size; ++i) {
            array[i] = new int[size];
        }
    }

    void clear() {
        for (int i = 0; i < this->size; ++i) {
            delete []this->array[i];
        }
        delete []this->array;
    }

public:
    explicit SquareMatrix(int num);
    SquareMatrix(const SquareMatrix& that);
    SquareMatrix& operator=(const SquareMatrix& that);

    int getDeterminant() const;
    int& operator()(int i, int j);
    const int& operator()(int i, int j) const;
    bool operator==(const SquareMatrix& that) const;
    bool operator!=(const SquareMatrix& that) const;
    int GetSize() const {
        return size;
    }

    bool AlmostEmpty() const;

    std::vector<SquareMatrix> AvailableMoves() const;

    ~SquareMatrix();
    friend istream& operator>>(istream& is, SquareMatrix& that);
    friend ostream& operator<<(ostream& os, const SquareMatrix& that);
};


#endif //HELLOWORLD_SQUAREMATRIX_HPP
