#include <bits/stdc++.h>
#define DEPTREE_HPP

using namespace std;

typedef enum {
    LINECOM,
    BLOCKCOM,
    CODE
} status;

class deptree {
    private:
        unordered_set<string> fid;
        status  current_status;
        const string include_token = "#include";

    public:
        deptree() {
            current_status = CODE;
        }

        void depends(string file1, string file2);
        void expl(string line);  
        void init() {
            current_status = CODE;
        }
        string sufheader(string line, int index);
};