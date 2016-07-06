#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>

class Quote{
    friend bool operator !=(const Quote&, const Quote&);
public:
    Quote()=default;
    Quote(const std::string& b, double p) : bookNo(b), price(p) {}
    Quote(const Quote& q) : bookNo(q.bookNo), price(q.price) {}
    Quote(const Quote&& q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price)) {}
    Quote& operator =(const Quote& rhs){
        if(*this!=rhs){
            bookNo=rhs.bookNo;
            price=rhs.price;
        }
        return *this;
    }
    Quote& operator =(Quote&& rhs) noexcept{
        if(*this!=rhs){
            bookNo=std::move(rhs.bookNo);
            price=std::move(rhs.price);
        }
        return *this;
    }
    virtual Quote* clone() const & {return new Quote(*this);}
    virtual Quote* clone() && {return new Quote(std::move(*this));}
    std::string    isbn() const {return bookNo;}
    virtual double net_price(std::size_t n) const {return n*price;}
    virtual ~Quote()=default;
private:
    std::string bookNo;
protected:
    double price = 10.0;
};

bool inline
operator != (const Quote& lhs, const Quote& rhs){
    return lhs.bookNo != rhs.bookNo && lhs.price != rhs.price;
}

double printTotal(std::ostream& os, const Quote& item, size_t n);

#endif