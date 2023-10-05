
#include<bits/stdc++.h>
using namespace std;

#ifndef FILETOKEN_HPP
#include "filetoken.hpp"
#endif

FileToken::FileToken(string file_name) {
    path_ = file_name;
    setFields();
    return;
};

FileToken::FileToken(string target_file, string parent_file) {
    uint8_t endex_par = parent_file.size()-1;
    uint8_t endex_tar = target_file.size()-1;
    int index_par = endex_par-1;
    int index_tar = 0;
    while (endex_par>=0 && parent_file[index_par--] != '/') {
        ;
    }

    /*
        index_tar+1 < endex_par
        assumption::
            file doesn't end with only '.'
    */
    while (index_tar+1 < endex_par) {
        if(target_file[index_tar] == '.') {
            if(target_file[index_tar+1] == '.') {
                // if "../" exists
                while(index_par>=0 && parent_file[index_par--] != '/') {
                    ;
                }
                index_tar += 3;
            } else if(target_file[index_tar+1] == '/'){
                // if "./" exists
                index_tar += 2;
            }
        } else break;
    }

    string file_path;
    for(int i=0;i<=index_par;i++) {
        file_path += parent_file[i];
    }
    file_path += '/';
    for(int i=index_tar;i<endex_tar;i++) {
        file_path += target_file[i];
    }

    path_ = file_path;
    setFields();
    return;
}

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

void FileToken::setFields() {
    int size = path_.size();
    int index = 0;

    string name;
    string ident;

    while (index+1<size 
        && (path_[index]!='.'
        || ((path_[index+1]=='.') 
        || (path_[index+1]=='/')))) {
        if(path_[index]=='/') {
            name = "";
        } else {
            name+=path_[index];
        }
        index++;
    }
    if(index<size && path_[index]!='.') name+=path_[index++];

    if(index<size && path_[index++]=='.') {
        while (index<size) {
            ident+=path_[index++];
        }
    } 
    name_ = name;
    ident_ = toFileIdent(ident);
    return;
}

string FileToken::getCFile() const{
    int index = path_.size()-1;
    while (index>=0 && path_[index]!='.') {
        index--;
    }
    
    string ret;
    for (int i=0;i<index;i++) {
        ret += path_[i];
    }
    // this depends on how identifying header file
    ret += ".cpp";
    return ret;
}