#include <algorithm>
#include <mutex>
#include <type_traits>

#include "Producer.h"

using std::shared_ptr;
using std::string;
using std::unique_lock;

Producer::Producer(
    MPMCDeque<shared_ptr<wordsList>> &rawData,
    MPMCDeque<shared_ptr<wordsDict>> &processedData
):
    rawData(rawData),
    processedData(processedData)
{}

void Producer::removePunctuation(string &target){
    target.erase(
        std::remove_if(
            target.begin(),
            target.end(),
            [](char c){return !isalpha(c);}
        )
    );
}

shared_ptr<wordsDict> Producer::produce(shared_ptr<wordsList> lst){
    shared_ptr<wordsDict> result(new wordsDict());

    for(auto &it: *lst)
        ++result->operator[](it);
    
    return result;
}

void Producer::run(){
    while(true){
        unique_lock<std::remove_reference<decltype(rawData.getMutex())>::type>
            lck(rawData.getMutex());

        while(rawData.empty())
            rawData.getConditionVariable().wait(lck);
        
        if(rawData.size() == 1 && rawData.back() == nullptr){
            rawData.getConditionVariable().notify_one();
            return;
        }
        
        auto it = rawData.pop_front();

        lck.unlock();

        processedData.push_front(produce(it));
    }
}