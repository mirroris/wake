#ifndef DEPTREE_HPP
#include "deptree.hpp"
#endif

#include <bits/stdc++.h>

using namespace std;

void deptree::depends(string file1, string file2) {
    return;
}

void deptree::expl(string line) {
    int index = 0;
    int size = line.size();

    int index_incl = 0;
    int size_incl = include_token.size();

    while (index<size) {
        if (corrent_status == code){
            if( index+1 < size && line[index] == '/') {
                if (line[index+1] == '/') {
                    corrent_status = linecom;
                    /* if "//" is inclueded, then no need to parse the line */
                    index=size;
                }
                else if (line[index+1] == '*') {
                    corrent_status = blockcom;
                    index+=2;
                }
                else {
                    index++;
                }
            } else {
                if (include_token[index_incl] == line[index]) {
                    if(index_incl == size_incl) {
                        // extract hpp file
                        string header = sufheader(line, index); 
                        if (!header.empty()) cout << "depens : " << header << endl;
                        index_incl = 0;
                    } else {
                        index_incl++;
                    }
                }
            }
        } else if (corrent_status == blockcom) {
            if (index+1 < size && line[index] == '*' && corrent_status == blockcom) {
                if(line[index+1] == '/') {
                    corrent_status = code;
                    index++;
                } else {
                    index++;
                }
            }
        }
    } 
    return;
}

string deptree::sufheader (string line, int index) {
    string ret;
    int n = line.size();
    while (index<n && line[index]==' ') {
        index++;
    }
    if (index<n && line[index]=='\"') {
        index++;
        ret = "";
        while (index<n && line[index]!='\"') {
            ret += line[index++];
        }
    } else {
        ret = nullptr;
    }
    return ret; 
}