#ifndef COMMON_H_
#define COMMON_H_

#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>

extern const size_t
    kMinBlockSize,
    kMaxBlockSize;

extern const size_t
    kMinProducerThreadsNum,
    kMaxProducerThreadsNum;

extern const size_t
    kMinConsumerThreadsNum,
    kMaxConsumerThreadsNum;

void displayHelp();

typedef std::vector<std::string> wordsList;
typedef std::unordered_map<std::string, size_t> wordsDict;

#endif