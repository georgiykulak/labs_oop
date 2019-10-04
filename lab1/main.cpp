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
        std::string getList() const;
        T& getCurrent() const;
        T popCurrent();
        T& setCurrent(std::istream obj = std::cin);
        T& changeCurrent(T new_data);
        void moveLeft();
        void moveRight();
        void insertAfterCurrent();
        void insertBeforeCurrent();
};

int main()
{
        RingList<int> obj(3);

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
                /*head = new Node;
                head->prev = nullptr;
                head->next = nullptr;
                end = head;
                curr = head;
                curr->data = filler;*/
                for ( auto i = size; i; --i ) {      //iteration summ == size - 1
                        temp = new Bead;
                        temp->next = head;
                        temp->prev = curr;
                        head->prev = temp;
                        curr->next = temp;
                        curr = curr->next;
                        std::cin >> curr->data;
                        /*Node* temp = new Node;
                        temp->prev = end;
                        temp->next = nullptr;
                        end->next = temp;
                        end = end->next;
                        end->data = filler;*/
                }
        }
}

template <class T>
RingList<T>::~RingList()
{
        Bead* temp;
        while ( curr->next != curr) {
                temp = curr;
                curr = curr->next;
                temp = temp->prev;
                delete temp->next;
                temp->next = curr;
                curr->prev = temp;
        }
        delete curr;
}
