#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>

struct method {
    std::string name;
    std::vector < std::pair<std::string,std::string> > params;
    std::string return_type;
    std::string to_str();
};

static const boost::regex
    constructor_start("<table class=\"memberSummary\".*summary=\"Constructor.*"),
    constructor_regex("^<td.*><code><span.*><a href=\".*\">(.+)</a></span>\\((.+)"),

    method_start("<table class=\"memberSummary\".*summary=\"Method.*"),
    method_type("^<td class=\"colFirst\"><code>(.+)</code></td>"),
    method_regex("^<td class=\"colLast\"><code><span.*><a\\s.*>(.+)</a>"),

    end("</table>.*");

static void constructor_p(std::vector<std::string>& lines,
                          std::vector<std::string>::iterator& it,
                          std::vector<method>& methods) {
    if(boost::regex_match(*it,constructor_regex)) {
        auto name = boost::regex_replace(*it,constructor_regex,"$1");
        auto params = boost::regex_replace(*it,constructor_regex,"$2");
        std::vector < std::pair<std::string,std::string> > params_vec;
        boost::regex reg("\\s*<a.*?>(.+)</a>&nbsp;(.+)[,)].*");
        if(boost::regex_match(params,reg)) {
#define body(__)                                                        \
            std::string _t = boost::regex_replace(__,reg,"$1"),         \
                _n = boost::regex_replace(__,reg,"$2");                 \
            params_vec.push_back(std::pair<std::string,std::string>(_t,_n));


            body(params);
            it++;
            for(; it < lines.end() && boost::regex_match(*it,reg); it++) {
                body(*it);
            }
#undef body
        }
        methods.push_back({ name, std::move(params_vec), name });
        // params_vec is **DEAD**
        std::cout << methods.back().to_str() << std::endl;
    }
}

static void methods_p(std::vector<std::string>& lines,
                      std::vector<std::string>::iterator& it,
                      std::vector<method>& methods) {
    if(boost::regex_match(*it,constructor_regex)) {
        std::string name = boost::regex_replace(*it,constructor_regex,"$1");
        std::string params = boost::regex_replace(*it,constructor_regex,"$2");
        std::vector < std::pair<std::string,std::string> > params_vec;
        boost::regex reg("\\s*<a.*?>(.+)</a>&nbsp;(.+)[,)].*");
        if(boost::regex_match(params,reg)) {
#define body(__)                                                        \
            std::string _t = boost::regex_replace(__,reg,"$1"),         \
                _n = boost::regex_replace(__,reg,"$2");                 \
            params_vec.push_back(std::pair<std::string,std::string>(_t,_n));


            body(params);
            it++;
            for(; it < lines.end() && boost::regex_match(*it,reg); it++) {
                body(*it);
            }
#undef body
        }
        methods.push_back({ name, std::move(params_vec), name });
        // params_vec is **DEAD**
        std::cout << methods.back().to_str() << std::endl;
    }
}

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
