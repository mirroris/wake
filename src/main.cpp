#include<iostream>

#include "parser/parser.hpp"
#include "builder/builder.hpp"

int main(){
    Parser parser = Parser();
    parser.parse(".");
    Builder builder;
    builder.build();
    parser.visualizeDependency();
    return 0;
}