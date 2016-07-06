#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <string>
#include <memory>
#include "Query_base.h"
#include "QueryResult.h"
#include "TextQuery.h"
#include "WordQuery.h"

class Query{
    friend Query operator ~ (const Query&);
    friend Query operator & (const Query&, const Query&);
    friend Query operator | (const Query&, const Query&);
public:
    Query(const std::string& s) : q(new WordQuery(s)) {
        std::cout << "Query::Query(const std::string& s) where s="+s+"" << std::endl;
    }
    QueryResult eval(const TextQuery& t) const {
        return q->eval(t);
    }
    std::string rep() const {
        std::cout << "Query::rep()" << std::endl;
        return q->rep();
    }
private:
    Query(std::shared_ptr<Query_base> query) : q(query) {
        std::cout << "Query::Query(std::shared_ptr<Query_base> query)" << std::endl;    
    }
    std::shared_ptr<Query_base> q;
};

inline std::ostream&
operator << (std::ostream& os, const Query& query) {
    return os << query.rep();
}

#endif