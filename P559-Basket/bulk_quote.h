#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H

#include "disc_quote.h"

class Bulk_quote : public Disc_quote{
public:
    Bulk_quote() {}
    using Disc_quote::Disc_quote;
    Bulk_quote(const Bulk_quote& bq) : Disc_quote(bq) {}
    Bulk_quote(Bulk_quote&& bq) : Disc_quote(std::move(bq)) {}
    Bulk_quote& operator =(const Bulk_quote& rhs) {
        Disc_quote::operator =(rhs);
        return *this;
    }
    Bulk_quote& operator =(Bulk_quote&& rhs) {
        Disc_quote::operator =(std::move(rhs));
        return *this;
    }
    virtual Bulk_quote* clone() const & {return new Bulk_quote(*this);}
    virtual Bulk_quote* clone() const && {return new Bulk_quote(std::move(*this));}
    double net_price(std::size_t n) const override;
    ~Bulk_quote() override {}

};

#endif