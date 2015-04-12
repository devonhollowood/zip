#ifndef ZIP
#define ZIP

#include <utility>
#include <tuple>
#include <iterator>

template<typename Iterator, typename... Iterators>
class zipIterator;

//recursive case
template<typename IteratorA, typename IteratorB, typename... Iterators>
class zipIterator<IteratorA, IteratorB, Iterators...>
    : public std::iterator<
        std::forward_iterator_tag,
        decltype(std::tuple_cat(
            std::declval<
                std::tuple<typename std::iterator_traits<IteratorA>
                    ::value_type>
            >(),
            std::declval<
                typename std::iterator_traits<zipIterator<IteratorB,
                    Iterators...>>::value_type
            >()
        ))
    >{
private:
    IteratorA itr_;
    zipIterator<IteratorB, Iterators...> rest_itr_;
public:
    zipIterator(IteratorA itr_a, IteratorB itr_b, Iterators... itrs)
        : itr_(itr_a),
            rest_itr_(zipIterator<IteratorB, Iterators...>(itr_b, itrs...)) {}
    auto operator*() -> decltype(std::tuple_cat(std::tie(*itr_), *rest_itr_)){
        return std::tuple_cat(std::tie(*itr_), *rest_itr_);
    }
    void operator++(){
        ++itr_;
        ++rest_itr_;
    }
    zipIterator<IteratorA, IteratorB, Iterators...> operator++(int){
        zipIterator<IteratorA, IteratorB, Iterators...> tmp(*this);
        ++itr_;
        ++rest_itr_;
        return tmp;}
    friend bool operator==(zipIterator<IteratorA, IteratorB, Iterators...> a,
            zipIterator<IteratorA, IteratorB, Iterators...> b){
        return a.itr_==b.itr_ || a.rest_itr_==b.rest_itr_;
    }

    friend bool operator!=(zipIterator<IteratorA, IteratorB, Iterators...> a,
            zipIterator<IteratorA, IteratorB, Iterators...> b){
        return a.itr_!=b.itr_ && a.rest_itr_!=b.rest_itr_;
    }
};

//base case
template<typename Iterator>
class zipIterator<Iterator>
    : public std::iterator<
        std::forward_iterator_tag,
        std::tuple<typename std::iterator_traits<Iterator>::value_type>
    > {
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


template<typename... Containers>
class ZipContainer{
public:
    using iterator = zipIterator<
        decltype(std::declval<Containers>().begin())...>;
    ZipContainer(Containers&... cs) : begin_(iterator(std::begin(cs)...)),
        end_(iterator(std::end(cs)...)) {};
    iterator begin() {return begin_;}
    iterator end() {return end_;}
private:
    iterator begin_;
    iterator end_;
};

template<typename... Containers>
ZipContainer<Containers...> zip(Containers&... cs){
    return ZipContainer<Containers...>(cs...);
}

#endif
