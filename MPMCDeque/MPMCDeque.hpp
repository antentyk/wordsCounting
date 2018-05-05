#ifndef CONCURRENT_QUEUE_H_
#define CONCURRENT_QUEUE_H_

#include <deque>
#include <mutex>
#include <condition_variable>

template<class T>
class MPMCDeque{
public:
    MPMCDeque(){}

    inline std::recursive_mutex& getMutex() noexcept{return mutex_;}
    inline std::condition_variable_any& getConditionVariable() noexcept{return condition_variable_;};

    bool empty() const{
        std::lock_guard<std::recursive_mutex> lck(mutex_);
        return deque_.empty();
    }

    size_t size(){
        std::lock_guard<decltype(mutex_)> lck(getMutex());
        return deque_.size();
    }

    const T& front() const{
        std::unique_lock<decltype(mutex_)> lck(mutex_);
        while(empty())
            condition_variable_.wait(lck);
        return deque_.front();
    }

    const T& back() const{
        std::unique_lock<decltype(mutex_)> lck(mutex_);
        while(empty())
            condition_variable_.wait(lck);
        return deque_.back();
    }

    T pop_front(){
        std::unique_lock<decltype(mutex_)> lck(getMutex());
        while(empty())
            getConditionVariable().wait(lck);
        T result = deque_.front();
        deque_.pop_front();
        return result;
    }

    T pop_back(){
        std::unique_lock<decltype(mutex_)> lck(getMutex());
        while(empty())
            getConditionVariable().wait(lck);
        T result = deque_.back();
        deque_.pop_back();
        return result;
    }

    void push_front(const T& val){
        std::unique_lock<decltype(mutex_)> lck(getMutex());
        deque_.push_front(val);
		lck.unlock();
        getConditionVariable().notify_one();
    }

    void push_back(const T& val){
        std::unique_lock<decltype(mutex_)> lck(getMutex());
        deque_.push_back(val);
		lck.unlock();
        getConditionVariable().notify_one();
    }
private:
    mutable std::recursive_mutex mutex_;
    mutable std::condition_variable_any condition_variable_;
    std::deque<T> deque_;
};

#endif