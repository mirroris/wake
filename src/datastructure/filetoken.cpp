
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

string FileToken::getPath() const{
    return path_;
}

FileIdent FileToken::getIdent() const{
    return ident_;
}

string FileToken::getName() const{
    return name_;
}   

bool FileToken::isCFile() const {
    return (ident_==C) || (ident_==CC) || (ident_==CPP);
}

bool FileToken::isHFile() const {
    return (ident_==H) || (ident_==HPP);
}

string FileToken::getObjFile() const {
    // skipping the './' if it exists
    int left = (path_[0]=='.')? 2: 0;
    int right = path_.size()-1;
    while (right>=0 && path_[right]!='.') {
        right--;
    }
    string ret = "$(BINDIR)/";
    for (int i=left;i<=right;i++) {
        ret += path_[i];
    }
    ret += 'o';
    return ret;
}
