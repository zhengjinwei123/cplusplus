#include <iostream>

class some_value;

typedef int (some_value::* some_value_mfp)(int);

template<some_value_mfp func>
int call(some_value &value, int op) { return (value.*func)(op); }

class some_value
{
    int value_;
public:
    some_value(int value) : value_(value) {}
    int add_by(int op) { return value_ += op; }
    int sub_by(int op) { return value_ -= op; }
    int mul_by(int op) { return value_ *= op; }
};

int main(int argc, char **argv)
{
    using namespace std;
    some_value v0(0);
    cout<< call<&some_value::add_by>(v0, 1) <<endl;
    cout<< call<&some_value::sub_by>(v0, 2) <<endl;
    cout<< call<&some_value::mul_by>(v0, 3) <<endl;
    return 0;
}
