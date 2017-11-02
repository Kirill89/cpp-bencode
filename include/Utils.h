#ifndef TORRENTO_UTILS_H
#define TORRENTO_UTILS_H

#include "BadBencodeException.h"

class Utils {
private:
    Utils() = default;

public:
    static void incrementPosOrThrow(std::vector<char> const &data, int &pos) {
        if (pos + 1 >= data.size()) throw BadBencodeException();
        pos++;
    }

    static std::vector<char> getVectorChar(std::string str) {
        return std::vector<char>(str.begin(), str.end());
    }
};

#endif //TORRENTO_UTILS_H
