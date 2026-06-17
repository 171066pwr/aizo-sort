#ifndef BASICIO_H
#define BASICIO_H

#include <fstream>
#include <vector>

using namespace std;

class BasicIO {
protected:
    std::string filename;
public:
    std::fstream istream;
    std::fstream ostream;

    BasicIO();
    BasicIO(std::string filename, bool trunc = false);
    ~BasicIO();

    vector<std::string> readLines();
    std::string readLine();
    void writeLine(std::string line);
    void writeLn();
};


#endif //BASICIO_H
