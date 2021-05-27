#include "task.hpp"
#include<memory>
#include <list>
#include <functional>
#include <type_traits>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <memory>


class loop{
        public:
                int start,end,step, tile_size;
                loop(int start, int end, int step, int tile_size) : start(start), end(end), step(step), tile_size(tile_size){}
                loop(const loop &a) : start(a.start), end(a.end), step(a.step), tile_size(a.tile_size){}
};

class loop2d{
        public:
                int start1,start2,end1,end2,step1,step2;
                loop2d(int start1,int start2,int end1,int end2,int step1,int step2) : start1(start1), start2(start2), end1(end1), end2(end2), step1(step1), step2(step2){}
                loop2d(const loop2d &a) : start1(a.start1), start2(a.start2), end1(a.end1), end2(a.end2), step1(a.step1), step2(a.step2){}
};
enum MODE{
        RECURSIVE, FLAT
};

class manager{
        public:
                std::queue<std::function<void()>> Queue;
                std::vector<std::thread> all_threads;
                int shutdown;
                int thread_num;
                std::mutex my_mutex;


                manager(int num);

                template <typename Function, typename... Args>
                void push(Function&& f, Args&&... args) {
                        std::lock_guard<std::mutex> guard(my_mutex);
                        Queue.push([=]{ std::invoke(f, args...);});
                }

                void pop_execute();
                void finish();
                void thread_fetch_execute();
                void finalize();
                void display() const;

                template <typename Function, typename... Args>
                void for_async_1d(loop loop_t, MODE mode, Function&& f,Args&&... args){
                        if( mode == FLAT) {
                                for(int i = loop_t.start; i < loop_t.end; i += loop_t.tile_size){
                                        for(int j = 0;j < loop_t.tile_size; j += loop_t.step){
                                                push(f,i + j,args...);
                                        }
                                }
                        }
                        else if(mode == RECURSIVE){
                                 // Working on it
                        }
                }
                
                template <typename Function, typename... Args>
                void for_async_2d(loop2d loop_t, MODE mode, Function&& f,Args&&... args){
                        if( mode == FLAT) {
                                for(int i = loop_t.start1; i < loop_t.end1; i+=loop_t.step1){
                                        for(int j = loop_t.start2; j < loop_t.end2; j+= loop_t.step2){
                                                push(f,i , j,args...);
                                        }
                                }
                        }
                        else if(mode == RECURSIVE){
                                 // Working on it
                        }
                }
                
};