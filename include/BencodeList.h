//
// Created by Kirill on 10/23/17.
//

#ifndef TORRENTO_BENCODELIST_H
#define TORRENTO_BENCODELIST_H

#include "../include/BencodeElement.h"
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>

typedef std::vector<std::shared_ptr<BencodeElement>> BencodeListVector;

class BencodeList : public BencodeElement {
private:
    BencodeListVector value;

    BencodeList() = default;

public:
    explicit BencodeList(BencodeListVector &&value) { this->value = std::move(value); }

    explicit BencodeList(BencodeListVector &value) { this->value = BencodeListVector(value); }

    BencodeListVector getValue() { return this->value; }

    void setValue(BencodeListVector &&value) { this->value = std::move(value); }

    void setValue(BencodeListVector &value) { this->value = BencodeListVector(value); }

    std::vector<char> toBencode();

    std::string toReadable(int deepness);

    static std::shared_ptr<BencodeElement> parse(std::vector<char> const &data, int &pos);
};

#endif //TORRENTO_BENCODELIST_H
