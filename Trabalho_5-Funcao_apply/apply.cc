template<typename T1, typename T2>
auto apply(const T1 &list, T2 F){
    std::vector<decltype( F(*std::begin(list)) )> ret;
    for(const auto &x: list)
        ret.push_back(F(x));
    return ret;
}

template<typename T1, typename T2>
auto apply(std::initializer_list<T1> list, T2 F){
    std::vector<decltype( F(*std::begin(list)) )> ret;
    for(const auto &x: list)
        ret.push_back(F(x));
    return ret;
}