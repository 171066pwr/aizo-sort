#ifndef BASICIO_H
#define BASICIO_H
#include <iostream>
#include <fstream>

using namespace std;

class BasicIO {
public:
    const std::string filename;
    std::fstream istream;
    std::fstream ostream;

    BasicIO(std::string filename, bool trunc = false);
    ~BasicIO();

    std::string readLine();
    void writeLine(std::string line);
    void writeLn();
};



#endif //BASICIO_H
