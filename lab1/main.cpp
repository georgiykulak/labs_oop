#include <iostream>

template <class T = long double>
struct RingList {
        private:
        struct Node {
                Node* prev;
                Node* next;
                T data;
        } *head,
           *end,
          *curr;

        public:
        RingList(size_t size = 0, 
                 T filler = static_cast<T>(0));
        RingList(RingList const & obj);
        ~RingList();
        std::string getList();
        T& getCurrent();
        T popCurrent();
        T& changeCurrent(T new_data);
        void moveLeft();
        void moveRight();
        void insertAfterCurrent();
        void insertBeforeCurrent();
};

int main()
{
        

        return 0;
}

template <class T>
RingList<T>::RingList(size_t size, T filler)
{
        if ( size-- ) {
                head = new Node;
                head->prev = nullptr;
                head->next = nullptr;
                end = head;
                curr = head;
                curr->data = filler;
                for ( auto i = size; i; --i ) {
                        Node* temp = new Node;
                        temp->prev = end;
                        temp->next = nullptr;
                        end->next = temp;
                        end = end->next;
                        end->data = filler;
                }
        }
}


