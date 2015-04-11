#ifndef ZIP
#define ZIP

#include <tuple>
#include <iterator>

//template<typename ...Iterators>
//class zipIterator;

template<typename Iterator>
class zipIterator
    : public std::iterator<
        std::forward_iterator_tag,
        std::tuple<typename std::iterator_traits<Iterator>::value_type>> {
private:
    Iterator itr_;
public:
    zipIterator(Iterator itr) : itr_(itr) {}
    auto operator*() -> decltype(std::tie(*itr_)){
        return std::tie(*itr_);
    }
    void operator++(){++itr_;}
    zipIterator<Iterator> operator++(int){
        zipIterator<Iterator> tmp(*this);
        ++itr_;
        return tmp;}
    friend bool operator==(zipIterator<Iterator> a, zipIterator<Iterator> b){
        return a.itr_==b.itr_;
    }

    friend bool operator!=(zipIterator<Iterator> a, zipIterator<Iterator> b){
        return a.itr_!=b.itr_;
    }
};

//template<typename Iterator, typename... Iterators>
//class zipIterator<Iterator, Iterators...>{
//public:
//};

//template<typename ...iterators>
//class zip{
//private:
    //zipIterator<Iterators...> begin_;
    //zipIterator<Iterators...> end_;
//public:
    //zip(Iterators... itrs_) : begin_(itrs_...) {};
    //zipIterator<Iterators...> begin() {return begin_;}
    //zipIterator<Iterators...> end() {return end_;}
//};

#endif
