#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ZipTest
#include "zip.hpp"
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(ZipIterator)

BOOST_AUTO_TEST_CASE(constructor_test) {
    vector<int> v = {0,1,2};
    zipIterator<vector<int>::iterator> itr_a(v.begin());
    zipIterator<vector<int>::iterator> itr_b(itr_a);
    zipIterator<vector<int>::iterator> itr_c = itr_a;
    BOOST_CHECK(itr_b==itr_c);
}

BOOST_AUTO_TEST_CASE(equality_test) {
    vector<int> v = {0,1,2};
    zipIterator<vector<int>::iterator> itr_a(v.begin());
    zipIterator<vector<int>::iterator> itr_b(v.begin());
    BOOST_CHECK(itr_a==itr_b);
    ++itr_a;
    BOOST_CHECK(itr_a!=itr_b);
    ++itr_b;
    BOOST_CHECK(itr_a==itr_b);
}

BOOST_AUTO_TEST_CASE(rvalue_deref_test) {
    vector<int> v = {0};
    zipIterator<vector<int>::iterator> itr(v.begin());
    int res = std::get<0>(*itr);
    BOOST_CHECK_EQUAL(res, 0);
}

BOOST_AUTO_TEST_CASE(lvalue_deref_test) {
    vector<int> v = {0,3};
    zipIterator<vector<int>::iterator> itr(v.begin());
    BOOST_CHECK(*itr==std::make_tuple(0));
    *itr = std::make_tuple(1);
    //v is {1,3}
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 1);
    BOOST_CHECK_EQUAL(v[0], 1);
    *itr++ = std::make_tuple(2);
    //v is {2,3}
    BOOST_CHECK_EQUAL(v[0], 2);
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 3);
}

BOOST_AUTO_TEST_CASE(increment_test){
    vector<int> v = {0,1,2,3};
    zipIterator<vector<int>::iterator> itr(v.begin());
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 0);
    ++itr;
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 1);
    itr++;
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 2);
    BOOST_CHECK_EQUAL(std::get<0>(*itr++), 2);
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 3);
}

BOOST_AUTO_TEST_CASE(iteration_test) {
    vector<int> v = {0,1,2,3,4};
    zipIterator<vector<int>::iterator> itr(v.begin());
    zipIterator<vector<int>::iterator> end(v.end());
    size_t i = 0;
    for(; itr!=end; ++itr, ++i){
        if(i>=v.size()){
            BOOST_FAIL("iterator overflow");
            break;
        }
        BOOST_CHECK_EQUAL(std::get<0>(*itr), v[i]);
    }
}

BOOST_AUTO_TEST_CASE(swap_test) {
    vector<int> v = {0,1};
    zipIterator<vector<int>::iterator> itr_a(v.begin());
    zipIterator<vector<int>::iterator> itr_b(++v.begin());
    BOOST_CHECK_EQUAL(std::get<0>(*itr_a), 0);
    BOOST_CHECK_EQUAL(std::get<0>(*itr_b), 1);
    std::swap(itr_a, itr_b);
    BOOST_CHECK_EQUAL(std::get<0>(*itr_a), 1);
    BOOST_CHECK_EQUAL(std::get<0>(*itr_b), 0);
    BOOST_CHECK_EQUAL(v[0], 0);
    BOOST_CHECK_EQUAL(v[1], 1);
}

BOOST_AUTO_TEST_SUITE_END()
