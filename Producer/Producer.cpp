#include <algorithm>
#include <mutex>
#include <type_traits>
#include <ctype.h>

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
            [](unsigned char it){
				return !(isalpha(it) || isdigit(it));
			}
        ),
		target.end()
    );
}

shared_ptr<wordsDict> Producer::produce(shared_ptr<wordsList> lst){
    shared_ptr<wordsDict> result(new wordsDict());

	for (auto &it : *lst)
	{
		removePunctuation(it);
        std::transform(it.begin(), it.end(), it.begin(), ::tolower);
		if (it.empty())continue;
		++result->operator[](it);
	}
    
    return result;
}

void Producer::run(){
    while(true){
        unique_lock<std::recursive_mutex> lck(rawData.getMutex());

        while(rawData.empty())
            rawData.getConditionVariable().wait(lck);
        
        if(rawData.size() == 1 && rawData.back() == nullptr){
			lck.unlock();
            rawData.getConditionVariable().notify_one();
            return;
        }
        
        auto it = rawData.pop_front();

        lck.unlock();

        processedData.push_front(produce(it));
    }
}
