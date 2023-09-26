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

class deptree {
    private:
        unordered_map<string, int> fid_;
        vector<string> file_list_;
        vector<vector<string>> file_lists_;
        string file_path_;
        status current_status;
        int file_count_;
        const string include_token = "#include";

    public:
        deptree() {
            current_status = CODE;
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
};