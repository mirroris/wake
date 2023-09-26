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

    if ((dir = opendir(dir_path.c_str())) == NULL) {
        cerr << "opendir error" << endl;
        exit(1);
    } 

    while((entry = readdir(dir))!=NULL) {
        string next_dir_path = dir_path + '/'; 
        
        if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) continue;
        else next_dir_path += entry->d_name;

        stat(next_dir_path.c_str(), &st);
        if(S_ISDIR(st.st_mode)) {
            parse(next_dir_path);
        } else if(S_ISREG(st.st_mode)){

            int index = 0;
            while (entry->d_name[index]!='\0' && entry->d_name[index]!='.') {
                index++;
            }
            string fileident = "";
            while (entry->d_name[index]!='\0') {
                fileident += entry->d_name[index];
                index++;
            }

            if ( fileident.compare(".hpp")!=0 && fileident.compare(".cpp")!=0) continue; 

            cout << "file (parent): " << entry->d_name << endl;

            ifstream ifs(next_dir_path , ios::in);
            string buffer;
            dep_.init(next_dir_path);
            if (ifs.is_open()) {
                while ( getline(ifs, buffer) ) {
                    dep_.expl(buffer);
                }
                ifs.close();
            } else {
                cerr << "Failed to open file ("<< next_dir_path << ")." << endl;
                continue;
            }
            dep_.appendFileList();
        }
    } 
    
    closedir(dir);
}

void parser::visualizeDependency() {
    vector<vector<string>> file_lists = dep_.getFileLists();
    int n = file_lists.size();
    for(int i=0;i<n;i++) {
        for(string file: file_lists[i]) {
            cout << file << " " ;
        }
        cout << endl;
    }
}