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

                template <typename Function, typename... Args>
                void push(Function&& f, Args&&... args) {
                        std::lock_guard<std::mutex> guard(my_mutex);
                        Queue.push([=]{ std::invoke(f, args...);});
                }

                void pop_execute();
                manager(int num);
                void finish();
                void thread_fetch_execute();
                void finalize();
                void display();

                template <typename Function, typename... Args>
                void for_async_1d(loop loop_t, MODE mode, Function&& f,Args&&... args){
                        if( mode == FLAT) {
                                for(int i = loop_t.start; i < loop_t.end; i += loop_t.tile_size){
                                        for(int j = 0;j < loop_t.tile_size; j += loop_t.step){
                                                int index = i + j;
                                                Queue.push([=]{ std::invoke(f,index,args...);});
                                        }
                                }
                        }
                        else if(mode == RECURSIVE){
                                 // Working on it
                        }
                }
                
};