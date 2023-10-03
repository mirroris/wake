#include<iostream>

#include "parser/parser.hpp"

int main(){
    Parser parser = Parser();
    parser.parse(".");
    parser.visualizeDependency();
    return 0;
}