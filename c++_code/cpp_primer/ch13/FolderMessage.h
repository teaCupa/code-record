//
// Created by teagm on 2023/4/16.
//

#ifndef CPP_PRIMER_FOLDERMESSAGE_H
#define CPP_PRIMER_FOLDERMESSAGE_H

#include <set>
#include <string>

class Folder;

class Message{
    friend void swap(Message&,Message&);
    friend class Folder;
public:
    explicit Message(std::string str="") : contents(std::move(str)){}
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();

    void save(Folder&);
    void remove(Folder&);

    void print_debug();
private:
    void add_to_folders(const Message&);
    void remove_from_folders();


private:
    std::string contents;
    std::set<Folder*> folders;
};

void swap(Message&,Message&);


/// Folder

class Folder{
    friend void swap(Folder&,Folder&);
public:
    Folder() = default;
    explicit Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();

    void addMsg(Message*);
    void removeMsg(Message*);
    void print_debug();
private:
   std::set<Message*> msgs;

    void add_to_msg(const Folder&);
    void remove_from_msg();
};

void swap(Folder&,Folder&);


#endif //CPP_PRIMER_FOLDERMESSAGE_H
