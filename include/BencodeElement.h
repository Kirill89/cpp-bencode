#ifndef TORRENTO_BENCODEELEMENT_H
#define TORRENTO_BENCODEELEMENT_H

#include <memory>
#include <string>
#include <vector>

class BencodeElement {
public:
    virtual std::string toReadable(int deepness = 0) = 0;

    virtual std::vector<char> toBencode() = 0;

    static std::shared_ptr<BencodeElement> parse(std::vector<char> const &data, int &pos);
};

#endif //TORRENTO_BENCODEELEMENT_H
