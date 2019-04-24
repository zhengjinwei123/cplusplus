#include <cstdlib>
#include <iostream>
#include <stdexcept>

template<typename T>
class my_vector
{
    T *array_;
    unsigned size_;
    unsigned block_size_;
public:
    my_vector(unsigned block_size) :
        array_((T*)malloc(sizeof(T)*block_size)),
        size_(0),
        block_size_(block_size)
    {}
    ~my_vector() { 
        if (array_) 
        {
            free(array_);
        }
    }

    void push_back(T const &elem) throw (std::runtime_error)
    {
        if (size_ == block_size_) {
            block_size_ *= 2;
            T *new_array = (T*)realloc(array_, block_size_*sizeof(T));
            if (new_array) {
                array_ = new_array;
            } else {
                free(array_);
                array_ = NULL;
                throw std::runtime_error("Out of memory");
            }
        }
        array_[size_++] = elem;
    }
    T& operator[](unsigned i) { return array_[i]; }
    const T& operator[](unsigned i) const { return array_[i]; }
    unsigned get_mem_size() const { return block_size_ * sizeof(T); }
};

template<>
class my_vector<bool>
{
    int *array_;
    unsigned size_;
    unsigned block_size_;
    const static unsigned seg_size_;
public:
    my_vector(unsigned block_size = 1) :
        array_((int*)malloc(sizeof(int)*block_size)),
        size_(0),
        block_size_(block_size)
    {
    }
    ~my_vector(){ if (array_) {free(array_);}}
    void push_back(bool elem) throw (std::runtime_error) {
        if (size_ == block_size_*seg_size_) {
            block_size_ *= 2;
            int *new_array = (int*)realloc(array_, block_size_*sizeof(int));
            if (new_array) {
                array_ = new_array;
            } else {
                free(array_);
                array_ = NULL;
                throw std::runtime_error("Out of memory");
            }
        }
        set(size_++, elem);
    }

    void set(unsigned i, bool elem)
    {
        if (elem) {
            array_[i / seg_size_] |= (0x1 << (i % seg_size_));
        } else {
            array_[i / seg_size_] &= ~(0x1 << (i % seg_size_));
        }
    }

    bool operator[] (unsigned i) const {
        return (array_[i / seg_size_] & (0x1 << (i % seg_size_))) != 0;
    }

    unsigned get_mem_size() const { return block_size_ * sizeof(int); }
};

const unsigned my_vector<bool>::seg_size_ = sizeof(int) * 8;

int main()
{
    my_vector<char> vi(2);
    my_vector<bool> vb(2);
    for(unsigned i = 0; i < 20; ++i) {
        vi.push_back('a'+i);
        vb.push_back((i % 4) == 0);
    }
    using namespace std;
    cout<< "MemSize of my_vector<char> is " << vi.get_mem_size() << endl;
    cout<< "MemSize of my_vector<bool> is "<< vb.get_mem_size() << endl;

    for(size_t i = 0 ;i < 20; ++i) {
        cout<< ' ' << vi[i]; 
    }
    cout << endl;

    for(size_t i = 0; i < 20; ++i) {
        cout<< vb[i] << ' ';
    }
    cout << endl;
    return 0;
}