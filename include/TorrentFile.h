#ifndef TORRENTO_TORRENTFILE_H
#define TORRENTO_TORRENTFILE_H

#include <fstream>
#include "BencodeElement.h"

class TorrentFile {
private:
    TorrentFile() = default;

public:
    static std::shared_ptr<BencodeElement> readFile(std::ifstream &file);

    static void writeFile(std::ofstream &file, std::shared_ptr<BencodeElement> element);
};


#endif //TORRENTO_TORRENTFILE_H
