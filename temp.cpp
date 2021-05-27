#include <bits/stdc++.h>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
using namespace std;
class Node{
    public:
        int get_f_cost();
};
template <typename T> std::string type_name(){
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
int main(){
    auto k = ([](Node* lhs, Node* rhs) { return lhs->get_f_cost() > rhs->get_f_cost(); });
    auto k1 = ([](Node* lhs, Node* rhs) { return lhs->get_f_cost() > rhs->get_f_cost(); });
    int k2 = 10;
    // std:: cout << decltype([](Node* lhs, Node* rhs) { return lhs->get_f_cost() > rhs->get_f_cost(); }) << std:: endl;
    std::cout << type_name<decltype(k)>()  << std::endl;;
    std::cout << type_name<decltype(k1)>()  << std::endl;;
    std::cout << type_name<decltype(k2)>()  << std::endl;;


}