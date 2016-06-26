#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>

using namespace std;

class Folder;
class Message{
    friend class Folder;
    public:
    explicit Message(const string& str=""):
             contents(str) { };
    Message(const Message&);
    ~Message();
    Message& operator= (const Message&);
    void save(Folder&);
    void remove(Folder&);
    void print();
    private:
    string contents;
    set<Folder*> folders;
    void addFolder(Folder* pFolder){ folders.insert(pFolder);}
    void removeFolder(Folder* pFolder){ folders.erase(pFolder);}
    void addToFolders(const Message&);
    void removeFromFolders();
};
class Folder{
    friend class Message;
    public:
    Folder()=default;
    Folder(const Folder&);
    Folder& operator= (const Folder&);
    ~Folder();
    void print();
    private:
    set<Message*> messages;
    void addMessage(Message* pMes){ messages.insert(pMes);}
    void removeMessage(Message* pMes){ messages.erase(pMes);}
    void addToMessage(const Folder&);
    void removeFromMessage();
};

Message::Message(const Message& mes):
    contents(mes.contents),folders(mes.folders){
    addToFolders(mes);
}
Message::~Message(){
    removeFromFolders();
}
Message& Message::operator=(const Message& mes){
    removeFromFolders();
    contents=mes.contents;
    folders=mes.folders;
    addToFolders(mes);
    return *this;
}
void Message::save(Folder& folder){
    addFolder(&folder);
    folder.addMessage(this);
}
void Message::remove(Folder& folder){
    removeFolder(&folder);
    folder.removeMessage(this);
}
void Message::print(){
    cout<<contents<<endl;
    cout<<"save in "<<folders.size()<<" folders"<<endl;
}
void Message::addToFolders(const Message& mes){
    for(auto i:mes.folders)
        i->addMessage(this);
}
void Message::removeFromFolders(){
    for(auto i:folders)
        i->removeMessage(this);
}
Folder::Folder(const Folder& folder):
    messages(folder.messages){
    addToMessage(folder);
}
Folder& Folder::operator=(const Folder& folder){
    removeFromMessage();
    messages=folder.messages;
    addToMessage(folder);
    return *this;
}
Folder::~Folder(){
    removeFromMessage();
}
void Folder::print(){
    cout<<"the folder have "<<messages.size()<<" messages:";
    for(auto i:messages)
        cout<<i->contents<<" ";
    cout<<endl;
}
void Folder::addToMessage(const Folder& folder){
    for(auto i:folder.messages)
        i->addFolder(this);
}
void Folder::removeFromMessage(){
    for(auto i:messages)
        i->removeFolder(this);
}


int main()
{
    Message mes1("message1"),mes2("message2");
    Folder folder1,folder2;
    mes1.save(folder1);
    mes2.save(folder1);
    folder2=folder1;

    mes1.print();
    mes2.print();
    cout<<"folder1:";
    folder1.print();
    cout<<"folder2:";
    folder2.print();

    return 0;
}