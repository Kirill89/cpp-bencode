#include "../include/BencodeNumber.h"
#include "../include/Utils.h"

std::shared_ptr<BencodeElement> BencodeNumber::parse(std::vector<char> const &data, int &pos) {
    std::string result;

    if (data[pos] != 'i') throw BadBencodeException();

    Utils::incrementPosOrThrow(data, pos);

    while (data[pos] != 'e') {
        result += data[pos];
        Utils::incrementPosOrThrow(data, pos);
    }

    pos++;

    return std::make_shared<BencodeNumber>(stol(result));
}


std::string BencodeNumber::toReadable(int deepness) {
    std::stringstream ss;
    ss << std::string(deepness, '\t') << "Number: " << this->value << std::endl;
    return ss.str();
};

std::vector<char> BencodeNumber::toBencode() {
    auto result = std::to_string(this->value);

    result = 'i' + result + 'e';

    return std::vector<char>(result.begin(), result.end());
};
