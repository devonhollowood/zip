#include "zip.hpp"
#include <iostream>
#include <vector>
#include <tuple>

int main(){
    std::vector<int> vec = {0,1,2,3};
    char arr[] = {'a','b', 'c'};
    zipIterator<decltype(vec.begin()), char*, decltype(vec.rbegin())>
        itr(vec.begin(), std::begin(arr), vec.rbegin());
    zipIterator<decltype(vec.begin()), char*, decltype(vec.rbegin())>
        end(vec.end(), std::end(arr), vec.rend());
    for(; itr!=end; ++itr){
        std::cout << "(" << std::get<0>(*itr) << ", " << std::get<1>(*itr)
            << ", " << std::get<2>(*itr) << ")" << std::endl;
    }
}
