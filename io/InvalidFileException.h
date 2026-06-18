#ifndef INVALIDFILEEXCEPTION_H
#define INVALIDFILEEXCEPTION_H


/* Util types and methods */
class InvalidFileException : public std::exception {
private: string message;

public:
    InvalidFileException(const string& message = "Cannot read or parse from file") {
        this -> message = "Cannot read or parse from file: " + message;
    }

    const char *what() const noexcept override  {
        return message.c_str();
    }
};


#endif //INVALIDFILEEXCEPTION_H
