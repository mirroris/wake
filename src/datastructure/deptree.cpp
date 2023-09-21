#ifndef DEPTREE_HPP
#include "deptree.hpp"
#endif

#include <bits/stdc++.h>

using namespace std;

void deptree::depends(FileToken file_par, FileToken file_chi) {
    auto file1_iterator = fid_.find(file_par.getName());
    auto file2_iterator = fid_.find(file_chi.getName());

    if(file1_iterator==fid_.end()) {
        fid_.insert(file_par.getName());
    }
    if(file2_iterator==fid_.end()) {
        fid_.insert(file_chi.getName());
    }

    int target = distance(fid_.begin(), fid_.find(file_par.getName()));
    file_list_[target].push_back(file_chi.getName());
    return;
}

void deptree::expl(string line) {
    int index_line = 0;
    int size_line = line.size();

    int index_incl = 0;
    int size_incl = include_token.size();

    while (index_line<size_line) {
        if (current_status == CODE){
            if( index_line+1 < size_line && line[index_line] == '/') {
                if (line[index_line+1] == '/') {
                    /* if "//" is inclueded, then no need to parse the line */
                    index_line = size_line;
                }
                else if (line[index_line+1] == '*') {
                    current_status = BLOCKCOM;
                    index_line += 2;
                }
                else {
                    index_line++;
                }
                index_incl = 0;
            } else {
                if (include_token[index_incl] == line[index_line++]) {
                    index_incl++;
                    if(index_incl == size_incl) {
                        // extract hpp file
                        string header = sufheader(line, index_line); 
                        if(!header.empty())cout << "\tdepends : " << header << endl;
                        index_line = size_line;
                    } 
                } else {
                    index_incl = 0;
                }
            } 
        } else if (current_status == BLOCKCOM) {
            if (index_line+1 < size_line && line[index_line] == '*') {
                if(line[index_line+1] == '/') {
                    current_status = CODE;
                    index_line+=2;
                } else {
                    index_line++;
                }
            } else {
                index_line++;
            }
        } 
    } 
    return;
}

string deptree::sufheader (string line, int index) {
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