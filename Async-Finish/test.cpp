#ifndef MANAGER
#include "manager.hpp"
#endif
#include <unistd.h>

void function(void* a){
    int* new_a = (int*) a;
    int k = ((*new_a) == 1)*100;
    sleep(abs(rand()%3));
    std ::cout << "Counter value" << ": " << *new_a << std :: endl;
}
int main(){
    int* a = new int(0);
    manager::start(10);
    for (int i = 0; i < 10; i++) {
        manager::push(function,new int(i));
    }
    manager::finish();
    manager::finalize();
    return 0;
}