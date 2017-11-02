#include "../include/BencodeByteArray.h"
#include "../include/Utils.h"

std::shared_ptr<BencodeElement> BencodeByteArray::parse(std::vector<char> const &data, int &pos) {
    std::string lengthStr;

    while (data[pos] != ':') {
        lengthStr += data[pos];
        Utils::incrementPosOrThrow(data, pos);
    }

    Utils::incrementPosOrThrow(data, pos);

    long length = stol(lengthStr);

    std::vector<char> result;

    if (pos + length > data.size()) throw BadBencodeException();

    while (length--) {
        result.push_back(data[pos]);
        pos++;
    }

    return std::make_shared<BencodeByteArray>(result);
}

std::string BencodeByteArray::toReadable(int deepness) {
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

std::vector<char> BencodeByteArray::toBencode() {
    auto result = std::vector<char>(this->value);
    auto length = std::to_string(result.size());

    result.insert(result.begin(), ':');

    for (std::string::reverse_iterator it = length.rbegin(); it != length.rend(); ++it) {
        result.insert(result.begin(), *it);
    }

    return result;
};
