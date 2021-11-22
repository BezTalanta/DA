#include <iostream>
#include <deque>
#include <algorithm>
#include <unordered_map>

//std::deque<std::deque<std::pair<int, int>>> all;
//std::deque<std::unordered_map<int, int>> all;
// Index(0) and weight
std::unordered_map<uint32_t, std::unordered_map<uint32_t, uint32_t>> all;
uint32_t n, m;

#define  debug  for(const auto& item: all){                                         \
        std::cout << item.first + 1 << ": ";                                        \
        for(const auto& item2: item.second){                                        \
            std::cout << "{" << item2.first + 1 << ", " << item2.second << "} ";    \
        }                                                                           \
        std::cout << '\n' << '\n';                                                  \
    }

#define debugQ     for(const auto& item: q){ \
        std::cout << item.first << ": "; \
        for(const auto& item2: item.second) \
            std::cout << item2 << ' '; \
        std::cout << '\n'; \
    } \
    std::cout << '\n';

int count_tmp = 0;
#define count std::cout << count_tmp++ << '\n';
#define flag std::cout << "Flag: " << __LINE__ << '\n';

inline std::pair<uint32_t, std::deque<uint32_t>>& dfsSearch(std::deque<std::pair<uint32_t, std::deque<uint32_t>>>& q){
    if(q.empty())
        throw std::runtime_error("");

    //debugQ

    // count
    // if(count_tmp == 23795)
    //     debugQ
    std::cout << "Size: " << q.size() << '\n';
    auto& last = q.front();
    flag
    if(last.second.back() == n - 1)
        return last;
    for(const auto& item: all[last.second.back()]){
        if(std::find(last.second.begin(), last.second.end(), item.first) == last.second.end()){
            //flag
            //std::cout << q.size() << '/' <<  q.max_size() << '\n';
            //flag
            q.push_back(last);
            //flag
            if(last.first > item.second){
                flag
                q.back().first = item.second;
            }
            //flag
            q.back().second.push_back(item.first);
        }
    }
    q.pop_front();

    //flag
    return dfsSearch(q);
}

int main(){
    std::cin >> n >> m;
    for(uint32_t i = 0; i < m; ++i){
        //std::cout << "Lol: " << i << '\n';
        uint32_t f, s, w; std::cin >> f >> s >> w;
        all[f - 1][s - 1] = w;
        //std::cout << "End Lol: " << i << '\n';
    }

    int result = 0;
    std::deque<std::pair<uint32_t, std::deque<uint32_t>>> tmp;   
    while(true){
        try{
            flag
            tmp = {{1'000'000'001, {0}}};
            std::pair<uint32_t, std::deque<uint32_t>>& step = dfsSearch(tmp);
            flag
            int prev = n - 1;
            while(step.second.size()){
                all[step.second.back()][prev] -= step.first;
                flag
                if(all[step.second.back()][prev] == 0)
                    all[step.second.back()].erase(prev);
                prev = step.second.back();
                step.second.pop_back();
                flag
            }

            result += step.first;
        }
        catch(const std::runtime_error& e){
            break;
        }
        flag
    }

    std::cout << result << '\n';
    return 0;
}

/*
5 6
1 2 4
1 3 3
1 4 1
2 5 3
3 5 3
4 5 10

5 2
1 2 4
2 5 3

6 9
1 2 7
1 3 4
2 3 4
2 4 2
3 4 8
3 5 4
4 5 4
4 6 5
5 6 12

5 8
1 2 30
1 3 40
1 4 20
2 5 40
2 3 50
3 4 20
3 5 30
4 5 30

5 8
1 4 10
1 3 30
1 2 20
2 5 30
2 3 40
3 5 20
4 3 10
4 5 20

6 8
1 2 11
1 3 12
3 2 1
2 4 12
3 5 11
5 4 7
4 6 19
5 6 4

14 31
1 2 6
1 3 6
1 4 8
1 5 9
2 3 3
3 4 4
4 5 3
2 6 4
6 3 9
3 7 4
7 4 10
4 8 5
4 9 10
5 9 6
7 6 8
8 7 8
9 8 7
6 10 5
10 7 10
7 11 5
11 8 12
8 12 5
8 13 12
9 13 7
11 10 8
12 11 8
13 12 7
10 14 6
11 14 9
12 14 7
13 14 6
*/
