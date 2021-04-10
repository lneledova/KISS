#include "SquareMatrix.hpp"
#include <queue>
#include <cmath>

void GetAnswer(SquareMatrix& matrix);

int main() {
    int size;
    std::cin >> size;
    SquareMatrix matrix(size);
    std::cin >> matrix;
    if (matrix.AlmostEmpty()) {
        std::cout << "Детерминант 0.\nХодов 0 \n.";
    } else {
        GetAnswer(matrix);
    }

    std::cout << matrix;
    return 0;
}

struct MoveMatrix {
    int moves = 0;
    SquareMatrix matrix;

    bool operator<(const MoveMatrix& that) const {
        return moves < that.moves;
    }
};


void GetAnswer(SquareMatrix& matrix) {
    int max_moves = std::pow(matrix.GetSize(), 4);
    int index = 0;
    std::priority_queue<MoveMatrix> tree;
    tree.push({0, matrix});
    MoveMatrix max_matrix = tree.top();
    while (!tree.empty() && index < max_moves) {
        ++index;
         MoveMatrix current = tree.top();
        int curr_det = current.matrix.getDeterminant();
        if (curr_det > max_matrix.matrix.getDeterminant()) {
            max_matrix = current;
        }
        tree.pop();
        std::vector<SquareMatrix> available = current.matrix.AvailableMoves();
        for (int i = 0; i < available.size(); ++i) {
            if (available[i].getDeterminant() >= curr_det) {
                tree.push({current.moves + 1, available[i]});
            }
        }
    }
    std::cout << "Детерминант " << max_matrix.matrix.getDeterminant() << ".\nХодов " << max_matrix.moves << ".\n";
    matrix = max_matrix.matrix;
}

istream& operator>>(istream& is, SquareMatrix& that) {
    for (int i = 0; i < that.size; ++i) {
        for (int j = 0; j < that.size; ++j) {
            is >> that(i, j);
        }
    }
    return is;
}


ostream& operator<<(ostream& os, const SquareMatrix& that) {
    for (int i = 0; i < that.size; ++i) {
        for (int j = 0; j < that.size; ++j) {
            os << that(i, j) << ' ';
        }
        os << endl;
    }
    return os;
}