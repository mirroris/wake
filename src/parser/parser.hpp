#define PARSER_HPP
#include <dirent.h>

using dirent = struct dirent;

class parser {
    private:
        dirent *m_dirent;
        string dir_path;

    public:
        Parser(){;}
        Parser(path):pathName(path) {;}

    void parse(string dir_path){}
}