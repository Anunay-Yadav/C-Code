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
        manager task_handler(8);

        for (int i = 0; i < SIZE; i++) {
            for(int j = 0;j < SIZE; j++){
                task_handler.push([](int x, int y){
                    for(int i1 = 0;i1 < SIZE; i1++){
                        c[x][y] += a[x][i1]*b[i1][y];
                    }
                },i , j);   
            }
        }
        std::cout << "Started" << std::endl;
        task_handler.finish();
        task_handler.finalize();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Parrallel   " << duration.count() << "ms" << std::endl;
        task_handler.display();

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