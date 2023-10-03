#ifndef DEPTREE_HPP
#include "deptree.hpp"
#endif

#include <bits/stdc++.h>

using namespace std;

void Deptree::depends(FileToken file_path) {
    if(file_path.getName() != FileToken(file_path_).getName()) file_list_.push_back(file_path.getName());
    return;
}

void Deptree::expl(string line) {
    int index_line = 0;
    int size_line = line.size();

    int index_incl = 0;
    int size_incl = kIncludeToken.size();

    while (index_line<size_line) {
        switch (current_status_){
            case CODE:
                if( index_line+1 < size_line && line[index_line] == '/') {
                    if (line[index_line+1] == '/') {
                        /* if "//" is inclueded, then no need to parse the line */
                        index_line = size_line;
                    }
                    else if (line[index_line+1] == '*') {
                        current_status_ = BLOCKCOM;
                        index_line += 2;
                    }
                    else {
                        index_line++;
                    }
                    index_incl = 0;
                } else if (line[index_line] == '\"') {
                    current_status_ = LITERAL; 
                    index_line++;
                } else {
                    if (kIncludeToken[index_incl] == line[index_line++]) {
                        index_incl++;
                        if(index_incl == size_incl) {
                            // extract hpp file
                            string header = sufheader(line, index_line); 
                            if(!header.empty()) {
                                depends(FileToken(header));
                            }
                            index_line = size_line;
                        } 
                    } else {
                        index_incl = 0;
                    }
                } 
                break;
            case BLOCKCOM:
                if (index_line+1 < size_line && line[index_line] == '*') {
                    if(line[index_line+1] == '/') {
                        current_status_ = CODE;
                        index_line+=2;
                    } else {
                        index_line++;
                    }
                } else {
                    index_line++;
                }
                break;
            case LITERAL:
                if (line[index_line] == '\"') {
                    current_status_ = CODE;
                }
                index_line++;
                break;
        }
    } 
    return;
}

string Deptree::sufheader(string line, int index) {
    string ret = "";
    int n = line.size();
    while (index<n && line[index]==' ') {
        index++;
    }
    if (index<n && line[index++]=='\"') {
        while (index<n && line[index]!='\"') {
            ret += line[index++];
        }
    } 
    return ret; 
}

void Deptree::init(string file_path) {
    current_status_ = CODE;
    file_list_.clear();
    file_path_ = file_path;
    file_list_.push_back(file_path);
}

string Deptree::getFilePath() {
    return file_path_;
}

vector<vector<string>>& Deptree::getFileLists() {
    return file_lists_;
}

void Deptree::appendFileList(){
    FileToken file_token(file_path_);
    if(fid_.find(file_token.getName()) == fid_.end()) {
        assignFileId(file_token.getName());
        file_lists_.push_back(file_list_);
    } else {
        int tar = fid_[file_token.getName()];
        for (string file: file_list_) {
            file_lists_[tar].push_back(file);
        }
    }
    return;
}

void Deptree::assignFileId(string file_path) {
    fid_.insert({file_path, file_count_++});
}

map<FileToken, int, Comparator>& Deptree::getFid(){
    return fid_;
}