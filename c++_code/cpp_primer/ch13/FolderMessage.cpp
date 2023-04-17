//
// Created by teagm on 2023/4/16.
//

#include "FolderMessage.h"
#include <iostream>

// Message Implementation

Message::Message(const Message& m)
    : contents(m.contents), folders(m.folders){
    add_to_folders(m);
}

Message& Message::operator=(const Message& rhs) {
    remove_from_folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}

Message::~Message() {
    remove_from_folders();
}

void Message::add_to_folders(const Message& m){
    for(auto p: m.folders){
        p->addMsg(this);
    }
}

void Message::remove_from_folders(){
    for(auto p: this->folders){
        p->removeMsg(this);
    }
}

void Message::save(Folder& f){
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder& f){
    folders.erase(&f);
    f.removeMsg(this);
}


void Message::print_debug(){
    std::cout << contents << std::endl;
}

void swap(Message &lhs, Message &rhs) {
    using std::swap;
    lhs.remove_from_folders();
    rhs.remove_from_folders();

    swap(lhs.contents,rhs.contents);
    swap(lhs.folders,rhs.folders);

    lhs.add_to_folders(lhs);
    rhs.add_to_folders(rhs);
}


// Folder Implementation

void swap(Folder& lhs, Folder& rhs){
    using std::swap;
    lhs.remove_from_msg();
    rhs.remove_from_msg();

    swap(lhs.msgs,rhs.msgs);

    lhs.add_to_msg(lhs);
    rhs.add_to_msg(rhs);
}

Folder::Folder(const Folder& rhs)
    : msgs(rhs.msgs)
{
    add_to_msg(rhs);
}

Folder& Folder::operator=(const Folder &rhs) {
    remove_from_msg();
    msgs = rhs.msgs;
    add_to_msg(rhs);
    return *this;
}

Folder::~Folder() {
    remove_from_msg();
}

void Folder::add_to_msg(const Folder &rhs)  {
    for(auto pm : rhs.msgs)
        pm->folders.insert(this);
}

void Folder::remove_from_msg()  {
    for(auto pm: msgs)
        pm->folders.erase(this);
}


void Folder::addMsg(Message* msg){
    msgs.insert(msg);
}

void Folder::removeMsg(Message* msg){
    msgs.erase(msg);
}

void Folder::print_debug(){
    for(auto m: msgs)
        std::cout << m->contents <<" ";
    std::cout << std::endl;
}


int main(){
    Message m1("QQ mail");
    Folder f;
    f.addMsg(&m1);
    m1.save(reinterpret_cast<Folder &>(f));
    m1.print_debug();
    f.print_debug();
}