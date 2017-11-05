#ifndef TORRENTO_LIST_H
#define TORRENTO_LIST_H

#include "Element.h"
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>

namespace Bencode {
    typedef std::vector<std::shared_ptr<Element>> ListVector;

    class List : public Element {
    private:
        ListVector value;

        List() = default;

    public:
        explicit List(ListVector &&value) { this->value = std::move(value); }

        explicit List(ListVector &value) { this->value = ListVector(value); }

        ListVector getValue() { return this->value; }

        void setValue(ListVector &&value) { this->value = std::move(value); }

        void setValue(ListVector &value) { this->value = ListVector(value); }

        std::vector<char> toBencode();

        std::string toReadable(int deepness);

        static std::shared_ptr<Element> parse(std::vector<char> const &data, int &pos);
    };
}

#endif //TORRENTO_LIST_H
