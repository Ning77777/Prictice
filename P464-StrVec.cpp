#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <utility>

using namespace std;

class StrVec{
public:
    StrVec():
        elements(nullptr),first_free(nullptr),cap(nullptr) { }
    StrVec(const StrVec&);
    StrVec& operator= (const StrVec&);
    ~StrVec();
    void push_back(const string&);
    size_t size() const;
    size_t capacity() const;
    string* begin() const;
    string* end() const;
    void print();
private:
    allocator<string> alloc;
    void chk_n_alloc();
    pair<string*,string*> alloc_n_copy(const string*,const string*);
    void free();
    void reallocate();
    string* elements;
    string* first_free;
    string* cap;
};
StrVec::StrVec(const StrVec& sv){
    auto pPair=alloc_n_copy(sv.begin(),sv.end());
    elements=pPair.first;
    first_free=cap=pPair.second;
}
StrVec& StrVec::operator= (const StrVec& sv){
    auto pPair=alloc_n_copy(sv.begin(),sv.end());
    free();
    elements=pPair.first;
    first_free=cap=pPair.second;
    return *this;
}
StrVec::~StrVec(){
    free();
}
void StrVec::push_back(const string& str){
    chk_n_alloc();
    alloc.construct(first_free++,str);
}
size_t StrVec::size() const{
    return size_t(first_free-elements);
}
size_t StrVec::capacity() const{
    return size_t(cap-elements);
}
string* StrVec::begin() const{
    return elements;
}
string* StrVec::end() const{
    return first_free;
}
void StrVec::chk_n_alloc(){
    if(size()==capacity())
        reallocate();
}
pair<string*,string*> StrVec::alloc_n_copy(const string* begin,const string* end){
    auto first=alloc.allocate(end-begin);
    return {first,uninitialized_copy(begin,end,first)};
}
void StrVec::free(){
    if(elements){
        for(auto p=first_free;p!=elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements,cap-elements);
    }
}
void StrVec::reallocate(){
    auto newCapcity=size()?size()*2:1;
    auto newElements=alloc.allocate(newCapcity);
    auto p=newElements;
    auto elem=elements;
    for(size_t i=0;i!=size();++i)
        alloc.construct(p++,move(*elem++));
    free();
    elements=newElements;
    first_free=p;
    cap=elements+newCapcity;
}
void StrVec::print(){
    cout<<"size:"<<size()<<endl;
    cout<<"capacity:"<<capacity()<<endl;
    cout<<"strings:";
    for(auto i=elements;i!=first_free;i++)
        cout<<*i<<" ";
    cout<<endl;
}

int main()
{
    StrVec test1,test2;
    test1.push_back("str1");
    cout<<"test1:"<<endl;
    test1.print();
    test1.push_back("str2");
    test1.print();
    test2=test1;
    cout<<"test2:"<<endl;
    test2.print();
    return 0;
}
