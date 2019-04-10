#include <iostream>

template<int *p>
struct wrapper {
    int get() { return *p; }
    void set(int v) { *p = v; }
};

template<int &p>
struct wrapper2 {
    int get() { return p; }
    void set(int v) { p = v; }
};

int global_variable = 0;

int main(int argc, char **argv) {
    using namespace std;
    wrapper<&global_variable> gwrapper;
    gwrapper.set(1);
    cout<<gwrapper.get()<<endl;

    wrapper2<global_variable> gwrapper2;
    gwrapper2.set(2);
    cout<<gwrapper2.get()<<endl;

    return 0;
}