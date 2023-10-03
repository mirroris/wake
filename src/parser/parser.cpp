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

void Parser::visualizeDependency() {
    ofstream ofs("Makefile", ios::app);
    vector<vector<FileToken>> file_lists = dep_.getFileLists();
    int n = file_lists.size();
    vector<string> src_files;

    for(auto p: dep_.getFid()) {
        int tar = p.second;
        ofs << p.first.getName() << " : ";
        if(p.first.isCFile()) src_files.push_back(p.first.getName());

        for(FileToken file_token: file_lists[tar]) {
            if(file_token.getName() != p.first.getName()) ofs << file_token.getName() << " " ;
            else ofs <<  file_token.getPath() << " ";
        }
        ofs << endl;
        ofs << "\t$(CC) $(OPT) -c " << p.first.getPath() << " -o ../bin/" << p.first.getName() << ".o" << endl; 
    }

    ofs << "SRC=";
    for (string src: src_files) {
        ofs << "../bin/" << src << ".o ";
    }
    ofs  << endl;
    ofs << "default : $(MAIN)" << endl;
    ofs << "\t$(CC) $(OPT) $(SRC) -o ../bin/$(COMMAND)" << endl;
    ofs.close();
}