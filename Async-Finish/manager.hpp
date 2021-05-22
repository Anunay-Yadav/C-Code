#include "task.hpp"
#include<memory>
namespace manager{
        
        // manager(int);
        void push(void (*heap_f)(void*), void* args);
        std::unique_ptr<task> pop_execute();
        void start(int num);
        void finish();
        void thread_fetch_execute();
        void finalize();
};