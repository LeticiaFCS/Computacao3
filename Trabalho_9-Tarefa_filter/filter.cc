#include <type_traits>

template<typename T1>
auto operator |(const T1 &list, decltype(&std::string::length) F){
    std::vector<size_t> ret;
    for(const auto &x: list)
        ret.push_back((x.*F)());
    return ret;    
}

template<typename T1, typename T2>
auto operator |(const T1 &list, T2 F){
    if constexpr (std::is_same<decltype( F(*std::begin(list)) ), bool>::value){
        auto firstElement = *std::begin(list);
        std::vector<decltype(firstElement)> ret;

        for(const auto &x: list)
            if(F(x))
                ret.push_back(x);
        return ret;

    } else if constexpr (std::is_same<decltype( F(*std::begin(list)) ), void>::value){
        for(const auto &x: list)
            F(x);
    } else {
        using t = decltype( F(*std::begin(list)) );
        std::vector<t> ret;

        for(const auto &x: list)
            ret.push_back(F(x));
        return ret;

    }
}