#ifndef TORRENTO_BENCODEDICTIONARY_H
#define TORRENTO_BENCODEDICTIONARY_H

#include "../include/BencodeElement.h"
#include "../include/BencodeByteArray.h"
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>
#include <map>

typedef std::map<std::shared_ptr<BencodeByteArray>, std::shared_ptr<BencodeElement>> BencodeDictionaryMap;

class BencodeDictionary : public BencodeElement {
private:
    BencodeDictionaryMap value;

    BencodeDictionary() = default;

public:
    explicit BencodeDictionary(BencodeDictionaryMap &&value) { this->value = std::move(value); }

    explicit BencodeDictionary(BencodeDictionaryMap &value) { this->value = BencodeDictionaryMap(value); }

    BencodeDictionaryMap getValue() { return this->value; }

    void setValue(BencodeDictionaryMap &&value) { this->value = std::move(value); }

    void setValue(BencodeDictionaryMap &value) { this->value = BencodeDictionaryMap(value); }

    std::vector<char> toBencode();

    std::string toReadable(int deepness);

    static std::shared_ptr<BencodeElement> parse(std::vector<char> const &data, int &pos);
};

#endif //TORRENTO_BENCODEDICTIONARY_H
