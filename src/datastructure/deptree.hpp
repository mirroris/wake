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

typedef struct Equal {
    bool operator()(const FileToken& a, const FileToken& b) const {
        return (a.getName() == b.getName());
    }
} Equal;

typedef struct Hash {
    size_t operator()(const FileToken& a) const {
        return hash<string>()(a.getName());
    }
} Hash;

class DepTree {
    private:
        unordered_map<FileToken, int, Hash, Equal> fid_;
        unordered_set<FileToken, Hash, Equal> child_;
        vector<FileToken> file_list_;
        vector<vector<FileToken>> file_lists_;
        string file_path_;
        status current_status_;
        int file_count_;
        const string kIncludeToken = "#include";

    public:
        DepTree() {
            current_status_ = CODE;
            file_count_ = 0;
        }

        void depends(FileToken file_token);
        void expl(string line);  
        void init(string file_path);
        string getFilePath();
        string sufheader(string line, int index);
        vector<vector<FileToken>>& getFileLists();
        void appendFileList();
        void assignFileId(FileToken file_token);
        unordered_map<FileToken, int, Hash, Equal>& getFid();
        bool isRoot(FileToken file_token);
};