#include <iostream>

#include "model/TableGenerator.h"
#include "io/BasicIO.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    TableGenerator tableGenerator = TableGenerator();

    SorTable<int> * sorTable = tableGenerator.generateIntTable(10);
    sorTable->print();

    SorTable<int> * sorTable2 = sorTable->clone();

    delete sorTable;
    sorTable2->print();

    BasicIO wio = BasicIO("test.txt");
    string s = sorTable2->getType();
    wio.writeLine(s);
    wio.writeLine("1");
    wio.writeLine("2");
    wio.writeLine("3");


    cout << wio.readLine() << endl;
    wio.writeLine("4");
    cout << wio.readLine() << endl;
    wio.~BasicIO();

    // fstream file;
    // file.open("test.txt", std::ios::out);
    // file << "kopytko" << std::endl;
    // file << "kopytko2";
    // fstream stream;
    // stream.open("test.txt", fstream::in | fstream::app);
    // std::string line;
    // std::getline (stream, line);
    // std::cout << "AAAH: " << line << std::endl;
    // std::getline (stream, line);
    // std::cout << "AAAH2: " << line;
    // file.close();
    // stream.close();
    system("pause");
}
