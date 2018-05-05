#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <memory>

#include "../Common/Common.h"
#include "../MPMCDeque/MPMCDeque.hpp"

class Consumer {
public:
	Consumer(MPMCDeque<std::shared_ptr<wordsDict>> &processedData);
	void run();
private:
	MPMCDeque<std::shared_ptr<wordsDict>> &processedData;

	std::shared_ptr<wordsDict> merge(
		std::shared_ptr<wordsDict> left,
		std::shared_ptr<wordsDict> right
	);
};

#endif