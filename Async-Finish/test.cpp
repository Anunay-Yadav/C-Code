#ifndef MANAGER
#include "manager.hpp"
#endif
#include <chrono>
using namespace std::chrono;
#include <unistd.h>
#include <cstring>
#define SIZE 1000
int a[SIZE][SIZE];
int b[SIZE][SIZE];
int c[SIZE][SIZE];
int c_correct[SIZE][SIZE];
void function(void* arg){
    int* ind = static_cast<int*>(arg);
    int x = ind[0];
    int y = ind[1];
    for(int i = 0;i < SIZE; i++){
        c[x][y] += a[x][i]*b[i][y];
    }
    // std::cout << x << " " << y << std::endl;
}
void function_correct(int x, int y){
    for(int i = 0;i < SIZE; i++){
        c_correct[x][y] += a[x][i]*b[i][y];
    }
}
int main(){
    for(int i1 = 0; i1 < 100; i1++){
        for (int i = 0; i < SIZE; i++) {
            for(int j = 0;j < SIZE; j++){
                a[i][j] = 1;
                b[i][j] = 2;       
            }
        }
        auto start = high_resolution_clock::now();

        manager::start(8);

        for (int i = 0; i < SIZE; i++) {
            for(int j = 0;j < SIZE; j++){
                int* p = new int[2];
                p[0] = i;
                p[1] = j;
                manager::push(function,static_cast<void*>(p));   
                // manager::push(function,nullptr);   
            }
        }
        std::cout << "Started" << std::endl;
        manager::finish();
        manager::finalize();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Parrallel   " << duration.count() << "ms" << std::endl;
        manager::display();

        auto start1 = high_resolution_clock::now();
        memset(c_correct,0,sizeof(c_correct));
        for(int i = 0;i < SIZE;i++){
            for(int j = 0;j < SIZE; j++){
                function_correct(i,j);
            }
        }
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        std::cout << "Sequential  " << duration1.count() << "ms" << std::endl;
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(c_correct[i][j] != c[i][j]){
                    std::cout << "Incorrect at "  << i << " : " << j << " ,value :" << c_correct[i][j] << " " << c[i][j] << std::endl;
                    return 0;
                }
            }
        }
        memset(c,0,sizeof(c));
    }
    return 0;
}