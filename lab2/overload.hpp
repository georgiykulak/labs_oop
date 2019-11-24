#pragma once

/*
		Definition
*/

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

/*
		Implementation
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
