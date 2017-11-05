#ifndef TORRENTO_ELEMENT_H
#define TORRENTO_ELEMENT_H

#include <memory>
#include <string>
#include <vector>
#include "MarkupException.h"

namespace Bencode {
    static void incrementPosOrThrow(std::vector<char> const &data, int &pos) {
        if (pos + 1 >= data.size()) throw MarkupException();
        pos++;
    }

    static std::vector<char> getVectorChar(std::string str) {
        return std::vector<char>(str.begin(), str.end());
    }

    class Element {
    public:
        virtual std::string toReadable(int deepness = 0) = 0;

        virtual std::vector<char> toBencode() = 0;

        static std::shared_ptr<Element> parse(std::vector<char> const &data, int &pos);
    };
}

#endif //TORRENTO_ELEMENT_H
