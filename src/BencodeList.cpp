#include "../include/BencodeList.h"
#include "../include/Utils.h"

std::shared_ptr<BencodeElement> BencodeList::parse(std::vector<char> const &data, int &pos) {
    BencodeListVector elements;

    if (data[pos] != 'l') throw BadBencodeException();

    Utils::incrementPosOrThrow(data, pos);

    while (data[pos] != 'e') {
        elements.push_back(BencodeElement::parse(data, pos));
    }

    pos++;

    return std::make_shared<BencodeList>(elements);
};

std::string BencodeList::toReadable(int deepness) {
    std::stringstream ss;

    ss << std::string(deepness, '\t') << "List:" << std::endl;

    for (const auto &element : this->value) {
        ss << element->toReadable(deepness + 1);
    }

    return ss.str();
};

std::vector<char> BencodeList::toBencode() {
    auto result = std::vector<char>{'l'};

    for (const auto &element : this->value) {
        auto elementData = element->toBencode();

        result.reserve(result.size() + elementData.size());
        result.insert(result.end(), elementData.begin(), elementData.end());
    }

    result.push_back('e');

    return result;
};
