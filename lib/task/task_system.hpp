#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>
#include "notification_queue.hpp"

namespace taskloop
{
    using namespace std;
    class task_system
    {
        const unsigned _count{thread::hardware_concurrency()};
        vector<thread> _threads;
        vector<notification_queue> _q{_count};
        atomic<unsigned> _index{0};

        void run(unsigned i){
           while (1)
           {
               function<void()> f;

               for(unsigned n = 0; n != _count; ++n){
                   if(_q[(i + n) % _count].try_pop(f)) break;
               }
               if(!f && !_q[i].pop(f)) break;
               f();
               printf("thread N = %d\n", i);
           }           
        }

        public:
           task_system()
           {
               for(unsigned n = 0; n != _count; ++n){
                   _threads.emplace_back([&, n]{run(n);});
               }
           }

           ~task_system(){
               for (auto &e : _q)e.done();
               for(auto& e : _threads)e.join();
           }

           template<class F>
           void async_(F&& f){
               auto i = _index++;
               //_q.push(forward<F>(f));

               for(unsigned n = 0; n != _count; ++n){
                   if (_q[(i + n) % _count].try_push(forward<F>(f))) return;
               }

               _q[i % _count].push(forward<F>(f));
           }
    };

}