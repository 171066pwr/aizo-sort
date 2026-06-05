#ifndef DISPLAYDATACONFIG_H
#define DISPLAYDATACONFIG_H
#include <string>


struct DisplayDataConfig: public virtual Serializable, public virtual Printable  {
    virtual ~DisplayDataConfig() = default;

    bool display;

    DisplayDataConfig(bool display = true): display(display) {};

    virtual std::string toString() const override {
        return "Display data: " + std::to_string(display);
    }

    virtual std::string serialize() const override {
        return "DISPLAY_DATA:"+ std::to_string(display);
    }
};



#endif //DISPLAYDATACONFIG_H
