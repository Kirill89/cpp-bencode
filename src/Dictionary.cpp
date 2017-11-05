#include "../include/Dictionary.h"

using namespace Bencode;

std::shared_ptr<Element> Dictionary::parse(std::vector<char> const &data, int &pos) {
    DictionaryMap elements;
    std::shared_ptr<ByteArray> key = nullptr;

    if (data[pos] != 'd') throw MarkupException();

    incrementPosOrThrow(data, pos);

    while (data[pos] != 'e') {
        if (key == nullptr) {
            auto suggestedKey = Element::parse(data, pos);

            key = std::dynamic_pointer_cast<ByteArray>(suggestedKey);

            if (key == nullptr) {
                throw MarkupException();
            }
        } else {
            elements.insert(make_pair(key, Element::parse(data, pos)));
            key = nullptr;
        }
    }

    pos++;

    return std::make_shared<Dictionary>(elements);
};


std::string Dictionary::toReadable(int deepness) {
    std::stringstream ss;

    ss << std::string(deepness, '\t') << "Dictionary:" << std::endl;

    for (const auto &element : this->value) {
        ss << std::string(deepness + 1, '\t') << "Pair:" << std::endl;
        ss << element.first->toReadable(deepness + 2);
        ss << element.second->toReadable(deepness + 2);
    }

    return ss.str();
};

std::vector<char> Dictionary::toBencode() {
    auto result = std::vector<char>{'d'};

    for (const auto &pair : this->value) {
        auto keyData = pair.first->toBencode();
        auto elementData = pair.second->toBencode();

        result.reserve(result.size() + keyData.size() + elementData.size());

        result.insert(result.end(), keyData.begin(), keyData.end());
        result.insert(result.end(), elementData.begin(), elementData.end());
    }

    result.push_back('e');

    return result;
};
