#ifndef DEPTREE_HPP
#include "deptree.hpp"
#endif

#include <bits/stdc++.h>

using namespace std;

void DepTree::depends(FileToken file_token) {
    if(file_token.getName() != FileToken(file_path_).getName()) {
        assignFileId(file_token);
        child_.insert(file_token);
        file_list_.push_back(file_token);
    }
    return;
}

void DepTree::expl(string line) {
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
                                depends(FileToken(header, file_path_));
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

string DepTree::sufheader(string line, int index) {
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

void DepTree::init(string file_path) {
    current_status_ = CODE;
    file_list_.clear();
    file_path_ = file_path;
    FileToken file_token(file_path);
    assignFileId(file_token);
    file_list_.push_back(file_token);
}

string DepTree::getFilePath() {
    return file_path_;
}

vector<vector<FileToken>>& DepTree::getFileLists() {
    return file_lists_;
}

void DepTree::appendFileList(){
    FileToken file_token(file_path_);
    int tar = fid_[file_token];
    for (FileToken file_token: file_list_) {
        file_lists_[tar].push_back(file_token);
    }
    return;
}

void DepTree::assignFileId(FileToken file_token) {
    if(fid_.find(file_token) == fid_.end()) {
        file_lists_.push_back(vector<FileToken>());
        fid_.insert({file_token, file_count_++});
    }
}

unordered_map<FileToken, int, Hash, Equal>& DepTree::getFid(){
    return fid_;
}

bool DepTree::isRoot(FileToken file_token) {
    if(child_.find(file_token) != child_.end()) {
        return false;
    } else {
        return true;
    }
}