//Добавить вывод ошибок при неправильной работе с классом

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
        RingList(std::vector<T> const& vec);
        RingList(T* const arr, size_t size);
        //RingList& operator=(RingList const & obj);
        T& getCurrent() const;
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

        private:
        void _deleteCurrent();
        void _makeCurrent(T new_data);
};

inline void print(std::string s)
{
        std::cout << s << std::endl;
}

inline void tilda()
{
std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

int main()
{
        tilda();
        print("~~~~~~THE TESTBENCH IS STARTING...~~~~~~");
        tilda();
        tilda();
        tilda();
        print("Test 1: Default constructor");
        tilda();

        RingList<int> ring1;
        
        if ( ring1.empty() ) 
                print("ring1 is empty now");
        print("Adding three elements");
        ring1.appendCurrent(13);
        ring1.appendCurrent(24);
        ring1.appendCurrent(356);
        print("Getting elements of ring1");
        ring1.getList();
        tilda();
        print("Test 2: Copy constructor");
        tilda();
        
        RingList<int> ring2(ring1);
        
        if ( !ring2.empty() )
                print("ring2 is not empty");
        print("Getting elements of ring2");
        ring2.getList();
        tilda();
        print("Test 3: Constructor with vector argument");
        tilda();

        std::vector<double> vctr{ 1.12, 4.25, -5.03, 23.4, 0.85 };
        RingList<double> ring3(vctr);
        
        print("Getting quantity of ring3 elements");
        std::cout << ring3.count() << "\n";
        print("Getting elements of ring3");
        ring3.getList();
        tilda();
        print("Test 4: Constructor with array argument");
        tilda();

        const size_t size = 4;
        unsigned* arr1(new unsigned [size]);
        for ( auto i = 0; i < size; ++i ) {
                arr1[i] = i + 1;
        }
        unsigned arr2[size] { 2, 4, 6, 8 };

        RingList<unsigned> r1(arr1, size);
        RingList<unsigned> r2(arr2, size);
        
        delete[] arr1;
        print("Getting ring r1 of first array");
        print("Getting with loop and \"moveRight()\"");
        for ( auto i = size; i; --i ) {
                std::cout
                << r1.getCurrent() 
                << " ";
                r1.moveRight();
        }
        print("");
        print("Analogically with function \"moveLeft()\"");
        for ( auto i = size; i; --i ) {
                std::cout
                << r1.getCurrent() 
                << " ";
                r1.moveLeft();
        }
        print("");
        tilda();
        print("Test 5: Poping and pushing elements");
        tilda();
        print("Poping");
        print("Getting ring r2 of second array");
        r2.getList();
        print("Appending");
        r2.appendCurrent(80);
        print("Getting ring r2 of second array");
        r2.getList();
        print("Inserting before current");
        r2.insertBeforeCurrent(60);
        print("Getting ring r2 of second array");
        r2.getList();
        print("Inserting after current");
        r2.insertAfterCurrent(70);
        print("Getting ring r2 of second array");
        r2.getList();
        tilda();
        print("Test 6: Comparing rings");
        tilda();
        
        RingList<int> ring6;
        
        print("Appending ring6");
        ring6.appendCurrent(13);
        ring6.appendCurrent(24);
        ring6.appendCurrent(356);
        print("Moving left the ring1");
        ring1.moveLeft();
        print("Getting elements of ring1");
        ring1.getList();
        print("Getting elements of ring6");
        ring6.getList();
        print("Comparing ring1 with ring6");
        if ( ring1.compare(ring6) )
                print("They are equal");
        else
                print("They are NOT equal");
        print("Comparing recursively");
        if ( ring1.compare_all(ring6) )
                print("They are equal");
        else
                print("They are NOT equal");
        tilda();
        tilda();
        tilda();
        print("~~~~~~~~~FINISH OF THE TESBENCH~~~~~~~~~");
        tilda();
        
        return EXIT_SUCCESS;
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
                std::cout << "empty vector\n"; //или по-другому вывести ошибку

        for ( auto const& elem: vec ) {
                _makeCurrent(elem);
        }
}

template <class T>
RingList<T>::RingList(T* const arr, size_t size) :
        curr{nullptr}
{
        if ( arr == nullptr )
                std::cout << "empty array\n"; //или по-другому вывести ошибку

        for ( size_t i = 0; i < size; ++i ) {
                _makeCurrent(*(arr + i));
        }
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
