#pragma once

#include <iostream>
#include <vector>
#include <string>

/**********************************************
				Definition
**********************************************/

template <class T = long double>
struct RingList {
        public:
        ~RingList();
        RingList(size_t size = 0);
        RingList(RingList<T> & obj);
        RingList& operator=(RingList const & obj); // realise soon
        RingList(std::vector<T> const& vec);
        RingList(T* const arr, size_t size);
        T getCurrent() const;
        T popCurrent();
        void getList();
        T& setCurrent(std::istream& obj = std::cin);
        T& changeCurrent(T new_data);
        void insertAfterCurrent(T new_data);
        void insertBeforeCurrent(T new_data);
        void appendCurrent(T new_data);
        void moveLeft();
        void moveRight();
        bool empty();
        size_t count();
        bool compare(RingList<T> & obj);
        bool compare_all(RingList<T> & obj);
        
        T operator>  (T& obj);
        T operator>> (T& obj);
        T operator<< (T& obj);
        
        template <class F>
        friend const F& operator++ (RingList<F> & obj);
        
        template <class F>
        friend const F& operator-- (RingList<F> & obj);
        
        template <class F>
        friend F operator++ (RingList<F> & obj, int);
        
        template <class F>
        friend F operator-- (RingList<F> & obj, int);

        operator std::vector<T>();
        
        operator T*();

        private:
        struct Bead {
                Bead* prev;
                Bead* next;
                T data;
        } *curr;
        
        void _deleteCurrent();
        void _makeCurrent(T new_data);
};

template <class F>
std::istream& operator>>
        (std::istream&  in, RingList<F> & obj);

template <class F>
std::ostream& operator<<
        (std::ostream& out, RingList<F> const& obj);

template <class F>
bool operator<
(RingList<F> const& obj1, RingList<F> const& obj2);

template <class F>
bool operator>
(RingList<F> const& obj1, RingList<F> const& obj2);

template <class F>
bool operator<=
(RingList<F> const& obj1, RingList<F> const& obj2);

template <class F>
bool operator>=
(RingList<F> const& obj1, RingList<F> const& obj2);

template <class F>
bool operator==
(RingList<F> const& obj1, RingList<F> const& obj2);

template <class F>
bool operator!=
(RingList<F> const& obj1, RingList<F> const& obj2);

/**********************************************
				Implementation
**********************************************/

template <class T>
RingList<T>::~RingList()
{
        if ( curr ) {
                while ( curr->next != curr) {
                        _deleteCurrent();
                }
                delete curr; 
        }
}

template <class T>
RingList<T>::RingList(size_t size) :
        curr{nullptr}
{
        if ( size-- ) {
                Bead* temp; 
                Bead* head;
                curr = new Bead;
                curr->prev = curr;
                curr->next = curr;
                std::cin >> curr->data;
                head = curr;
                for ( auto i = size; i; --i ) {    //iteration summ == size - 1
                        temp = new Bead;
                        temp->next = head;
                        temp->prev = curr;
                        head->prev = temp;
                        curr->next = temp;
                        curr = curr->next;
                        std::cin >> curr->data;
                }
        }
}

template <class T>
RingList<T>::RingList(RingList<T> & obj) :
        curr{nullptr}
{
        if ( !obj.empty() ) {
                obj.moveRight();
        
                for ( auto i = obj.count(); i; --i ) {
                        _makeCurrent(obj.getCurrent());
                        obj.moveRight();
                }
        
                obj.moveLeft();
        }
}

template <class T>
RingList<T>::RingList(std::vector<T> const& vec) :
        curr{nullptr}
{
        if ( vec.empty() )
                std::cerr << "empty vector\n";

        for ( auto const& elem: vec ) {
                _makeCurrent(elem);
        }
}

template <class T>
RingList<T>::RingList(T* const arr, size_t size) :
        curr{nullptr}
{
        if ( arr == nullptr )
                std::cerr << "empty array\n";

        for ( size_t i = 0; i < size; ++i ) {
                _makeCurrent(*(arr + i));
        }
}

template <class T>
inline T RingList<T>::getCurrent() const
{
        if ( !curr )
                return 0;
        return curr->data;
}

template <class T>
inline T RingList<T>::popCurrent()
{
        if ( !curr )
                return 0;
        
        T tempdata = curr->data;
        
        _deleteCurrent();

        return tempdata;
}

template <class T>
inline void RingList<T>::getList()
{
        moveRight();
        for ( auto i = count(); i; --i ) {
                std::cout << getCurrent() << " ";
                moveRight();
        }
        moveLeft();
        std::cout << "\n";
}

template <class T>
inline T& RingList<T>::setCurrent(std::istream& obj)
{
        T tempdata;
        obj >> tempdata;
        _makeCurrent(tempdata);
        return curr->data;
}

template <class T>
inline T& RingList<T>::changeCurrent(T new_data) {
        curr->data = new_data;
        return     curr->data;
}

template <class T>
inline void RingList<T>::insertAfterCurrent(T new_data)
{
        appendCurrent(new_data);
}

template <class T>
inline void RingList<T>::insertBeforeCurrent(T new_data)
{
        moveLeft();
        appendCurrent(new_data);
}

template <class T>
inline void RingList<T>::appendCurrent(T new_data)
{
        _makeCurrent(new_data);
}

