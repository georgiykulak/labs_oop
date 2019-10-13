#include <iostream>
#include <vector>

template <class T = long double>
struct RingList {
        private:
        struct Bead {
                Bead* prev;
                Bead* next;
                T data;
        } *curr;

        public:
        RingList(size_t size = 0);
        ~RingList();
        RingList(RingList<T> & obj);
        RingList(std::vector<T> const& vec);//////////////////////
        RingList(T* const arr);///////////////////////////////////
        //RingList& operator=(RingList const & obj);
        T& getCurrent() const;
        T popCurrent();
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

        private:
        void _deleteCurrent();
        void _makeCurrent(T new_data);
};

int main()
{
        /*
        size_t numb;
        std::cout << "First Test\n"; 
        std::cout << "Enter number of beads for constructor:\n";
        std::cin >> numb;
        RingList<int> obj(numb);
        std::cout << "Move right\n";
        for ( auto i = numb; i; --i ) {
                std::cout << obj.getCurrent() << "\n";
                obj.moveRight();
        }
        std::cout << "Move left\n";
        for ( auto i = numb; i; --i ) {
                std::cout << obj.getCurrent() << "\n";
                obj.moveLeft();
        }
        std::cout << "Pop\n";
        obj.popCurrent();
        //obj.setCurrent();
        for ( auto i = numb - 1; i; --i ) {
                std::cout << obj.getCurrent() << "\n";
                obj.moveRight();
        }
        std::cout << "Set\n";
        obj.setCurrent();
        for ( auto i = numb; i; --i ) {
                std::cout << obj.getCurrent() << "\n";
                obj.moveRight();
        }
        std::cout << "Triple loop\n";
        for ( auto i = numb * 3; i; --i ) {
                std::cout << obj.getCurrent() << " ";
                obj.moveRight();
        }
        std::cout << "\n";
        */
        //RingList<int> obj1(3);
        //RingList<int> obj2(obj1);
        
        RingList<int> obj1;
        //obj1.moveRight();
        RingList<int> obj2;
        if ( obj1.compare(obj2) ) std::cout << "true" << "\n";
        std::cout << obj1.count() << " " << obj2.count() << "\n";
        return 0;
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
                for ( auto i = size; i; --i ) {      //iteration summ == size - 1
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
RingList<T>::RingList(RingList & obj)
{
        //////////////////////////////////////////////////////////////////////////////////////////
}
/*
template <class T>
RingList<T>::RingList(std::vector<T> const& vec)
{
        //////////////////////////////////////////////////////////////////////////////////////////
}
*/
        
template <class T>
RingList<T>::RingList(T* const arr)
{
        //////////////////////////////////////////////////////////////////////////////////////////
}

template <class T>
inline T& RingList<T>::getCurrent() const
{
        return curr->data; //добавить позднее ошибку для случая когда curr == nullptr
}

template <class T>
inline T RingList<T>::popCurrent()
{
        T tempdata = curr->data;
        
        _deleteCurrent();

        return tempdata; //добавить позднее ошибку для случая когда curr == nullptr
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
        
        bool flag = true;
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
        
        return flag;
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
