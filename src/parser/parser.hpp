#define PARSER_HPP

#ifndef DEPTREE_HPP
#include "../datastructure/deptree.hpp"
#endif

#include <dirent.h>
#include <bits/stdc++.h>

using dirent = struct dirent;
using namespace std;

class Parser {
    private:
        dirent *m_dirent_;
        string dir_path_;
        Deptree dep_;
        vector<FileToken> src_files_;
    public:
        Parser(){return;}
        Parser(string path):dir_path_(path) {return;}
        void parse(string dir_path);
        void dependencyBuild();
        vector<FileToken>& getSrcFiles();
};