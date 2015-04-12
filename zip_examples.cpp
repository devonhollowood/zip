#include "zip.hpp"
#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

template<typename Container>
string contents(Container c){
    stringstream s;
    for(auto el : c){
        s << el << ' ';
    }
    auto res = s.str();
    res.pop_back();
    return res;
}

void read_example(){
    std::cout << "Read example:" << std::endl;
    vector<int> vec{1, 2, 3};
    string str("abcd");
    set<string> s {"hello", "world", "this", "is", "cool"};
    std::cout << "\tvec contains: " << contents(vec) << std::endl;
    std::cout << "\tstr contains: " << contents(str) << std::endl;
    std::cout << "\ts contains: " << contents(s) << std::endl;
    std::cout << "\tzip contains: ";
    for(auto t : zip(vec, str, s)){
        cout << "(" << get<0>(t) << "," << get<1>(t) << "," << get<2>(t)
            << ") ";
    }
    cout << endl;
}
// Output:
//
// Read example:
//     vec contains: 1 2 3
//     str contains: a b c d
//     s contains: cool hello is this world
//     zip contains: (1,a,cool) (2,b,hello) (3,c,is)

void write_example(){
    std::cout << "Write example:" << std::endl;
    vector<int> vec{1, 2, 3};
    string str("abcd");
    std::cout << "\tvec contains: " << contents(vec) << std::endl;
    std::cout << "\tstr contains: " << contents(str) << std::endl;
    for(auto t : zip(vec, str)){
        t = std::make_tuple(0, 'z');
    }
    std::cout << "\tvec contains: " << contents(vec) << std::endl;
    std::cout << "\tstr contains: " << contents(str) << std::endl;
}
// Output:
//
// Write example:
//     vec contains: 1 2 3
//     str contains: a b c d
//     vec contains: 0 0 0
//     str contains: z z z d

int main(){
    read_example();
    write_example();
}
