#ifndef ORQUERY_H
#define ORQUERY_H

#include "Query_base.h"
#include "Query.h"

class OrQuery : public Query_base {
    friend Query operator | (const Query&, const Query&);
private:
    
};

#endif