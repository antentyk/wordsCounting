#include <iostream>

#include "Common.h"

using std::cout;
using std::endl;

const size_t
    kMinBlockSize{1},
    kMaxBlockSize{1000000};

const size_t
    kMinProducerThreadsNum{1},
    kMaxProducerThreadsNum{100};

const size_t
    kMinConsumerThreadsNum{1},
    kMaxConsumerThreadsNum{100};

void displayHelp(){
    cout << "wordsCounting [-h | --help] config_file_name" << endl;
    cout << "you should launch the program in the same directory where config file is located" << endl;
}