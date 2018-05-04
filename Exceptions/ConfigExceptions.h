#ifndef READER_EXCEPTIONS_H_
#define READER_EXCEPTIONS_H_

#include <exception>

class ConfigError : public std::exception{
public:
    const char *what() const throw(){
        return "Erorr occured while manipulating with Config";
    }
};

class ConfigReadError : public std::exception{
public:
    const char *what() const throw(){
        return "Error while parsing Config";
    }
};

class ConfigBlockSizeError : public ConfigReadError{
public:
    const char *what() const throw(){
        return "Value of block size is inappropriate";
    }
};

class ConfigProducerThreadsNumError : public ConfigReadError{
public:
    const char *what() const throw(){
        return "Value of producer threads num is inappropriate";
    }
};

class ConfigConsumerThreadsNumError : public ConfigReadError{
public:
    const char *what() const throw(){
        return "Value of consumer threads num is inappropriate";
    }
};

class ConfigInvalidTokenError : public ConfigReadError{
public:
    const char *what() const throw(){
        return "Invalid token detected";
    }
};

class ConfigParseError : public ConfigReadError{
public:
    const char *what() const throw(){
        return "Cannot parse the line";
    }
};

class ConfigMissingDataError : public ConfigReadError{
public:
    const char *what() const throw(){
        return "Some of the config arguments are missing";
    }
};

class ConfigFileNameError : public ConfigError{
public:
    const char *what() const throw(){
        return "Cannot find config file";
    }
};

#endif