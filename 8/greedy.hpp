#pragma once
  2 #include <iostream>
  3 #include <vector>
  4 #include <math.h>
  5 
  6 namespace NGreedy{
  7     std::vector<int> solution(const unsigned int& N, const unsigned int& p,     unsigned int exchange){
  8         std::vector<int> result(N, 0);
  9         for(int i = N - 1; i >= 0; --i){
 10             unsigned int current = pow(p, i);
 11             if(current > exchange)
 12                 continue;
 13 
 14             result[i] = exchange / current;
 15             exchange = exchange % current;
 16             if(exchange == 0)
 17                 break;
 18         }
 19         return result;
 20     }
 21 }; // nam
