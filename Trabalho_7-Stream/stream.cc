template<typename T1, typename T2>
void operator |(const T1 &list, T2 F){
    for(const auto &x: list)
        F(x);
}