#include <algorithm>
#include <mutex>

#include "Consumer.h"

using std::shared_ptr;
using std::recursive_mutex;
using std::unique_lock;

Consumer::Consumer(MPMCDeque<shared_ptr<wordsDict>> &processedData):
	processedData(processedData)
{}

shared_ptr<wordsDict> Consumer::merge(
	shared_ptr<wordsDict> left,
	shared_ptr<wordsDict> right
)
{
	for (auto &it : *left)
		(*right)[it.first] += it.second;

	return right;
}

void Consumer::run() {
	while (true) {
		unique_lock<recursive_mutex> lck(processedData.getMutex());

		while (processedData.size() < 2)
			processedData.getConditionVariable().wait(lck);

		if (processedData.size() == 2 && processedData.back() == nullptr) {
			lck.unlock();
			processedData.getConditionVariable().notify_one();
			return;
		}

		auto left = processedData.pop_front();
		auto right = processedData.pop_front();

		lck.unlock();

		processedData.push_front(merge(left, right));
	}
}