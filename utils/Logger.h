#ifndef DERIVATIVES_LOGGER_H
#define DERIVATIVES_LOGGER_H

#include <iostream>

#include "../model/config/GlobalConfig.h"

using namespace std;
using namespace Globals;

class Logger {
public:
    static inline void log(const string& s) {
        cout << s << endl;
    }

    static inline void logInline(const string& s) {
        cout << s;
    }

    static inline void logProgress(const string& s) {
        if(Globals::DISPLAY_LOG >= Globals::PROGRESS)
            cout << s << endl;
    }

    static inline void logData(const string& s) {
        if(Globals::DISPLAY_LOG >= Globals::DATA)
            cout << s << endl;
    }

    static void logWithColor(const string &s, const string &color) {
        string c = "\033[" + color + "m" + s + "\033[0m";
        log(c);
    };

    static void warn(const string& s){
        logWithColor(s, "31");
    };

    static void important(const string& s){
        logWithColor(s, "93");
    };

    static void success(const string& s){
        logWithColor(s, "92");
    };

    static void title(const string &title){
        Logger::log("\n------------\t" + title + "        ------------");
    };
};

#endif //DERIVATIVES_LOGGER_H
