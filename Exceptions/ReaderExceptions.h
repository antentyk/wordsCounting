#ifndef READER_EXCEPTIONS_H_
#define READER_EXCEPTIONS_H_

#include <exception>

class ReaderError : public std::exception{
public:
    const char *what() const throw(){
        return "Error occured while manipulating with Reader";
    }
};

class ReaderInitError : public ReaderError{
public:
    const char *what() const throw(){
        return "Error while initializing Reader instance";
    }
};

class ReaderBlockSizeError : public ReaderInitError{
public:
    const char *what() const throw(){
        return "Invalid value for block size";
    }
};

class ReaderFileError : public ReaderInitError{
public:
    const char *what() const throw(){
        return "Invalid file";
    }
};

#endif