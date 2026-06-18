#ifndef DISPLAYDATACONFIG_H
#define DISPLAYDATACONFIG_H

#include <string>

#include "GlobalConfig.h"

struct DisplayDataConfig: public virtual Serializable, public virtual Printable  {
    virtual ~DisplayDataConfig() = default;

    Globals::DisplaySetting display;

    DisplayDataConfig(Globals::DisplaySetting display = Globals::DATA): display(display) {};

    DisplayDataConfig(int display): display((Globals::DisplaySetting) (display%3)) {};

    static DisplayDataConfig deserialize(const string &s) {
        if(s.empty() || s[0] == '2') return DisplayDataConfig(Globals::DATA);
        return DisplayDataConfig(std::stoi(s));
    }

    virtual std::string toString() const override {
        return "Display data: " + std::to_string(display);
    }

    virtual std::string serialize() const override {
        return "DISPLAY_DATA:"+ std::to_string(display);
    }
};



#endif //DISPLAYDATACONFIG_H
