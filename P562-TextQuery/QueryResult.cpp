#include <iostream>
#include <memory>

#include "QueryResult.h"

std::ostream& print(std::ostream& os, const QueryResult& qr) {
    os << qr.sought << "occurs" << qr.lines->size()
        << (qr.lines->size() > 1 ? "times" : "time") << std::endl;
    for(auto i : *qr.lines)
        os << "\t(line" << i+1 << ")" <<qr.file->at(i) << std::endl;
    return os;
}