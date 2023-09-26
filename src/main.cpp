#include<iostream>

#include "parser/parser.hpp"

int main(){
    parser m_parser = parser();
    m_parser.parse(".");
    m_parser.visualizeDependency();
    return 0;
}