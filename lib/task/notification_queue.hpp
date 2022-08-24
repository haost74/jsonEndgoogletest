#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>

namespace taskloop
{

    using namespace std;
    using lock_t = unique_lock<mutex>;
    class notification_queue
    {
        deque <function<void()>> _q;
        bool                     _done{false};
        mutex                    _mutex;
        condition_variable       _ready;

        public:
        void done(){
           {
               unique_lock<mutex> lock{_mutex};
               _done = true;
           }

           _ready.notify_all();
        }
        
        bool pop(function<void()> & x){
            lock_t lock{_mutex};
            while (_q.empty() && !_done) _ready.wait(lock);
            if(_q.empty()) return false;
            x = move(_q.front());
            _q.pop_front();
            return true;
        }

        bool try_pop(function<void()> &x)
        {
            lock_t lock{_mutex, std::try_to_lock};
            // while (_q.empty() && !_done) _ready.wait(lock);
            if (!lock || _q.empty()) return false;
            // if(_q.empty()) return false;
            x = move(_q.front());
            _q.pop_front();
            return true;
        }

        template <typename F>
        bool try_push(F &&f)
        {
            {
                lock_t lock{_mutex, try_to_lock};
                if (!lock)
                    return false;
                _q.emplace_back(forward<F>(f));
            }
            _ready.notify_one();
            return true;
        }

       

        template<class F>
        bool push(F&& f){
            {
            lock_t lock{_mutex, std::try_to_lock};
            if (!lock) return false;
            _q.emplace_back(forward<F>(f));
            }
            _ready.notify_one();
            return true;
        }
    };

}
