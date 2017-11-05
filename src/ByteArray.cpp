#include "../include/ByteArray.h"

using namespace Bencode;

std::shared_ptr<Element> ByteArray::parse(std::vector<char> const &data, int &pos) {
    std::string lengthStr;

    while (data[pos] != ':') {
        lengthStr += data[pos];
        incrementPosOrThrow(data, pos);
    }

    incrementPosOrThrow(data, pos);

    long length = stol(lengthStr);

    std::vector<char> result;

    if (pos + length > data.size()) throw MarkupException();

    while (length--) {
        result.push_back(data[pos]);
        pos++;
    }

    return std::make_shared<ByteArray>(result);
}

std::string ByteArray::toReadable(int deepness) {
    std::stringstream ss;

    ss << std::string(deepness, '\t') << "ByteArray: ";

    if (this->value.size() > 300) {
        ss << "{" << this->value.size() << " bytes}";
    } else {
        for (char c : this->value) {
            ss << c;
        }
    }

    ss << std::endl;

    return ss.str();
};

std::vector<char> ByteArray::toBencode() {
    auto result = std::vector<char>(this->value);
    auto length = std::to_string(result.size());

    result.insert(result.begin(), ':');

    for (std::string::reverse_iterator it = length.rbegin(); it != length.rend(); ++it) {
        result.insert(result.begin(), *it);
    }

    return result;
};
