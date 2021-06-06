#include <cstdlib>
#ifndef MANAGER
    #include "../header files/manager.hpp"
#endif
#include <iostream>
#include <chrono>
using namespace std::chrono;
#include <unistd.h>
#include <cstring>
#define SIZE 250


int main(){
    for(int i1 = 0; i1 < 1; i1++){
        manager task_handler(16);
        call_id a1,a2;
        for(int i = 0;i < 10; i++){
            future_t<int>* k = task_handler.async([&]() -> int{
                int k = 0;
                for(int i = 0;i < SIZE; i++){
                    k += 1;
                }
                return k;
            });
            std::cout << k -> get_status() << std:: endl;
            std::cout << k -> get() << std:: endl;
            std::cout << k -> get_status() << std:: endl;
            delete k;
        }
        task_handler.finish();
        task_handler.finalize();
    }
    return 0;
}