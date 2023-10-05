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
        string path_;
        string name_;
        FileIdent ident_;
        void setFields();

    public:
        FileToken(){};
        FileToken(string file_path);
        // parent_fileからtarget_fileの相対パスを絶対パスに変更したい場合のコンストラクタ
        FileToken(string target_file, string parent_file);
        FileIdent toFileIdent(string ident);
        bool isCFile() const;
        bool isHFile() const;
        FileIdent getIdent() const;
        string getName() const;    
        string getPath() const;
        string getObjFile() const;
        string getCFile() const;
};