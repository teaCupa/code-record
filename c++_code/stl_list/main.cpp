#include <stdio.h>

///////////////////////////////////////  list.h  ////////////////////////////

#include <assert.h>
#include <utility>   // for std::move and initializer_list

namespace learnstl
{

    template <class T>
    struct _list_node
    {
        _list_node* next;
        _list_node* prev;
        T value_;

        _list_node() : value_() {}
        _list_node(const T& x) : value_(x) {}
        _list_node(T&& x) : value_(std::move(x)) {}
    };

    template <class T>
    class iterator
    {
        typedef _list_node<T> list_node;
    public:
        iterator(list_node* n = nullptr) : node_(n) {}
        T& operator*() { return *operator->(); }
        T* operator->() { return &static_cast<list_node*>(node_)->value_; }
        iterator& operator++() { node_ = node_->next; return *this; }
        iterator operator++(int) { iterator old = *this; operator++(); return old; }
        iterator& operator--() { node_ = node_->prev; return *this; }
        iterator operator--(int) { iterator old = *this; operator--(); return old; }
        bool operator==(iterator rhs) const { return node_ == rhs.node_; }
        bool operator!=(iterator rhs) const { return node_ != rhs.node_; }

    private:
        list_node* node_;
    };

    template <class T>
    class const_iterator
    {
        typedef _list_node<T> list_node;
    public:
        const_iterator(const list_node* n = nullptr) : node_(n) {}
        const T& operator*() { return *operator->(); }
        const T* operator->() { return &static_cast<const list_node*>(node_)->value_; }
        const_iterator& operator++() { node_ = node_->next; return *this; }
        const_iterator operator++(int) { const_iterator old = *this; operator++(); return old; }
        const_iterator& operator--() { node_ = node_->prev; return *this; }
        const_iterator operator--(int) { const_iterator old = *this; operator--(); return old; }
        bool operator==(const_iterator rhs) const { return node_ == rhs.node_; }
        bool operator!=(const_iterator rhs) const { return node_ != rhs.node_; }

    private:
        const list_node* node_;
    };


    ///   队头   |---|  <---  ...  |---|  队尾
    ///         |---|  --->  ...  |---|
    ///           ^                 ^               初始时，head_的prev和next都指向自身
    ///           | next            | prev
    ///         head_ --------------
    template <typename T>
    class list
    {

    public:
        typedef _list_node<T> list_node;
        typedef iterator<T> iterator;
        typedef const_iterator<T> const_iterator;

        list() { empty_init(); }

        ~list()
        {
            for (list_node* n = head_->next; n != head_;)
            {
                list_node* tmp = n;
                n = n->next;
                delete tmp;
            }
            head_->prev = head_;
            head_->next = head_;
            delete head_;
        }

        list(const list& rhs)  {
            empty_init();
            for (auto it=rhs.begin(); it != rhs.end(); ++it)
                push_back(*it);
        }
        list(list&& rhs) { empty_init(); take_over(rhs); }
        list& operator=(list rhs) {
            swap(rhs);   return *this;  //rhs析构
        }

        explicit list(size_t n)
        {
            empty_init();
            for (size_t i = 0; i < n; ++i)
                insert_node(head_, new list_node);
            size_ = n;
        }

        list(size_t n, const T& value)
        {
            empty_init();
            for (size_t i = 0; i < n; ++i)
                push_back(value);
        }

        template <typename InputIterator>
        list(InputIterator first, InputIterator last)
        {
            empty_init();
            initialize(first, last, typename std::is_integral<InputIterator>::type());
        }

        list(std::initializer_list<T> il) :list(il.begin(), il.end()) {}

        void swap(list& rhs)
        {
            list tmp(std::move(rhs));   //move构造, 临时变量tmp, 函数结束时析构
            rhs.take_over(*this);
            take_over(tmp);
        }

        iterator begin() { return (list_node*)(head_->next); }
        const_iterator begin() const { return (list_node*)(head_->next); }
        iterator end() { return (list_node*)(head_); }
        const_iterator end() const { return (list_node*)(head_); }

        void push_front(T x)
        {
            list_node* n = new list_node(std::move(x));
            insert_node(head_->next, n);
            size_++;
        }

        void push_back(const T& x)
        {
            list_node* n = new list_node(x);
            insert_node(head_, n);
            size_++;
        }

        T& front()
        {
            return *begin();
        }

    private:
        list_node* head_;
        size_t size_;

        void empty_init(){
            head_ = new list_node;
            head_->next = head_;
            head_->prev = head_;
            size_ = 0;
        }


        void init_head()
        {
            head_->next = head_;
            head_->prev = head_;
        }

        void insert_node(list_node* pos, list_node* n)
        {
            n->next = pos;
            n->prev = pos->prev;
            pos->prev->next = n;
            pos->prev = n;
        }

        void take_over(list& rhs)
        {
            assert(size_ == 0);
            assert(head_->next == head_);
            assert(head_->prev == head_);

            if (rhs.size_ > 0)
            {
                head_->next = rhs.head_->next;
                head_->prev = rhs.head_->prev;
                head_->next->prev = head_;
                head_->prev->next = head_;
                rhs.init_head();
                size_ = rhs.size_;
                rhs.size_ = 0;
            }
        }

        template <typename InputIterator>
        void initialize(InputIterator first, InputIterator last, std::false_type)
        {
            for (; first != last; ++first)
                push_back(*first);
        }

        template <typename Integer>
        void initialize(Integer n, Integer value, std::true_type)
        {
            for (Integer i = 0; i < n; ++i)
                push_back(value);
        }
    };

}  // namespace learnstl

///////////////////////////////////////  main()  ////////////////////////////

#include <memory>
#include <string>

int main()
{
    learnstl::list<int> li(3, 8);    //list带参构造
    li.push_front(43);
    li.push_front(82);
    li.push_back(19);

    learnstl::list<int> lic(li);    //list(const list& rhs)拷贝构造->list带参构造,

    for (auto x : li)    //调用begin
        printf("%d\n", x);
//    for(learnstl::list<int>::iterator it=li.begin();it !=li.end();++it){
//        printf("%d\n", *it);
//    }

    learnstl::list<int> lim(std::move(lic));   //move构造

    lic = lim;                   //operator=构造

    int arr[3] = { 1, 2, 3};
//    learnstl::list<int> lia(arr, arr+3);
    learnstl::list<int> lia({1,2,3});
    for (auto x : lia)
        printf("%d\n", x);

    learnstl::list<std::string> ls;
    ls.push_front("hello");
    printf("front=%s\n", ls.front().c_str());

    learnstl::list<std::unique_ptr<double>> lu(5);
    lu.push_front(std::unique_ptr<double>(new double(5.0)));  // make_unique in C++14
    printf("front=%f\n", *lu.front());
}