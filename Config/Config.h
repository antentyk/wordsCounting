#ifndef CONFIG_H_
#define CONFIG_H_

#include <fstream>
#include <string>

#include "../Common/Common.h"

class Config{
public:
    size_t
        blockSize{kMinBlockSize},
        producerThreadsNum{kMinProducerThreadsNum},
        consumerThreadsNum{kMinConsumerThreadsNum};

    std::string
        inFileName{""},
        resAFileName{""},
        resNFileName{""};
};

std::ifstream &operator>>(std::ifstream &str, Config &target);

Config getConfig(std::string configFileName);

#endif