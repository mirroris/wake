#ifndef ZZZ_HPP
#define ZZZ_HPP
#include "zzz.hpp"
#endif

#include <string>
using namespace std;

string snore(int length) {
    string ret = "";
    for(int i=0;i<length;i++) ret += 'z';
    return ret;
}