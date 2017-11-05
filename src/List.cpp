#include "../include/List.h"

using namespace Bencode;

std::shared_ptr<Element> List::parse(std::vector<char> const &data, int &pos) {
    ListVector elements;

    if (data[pos] != 'l') throw MarkupException();

    incrementPosOrThrow(data, pos);

    while (data[pos] != 'e') {
        elements.push_back(Element::parse(data, pos));
    }

    pos++;

    return std::make_shared<List>(elements);
};

std::string List::toReadable(int deepness) {
    std::stringstream ss;

    ss << std::string(deepness, '\t') << "List:" << std::endl;

    for (const auto &element : this->value) {
        ss << element->toReadable(deepness + 1);
    }

    return ss.str();
};

std::vector<char> List::toBencode() {
    auto result = std::vector<char>{'l'};

    for (const auto &element : this->value) {
        auto elementData = element->toBencode();

        result.reserve(result.size() + elementData.size());
        result.insert(result.end(), elementData.begin(), elementData.end());
    }

    result.push_back('e');

    return result;
};
