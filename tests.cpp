#include <cassert>
#include "include/Number.h"
#include "include/ByteArray.h"
#include "include/List.h"
#include "include/Dictionary.h"

using namespace Bencode;

void NumberParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<Number>(Number::parse(getVectorChar("i123e"), pos));

    assert(result->getValue() == 123);
}

void NumberToBencodeTest() {
    auto result = Number(10).toBencode();
    auto check = getVectorChar("i10e");

    assert(result == check);
}

void ByteArrayParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<ByteArray>(ByteArray::parse(getVectorChar("2:23"), pos));
    auto check = getVectorChar("23");

    assert(result->getValue() == check);
}

void ByteArrayToBencodeTest() {
    auto result = ByteArray(getVectorChar("abc")).toBencode();
    auto check = getVectorChar("3:abc");

    assert(result == check);
}

void ListParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<List>(List::parse(getVectorChar("l1:xe"), pos));
    auto check = getVectorChar("x");

    assert(result->getValue().size() == 1);

    auto array = std::static_pointer_cast<ByteArray>(result->getValue()[0]);

    assert(array->getValue() == check);
}

void ListToBencodeTest() {
    auto result = List(std::vector<std::shared_ptr<Element>>{
            std::make_shared<Number>(7),
            std::make_shared<ByteArray>(getVectorChar("xyq"))
    }).toBencode();
    auto check = getVectorChar("li7e3:xyqe");

    assert(result == check);
}

void DictionaryParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<Dictionary>(Dictionary::parse(getVectorChar("d1:x1:xe"), pos));
    auto check = getVectorChar("x");

    assert(result->getValue().size() == 1);

    auto key = std::static_pointer_cast<ByteArray>(result->getValue().begin()->first);
    auto val = std::static_pointer_cast<ByteArray>(result->getValue().begin()->second);

    assert(key->getValue() == check);
    assert(val->getValue() == check);
}

void DictionaryToBencodeTest() {
    auto list = std::make_shared<List>(std::vector<std::shared_ptr<Element>>{
            std::make_shared<Number>(1),
            std::make_shared<ByteArray>(getVectorChar("b"))
    });

    auto result = Dictionary(DictionaryMap{
            {
                    std::make_shared<ByteArray>(getVectorChar("q")),
                    list
            }
    }).toBencode();
    auto check = getVectorChar("d1:qli1e1:bee");

    assert(result == check);
}

void bencodeElementParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<List>(Element::parse(getVectorChar("ll1:tee"), pos));
    auto check = getVectorChar("t");

    assert(result->getValue().size() == 1);

    auto list = std::static_pointer_cast<List>(result->getValue()[0]);

    assert(list->getValue().size() == 1);

    auto array = std::static_pointer_cast<ByteArray>(list->getValue()[0]);

    assert(array->getValue() == check);
}

int main() {
    // toBencode()
    NumberToBencodeTest();
    ByteArrayToBencodeTest();
    ListToBencodeTest();
    DictionaryToBencodeTest();

    // parse()
    NumberParseTest();
    ByteArrayParseTest();
    ListParseTest();
    DictionaryParseTest();
    bencodeElementParseTest();

    return 0;
}
