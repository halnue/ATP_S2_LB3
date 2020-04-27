//#include <iostream>
//
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}
//
// Created by Michael on 24.04.2020.
//
#include <vector>
#include <iostream>
#include "Matrix.h"
#include "List.cpp"
#include "Matrix.cpp"
using namespace std;

#define PRINT_MATRIX(variable) std::cout << std::string(#variable) << ": "<< std::endl<<variable << std::endl;

int main() {

    vector<vector<double>> list1 = {{0.6, 2.3},{7.6, 4.7}};
    vector<vector<double>> list2 = {{8.5, 1.5},{8.9, 5.5}};
//            vector<vector<int>>();
//    list1.push_back(vector<int>(2, new int[2]{0, 2}));                     {0.6, 2.3}
//    list1.push_back(vector<int>(2, new int[2]{7, 4}));                     {7.6, 4.7}

//    vector<vector<int>> list2 = vector<vector<int>>();                     uble>>();
//    list2.push_back(vector<int>(2, new int[2]{8, 1}));                     {8.5, 1.5}
//    list2.push_back(vector<int>(2, new int[2]{8, 5}));                     {8.9, 5.5}

    Matrix matrix1 = Matrix(list1);
    Matrix matrix2 = Matrix(list2);

    PRINT_MATRIX(matrix1)
    PRINT_MATRIX(&matrix2)
    Matrix matrix3 = changeNum(matrix1);
    PRINT_MATRIX(matrix3)

    Matrix matrixSum = matrix1.plus(matrix2);
    PRINT_MATRIX(matrixSum)
    PRINT_MATRIX(matrix1.subtraction(matrix2))
    PRINT_MATRIX(matrix1 * matrix2)
}