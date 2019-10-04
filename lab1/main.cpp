#include <iostream>

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
        //RingList(RingList const & obj);
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
        //Bead* _getPointer();
        //void _setPointer(Bead* elem);

        private:
        void _deleteCurrent();
        void _makeCurrent(T new_data);
};

int main()
{
        RingList<int> obj(3);
        for ( auto i = 3; i; --i ) {
                std::cout << obj.getCurrent() << "\n";
                obj.moveRight();
        }
        std::cout << "\n";
        obj.popCurrent();
        obj.setCurrent();
        for ( auto i = 3; i; --i ) {
                std::cout << obj.getCurrent() << "\n";
                obj.moveRight();
        }
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
        while ( curr->next != curr) {
                _deleteCurrent();
        }
        delete curr;
}

template <class T>
inline T& RingList<T>::getCurrent() const
{
        return curr->data;
}

template <class T>
inline T RingList<T>::popCurrent()
{
        T tempdata = curr->data;
        
        _deleteCurrent();

        return  tempdata;
}

template <class T>
inline T& RingList<T>::setCurrent(std::istream& obj)
{
        obj >> curr->data;
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
