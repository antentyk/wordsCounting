#include <iostream>
#include <set>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "Config.h"
#include "../Common/Common.h"
#include "../Exceptions/ConfigExceptions.h"

using std::string;
using std::set;
using std::vector;
using std::ifstream;
using std::cerr;
using std::endl;

ifstream &operator>>(ifstream &strm, Config &target){
    set<string> unReadTokens{
        "infile",
        "out_by_a",
        "out_by_n",
        "producer_threads_num",
        "consumer_threads_num",
        "block_size"
    };

    string line;
    while(strm >> line){
        vector<string> parts;
        boost::split(parts, line, boost::is_any_of("="));
        
        if(parts.size() != 2)
            throw ConfigParseError();
        
        string
            name = parts.front(),
            val = parts.back();

        if(name == "infile"){
            unReadTokens.erase(name);
            target.inFileName = val;
        }
        else if(name == "out_by_a"){
            unReadTokens.erase(name);
            target.resAFileName = val;
        }
        else if(name == "out_by_n"){
            unReadTokens.erase(name);
            target.resNFileName = val;
        }
        else if(name == "producer_threads_num"){
            unReadTokens.erase(name);

            try{
                target.producerThreadsNum = boost::lexical_cast<size_t>(val);
            }
            catch(const boost::bad_lexical_cast &e){
                throw ConfigProducerThreadsNumError();
            }

            if(
                target.producerThreadsNum < kMinProducerThreadsNum ||
                target.producerThreadsNum > kMaxProducerThreadsNum
            )
                throw ConfigProducerThreadsNumError();
        }
        else if(name == "consumer_threads_num"){
            unReadTokens.erase(name);

            try{
                target.consumerThreadsNum = boost::lexical_cast<size_t>(val);
            }
            catch(const boost::bad_lexical_cast &e){
                throw ConfigConsumerThreadsNumError();
            }

            if(
                target.consumerThreadsNum < kMinConsumerThreadsNum ||
                target.consumerThreadsNum > kMaxConsumerThreadsNum
            )
                throw ConfigConsumerThreadsNumError();
        }
        else if(name == "block_size"){
            unReadTokens.erase(name);

            try{
                size_t  numVal = boost::lexical_cast<size_t>(val);
                target.blockSize = numVal;
            }
            catch(const boost::bad_lexical_cast &e){
                throw ConfigBlockSizeError();
            }

            if(
                target.blockSize < kMinBlockSize ||
                target.blockSize > kMaxBlockSize
            )
                throw ConfigBlockSizeError();
        }
        else
            throw ConfigInvalidTokenError();
    }

    if(!unReadTokens.empty())
        throw ConfigMissingDataError();
    
    return strm;
}

Config getConfig(string configFileName){
    ifstream file;
    file.open(configFileName);
    
    if(!file.is_open())
        throw ConfigFileNameError();

    Config config;
    file >> config;

    return config;   
}