#include "Reader.h"
#include "../Exceptions/Exceptions.h"
#include "../Common/Common.h"

using std::string;
using std::shared_ptr;
using std::ifstream;

Reader::Reader(
    ifstream &file,
    MPMCDeque<shared_ptr<wordsList>> &rawData,
    size_t blockSize
):
    file(file),
    rawData(rawData),
    blockSize(blockSize)
{
    if(!file.is_open())
        throw ReaderFileError();
    if(blockSize < kMinBlockSize || blockSize > kMaxBlockSize)
        throw ReaderBlockSizeError();
}

void Reader::run(){
    // in case file is empty
    rawData.push_front(shared_ptr<wordsList>(new wordsList()));

    while(file)
    {
        shared_ptr<wordsList> block(new wordsList());
        prepareBlock(block);
        rawData.push_front(block);
    }
}

void Reader::prepareBlock(shared_ptr<wordsList> block){
    if(block == nullptr)
        return;
    
	block->reserve(blockSize);

    string word;

	for
	(
		size_t left = blockSize;
		left >= 1 && file >> word;
		--left
	)
		block->push_back(std::move(word));
}
