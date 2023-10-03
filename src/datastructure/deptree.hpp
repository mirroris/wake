#include <bits/stdc++.h>
#define DEPTREE_HPP

#ifndef FILETOKEN_HPP
#include "filetoken.hpp"
#endif

using namespace std;

typedef enum {
    BLOCKCOM,
    CODE,
    LITERAL
} status;

typedef struct Comparator {
    bool operator()(const FileToken& a, const FileToken& b) const{
        return (a.getName() < b.getName());
    }
} Comparator;

class Deptree {
    private:
        map<FileToken, int, Comparator> fid_;
        vector<string> file_list_;
        vector<vector<string>> file_lists_;
        string file_path_;
        status current_status_;
        int file_count_;
        const string kIncludeToken = "#include";

    public:
        Deptree() {
            current_status_ = CODE;
            file_count_ = 0;
        }

        void depends(FileToken file_path);
        void expl(string line);  
        void init(string file_path);
        string getFilePath();
        string sufheader(string line, int index);
        vector<vector<string>>& getFileLists();
        void appendFileList();
        void assignFileId(string file_path);
        map<FileToken, int, Comparator>& getFid();
};