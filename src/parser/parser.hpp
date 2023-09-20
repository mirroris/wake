#define PARSER_HPP

#ifndef DEPTREE_HPP
#include "../datastructure/deptree.hpp"
#endif

#include <dirent.h>
#include <bits/stdc++.h>


using dirent = struct dirent;
using namespace std;

class parser {
    private:
        dirent *m_dirent;
        string dir_path;
        deptree dep;
    public:
        parser(){return;}
        parser(string path):dir_path(path) {return;}

        void parse(string dir_path);
};