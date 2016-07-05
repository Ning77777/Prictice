#ifndef DISC_QUOTE_H
#define DISC_QUOTE_H

#include "quote.h"

class Disc_quote : public Quote{
    friend bool operator !=(const Disc_quote& lhs, const Disc_quote& rhs);
public:
    Disc_quote() {}
    Disc_quote(const std::string& b, double p, std::size_t q, double d) :
        Quote(b, p), quantity(q), discount(d){}
    Disc_quote(Disc_quote& dq) : 
        Quote(dq), quantity(dq.quantity), discount(dq.discount){}
    Disc_quote(Disc_quote&& dq) noexcept :
        Quote(std::move(dq)), quantity(std::move(dq.quantity)), discount(std::move(dq.discount)) {}
    Disc_quote& operator =(const Disc_quote& rhs){
        Quote::operator = (rhs);
        this->quantity = rhs.quantity;
        this->discount = rhs.discount;
        return *this;
    }
    Disc_quote& operator =(Disc_quote&& rhs) noexcept{
        if(*this!=rhs){
            Quote::operator =(std::move(rhs));
            this->quantity = std::move(rhs.quantity);
            this->discount = std::move(rhs.discount);
        }
        return *this;
    }
    virtual double net_price(std::size_t n) const override =0;
    ~Disc_quote() {}

protected:
    std::size_t quantity = 3;
    double      discount = 0.0;
};

bool inline
operator !=(const Disc_quote& lhs; const Disc_quote& rhs){
    return Quote(lhs) != Quote(rhs)
           &&
           lhs.quantity != rhs.quantity
           &&
           lhs.discount != rhs.discount;
}

#endif
