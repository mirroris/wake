#ifndef BUILDER_HPP
#define BUILDER_HPP
#include"builder.hpp"
#endif

void Builder::build() {
    ifstream ifs(kConfigPath, ios::in);
    ofstream ofs(kMakePath, ios::out);

    string buffer;
    if(ifs.is_open()) {
        while (getline(ifs, buffer)) {
            ofs << buffer << endl;
        }
        ofs.close();
    } else {
        cerr << "file (.wakeconfig) cannnot be open" << endl;
        ofs.close();
    }
    ifs.close();
    return;
}



