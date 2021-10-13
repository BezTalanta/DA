#include <iostream>
#include "ll.hpp"

int main(){
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	std::ios::sync_with_stdio(false);

	suplong f, s;
	while(std::cin >> f >> s){
		char act; std::cin >> act;
		switch (act)
		{
			case '+':
				std::cout << f + s << '\n';
				break;
			
			case '-':
				try{
					std::cout << f - s << '\n';
				}
				catch(const std::runtime_error& e){
					std::cout << e.what() << '\n';
				}
				break;

			case '*':
				std::cout << f * s << '\n';
				break;

			case '/':
				try{
					std::cout << f / s << '\n';
				}
				catch(const std::runtime_error& e){
					std::cout << e.what() << '\n';
				}
				break;

			case '^':
				try{
					std::cout << (f ^ s) << '\n';
				}
				catch(const std::runtime_error& e){
					std::cout << e.what() << '\n';
				}
				break;

			case '<':
				std::cout << std::boolalpha << (f < s) << '\n';
				break;

			case '>':
				std::cout << std::boolalpha << (f > s) << '\n';
				break;

			case '=':
				std::cout << std::boolalpha << (f == s) << '\n';
				break;

			default:
				break;
		}
	}
	return 0;
}
