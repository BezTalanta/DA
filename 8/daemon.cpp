#include <iostream>
#include "greedy.hpp"

int main(){
    unsigned int N, p, exchange;
    std::cin >> N >> p >> exchange;
    auto ret = NGreedy::solution(N, p, exchange);
    for(const auto& item: ret)
        std::cout << item << '\n';
    return 0;
}