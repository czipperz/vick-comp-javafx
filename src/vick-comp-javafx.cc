#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>

#include "regex.hh"

std::vector<std::string> get_lines(const char*const path) {
    std::vector<std::string> lines;
    std::string line;
    lines.reserve(1000);
    std::ifstream myfile(path);
    while(std::getline(myfile,line)) {
        lines.push_back(line);
    }
    return lines;
}

int main() {
    std::string line;
    std::vector<std::string> lines =
        get_lines("api/javafx/application/Preloader.ErrorNotification.html"
                  // "api/javafx/application/HostServices.html"
                  );
    std::vector<method> methods;
    for(auto it = lines.begin(); it < lines.end(); it++) {
        if(boost::regex_match(*it,constructor_start)) {
            it++;
            for(; it < lines.end() && !boost::regex_match(*it,end); it++) {
                constructor_p(lines,it,methods);
            }
        }
        if(boost::regex_match(*it,method_start)) {
            it++;
            for(; it < lines.end() && !boost::regex_match(*it,end); it++) {
                methods_p(lines,it,methods);
            }
        }
    }
    return 0;
}

std::string method::to_str() {
    std::string par(return_type + " " + name + "(");
    for(std::vector < std::pair<std::string,std::string> >::iterator
            pair = params.begin(); pair < params.end(); pair++) {
        par += pair->first;
        par += ' ';
        par += pair->second;
        if(pair < params.end() - 1) par += ", ";
    }
    par += ')';
    return par;
}