template <class T>
inline void RingList<T>::moveLeft()
{
        curr = curr->prev;
}

template <class T>
inline void RingList<T>::moveRight()
{
        curr = curr->next;
}

template <class T>
inline bool RingList<T>::empty()
{
        return curr == nullptr;
}

template <class T>
inline size_t RingList<T>::count()
{
        if ( empty() )
                return 0;
        
        Bead* temp = curr->prev;
        size_t counter = 0;

        while ( temp != curr ) {
                ++counter;
                moveRight();
        }

        moveRight();

        return counter + 1;
}

template <class T>
inline bool RingList<T>::compare(RingList<T> & obj)
{
        if ( empty() && obj.empty() )
                return true;
        
        if ( !empty() &&  obj.empty() ||
              empty() && !obj.empty()    )
                return false;
        
        Bead* temp = curr->prev;
        size_t counter = 0;

        while ( temp != curr ) {
                if ( curr->data != obj.getCurrent() ) {
                        for ( auto i = counter; i; --i ) {
                                moveLeft();
                                obj.moveLeft();
                        }
                        
                        return false;
                }

                ++counter;
                moveRight();
                obj.moveRight();
        }
        
        moveRight();
        obj.moveRight();
        
        return true;
}

template <class T>
inline bool RingList<T>::compare_all(RingList<T> & obj)
{
        if ( empty() && obj.empty() )
                return true;
        
        if ( !empty() &&  obj.empty() ||
              empty() && !obj.empty()    )
                return false;
        
        Bead* temp = curr->prev;
        size_t counter = 0;

        while ( temp != curr ) {
                if ( compare(obj) ) {
                        for ( auto i = counter; i; --i ) {
                                moveLeft();
                        }
                        
                        return true;
                }

                ++counter;
                moveRight();
        }
        
        if ( compare(obj) ) {
                moveRight();
                
                return true;
        }

        moveRight();

        return false;
}

template <class T>
inline void RingList<T>::_deleteCurrent()
{
        Bead* temp = curr;

        curr = curr->next;
        temp = temp->prev;
        delete temp->next;
        temp->next = curr;
        curr->prev = temp;
}

template <class T>
inline void RingList<T>::_makeCurrent(T new_data)
{
        if ( curr ) {
                Bead* temp; 
                Bead*  end;

                temp =   new Bead;
                end  = curr->next;
                temp->prev = curr;
                temp->next =  end;
                curr->next = temp;
                end->prev  = temp;
                curr = curr->next; 
        }
        else {
                curr =   new Bead;
                curr->prev = curr;
                curr->next = curr;
        }

        curr->data = new_data;
}

template <class T>
T RingList<T>::operator>  (T& obj)
{
        return obj = getCurrent();
}

template <class T>
T RingList<T>::operator>> (T& obj)
{
        return obj = popCurrent();
}

template <class T>
T RingList<T>::operator<< (T& obj)
{
        appendCurrent(obj);
        return obj;
}

template <class F>
const F& operator++ (RingList<F> & obj)
{
        obj.moveLeft();
        return obj.getCurrent();
}

template <class F>
const F& operator-- (RingList<F> & obj)
{
        obj.moveRight();
        return obj.getCurrent();
}

template <class F>
F operator++ (RingList<F> & obj, int)
{
        obj.moveLeft();
        return obj.getCurrent();
}

template <class F>
F operator-- (RingList<F> & obj, int)
{
        obj.moveRight();
        return obj.getCurrent();
}

template <class F>
std::istream& operator>>
        (std::istream&  in, RingList<F> & obj)
{
        obj.setCurrent(in);
        return  in;
}

template <class F>
std::ostream& operator<<
        (std::ostream& out, RingList<F> const& obj)
{
        out << obj.getCurrent();
        return out;
}

template <class F>
bool operator<
(RingList<F> const& obj1, RingList<F> const& obj2)
{
        return  obj1.getCurrent() < obj2.getCurrent();
}

template <class F>
bool operator>
(RingList<F> const& obj1, RingList<F> const& obj2)
{
        return  obj1.getCurrent() > obj2.getCurrent();
}

template <class F>
bool operator<=
(RingList<F> const& obj1, RingList<F> const& obj2)
{
        return obj1.getCurrent() <= obj2.getCurrent();
}

template <class F>
bool operator>=
(RingList<F> const& obj1, RingList<F> const& obj2)
{
        return obj1.getCurrent() >= obj2.getCurrent();
}

template <class F>
bool operator==
(RingList<F> const& obj1, RingList<F> const& obj2)
{
        return obj1.getCurrent() == obj2.getCurrent();
}

template <class F>
bool operator!=
(RingList<F> const& obj1, RingList<F> const& obj2)
{
        return obj1.getCurrent() != obj2.getCurrent();
}

template <class T>
RingList<T>::operator std::vector<T>()
{
        std::vector<T> vec;
        
        for ( auto i = this->count(); i; --i ) {
                vec.push_back(this->getCurrent());
                this->moveRight();
        }
        
        return vec;
}

template <class T>
RingList<T>::operator T*()
{
        auto size = this->count();
        T* arr = new T [size];
        
        for ( auto i = 0; i < size; ++i ) {
                *(arr + i) = this->getCurrent();
                this->moveRight();
        }
        
        return arr;
}
