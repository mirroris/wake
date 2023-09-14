#include <bits/stdc++.h>

using namespace std;

typedef enum {
    linecom,
    blockcom,
    code
} status;

class deptree {
    private:
        unordered_set<string> fid;
        status  corrent_status;
        const string include_token = "#inculde";

    public:
        deptree() {
            corrent_status = code;
        }

        void depends(string file1, string file2);
        void expl(string line);  
        void init() {
            corrent_status = code;
        }
        string sufheader(string line, int index);
};