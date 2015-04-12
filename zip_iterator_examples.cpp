#include "zip.hpp"
#include <iostream>
#include <vector>
#include <tuple>

void const_itr_example(){
    std::cout << "Example zipping of const_iterators:" << std::endl;
    std::vector<int> vec = {0,1,2,3};
    char arr[] = {'a','b', 'c'};
    zip_iterator<decltype(vec.cbegin()), char*, decltype(vec.crbegin())>
        itr(vec.cbegin(), std::begin(arr), vec.crbegin());
    zip_iterator<decltype(vec.cbegin()), char*, decltype(vec.crbegin())>
        end(vec.cend(), std::end(arr), vec.crend());
    for(; itr!=end; ++itr){
        std::cout << "\t(" << std::get<0>(*itr) << ", " << std::get<1>(*itr)
            << ", " << std::get<2>(*itr) << ")" << std::endl;
    }
    // Output:
    //
    // Example zipping of const_iterators:
    //     (0, a, 3)
    //     (1, b, 2)
    //     (2, c, 1)
}

void mutable_itr_example(){
    std::cout << "Example zipping of mutable iterators:" << std::endl;
    std::vector<int> vec = {0,1,2,3};
    char arr[] = {'a','b', 'c'};
    std::cout << "\tContents of vec: ";
    for (auto el : vec) std::cout << el << ' ';
    std::cout << std::endl;
    std::cout << "\tContents of arr: ";
    for (auto el : arr) std::cout << el << ' ';
    std::cout << std::endl;
    std::cout << "\tAssigning elements of zip_iterator to (0, 'z')...";
    std::cout << std::endl;
    zip_iterator<decltype(vec.begin()), char*>
        itr(vec.begin(), std::begin(arr));
    zip_iterator<decltype(vec.begin()), char*>
        end(vec.end(), std::end(arr));
    for(; itr!=end; ++itr){
        *itr = std::make_tuple(0, 'z');
    }
    std::cout << "\tContents of vec: ";
    for (auto el : vec) std::cout << el << ' ';
    std::cout << std::endl;
    std::cout << "\tContents of arr: ";
    for (auto el : arr) std::cout << el << ' ';
    std::cout << std::endl;
    //Output:
    //
    // Example zipping of mutable iterators:
    //     Contents of vec: 0 1 2 3
    //     Contents of arr: a b c
    //     Assigning elements of zip_iterator to (0, 'z')...
    //     Contents of vec: 0 0 0 3
    //     Contents of arr: z z z
}

int main(){
    const_itr_example();
    mutable_itr_example();
}
