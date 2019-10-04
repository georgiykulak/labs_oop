#include <iostream>

template <class T>
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
        RingList(RingList const & obj);
        T& getCurrent() const;
        T popCurrent();
        T& setCurrent(std::istream obj = std::cin);
        T& changeCurrent(T new_data);
        void insertAfterCurrent();
        void insertBeforeCurrent();
        void moveLeft();
        void moveRight();
 
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
        Bead* temp;               //
        
        while ( curr->next != curr) {
                temp = curr;
                curr = curr->next;
                temp = temp->prev;
                delete temp->next;
                temp->next = curr;
                curr->prev = temp;//
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
        Bead* temp = curr;//

        curr = curr->next;
        temp = temp->prev;
        delete temp->next;
        temp->next = curr;
        curr->prev = temp;//

        return tempdata;
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
