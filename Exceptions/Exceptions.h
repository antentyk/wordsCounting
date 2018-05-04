#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include "ReaderExceptions.h"
#include "ConfigExceptions.h"

class ArgumentsNumError : public std::exception{
public:
    const char *what() const throw(){
        return "Invalid number of arguments (run with --help)";      
    }
};

class DataFileError : public std::exception{
public:
    const char *what() const throw(){
        return "Cannot find data file";
    }
};

#endif