#include <iostream>
#include <time.h>
#include <cstdlib>

const int NC = 100, MC = NC, WC = 100;

int main(){
    std::srand(time(0));
    int n = rand() % NC + 1, m = rand() % MC + 1;
    std::cout << n << ' ' << m << '\n';
    for(int i = 0; i < m; ++i){
        int x = rand() % (n - 1) + 1;
        int y = rand() % n + 1;
        int weight = rand() % WC + 1;
        std::cout << x << ' ' << y << ' ' << weight << '\n';
    }
    std::cout << '\n';
    return 0;
}