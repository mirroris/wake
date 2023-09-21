
#include<bits/stdc++.h>
using namespace std;

#ifndef FILETOKEN_HPP
#include "filetoken.hpp"
#endif

FileToken::FileToken(string file_name) {
    token_ = file_name;
    
    int size = file_name.size();
    int index = 0;

    string name;
    string ident;

    while (index<size && file_name[index]!='.') {
        if(file_name[index]=='/') {
            name = "";
        } else {
            name+=file_name[index];
        }

    }

    if(index<size && file_name[index]=='.') {
        while (index<size) {
            ident+=file_name[index];
        }
    } 

    name_ = name;
    ident_ = toFileIdent(ident);
    return;
};

FileIdent FileToken::toFileIdent(string ident) {
    unordered_map<string, FileIdent> id({{"cpp", CPP}, {"cc", CC}, {"c", C}, {"hpp", HPP}, {"h", H}});
    auto key = id.find(ident);
    if (key!=id.end()) {
        return id[ident];
    } else {
        return NONE;
    }
}

FileIdent FileToken::getIdent() {
    return ident_;
}

string FileToken::getName() {
    return name_;
}   