//Переделать детерминирование (избавиться от векторов)
//Сделать деление матриц
//Сделать вместо (.. , ..) [..][..]
//Сделать оператор присваивания
//Сделать 5 файлов: main.cpp, source.hpp, source.cpp, testbench.hpp, testbench.cpp + Makefile
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>

template <class T>
struct Matrix {
        private:
        T** array;
        size_t    rows;
        size_t columns;

        public:
        Matrix(size_t row = 1, size_t col = 1);
        ~Matrix();
        Matrix(Matrix<T> const& obj);
        Matrix<T>& operator= (Matrix<T> const& obj);
        size_t sizeX() const {    return rows; }
        size_t sizeY() const { return columns; }
        void resize(size_t row, size_t col);
        void fill();
        T operator* ();
        
        private:
        T _determinate(std::vector<std::vector<T>> det); //переделать
        
        public:
        Matrix<T> const& operator+ () const;
        Matrix<T> operator- ();
        Matrix<T> operator* (Matrix<T> const& obj);
        Matrix<T> operator* (T const& obj);
        Matrix<T> operator+ (Matrix<T> & obj);
        Matrix<T> operator- (Matrix<T> & obj);
        T& operator() (size_t i, size_t j) const;

        private:
        void _alloc(size_t row, size_t col);
        void _delete();
};

template <class F>
std::istream& operator>>
        (std::istream&  in, Matrix<F> & obj);

template <class F>
std::ostream& operator<<
        (std::ostream& out, Matrix<F> obj);

template <class F>
bool operator<
(Matrix<F> const& obj1, Matrix<F> const& obj2);

template <class F>
bool operator==
(Matrix<F> const& obj1, Matrix<F> const& obj2);

template <class F>
bool operator>
(Matrix<F> const& obj1, Matrix<F> const& obj2);

template <class F>
bool operator<= 
(Matrix<F> const& obj1, Matrix<F> const& obj2);

template <class F>
bool operator>=
(Matrix<F> const& obj1, Matrix<F> const& obj2);

template <class F>
bool operator!=
(Matrix<F> const& obj1, Matrix<F> const& obj2);

int main()
{
        std::cout << "~~~~~TESTBENCH~~~~~\n";
        std::cout << "First matrix:\n";
        Matrix<int> det1(3, 4);
        det1.fill();
        std::cout << det1 << "\n";
        std::cout << "Second matrix:\n";
        Matrix<int> det2(4, 5);
        det2.fill();
        std::cout << det2 << "\n";
        std::cout << "Third matrix:\n";
        Matrix<int> det3;
        det3.resize(3, 5);
        det3.fill();
        std::cout << det3 << "\n";
        std::cout << "Multipling\n";
        Matrix<int> det4 = det1 * det2;
        std::cout << det4 << "\n";
        std::cout << "Adding third and fourth\n";
        std::cout << det4 + det3 << "\n";
        std::cout << "Determinating\n";
        Matrix<long> det(4, 4);
        det.fill();
        std::cout << det  << "\n";
        std::cout << *det << "\n";
        std::cout << "Comparing third and fourth\n";
        if ( det3 == det4 ) {
                std::cout << "equal\n";
        }
        if ( det3 != det4 ) {
                std::cout << "not equal\n";
        }
        if ( det3 < det4 ) {
                std::cout << "smaller\n";
        }
        else {
                std::cout << "bigger or equal\n";
        }

        return 0;
}

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

template <class F>
std::istream& operator>>
        (std::istream&  in, Matrix<F> & obj)
{
        size_t row = obj.sizeX();
        size_t col = obj.sizeY();

        for ( size_t i = 0; i < row; ++i ) {
                for ( size_t j = 0; j < col; ++j ) {
                        in >> obj(i, j);
                }
        }
        
        return  in;
}

template <class F>
std::ostream& operator<<
        (std::ostream& out, Matrix<F> obj)
{
        size_t row = obj.sizeX();
        size_t col = obj.sizeY();
        
        for ( size_t i = 0; i < row; ++i ) {
                for ( size_t j = 0; j < col; ++j ) {
                        out << obj(i, j) << "\t";
                }
                out << std::endl;
        }
        
        return out;
}

template <class F>
bool operator<
(Matrix<F> const& obj1, Matrix<F> const& obj2)
{
        return obj1.sizeX() * obj1.sizeY() <
               obj2.sizeX() * obj2.sizeY();
}

template <class F>
bool operator==
(Matrix<F> const& obj1, Matrix<F> const& obj2)
{
        return obj1.sizeX() * obj1.sizeY() ==
               obj2.sizeX() * obj2.sizeY();
}

template <class F>
bool operator>
(Matrix<F> const& obj1, Matrix<F> const& obj2)
{
        return !(obj1 < obj2) && !(obj1 == obj2);
}

template <class F>
bool operator<= 
(Matrix<F> const& obj1, Matrix<F> const& obj2)
{
        return !(obj1 > obj2);
}

template <class F>
bool operator>=
(Matrix<F> const& obj1, Matrix<F> const& obj2)
{
        return !(obj1 < obj2);
}

template <class F>
bool operator!=
(Matrix<F> const& obj1, Matrix<F> const& obj2)
{
        return !(obj1 == obj2);
}
