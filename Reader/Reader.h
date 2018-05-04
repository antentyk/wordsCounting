#ifndef READER_H_
#define READER_H_

#include <fstream>
#include <string>
#include <memory>

#include "../Common/Common.h"
#include "../MPMCDeque/MPMCDeque.hpp"

class Reader{
public:
    Reader(
        std::ifstream &file,
        MPMCDeque<std::shared_ptr<wordsList>> &rawData,
        size_t blockSize
    );
    void run();
private:
    std::ifstream &file;
    MPMCDeque<std::shared_ptr<wordsList>> &rawData;
    size_t blockSize;

    void prepareBlock(std::shared_ptr<wordsList> block);
};

#endif