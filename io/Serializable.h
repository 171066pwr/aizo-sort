#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H


struct Serializable {
    virtual ~Serializable() {}

    virtual std::string serialize() const = 0;
};


#endif //SERIALIZABLE_H
