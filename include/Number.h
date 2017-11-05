#ifndef TORRENTO_NUMBER_H
#define TORRENTO_NUMBER_H

#include "Element.h"
#include <sstream>
#include <vector>

namespace Bencode {
    class Number : public Element {
    private:
        long value;

        Number() = default;

    public:
        explicit Number(long value) { this->value = value; };

        long getValue() { return this->value; }

        void setValue(long value) { this->value = value; }

        std::vector<char> toBencode();

        std::string toReadable(int deepness);

        static std::shared_ptr<Element> parse(std::vector<char> const &data, int &pos);
    };
}

#endif //TORRENTO_NUMBER_H
