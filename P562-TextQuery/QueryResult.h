#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>

class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult);
public:
    using lineNo = std::vector<std::string>::size_type;
    QueryResult (std::string s,
                 std::shared_ptr<std::set<lineNo>> p,
                 std::shared_ptr<std::vector<std::string>> f) :
        sought(s), lines(p), file(f) {}
private:
    std::string sought;
    std::shared_ptr<std::set<lineNo>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

#endif