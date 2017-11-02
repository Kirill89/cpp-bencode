#include <cassert>
#include "include/BencodeNumber.h"
#include "include/BencodeByteArray.h"
#include "include/BencodeList.h"
#include "include/BencodeDictionary.h"

void bencodeNumberParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<BencodeNumber>(
            BencodeNumber::parse(std::vector<char>{'i', '1', '2', '3', 'e'}, pos));

    assert(result->getValue() == 123);
}

void bencodeNumberToBencodeTest() {
    auto result = BencodeNumber(10).toBencode();
    auto check = std::vector<char>{'i', '1', '0', 'e'};

    assert(result == check);
}

void bencodeByteArrayParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<BencodeByteArray>(
            BencodeByteArray::parse(std::vector<char>{'2', ':', '2', '3'}, pos));
    auto check = std::vector<char>{'2', '3'};

    assert(result->getValue() == check);
}

void bencodeByteArrayToBencodeTest() {
    auto result = BencodeByteArray(std::vector<char>{'a', 'b', 'c'}).toBencode();
    auto check = std::vector<char>{'3', ':', 'a', 'b', 'c'};

    assert(result == check);
}

void bencodeListParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<BencodeList>(
            BencodeList::parse(std::vector<char>{'l', '1', ':', 'x', 'e'}, pos));
    auto check = std::vector<char>{'x'};

    assert(result->getValue().size() == 1);

    auto array = std::static_pointer_cast<BencodeByteArray>(result->getValue()[0]);

    assert(array->getValue() == check);
}

void bencodeListToBencodeTest() {
    auto result = BencodeList(std::vector<std::shared_ptr<BencodeElement>>{
            std::make_shared<BencodeNumber>(7),
            std::make_shared<BencodeByteArray>(std::vector<char>{'x', 'y', 'q'})
    }).toBencode();
    auto check = std::vector<char>{'l', 'i', '7', 'e', '3', ':', 'x', 'y', 'q', 'e'};

    assert(result == check);
}

void bencodeDictionaryParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<BencodeDictionary>(
            BencodeDictionary::parse(std::vector<char>{'d', '1', ':', 'x', '1', ':', 'x', 'e'}, pos));
    auto check = std::vector<char>{'x'};

    assert(result->getValue().size() == 1);

    auto key = std::static_pointer_cast<BencodeByteArray>(result->getValue().begin()->first);
    auto val = std::static_pointer_cast<BencodeByteArray>(result->getValue().begin()->second);

    assert(key->getValue() == check);
    assert(val->getValue() == check);
}

void bencodeDictionaryToBencodeTest() {
    auto list = std::make_shared<BencodeList>(std::vector<std::shared_ptr<BencodeElement>>{
            std::make_shared<BencodeNumber>(1),
            std::make_shared<BencodeByteArray>(std::vector<char>{'b'})
    });

    auto result = BencodeDictionary(BencodeDictionaryMap{
            {
                    std::make_shared<BencodeByteArray>(std::vector<char>{'q'}),
                    list
            }
    }).toBencode();
    auto check = std::vector<char>{'d', '1', ':', 'q', 'l', 'i', '1', 'e', '1', ':', 'b', 'e', 'e'};

    assert(result == check);
}

void bencodeElementParseTest() {
    auto pos = 0;
    auto result = std::static_pointer_cast<BencodeList>(
            BencodeElement::parse(std::vector<char>{'l', 'l', '1', ':', 't', 'e', 'e'}, pos));
    auto check = std::vector<char>{'t'};

    assert(result->getValue().size() == 1);

    auto list = std::static_pointer_cast<BencodeList>(result->getValue()[0]);

    assert(list->getValue().size() == 1);

    auto array = std::static_pointer_cast<BencodeByteArray>(list->getValue()[0]);

    assert(array->getValue() == check);
}

int main() {
    // toBencode()
    bencodeNumberToBencodeTest();
    bencodeByteArrayToBencodeTest();
    bencodeListToBencodeTest();
    bencodeDictionaryToBencodeTest();

    // parse()
    bencodeNumberParseTest();
    bencodeByteArrayParseTest();
    bencodeListParseTest();
    bencodeDictionaryParseTest();
    bencodeElementParseTest();

    return 0;
}
