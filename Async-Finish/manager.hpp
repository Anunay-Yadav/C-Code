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
                        Queue.push([=]{ std::invoke(f, args...);  return 1;});
                }

                std::function<void()> pop_execute();
                manager(int num);
                void finish();
                void thread_fetch_execute();
                void finalize();
                void display();
                void for_async_1d(loop , void func(void*) , void*, MODE mode);
                void flat_1d_gen(loop, void func(void*), void*);
};