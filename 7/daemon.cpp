#include <iostream>

int main(){
    unsigned long long n, m; std::cin >> n >> m;
    if(m >= n){
        std::cout << "0\n";
        return 0;
    }

    unsigned long long result = 0, tens = 1;
    std::string n_str = std::to_string(n),
                cur_str = "";
    for(uint32_t i = 0; i < n_str.size(); ++i, tens *= 10){
        cur_str += n_str[i];
        unsigned long long  max = std::stoull(cur_str),
                            min = tens;

        if(min % m != 0)
            min += m - (min % m);

        if(max >= min)
            result += (max / m) - (min / m) + 1;
    }

    std::cout << (n % m == 0 ? result - 1 : result) << '\n';
    return 0;
}
