#ifndef TORRENTO_BADBENCODEEXCEPTION_H
#define TORRENTO_BADBENCODEEXCEPTION_H

#include <iostream>

class BadBencodeException : public std::exception {
public:
    const char *what() const throw() override {
        return "Wrong bencode markup";
    }
};

#endif //TORRENTO_BADBENCODEEXCEPTION_H
