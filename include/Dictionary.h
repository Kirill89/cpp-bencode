#ifndef TORRENTO_DICTIONARY_H
#define TORRENTO_DICTIONARY_H

#include "Element.h"
#include "ByteArray.h"
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>
#include <map>

namespace Bencode {
    typedef std::map<std::shared_ptr<ByteArray>, std::shared_ptr<Element>> DictionaryMap;

    class Dictionary : public Element {
    private:
        DictionaryMap value;

        Dictionary() = default;

    public:
        explicit Dictionary(DictionaryMap &&value) { this->value = std::move(value); }

        explicit Dictionary(DictionaryMap &value) { this->value = DictionaryMap(value); }

        DictionaryMap getValue() { return this->value; }

        void setValue(DictionaryMap &&value) { this->value = std::move(value); }

        void setValue(DictionaryMap &value) { this->value = DictionaryMap(value); }

        std::vector<char> toBencode() const;

        std::string toReadable(int deepness) const;

        static std::shared_ptr<Element> parse(std::vector<char> const &data, int &pos);
    };
}

#endif //TORRENTO_DICTIONARY_H
