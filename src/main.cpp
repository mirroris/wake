#include<iostream>

#include "parser/parser.hpp"
#include "builder/builder.hpp"

int main(int argc, char** argv){
    Parser parser = Parser();
    if(argc==2) parser.parse(argv[1]);
    else cerr << "src dir is needed!" << endl;
    Builder builder;
    builder.build();
    parser.dependencyBuild();
    return 0;
}