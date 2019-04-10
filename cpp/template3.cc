#include <iostream>

template<typename T, template<typename> class Func>
void foreach(T array[], unsigned size)
{
    Func<T> func;
    for(unsigned i = 0; i < size; ++i) { func(array[i]); } 
}

template<typename T>
class inc
{
public:
    void operator()(T &v) const { ++v; }
};

template<typename T>
class dec1
{
public:
    void operator()(T &v) const { --v; }
};

template<typename T>
class print
{
public:
    void operator()(T &v) { std::cout << ' ' << v; }
};


int main(int argc, char **argv)
{
    using namespace std;

    int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    foreach<int, print>(array, 7);
    cout<< endl;

    foreach<int, inc>(array, 7);
    foreach<int, print>(array, 7);
    cout<< endl;

    foreach<int, dec1>(array, 7);
    foreach<int, print>(array, 7);
    cout<< endl;

    return 0;
}
