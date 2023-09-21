#define FILETOKEN_HPP

#include<bits/stdc++.h>
using namespace std;

/// @brief 
typedef enum FileIdent {
    NONE,
    CPP,
    CC,
    C,
    HPP,
    H
} FileIdent;


class FileToken {
    private:
    string token_;
    string name_;
    FileIdent ident_;

    public:
    FileToken(){};
    FileToken(string file_name);
    FileIdent toFileIdent(string ident);

    FileIdent getIdent();
    string getName();    
};