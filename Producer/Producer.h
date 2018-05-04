#ifndef PRODUCER_H_
#define PRODUCER_H_

#include <memory>
#include <string>

#include "../Common/Common.h"
#include "../MPMCDeque/MPMCDeque.hpp"

class Producer{
public:
    Producer(
        MPMCDeque<std::shared_ptr<wordsList>> &rawData,
        MPMCDeque<std::shared_ptr<wordsDict>> &processedData
    );

    void run();
private:
    MPMCDeque<std::shared_ptr<wordsList>> &rawData;
    MPMCDeque<std::shared_ptr<wordsDict>> &processedData;

    std::shared_ptr<wordsDict> produce(std::shared_ptr<wordsList> lst);
    inline void removePunctuation(std::string &target);
};

#endif