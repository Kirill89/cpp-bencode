#include "../include/BencodeDictionary.h"
#include "../include/Utils.h"

std::shared_ptr<BencodeElement> BencodeDictionary::parse(std::vector<char> const &data, int &pos) {
    BencodeDictionaryMap elements;
    std::shared_ptr<BencodeByteArray> key = nullptr;

    if (data[pos] != 'd') throw BadBencodeException();

    Utils::incrementPosOrThrow(data, pos);

    while (data[pos] != 'e') {
        if (key == nullptr) {
            auto suggestedKey = BencodeElement::parse(data, pos);

            key = std::dynamic_pointer_cast<BencodeByteArray>(suggestedKey);

            if (key == nullptr) {
                throw BadBencodeException();
            }
        } else {
            elements.insert(make_pair(key, BencodeElement::parse(data, pos)));
            key = nullptr;
        }
    }

    pos++;

    return std::make_shared<BencodeDictionary>(elements);
};


std::string BencodeDictionary::toReadable(int deepness) {
    std::stringstream ss;

    ss << std::string(deepness, '\t') << "Dictionary:" << std::endl;

    for (const auto &element : this->value) {
        ss << std::string(deepness + 1, '\t') << "Pair:" << std::endl;
        ss << element.first->toReadable(deepness + 2);
        ss << element.second->toReadable(deepness + 2);
    }

    return ss.str();
};

std::vector<char> BencodeDictionary::toBencode() {
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
