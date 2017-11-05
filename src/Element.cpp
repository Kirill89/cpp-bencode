#include "../include/Element.h"
#include "../include/Dictionary.h"
#include "../include/Number.h"
#include "../include/List.h"

using namespace Bencode;

std::shared_ptr<Element> Element::parse(std::vector<char> const &data, int &pos) {
    char c = data[pos];

    if (c == 'i') {
        return Number::parse(data, pos);
    } else if (c >= '0' && c <= '9') {
        return ByteArray::parse(data, pos);
    } else if (c == 'l') {
        return List::parse(data, pos);
    } else if (c == 'd') {
        return Dictionary::parse(data, pos);
    } else {
        throw MarkupException();
    }
}
