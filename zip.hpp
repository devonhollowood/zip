#ifndef ZIP
#define ZIP

#include <utility>
#include <tuple>
#include <iterator>

template<typename Iterator, typename... Iterators>
class zip_iterator;

//recursive case
template<typename IteratorA, typename IteratorB, typename... Iterators>
class zip_iterator<IteratorA, IteratorB, Iterators...>
    : public std::iterator<
        std::forward_iterator_tag,
        decltype(std::tuple_cat(
            std::declval<
                std::tuple<typename std::iterator_traits<IteratorA>
                    ::value_type>
            >(),
            std::declval<
                typename std::iterator_traits<zip_iterator<IteratorB,
                    Iterators...>>::value_type
            >()
        ))
    >{
private:
    IteratorA itr_;
    zip_iterator<IteratorB, Iterators...> rest_itr_;
public:
    zip_iterator(IteratorA itr_a, IteratorB itr_b, Iterators... itrs)
        : itr_(itr_a),
            rest_itr_(zip_iterator<IteratorB, Iterators...>(itr_b, itrs...)) {}
    auto operator*() -> decltype(std::tuple_cat(std::tie(*itr_), *rest_itr_)){
        return std::tuple_cat(std::tie(*itr_), *rest_itr_);
    }
    void operator++(){
        ++itr_;
        ++rest_itr_;
    }
    zip_iterator<IteratorA, IteratorB, Iterators...> operator++(int){
        zip_iterator<IteratorA, IteratorB, Iterators...> tmp(*this);
        ++itr_;
        ++rest_itr_;
        return tmp;}
    friend bool operator==(zip_iterator<IteratorA, IteratorB, Iterators...> a,
            zip_iterator<IteratorA, IteratorB, Iterators...> b){
        return a.itr_==b.itr_ || a.rest_itr_==b.rest_itr_;
    }

    friend bool operator!=(zip_iterator<IteratorA, IteratorB, Iterators...> a,
            zip_iterator<IteratorA, IteratorB, Iterators...> b){
        return a.itr_!=b.itr_ && a.rest_itr_!=b.rest_itr_;
    }
};

//base case
template<typename Iterator>
class zip_iterator<Iterator>
    : public std::iterator<
        std::forward_iterator_tag,
        std::tuple<typename std::iterator_traits<Iterator>::value_type>
    > {
private:
    Iterator itr_;
public:
    zip_iterator(Iterator itr) : itr_(itr) {}
    auto operator*() -> decltype(std::tie(*itr_)){
        return std::tie(*itr_);
    }
    void operator++(){++itr_;}
    zip_iterator<Iterator> operator++(int){
        zip_iterator<Iterator> tmp(*this);
        ++itr_;
        return tmp;}
    friend bool operator==(zip_iterator<Iterator> a, zip_iterator<Iterator> b){
        return a.itr_==b.itr_;
    }

    friend bool operator!=(zip_iterator<Iterator> a, zip_iterator<Iterator> b){
        return a.itr_!=b.itr_;
    }
};


template<typename... Containers>
class ZipContainer{
public:
    using iterator = zip_iterator<
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
