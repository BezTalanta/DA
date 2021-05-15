#include <iostream>
#include "LA.hpp"

int main(){
	std::string f,s; std::cin >> f >> s;
	NLA::TSuperLong t1(f), t2(s);
	NLA::TSuperLong t3 = t1 + t2;
	std::cout << "\n+: ";
	t3.Print();
	try{
		NLA::TSuperLong tMin = t1 - t2;
		std::cout << "-: ";
		tMin.Print();
	}
	catch(const std::runtime_error& e){
		std::cout << "-: " << e.what() << '\n';
	}
	return 0;
}
