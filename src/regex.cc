#include <boost/regex.hpp>
#include <string>
#include <vector>

#include "method.hh"
#include "regex.hh"

const boost::regex
    constructor_start("<table class=\"memberSummary\".*summary=\"Constructor.*"),
    method_start("<table class=\"memberSummary\".*summary=\"Method.*"),
    end("</table>.*");

static const boost::regex
    constructor_regex("<td.*><code><span.*><a href=\".*\">(.+)</a></span>\\((.+)"),
    method_type("<td class=\"colFirst\"><code><a\\s.*?>(.+)</a></code></td>.*"),
    method_regex("<td class=\"colLast\"><code><span.*><a\\s.*?>(.+)</a></span>\\((.+)");

void constructor_p(std::vector<std::string>& lines,
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
        methods.push_back({ name, name, std::move(params_vec) });
        // params_vec is **DEAD**
        std::cout << methods.back().to_str() << std::endl;
    }
}

void methods_p(std::vector<std::string>& lines,
               std::vector<std::string>::iterator& it,
               std::vector<method>& methods) {
    // boost::regex method("<td class=\"colFirst\"><code><a\\s.*?>(.+)");
    // if(boost::regex_match(*it,method)) {
    //     std::cout << *it << std::endl;
    //     std::cout << '"' << boost::regex_replace(*it,method,"$1")
    //               << '"' << std::endl;
    // }
    if(boost::regex_match(*it,method_type)) {
        std::string type = boost::regex_replace(*it,method_type,"$1");
        it++;
        std::string name = boost::regex_replace(*it,method_regex,"$1");
        std::string params = boost::regex_replace(*it,method_regex,"$2");
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
        methods.push_back({ type, name, std::move(params_vec) });
        // params_vec is **DEAD**
        std::cout << methods.back().to_str() << std::endl;
    }
}
