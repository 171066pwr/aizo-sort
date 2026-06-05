#include "BasicIO.h"
#include <ctime>

BasicIO::BasicIO() {
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S.txt", local);
    filename = std::string(buffer);
    ostream.open(filename, fstream::out | fstream::trunc);
    istream.open(filename, fstream::in);
}

BasicIO::BasicIO(std::string filename, bool trunc): filename(filename) {
    ostream.open(filename, trunc ? fstream::out | fstream::trunc : fstream::out | fstream::app);
    istream.open(filename, fstream::in);
}

BasicIO::~BasicIO() {
    istream.close();
    ostream.close();
}

std::string BasicIO::readLine() {
    std::string line;
    std::getline (istream, line);
    return line;
}

void BasicIO::writeLine(std::string line) {
    ostream << line << std::endl;
}

void BasicIO::writeLn() {
    ostream << std::endl;
}
