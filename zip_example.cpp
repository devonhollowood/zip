#include "zip.hpp"
#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>
#include <string>

using namespace std;

int main(){
    vector<int> listA {1, 2, 3};
    string listB("abcd");
    for(auto t : zip<vector<int>, string>(listA, listB)){
        int i;
        char c;
        std::tie(i, c) = t;
        cout << "(" << i << ", " << c << ")" << endl;
    }
}
