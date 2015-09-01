#ifndef HEADER_GUARD_REGEX_H
#define HEADER_GUARD_REGEX_H

#include <vector>
#include <string>
#include <boost/regex.hpp>

#include "method.hh"

extern const boost::regex
    constructor_start,
    method_start,
    end;

void constructor_p(std::vector<std::string>& lines,
                   std::vector<std::string>::iterator& it,
                   std::vector<method>& methods);

void methods_p(std::vector<std::string>& lines,
               std::vector<std::string>::iterator& it,
               std::vector<method>& methods);

#endif
