#include <bits/stdc++.h>
#define DEPTREE_HPP

#ifndef FILETOKEN_HPP
#include "filetoken.hpp"
#endif

using namespace std;

typedef enum {
    BLOCKCOM,
    CODE
} status;

class deptree {
    private:
        unordered_set<string> fid_;
        vector<vector<string>> file_list_;
        status  current_status;
        const string include_token = "#include";

    public:
        deptree() {
            current_status = CODE;
        }

        void depends(FileToken file_par, FileToken file_chi);
        void expl(string line);  
        void init() {
            current_status = CODE;
        }
        string sufheader(string line, int index);
};