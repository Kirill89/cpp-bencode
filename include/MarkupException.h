#ifndef TORRENTO_MARKUPEXCEPTION_H
#define TORRENTO_MARKUPEXCEPTION_H

#include <iostream>

namespace Bencode {
    class MarkupException : public std::exception {
    public:
        const char *what() const throw() override {
            return "Wrong bencode markup";
        }
    };
}

#endif //TORRENTO_MARKUPEXCEPTION_H
