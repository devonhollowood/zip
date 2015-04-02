#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>
#include <string>

using namespace std;

template<typename IteratorA, typename IteratorB>
auto zip2(const IteratorA& beginA, const IteratorA& endA,
        const IteratorB& beginB, const IteratorB& endB){
    using ResultTypeA = typename std::decay<decltype(*beginA)>::type;
    using ResultTypeB = typename std::decay<decltype(*beginB)>::type;
    vector<tuple<ResultTypeA, ResultTypeB>> result;
    auto itrA = beginA;
    auto itrB = beginB;
    while(itrA!=endA && itrB!=endB){
        ResultTypeA elementA = *itrA;
        ResultTypeB elementB = *itrB;
        result.push_back(std::make_tuple(elementA, elementB));
        ++itrA;
        ++itrB;
    }
    return result;
}

int main(){
    vector<int> listA {1,2,3};
    vector<char> listB {'a','b','c'};
    auto ziplist = zip2(listA.cbegin(), listA.cend(), listB.cbegin(),
            listB.cend());
    for(auto t : ziplist) {
        int i;
        char c;
        tie(i, c) = t;
        cout << i << ": " << c << endl;
    }
}
