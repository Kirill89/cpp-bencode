#include "../include/TorrentFile.h"
#include "../include/BencodeDictionary.h"

std::shared_ptr<BencodeElement> TorrentFile::readFile(std::ifstream &file) {
    if (!file.is_open() || file.eof() || file.fail()) {
        return nullptr;
    }

    std::vector<char> data;
    int pos = 0;

    file.seekg(0, std::ios_base::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios_base::beg);

    data.reserve(fileSize);

    data.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    return BencodeDictionary::parse(data, pos);
}


void TorrentFile::writeFile(std::ofstream &file, std::shared_ptr<BencodeElement> element) {
    if (!file.is_open() || file.fail()) {
        return;
    }

    auto data = element->toBencode();

    file.write(&data[0], data.size());
}
