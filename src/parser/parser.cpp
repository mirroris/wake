#ifndef PARSER_HPP
#include "parser.hpp"
#endif

void parser::parse(string dir_path){
    DIR *dir;
    dirent entry;

    if ((dir = opendir(dir_path)) == NULL) {
        cerr << "opendir error" << endl;
        exit(1);
    } 

    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_type == DT_DIR){
            parse(entry->d_name);
        }
    }
}