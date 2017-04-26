#ifndef KUI_EASY_EXCEPTION_H
#define KUI_EASY_EXCEPTION_H

#include <exception>
#include <sstream>

#define KUI_EASY_EXCEPTION(NAME, MESSAGE) \
class NAME: public std::exception { \
public: \
    NAME() { \
      my_what = MESSAGE; \
    } \
    virtual const char* what() const noexcept { return my_what.c_str(); } \
private: \
    std::string my_what; \
};

#endif