#ifndef PARSER_HPP
#include "parser.hpp"
#endif

/* C */
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* C++ */
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
using mystat = struct stat;

void parser::parse(string dir_path){
    DIR *dir;
    mystat st;
    dirent *entry;

    cout << dir_path << endl;
    if ((dir = opendir(dir_path.c_str())) == NULL) {
        cerr << "opendir error" << endl;
        exit(1);
    } 

    while((entry = readdir(dir))!=NULL) {
        string next_dir_path = dir_path + '/';
        if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) continue;
        else next_dir_path += entry->d_name;
        cout << next_dir_path << endl;
        stat(next_dir_path.c_str(), &st);
        if(S_ISDIR(st.st_mode)) {
            parse(next_dir_path);
        } else if(S_ISREG(st.st_mode)){    
            cout << entry->d_name << endl;
        }
    } 
    
    closedir(dir);
}