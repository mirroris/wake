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

void Parser::parse(string dir_path){
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

            FileToken file_token(next_dir_path);
            if ( !file_token.isCFile() && !file_token.isHFile()) continue; 
            if(file_token.isCFile()) src_files_.push_back(file_token);

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

void Parser::dependencyBuild() {
    ofstream ofs("Makefile", ios::app);
    vector<vector<FileToken>> file_lists = dep_.getFileLists();
    int n = file_lists.size();

    ofs << "SRC=";
    for (FileToken file_token: src_files_) {
        ofs << file_token.getObjFile() << " ";
    }
    ofs  << endl;

    ofs << "dir_guard=@mkdir -p $(@D)" <<endl;

    ofs << "default : $(MAIN)" << endl;
    ofs << "\t$(dir_guard)" <<endl;
    ofs << "\t$(CC) $(OPT) $(SRC) -o $(BINDIR)/$(COMMAND)" << endl;

    for(auto p: dep_.getFid()) {
        int tar = p.second;
        ofs << p.first.getObjFile() << " : ";
        if(p.first.isCFile()) src_files_.push_back(p.first.getName());

        int dep_count=0;
        for(FileToken file_token: file_lists[tar]) {
            if(file_token.getName() != p.first.getName()) {
                ofs << file_token.getObjFile() << " " ;
            } else {
                ofs <<  file_token.getPath() << " ";
            }
        }
        ofs << endl;
        ofs << "\t$(dir_guard)" <<endl;
        ofs << "\t$(CC) $(OPT) -c " << p.first.getPath() << " -o $@"<< endl; 
    }

    ofs.close();
}

vector<FileToken>& Parser::getSrcFiles() {
    return src_files_;
}