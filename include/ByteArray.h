#ifndef TORRENTO_BYTEARRAY_H
#define TORRENTO_BYTEARRAY_H

#include "Element.h"
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>

namespace Bencode {
    class ByteArray : public Element {
    private:
        std::vector<char> value;

        ByteArray() = default;

    public:
        explicit ByteArray(std::vector<char> &&value) { this->value = std::move(value); };

        explicit ByteArray(std::vector<char> &value) { this->value = std::vector<char>(value); };

        std::vector<char> getValue() { return this->value; }

        void setValue(std::vector<char> &&value) { this->value = std::move(value); };

        void setValue(std::vector<char> &value) { this->value = std::vector<char>(value); };

        std::vector<char> toBencode();

        std::string toReadable(int deepness);

        static std::shared_ptr<Element> parse(std::vector<char> const &data, int &pos);
    };
}

#endif //TORRENTO_BYTEARRAY_H
