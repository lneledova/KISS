#include <stdexcept>
#include "SquareMatrix.hpp"

class MatrixWrongSizeError: public logic_error {
public:
    MatrixWrongSizeError(): logic_error("Matrix wrong size.") {}
};

class MatrixIndexError: public range_error {
public:
    MatrixIndexError(): range_error("Index out of range.") {}
};


SquareMatrix::SquareMatrix(int num) {
    this->initialization(num);
}

SquareMatrix::~SquareMatrix(){
    this->clear();
};

int SquareMatrix::getDeterminant() const {
    int determinant = 1;
    SquareMatrix other(*this);
    for (int i = 0; i < size; ++i) {
        int maxI = i;
        for (int j = i + 1; j < size; ++j) {
            if (abs(other(maxI, i)) < abs(other(j, i)))  {
                maxI = j;
            }
        }
        if (other(maxI, i) == 0) {
            return 0;
        }
        if (maxI != i) {
            determinant *= (-1);
            swap(other.array[i], other.array[maxI]);
        }
        determinant *= other(i, i);
        for (int j = i + 1; j < size; ++j) {
            if (other(j, i) != 0) {
                int number = other(j, i) / other(i, i);
                for (int k = 0; k < size; ++k) {
                    other(j, k) -= other(i, k) * number;
                }
            }
        }
    }
    return determinant;
}


const int& SquareMatrix::operator()(int i, int j) const {
    if (i >= size || j >= size) {
        throw MatrixIndexError();
    }
    return this->array[i][j];
}

int& SquareMatrix::operator()(int i, int j) {
    if (i >= size || j >= size) {
        throw MatrixIndexError();
    }
    return this->array[i][j];
}

bool SquareMatrix::AlmostEmpty() const {
    int counter_not_empty = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if ((*this)(i, j) != 0) {
                ++counter_not_empty;
            }
        }
    }
    if (counter_not_empty < size) {
        return true;
    }
    return false;
}



std::vector<SquareMatrix> SquareMatrix::AvailableMoves() const {
    std::vector<SquareMatrix> available;
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            for (int k = 2; (i + k) <= size && (k + j) <= size; ++k) {
                SquareMatrix new_m = *this;
                for (int l = i; l < i + k; ++l) {
                    for (int m = j; m < j + k; ++m) {
                        new_m(l, m) = (*this)(l - i + j, m - j + i);
                    }
                }
                if (new_m != *this) {
                    available.push_back(new_m);
                }
                new_m = *this;
                for (int l = i; l < i + k; ++l) {
                    for (int m = j; m < j + k; ++m) {
                        new_m(l, m) = (*this)(k - 1 - m + j, k - 1 - l + i);
                    }
                }
                if (new_m != *this) {
                    available.push_back(new_m);
                }
            }
        }
    }
    return available;
}

SquareMatrix::SquareMatrix(const SquareMatrix& that) {
    this->initialization(that.size);
    for (int i = 0; i < this->size; ++i) {
        for (int j = 0; j < this->size; ++j) {
            (*this)(i, j)= that(i, j);
        }
    }
}


SquareMatrix& SquareMatrix::operator=(const SquareMatrix& that) {
    if (*this == that) {
        return *this;
    }
    this->clear();
    this->initialization(that.size);
    for (int i = 0; i < this->size; ++i) {
        for (int j = 0; j < this->size; ++j) {
            (*this)(i, j) = that(i, j);
        }
    }
    return *this;
}

bool SquareMatrix::operator==(const SquareMatrix& that) const {
    if (size != that.size) {
        return false;
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if ((*this)(i, j) != that(i, j)) {
                return false;
            }
        }
    }
    return true;
}
bool SquareMatrix::operator!=(const SquareMatrix& that) const {
    return !((*this) == that);
}