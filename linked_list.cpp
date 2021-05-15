#include <iostream>
#include "linked_list.hpp"

using namespace std;


int main(){
    LinkedList<int> a;
    a.push_back(new Node<int>(3));
    a.push_back(new Node<int>(4));
    a.push_back(new Node<int>(6));
    a.push_mid(new Node<int>(5), 4);
    a.delete_mid(5);
    cout << "Done" << endl;
}