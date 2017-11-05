#include "../include/Number.h"

using namespace Bencode;

std::shared_ptr<Element> Number::parse(std::vector<char> const &data, int &pos) {
    std::string result;

    if (data[pos] != 'i') throw MarkupException();

    incrementPosOrThrow(data, pos);

    while (data[pos] != 'e') {
        result += data[pos];
        incrementPosOrThrow(data, pos);
    }

    pos++;

    return std::make_shared<Number>(stol(result));
}


std::string Number::toReadable(int deepness) {
    std::stringstream ss;
    ss << std::string(deepness, '\t') << "Number: " << this->value << std::endl;
    return ss.str();
};

std::vector<char> Number::toBencode() {
    auto result = std::to_string(this->value);

    result = 'i' + result + 'e';

    return std::vector<char>(result.begin(), result.end());
};
