#include <stdexcept>
#include <vector>

template<typename T> class list;

template<typename N>
class list_iterator
{
    N *pos;
    template<typename T> friend class list;
public:
    typedef typename N::value_type value_type;
    typedef typename N::reference_type reference_type;
    typedef typename N::const_reference_type const_reference_type;
    typedef list_iterator<N> self_type;

    list_iterator() : pos(0) {}
    list_iterator(N *pos) : pos(pos) {}

    bool operator != (self_type const &right) const {
        return pos != right.pos;
    }

    bool operator == (self_type const &right) const {
        return pos == right.pos;
    }

    self_type& operator ++ ()
    {
        if (pos) { pos = pos->next; }
        return *this;
    }
    reference_type operator * () throw (std::runtime_error) {
        if (pos) { 
            return pos->value;
        } else {
            throw (std::runtime_error("dereferenceing null iterator!"));
        }
    }
};

template<typename T>
struct list_node {
    typedef T value_type;
    typedef T& reference_type;
    typedef const T& const_reference_type;

    T value_;
    list_node *prev_;
    list_node *next_;

    list_node(T const &value, list_node *prev, list_node *next) :
        value_(value),
        prev_(prev),
        next_(next)
    {
    }
};

template<typename T>
class list
{
    typedef list_node<T> node_type;
    node_type *head_;
public:
    typedef T value_type;
    typedef list_iterator<node_type> iterator;

    list() :
        head_()
    {
    }

    ~list()
    {
        while(head_)
        {
            node_type *n = head_;
            head_ = head_->next_;
            delete n;
        }
    }

    void push_front(T const &v)
    {
        head_ = new node_type(v, 0, head_);
        if (head_->next_) {
            head_->next_->prev_ = head_;
        }
    }

    void pop_front(T const &v) {
        if (head_) {
            node_type *n = head_;
            head_ = head_->next_;
            head_->prev_ = 0;
            delete n;
        }
    }

    void insert(iterator it, T const &v)
    {
        node_type *n = it.pos;
        if (n) {
            node_type *new_node = new node_type(v, n, n->next_);
            new_node->next_->prev_ = new_node;
            n->next_ = new_node;
        }
    }

    void erase(iterator &it)
    {
        node_type *n = it.pos;
        ++it;
        if (n) {
            if (n->next_) {
                n->next_->prev_ = n->prev_;
            }
            if (n->prev_) {
                n->prev_->next_ = n->next_;
            }
            if (head_ == n) {
                head_ = n->next_;
            }
            delete n;
        }
    }

    bool is_empty() const { return head_ == 0; }

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(); }
};
