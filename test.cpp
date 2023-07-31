#include <iostream>
#include <typeinfo>

// ================================================================================================ //
// https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>

template <typename T> std::string type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
           (
#ifndef _MSC_VER
                abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                           nullptr, nullptr),
#else
                nullptr,
#endif
                std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}
// ================================================================================================ //


template<typename T>
void f(const T& param)
{
  using std::cout;

  cout << "T =     " << typeid(T).name() << '\n';     // show T

  cout << "param = " << typeid(param).name() << '\n'; // show
                                                      // param's
                                                      // type

  // cout << type_name<decltype(T)>() << "\n";
  cout << type_name<decltype(param)>() << "\n";
}


int main(){
    const int theAnswer = 42;

    auto x = theAnswer;
    auto y = &theAnswer;
    
    std::cout << typeid(x).name() << '\n';
    std::cout << typeid(y).name() << '\n';

    std::cout << type_name<decltype(x)>() << std::endl;
    std::cout << type_name<decltype(y)>() << std::endl;

    std::vector<int> createVec;     // factory function
    createVec.push_back(theAnswer);

    const auto vw = createVec;         // init vw w/factory return

    if (!vw.empty()) {
        f(&vw[0]);                         // call f
    }
    return 0;
}