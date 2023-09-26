
#include<bits/stdc++.h>
using namespace std;

#ifndef FILETOKEN_HPP
#include "filetoken.hpp"
#endif

FileToken::FileToken(string file_name) {
    path_ = file_name;
    
    int size = file_name.size();
    int index = 0;

    string name;
    string ident;

    while (index+1<size 
        && (file_name[index]!='.'
        || ((file_name[index+1]=='.') 
        || (file_name[index+1]=='/')))) {
        if(file_name[index]=='/') {
            name = "";
        } else {
            name+=file_name[index];
        }
        index++;
    }
    if(index<size && file_name[index]!='.') name+=file_name[index++];

    if(index<size && file_name[index++]=='.') {
        while (index<size) {
            ident+=file_name[index++];
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

string FileToken::getPath() {
    return path_;
}

FileIdent FileToken::getIdent() {
    return ident_;
}

string FileToken::getName() {
    return name_;
}   