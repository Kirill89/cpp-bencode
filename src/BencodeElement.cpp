#include "../include/BencodeElement.h"
#include "../include/BencodeDictionary.h"
#include "../include/BencodeNumber.h"
#include "../include/BencodeList.h"
#include "../include/BadBencodeException.h"

std::shared_ptr<BencodeElement> BencodeElement::parse(std::vector<char> const &data, int &pos) {
    char c = data[pos];

    if (c == 'i') {
        return BencodeNumber::parse(data, pos);
    } else if (c >= '0' && c <= '9') {
        return BencodeByteArray::parse(data, pos);
    } else if (c == 'l') {
        return BencodeList::parse(data, pos);
    } else if (c == 'd') {
        return BencodeDictionary::parse(data, pos);
    } else {
        throw BadBencodeException();
    }
}
