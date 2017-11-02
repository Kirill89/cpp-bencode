#ifndef TORRENTO_BENCODEBYTEARRAY_H
#define TORRENTO_BENCODEBYTEARRAY_H

#include "../include/BencodeElement.h"
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>

class BencodeByteArray : public BencodeElement {
private:
    std::vector<char> value;

    BencodeByteArray() = default;

public:
    explicit BencodeByteArray(std::vector<char> &&value) { this->value = std::move(value); };

    explicit BencodeByteArray(std::vector<char> &value) { this->value = std::vector<char>(value); };

    std::vector<char> getValue() { return this->value; }

    void setValue(std::vector<char> &&value) { this->value = std::move(value); };

    void setValue(std::vector<char> &value) { this->value = std::vector<char>(value); };

    std::vector<char> toBencode();

    std::string toReadable(int deepness);

    static std::shared_ptr<BencodeElement> parse(std::vector<char> const &data, int &pos);
};

#endif //TORRENTO_BENCODEBYTEARRAY_H
