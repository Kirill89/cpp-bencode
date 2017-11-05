#ifndef TORRENTO_TORRENTFILE_H
#define TORRENTO_TORRENTFILE_H

#include <fstream>
#include "Element.h"

using namespace Bencode;

class TorrentFile {
private:
    TorrentFile() = default;

public:
    static std::shared_ptr<Element> readFile(std::ifstream &file);

    static void writeFile(std::ofstream &file, std::shared_ptr<Element> element);
};


#endif //TORRENTO_TORRENTFILE_H
