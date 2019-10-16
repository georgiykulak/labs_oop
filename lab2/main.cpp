//Сделать праавильную перегрузку []

#include <iostream>

template <class T>
struct Matrix {
        private:
        T** array;
        size_t    rows;
        size_t columns;

        public:
        Matrix(size_t row = 1, size_t col = 1);
        ~Matrix();
        T operator* ();
        Matrix<T> const& operator+ () const;
        Matrix<T>& operator- ();
        Matrix<T>& operator* (Matrix<T> & obj);
        Matrix<T>& operator* (T const& obj);
        Matrix<T>& operator+ (Matrix<T> & obj);
        T& operator() (size_t i, size_t j);             // []
        Matrix<T>& operator() (...);

};

//template <class F>
//Matrix<F>& operator* (F const& obj, Matrix<F> & obj);

template <class F>
std::istream& operator>>
        (std::istream&  in, Matrix<F> & obj);

template <class F>
std::ostream& operator<<
        (std::ostream& out, Matrix<F> const& obj);

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
        

        return 0;
}

template <class T>
Matrix::Matrix(size_t row = 1, size_t col = 1) :
   rows{row},
columns{col}
{
        //попробовать быстрый метод со степика
        array = new T* [row];
        for ( size_t i = 0; i < row; ++i ) {
                array[i] = new T [col];
        }
}

template <class T>
Matrix::~Matrix()
{
        for ( auto i = 0; i < rows; ++i ) {
                delete[] array;
        }
        delete array;
}
/*
template <class F>
Matrix<F>& operator* (F const& obj, Matrix<F> & obj)
{
        //////////////////////
        return obj;
}
*/
template <class F>
std::istream& operator>>
        (std::istream&  in, Matrix<F> & obj)
{
        for ( auto i = 0; i < rows; ++i ) {
                for ( auto j = 0; j < columns; ++j ) {
                        in >> obj(i, j);
                }
        }
        return  in;
}

template <class F>
std::ostream& operator<<
        (std::ostream& out, Matrix<F> const& obj)
{
        for ( auto i = 0; i < rows; ++i ) {
                for ( auto j = 0; j < columns; ++j ) {
                        out << obj(i, j) << "\t";
                }
                out << endl;
        }
        return out;
}


template <class F>
bool operator<
(Matrix<F> const& obj1, Matrix<F> const& obj2)
{
        //////////////////////////////////////
        return false;
}

template <class F>
bool operator==
(Matrix<F> const& obj1, Matrix<F> const& obj2)
{
        //////////////////////////////////////
        return false;
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
