//
// Created by Michael on 09.02.2020.
//

#ifndef S2LB1_2_MATRIX_H
#define S2LB1_2_MATRIX_H

#include <vector>
#include <ostream>
#include "List.cpp"
#include "IncompatibleMatrices.h"
#include "NullPointErexception.h"
using namespace std;

template <typename T> class Matrix {

private:
    vector<vector<T>> list = vector<vector<T>>();
    int width, height;
public:

    Matrix():Matrix(1, 1) {}

    Matrix(const Matrix &m){
        vector list = createArray(m.getWidth(), m.getHeight(), 1);

        for (int i = 0; i < m.getWidth(); ++i) {
            for (int j = 0; j < m.getHeight(); ++j) {
                list[i][j] =  m.get(i, j);
            }
        }
        this->list = list;
        this->height = m.getHeight();
        this->width = m.getWidth();
    }

    Matrix(int width, int height);

    Matrix(int width, int height, int defaultValue){
        vector list = createArray(width, height, defaultValue);
        this->list = list;
        this->height = height;
        this->width = width;
    }

    Matrix(vector<vector<T>> array) {
        list = array;
        this->width = array.size();
        this->height = array[0].size();
    }

    virtual ~Matrix(){

        width = 0;
        height = 0;
    }

    friend std::ostream &operator<<(std::ostream &os, Matrix *matrix){
//        todo("fix the conclusion")
        for (int i = 0; i < matrix->getWidth(); i++) {
            os << "| ";
            for (int i1 = 0; i1 < matrix->getHeight(); i1++) {
                os << matrix->get(i, i1) << " ";
            }
            os << "|" << std::endl;
        }
        return os;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix){
//    todo("fix the conclusion")
        for (int i = 0; i < matrix.getWidth(); i++) {
            os << "| ";
            for (int i1 = 0; i1 < matrix.getHeight(); i1++) {
                os << matrix.get(i, i1) << " ";
            }
            os << "|" << std::endl;
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Matrix matrix){
        for (int j = 0; j < matrix.getWidth(); ++j) {
            for (int i = 0; i < matrix.getHeight(); ++i) {
                int num;
                is >> num;
                matrix.set(j, i, num);
            }
        }
        return is;
    }

    vector<T> &operator[](int i){
        if (width > i)
            return list[i];
        else
            throw NullPointErexception();
    }

    friend Matrix operator+(Matrix m1, Matrix m2) {
//    Matrix result = Matrix(m1.getWidth(), m1.getHeight(), 1);

        return m1.plus(m2);
    }

    friend Matrix operator-(Matrix m1, Matrix m2){
//    Matrix result = Matrix(m1.getWidth(), m1.getHeight(), 1);

        return m1.subtraction(m2);
    }

    friend Matrix operator*(Matrix m1, Matrix m2){
        return m1.multiply(m2);
    }

//    friend  Matrix operator=(const Matrix &m)
    T get(int width, int height) const{
        if (width > getWidth() && height > getHeight())
            throw NullPointErexception();
        return list[width][height];
    }

    void set(int width, int height, T value){
        list[width][height] = value;
    }

    Matrix plus(Matrix matrix){
        if (this->getWidth() != matrix.getWidth() && this->getHeight() != matrix.getHeight())
            throw IncompatibleMatrices();
        else {
            Matrix matrixResult = Matrix(width, height, 1);
            for (int i = 0; i < matrix.getWidth(); ++i) {
                for (int j = 0; j < matrix.getHeight(); ++j) {
                    T r = get(i, j) + matrix.get(i, j);
                    matrixResult.set(i, j, r);
                }
            }
            return matrixResult;
        }
    }

    const Matrix subtraction(Matrix matrix) {
        if (this->getWidth() != matrix.getWidth() && this->getHeight() != matrix.getHeight())
            throw IncompatibleMatrices();
        else {
            Matrix matrixResult = Matrix(width, height, 1);
            for (int i = 0; i < matrix.getWidth(); ++i) {
                for (int j = 0; j < matrix.getHeight(); ++j) {
                    matrixResult.set(i, j, get(i, j) - matrix.get(i, j));
                }
            }
            return matrixResult;
        }
    }

    const Matrix multiply(Matrix matrix){
        if (this->getHeight() != matrix.getWidth())
            throw IncompatibleMatrices();
        else {
            Matrix result = Matrix(width, matrix.getHeight(), 1);
            for (int x = 0; x < matrix.getWidth(); ++x) {
                for (int y = 0; y < matrix.getHeight(); ++y) {
                    vector<T> m2 = matrix.getLineWidth(y);
                    vector<T> m1 = getLineHeight(x);
                    T r = multiplyLines(m1, m2);
                    result.set(x, y, r);
                }
            }
            return result;
        }
    }

    Matrix multiply(T value){
        Matrix matrixResult = Matrix(width, height, 1);
        for (int x = 0; x < matrixResult.getWidth(); ++x) {
            for (int y = 0; y < matrixResult.getHeight(); ++y) {
                matrixResult.set(x, y, this->get(x, y) * value);
            }
        }
        return matrixResult;
    }

    T getWidth() const{
        return width;
    }

    T getHeight() const{
        return height;
    }


    friend Matrix changeNum(Matrix m){
        int w = m.getWidth();
        int h = m.getHeight();
        vector<vector<T>> l = vector<vector<T>>();
        for (int x = 0; x < w; ++x) {
            vector<T> listInt = vector<T>();
            for (int y = 0; y < h; ++y) {
                T num = m.get(x, y);
                if (num == 0)
                    listInt.push_back(1);
                else
                    listInt.push_back(num);

            }
            l.push_back(listInt);
        }
        return Matrix(l);
    }

private:

    T multiplyLines(vector<T> line1, vector<T> line2){
        T result = 0;
        for (int i = 0; i < line1.size(); ++i) {
            T sum = line1[i] * line2[i];
            result += sum;
        }
        return result;
    }

    vector<T> getLineHeight(int width){
        return list[width];
    }

    vector<T> getLineWidth(int height){
        vector<T> listResult = vector<T>();
        for (int j = 0; j < getHeight(); ++j) {
            listResult.push_back(get(j, height));
        }
        return listResult;
    }

    vector<vector<T>> createArray(int width, int height, int defaultValue) const{
        vector<vector<T>> list = vector<vector<T>>();
        for (int i = 0; i < width; ++i) {
            vector<T> list1 = vector<T>();
            for (int j = 0; j < height; ++j) {
//            list1.set(j,defaultValue);
                list1.push_back(defaultValue);
            }
            list.push_back(list1);
        }
        return list;
    }
};

#endif //S2LB1_2_MATRIX_H
