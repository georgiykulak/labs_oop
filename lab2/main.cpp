//Если будут проблемы с удалением объекта - юзать шаредптр
//Сделать правильную перегрузку []
//Добавить транспонирование
//Добавить деление
//Добавить итератор и поменять все пробежки по матрице на пробежке по итераторам итераторов

#include <iostream>
#include <cmath>

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
        T _determinate1(Matrix<T> det);
        T _determinate2(Matrix<T> det);
        
        public:
        Matrix<T> const& operator+ () const;
        Matrix<T> operator- ();
        Matrix<T> operator* (Matrix<T> const& obj);
        Matrix<T> operator* (T const& obj);
        Matrix<T> operator+ (Matrix<T> & obj);
        Matrix<T> operator- (Matrix<T> & obj);
        T& operator() (size_t i, size_t j) const;             // [][]
        Matrix<T>& operator() (T*  arr);
        Matrix<T>& operator() (T** det);

        private:
        void _alloc(size_t row, size_t col);
        void _delete();
};

//template <class F>
//Matrix<F>& operator* (F const& obj, Matrix<F> & obj);

template <class F>
std::istream& operator>>
        (std::istream&  in, Matrix<F> & obj);

template <class F>
std::ostream& operator<<
        (std::ostream& out, Matrix<F> /*const*/& obj);

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
        Matrix<int> det1(3, 4);
        det1.fill();
        std::cout << det1 << "\n";
        Matrix<int> det2(4, 5);
        det2.fill();
        std::cout << det2 << "\n";
        Matrix<int> det3 = det1 * det2;
        std::cout << det3 << "\n";
        
        Matrix<double> det(4, 4);
        det.fill();
        std::cout << det  << "\n";
        std::cout << *det << "\n";
        return 0;
}

template <class T>
Matrix<T>::Matrix(size_t row, size_t col)
{
        //попробовать быстрый метод со степика
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
        else if (rows == 1) {
                return **array;
        }
        
        return _determinate2(*this);
}

template <class T>
T Matrix<T>::_determinate1(Matrix<T> det) //make with no recursion
{
        //                                                      finished here
}

template <class T>
T Matrix<T>::_determinate2(Matrix<T> det) //doesn`t work
{
        size_t sz = det.sizeX() - 1;
        T dt = 0;
        T pref;
        T  swp;
        
        if ( sz == 1 ) {
                return det(0, 0) * det(1, 1) - 
                       det(0, 1) * det(1, 0);  //вычисление
        }
        
        for ( size_t k = 0; k < sz + 1; ++k ) {
                Matrix<T> temp(sz, sz);
                size_t m = 0;
                size_t n = 0;

                pref = det(0, k);

                for ( size_t i = 1; i < sz; ++i ) {
                        for ( size_t j = 0; j < k; ++j ) {
                                swp =  det(i, j);
                                temp(m, n) = swp;
                                ++n;
                        }
                        for ( size_t j = k + 1; j < sz; ++j ) {
                                swp =  det(i, j);
                                temp(m, n) = swp;
                                ++n;
                        }
                        ++m;
                }
                
                dt += pref * ( k % 2 ?
                (-_determinate2(temp)):
                  _determinate2(temp)
                );
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
Matrix<T> Matrix<T>::operator* (Matrix<T> const& obj) //позже сделать деление
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
Matrix<T>& Matrix<T>::operator() (T* arr)
{
        if ( arr == nullptr )
                return *this;

        size_t size = sizeof(arr) / sizeof(T);
        size_t sz;

        if ( std::pow(sz = std::sqrt(size), 2) == size ) {
                std::cout << "Wrong size of determinant\n";
                return *this;
        }

        resize(sz, sz);

        for ( size_t i = 0, c = 0; i < sz; ++i, ++c ) {
                for ( size_t j = 0; j < sz; ++j, ++c ) {
                        *(*(array + i) + j) = *(arr + c);
                }
        }
        
        return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator() (T** det)
{
        if ( det == nullptr )
                return *this;
        
        size_t size = sizeof(det) / sizeof(T*);
        size_t sz = size;
        
        for ( size_t i = 0; i < sz; ++i ) {
                if ( sz != sizeof(*det) / sizeof(T) ) {
                        std::cout << "error\n";
                        return *this;
                }
        }

        //////////////////////////////////////////////        filling

        return *this;
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
        (std::ostream& out, Matrix<F> /*const*/& obj)
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
