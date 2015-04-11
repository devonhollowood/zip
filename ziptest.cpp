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

BOOST_AUTO_TEST_SUITE(MultiZipIterator)

BOOST_AUTO_TEST_CASE(constructor_test) {
    vector<int> v1 = {0,1,2};
    vector<char> v2 = {'a','b','c'};
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        itr_a(v1.begin(), v2.begin());
    zipIterator<vector<int>::iterator, vector<char>::iterator> itr_b(itr_a);
    zipIterator<vector<int>::iterator, vector<char>::iterator> itr_c = itr_a;
    BOOST_CHECK(itr_b==itr_c);
}

BOOST_AUTO_TEST_CASE(equality_test) {
    vector<int> v1 = {0,1,2};
    vector<char> v2 = {'a','b','c'};
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        itr_a(v1.begin(), v2.begin());
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        itr_b(v1.begin(), v2.begin());
    BOOST_CHECK(itr_a==itr_b);
    ++itr_a;
    BOOST_CHECK(itr_a!=itr_b);
    ++itr_b;
    BOOST_CHECK(itr_a==itr_b);
}

BOOST_AUTO_TEST_CASE(rvalue_deref_test) {
    vector<int> v1 = {0};
    vector<char> v2 = {'a'};
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        itr(v1.begin(), v2.begin());
    int res1 = std::get<0>(*itr);
    char res2 = std::get<1>(*itr);
    BOOST_CHECK_EQUAL(res1, 0);
    BOOST_CHECK_EQUAL(res2, 'a');
}

BOOST_AUTO_TEST_CASE(lvalue_deref_test) {
    vector<int> v1 = {0,3};
    vector<char> v2 = {'a','d'};
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        itr(v1.begin(), v2.begin());
    BOOST_CHECK(*itr==std::make_tuple(0, 'a'));
    *itr = std::make_tuple(1,'b');
    //v1 is {1,3}, v2 is {'b', 'd'}
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 1);
    BOOST_CHECK_EQUAL(std::get<1>(*itr), 'b');
    BOOST_CHECK_EQUAL(v1[0], 1);
    BOOST_CHECK_EQUAL(v2[0], 'b');
    *itr++ = std::make_tuple(2,'c');
    //v1 is {2,3}, v2 is {'c', 'd'}
    BOOST_CHECK_EQUAL(v1[0], 2);
    BOOST_CHECK_EQUAL(v2[0], 'c');
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 3);
    BOOST_CHECK_EQUAL(std::get<1>(*itr), 'd');
}

BOOST_AUTO_TEST_CASE(increment_test){
    vector<int> v1 = {0, 1, 2, 3};
    vector<char> v2 = {'a', 'b', 'c', 'd'};
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        itr(v1.begin(), v2.begin());
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 0);
    BOOST_CHECK_EQUAL(std::get<1>(*itr), 'a');
    ++itr;
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 1);
    BOOST_CHECK_EQUAL(std::get<1>(*itr), 'b');
    itr++;
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 2);
    BOOST_CHECK_EQUAL(std::get<1>(*itr), 'c');
    BOOST_CHECK(*itr++==std::make_tuple(2,'c'));
    BOOST_CHECK_EQUAL(std::get<0>(*itr), 3);
    BOOST_CHECK_EQUAL(std::get<1>(*itr), 'd');
}

BOOST_AUTO_TEST_CASE(iteration_test) {
    vector<int> v1 = {0, 1, 2, 3};
    vector<char> v2 = {'a', 'b', 'c'};
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        itr(v1.begin(), v2.begin());
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        end(v1.end(), v2.end());
    size_t i = 0;
    for(; itr!=end; ++itr, ++i){
        if(i>=std::min(v1.size(), v2.size())){
            BOOST_FAIL("iterator overflow");
            break;
        }
        BOOST_CHECK_EQUAL(std::get<0>(*itr), v1[i]);
        BOOST_CHECK_EQUAL(std::get<1>(*itr), v2[i]);
    }
}

BOOST_AUTO_TEST_CASE(swap_test) {
    vector<int> v1 = {0, 1};
    vector<char> v2 = {'a', 'b'};
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        itr_a(v1.begin(), v2.begin());
    zipIterator<vector<int>::iterator, vector<char>::iterator>
        itr_b(++v1.begin(), ++v2.begin());
    BOOST_CHECK_EQUAL(std::get<0>(*itr_a), 0);
    BOOST_CHECK_EQUAL(std::get<1>(*itr_a), 'a');
    BOOST_CHECK_EQUAL(std::get<0>(*itr_b), 1);
    BOOST_CHECK_EQUAL(std::get<1>(*itr_b), 'b');
    std::swap(itr_a, itr_b);
    BOOST_CHECK_EQUAL(std::get<0>(*itr_a), 1);
    BOOST_CHECK_EQUAL(std::get<1>(*itr_a), 'b');
    BOOST_CHECK_EQUAL(std::get<0>(*itr_b), 0);
    BOOST_CHECK_EQUAL(std::get<1>(*itr_b), 'a');
    BOOST_CHECK_EQUAL(v1[0], 0);
    BOOST_CHECK_EQUAL(v2[0], 'a');
    BOOST_CHECK_EQUAL(v1[1], 1);
    BOOST_CHECK_EQUAL(v2[1], 'b');
}

BOOST_AUTO_TEST_SUITE_END()
