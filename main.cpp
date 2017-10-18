#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include <sstream>

using namespace std;

class BadBencodeException : public exception {
public:
    const char *what() const throw() override {
        return "Wrong bencode markup";
    }
};

class BencodeElement {
public:
    static shared_ptr<BencodeElement> parse(char *&it, char *end);

    virtual string print(int deepness = 0) = 0;
};


class BencodeNumber : public BencodeElement {
private:
    long value;

    BencodeNumber() = default;

public:
    explicit BencodeNumber(long value) { this->value = value; };

    long getValue() { return this->value; }

    static shared_ptr<BencodeElement> parse(char *&it, char *end);

    string print(int deepness = 0) {
        stringstream ss;
        ss << string(deepness, '\t') << "<number>" << this->value << "</number>" << endl;
        return ss.str();
    };
};

class BencodeList : public BencodeElement {
private:
    vector<shared_ptr<BencodeElement>> value;

    BencodeList() = default;

public:
    explicit BencodeList(vector<shared_ptr<BencodeElement>> &&value) { this->value = move(value); }

    explicit BencodeList(vector<shared_ptr<BencodeElement>> &value) { this->value = value; }

    vector<shared_ptr<BencodeElement>> getValue() { return this->value; }

    static shared_ptr<BencodeElement> parse(char *&it, char *end);

    string print(int deepness = 0) {
        stringstream ss;

        ss << string(deepness, '\t') << "<list>" << endl;

        for (const auto &element : this->value) {
            ss << element->print(deepness + 1);
        }

        ss << string(deepness, '\t') << "</list>" << endl;

        return ss.str();
    };
};

class BencodeDictionary : public BencodeElement {
private:
    vector<shared_ptr<BencodeElement>> value;

    BencodeDictionary() = default;

public:
    explicit BencodeDictionary(vector<shared_ptr<BencodeElement>> &&value) { this->value = move(value); }

    explicit BencodeDictionary(vector<shared_ptr<BencodeElement>> &value) { this->value = value; }

    vector<shared_ptr<BencodeElement>> getValue() { return this->value; }

    static shared_ptr<BencodeElement> parse(char *&it, char *end);

    string print(int deepness = 0) {
        stringstream ss;

        ss << string(deepness, '\t') << "<dict>" << endl;

        for (const auto &element : this->value) {
            ss << element->print(deepness + 1);
        }

        ss << string(deepness, '\t') << "</dict>" << endl;

        return ss.str();
    };
};

class BencodeByteArray : public BencodeElement {
private:
    vector<char> value;

    BencodeByteArray() = default;

public:
    explicit BencodeByteArray(vector<char> &value) { this->value = value; };

    explicit BencodeByteArray(vector<char> &&value) { this->value = move(value); };

    vector<char> getValue() { return this->value; }

    static shared_ptr<BencodeElement> parse(char *&it, char *end);

    string print(int deepness = 0) {
        stringstream ss;

        ss << string(deepness, '\t') << "<array>";

        for (char c : this->value) {
            ss << c;
        }

        ss << "</array>" << endl;

        return ss.str();
    };
};

shared_ptr<BencodeElement>
BencodeElement::parse(char *&it, char *end) {
    if (*it == 'i') {
        it++;
        return BencodeNumber::parse(it, end);
    } else if (*it >= '0' && *it <= '9') {
        return BencodeByteArray::parse(it, end);
    } else if (*it == 'l') {
        it++;
        return BencodeList::parse(it, end);
    } else if (*it == 'd') {
        it++;
        return BencodeDictionary::parse(it, end);
    } else {
        throw BadBencodeException();
    }
};

shared_ptr<BencodeElement>
BencodeNumber::parse(char *&it, char *end) {
    string data;

    while (*it != 'e' && it != end) {
        data += *it;
        it++;
    }

    if (*it == 'e') it++;

    return make_shared<BencodeNumber>(stol(data));
};

shared_ptr<BencodeElement> BencodeList::parse(char *&it, char *end) {
    vector<shared_ptr<BencodeElement>> elements;

    while (*it != 'e' && it != end) {
        elements.push_back(BencodeElement::parse(it, end));
    }

    if (*it == 'e') it++;

    return make_shared<BencodeList>(elements);
};

shared_ptr<BencodeElement>
BencodeDictionary::parse(char *&it, char *end) {
    // TODO

    vector<shared_ptr<BencodeElement>> elements;

    while (*it != 'e' && it != end) {
        elements.push_back(BencodeElement::parse(it, end));
    }

    if (*it == 'e') it++;

    return make_shared<BencodeDictionary>(elements);
};

shared_ptr<BencodeElement>
BencodeByteArray::parse(char *&it, char *end) {
    string lengthStr;

    while (*it != ':' && it != end) {
        lengthStr += *it;
        it++;
    }

    it++;

    long length = stol(lengthStr);

    vector<char> data;

    while (length-- && it != end) {
        data.push_back(*it);
        it++;
    }

    return make_shared<BencodeByteArray>(data);
};

int main() {
    ifstream file;

    file.open("ubuntu-17.04-desktop-amd64.iso.torrent");

    if (file.is_open() && !file.eof() && !file.fail()) {
        char *data;

        file.seekg(0, ios_base::end);
        streampos fileSize = file.tellg();

        data = new char[fileSize];

        file.seekg(0, ios_base::beg);
        file.read(data, fileSize);

        auto x = BencodeList::parse(data, &data[fileSize]);

        cout << x->print() << endl;

        delete data;

        file.close();
    }

    cout << "End." << endl;
    return 0;
}
