#pragma once

#include <iostream>
#include <cmath>
#include <memory>
#include <vector>

/*
		Definition
*/

template <class T>
struct Matrix {
        public:
        ~Matrix();
        Matrix(size_t row = 1, size_t col = 1);
        Matrix(Matrix<T> const& obj);
        Matrix<T>& operator= (Matrix<T> const& obj);
        
        size_t sizeX() const {    return rows; }
        size_t sizeY() const { return columns; }
        
        void resize(size_t row, size_t col);
        void fill();
        
        T operator* ();
        Matrix<T> const& operator+ () const;
        Matrix<T> operator- ();
        Matrix<T> operator* (Matrix<T> const& obj);
        Matrix<T> operator* (T const& obj);
        Matrix<T> operator+ (Matrix<T> & obj);
        Matrix<T> operator- (Matrix<T> & obj);
        T& operator() (size_t i, size_t j) const;
        
        private:
        T** array;
        size_t    rows;
        size_t columns;
        
        T _determinate(std::vector<std::vector<T>> det);
        void _alloc(size_t row, size_t col);
        void _delete();
};

/*
		Implementation
*/

template <class T>
Matrix<T>::Matrix(size_t row, size_t col)
{
        _alloc(row, col);
}

template <class T>
Matrix<T>::~Matrix()
{
        _delete();
}

template <class T>
Matrix<T>::Matrix(Matrix<T> const& obj)
{
        size_t szX = obj.sizeX();
        size_t szY = obj.sizeY();
        
        _alloc(szX, szY);

        for ( size_t i = 0; i < szX; ++i ) {
                for ( size_t j = 0; j < szY; ++j ) {
                        *(*(array + i) + j) = obj(i, j);
                }
        }
}

template <class T>
Matrix<T>& Matrix<T>::operator= (Matrix<T> const& obj)
{
        if ( this == &obj )
                return *this;
        
        size_t szX = obj.sizeX();
        size_t szY = obj.sizeY();
        
        resize(szX, szY);

        for ( size_t i = 0; i < szX; ++i ) {
                for ( size_t j = 0; j < szY; ++j ) {
                        *(*(array + i) + j) = obj(i, j);
                }
        }

        return *this;
}

template <class T>
void Matrix<T>::resize(size_t row, size_t col)
{
        _delete();
        _alloc(row, col);
}

template <class T>
void Matrix<T>::fill()
{
        for ( size_t i = 0; i < rows; ++i ) {
                for ( size_t j = 0; j < columns; ++j ) {
                        *(*(array + i) + j) =
                        std::rand() * 15 % 19;
                }
        }
}

template <class T>
T Matrix<T>::operator* ()
{
        if ( rows != columns ) {
                std::cout << "Wrong matrix size!\n";
                return 0;
        }
        else if ( rows == 1 ) {
                return **array;
        }

        std::vector<std::vector<T>> vec(rows);

        for ( size_t i = 0; i < rows; ++i ) {
                for ( size_t j = 0; j < columns; ++j ) {
                        vec[i].push_back(array[i][j]);
                }
        }

        return _determinate(vec);
}

template <class T>
T Matrix<T>::_determinate(std::vector<std::vector<T>> det)
{
        T dt = 0;
        size_t size = det.size();
        if ( size == 2 ) {
                return det[0][0] * det[1][1] - det[0][1] * det[1][0];
        }
        size_t j;
        std::vector<std::vector<T>> vec(size - 1);
        for (size_t i = 0; i < size; ++i) {
                for (j = 0; j < size - 1; ++j) {
                        if (j < i) {
                                vec[j] = det[j];
                        }
                        else {
                                vec[j] = det[j + 1];
                        }
                }
                dt += pow(double(-1), (i + j)) * _determinate(vec) * det[i][size - 1];
        }

        return dt;
}

template <class T>
Matrix<T> const& Matrix<T>::operator+ () const
{
        return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator- ()
{
        Matrix<T> temp(rows, columns);
        
        for ( size_t i = 0; i < rows; ++i ) {
                for ( size_t j = 0; j < columns; ++j ) {
                        temp(i, j) = -(*(*(array + i) + j));
                }
        }

        return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator* (Matrix<T> const& obj)
{
        size_t szX = this->sizeX();
        size_t szY =   obj.sizeY();
        size_t sz  =       columns;

        Matrix<T> temp(szX, szY);

        if ( this->sizeY() != obj.sizeX() ) {
                std::cout << "matrices can`t be multiplied\n";
                return temp;
        }
        
        for ( size_t i = 0; i < szX; ++i ) {
                for ( size_t j = 0; j < szY; ++j ) {
                        for ( size_t k = 0; k < sz; ++k ) {
                                temp(i, j) +=
                                *(*(array + i) + k) *
                                obj(k, j);
                        }
                }
        }

        return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator* (T const& obj)
{
        Matrix<T> temp(rows, columns);

        for ( size_t i = 0; i < rows; ++i ) {
                for ( size_t j = 0; j < columns; ++j ) {
                        temp(i, j) =
                        *(*(array + i) + j) * obj;
                }
        }

        return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator+ (Matrix<T> & obj)
{
        if ( sizeX() != obj.sizeX() &&
             sizeY() != obj.sizeY() ) {
                std::cout << "matrices can`t be added\n";
                return Matrix();
        }

        Matrix<T> temp(rows, columns);
        
        for ( size_t i = 0; i < rows; ++i ) {
                for ( size_t j = 0; j < columns; ++j ) {
                        temp(i, j) = 
                        (*(*(array + i) + j)) + obj(i, j);
                }
        }

        return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator- (Matrix<T> & obj)
{
        if ( sizeX() != obj.sizeX() &&
             sizeY() != obj.sizeY() ) {
                std::cout << "matrices can`t be added\n";
                return Matrix();
        }

        Matrix<T> temp(rows, columns);
        
        for ( size_t i = 0; i < rows; ++i ) {
                for ( size_t j = 0; j < columns; ++j ) {
                        temp(i, j) = 
                        (*(*(array + i) + j)) - obj(i, j);
                }
        }

        return temp;
}

template <class T>
T& Matrix<T>::operator() (size_t i, size_t j) const
{
        return *(*(array + i) + j);
}

template <class T>
void Matrix<T>::_alloc(size_t row, size_t col)
{
        rows = row;
        columns = col;
        array = new T* [row];
        for ( size_t i = 0; i < row; ++i ) {
                *(array + i) = new T [col];
                for ( size_t j = 0; j < col; ++j ) {
                        *(*(array + i) + j) = 0;
                }
        }
}

template <class T>
void Matrix<T>::_delete()
{
        if ( array == nullptr )
                return;

        for ( size_t i = 0; i < rows; ++i ) {
                delete[] array[i];
        }
        delete array;
        array = nullptr;
        columns = 0;
        rows = 0;
}
