#include <iostream>
#include <fstream>
#include <memory>
#include "include/TorrentFile.h"
#include "include/BencodeDictionary.h"
#include "include/Utils.h"

int main() {
    std::ifstream file("ubuntu-17.04-desktop-amd64.iso.torrent");

    auto result = TorrentFile::readFile(file);

    file.close();

    auto data = std::dynamic_pointer_cast<BencodeDictionary>(result);
    auto search = Utils::getVectorChar("announce");

    if (data != nullptr) {
        for (const auto &element : data->getValue()) {
            auto key = std::static_pointer_cast<BencodeByteArray>(element.first);

            if (key->getValue() == search) {
                auto value = std::static_pointer_cast<BencodeByteArray>(element.second);

                value->setValue(Utils::getVectorChar("http://test.test"));
            }
        }
    }

    std::cout << result->toReadable() << std::endl;

    std::ofstream oFile("ubuntu-17.04-desktop-amd64.iso_2.torrent");

    TorrentFile::writeFile(oFile, result);

    file.close();

    return 0;
}
