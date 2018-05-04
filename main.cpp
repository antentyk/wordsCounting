#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <memory>
#include <functional>
#include <vector>
#include <chrono>
#include <atomic>

#include "Common/Common.h"
#include "Config/Config.h"
#include "Reader/Reader.h"
#include "Exceptions/Exceptions.h"
#include "Producer/Producer.h"

/*
*   Reader - reads data in raw format
*   Producer - transforms data from raw format
*   Consumer - merges data
*/

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced(){
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D& d){
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

int main(int argc, char ** argv){
    if(argc != 2)
        throw ArgumentsNumError();

    string configFileName{*(argv + 1)};
    if(configFileName == "-h" || configFileName == "--help"){
        displayHelp();
        return EXIT_SUCCESS;
    }

    Config config = getConfig(configFileName);

    std::ifstream dataFile;
    dataFile.open(config.inFileName);
    if(!dataFile.is_open())
        throw DataFileError();
    
    MPMCDeque<shared_ptr<wordsList>> rawData;
    MPMCDeque<shared_ptr<wordsDict>> processedData;

    Reader reader(dataFile, rawData, config.blockSize);
    Producer producer(rawData, processedData);

    auto start = get_current_time_fenced();

    std::thread readerThread(std::bind(&Reader::run, &reader));

    std::vector<std::thread> producerThreads;
    for(size_t i = 0; i < config.producerThreadsNum; ++i)
        producerThreads.emplace_back(
            std::bind(&Producer::run, &producer)
        );
    
    readerThread.join();
    dataFile.close();
    rawData.push_back(nullptr);

    for(auto &producerThread: producerThreads)
        producerThread.join();
    
    auto end = get_current_time_fenced();

    return 0;
}