// Hashing function Testing Sandbox
// Jackie Adair
// jakadair@gmail.com
// 2018 11 13

#include <iostream>
#include <string>

template <class T>
class Hash {
public:
    void fun(T a)
    {
        std::cout << "The main template fun(): "
            << a << std::endl;
    }

};

template <>
class Hash <int> {
public:
    void fun(int a){
        std::cout << "Specialized Templatle for int type: "
            << a << std::endl;
    }
};

int main()
{
    Hash<char> test;
    Hash<int> test2;
    Hash<std::string> test3;
    Hash<double> test4;

    test.fun('a');
    test2.fun(10);
    test3.fun("Jackie");
    test4.fun(10.14);
}