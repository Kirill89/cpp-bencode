#ifndef TORRENTO_BENCODENUMBER_H
#define TORRENTO_BENCODENUMBER_H

#include "../include/BencodeElement.h"
#include <sstream>
#include <vector>

class BencodeNumber : public BencodeElement {
private:
    long value;

    BencodeNumber() = default;

public:
    explicit BencodeNumber(long value) { this->value = value; };

    long getValue() { return this->value; }

    void setValue(long value) { this->value = value; }

    std::vector<char> toBencode();

    std::string toReadable(int deepness);

    static std::shared_ptr<BencodeElement> parse(std::vector<char> const &data, int &pos);
};

#endif //TORRENTO_BENCODENUMBER_H
