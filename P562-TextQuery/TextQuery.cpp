#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "TextQuery.h"

TextQuery::TextQuery(std::ifstream& is) : file(new std::vector<std::string>) {
    std::string text;
    while(std::getline(is,text)) {
        file->push_back(text);
        int n = file->size()-1;
        std::istringstream line(text);
        std::string word;
        while(line >> word) {
            auto &lines = wordMap[word];
            if(!lines)
                lines.reset(new std::set<lineNo>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string& str) const {
    static shared_ptr<std::set<lineNo>> nodata(new std::set<lineNo>);
    auto found = wordMap.find(str);
    if(found == wordMap.end())
        return QueryResult(str, nodate, file);
    else
        return QueryResult(str, found->second, file);
}