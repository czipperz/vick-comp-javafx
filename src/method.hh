#ifndef HEADER_GUARD_METHOD_H
#define HEADER_GUARD_METHOD_H

#include <string>
#include <vector>

struct method {
    std::string return_type;
    std::string name;
    std::vector < std::pair<std::string,std::string> > params;

    std::string to_str();
};

#endif
