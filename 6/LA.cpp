#include "LA.hpp"

NLA::TSuperLong::TSuperLong(const std::string& str){
	int div_ = str.size() / NLA::DISCHARGE, mod_ = str.size() % NLA::DISCHARGE;
	uint32_t curNum = 0;
	for(int i = 0; i < mod_; ++i){ // Заполняем первый разряд
		curNum *= 10;
		curNum += str[i] - '0';
	}
	if(mod_){ // Закидываем первый разряд
		number.push_back(curNum);
	}

	for(int i = 0; i < div_; ++i){ // Заполняем последюущие разряды
		int currentZeroIndex = NLA::DISCHARGE * i + mod_;
		curNum = 0;
		for(int j = 0; j < NLA::DISCHARGE; ++j){
			curNum *= 10;
			curNum += str[currentZeroIndex + j] - '0';
		}
		number.push_back(curNum);
	}

	if(mod_){
		NLA::TSuperLong::numSize = div_ + 1;
	}
	else{
		NLA::TSuperLong::numSize = div_;
	}
}

NLA::TSuperLong::TSuperLong(const std::vector<uint32_t>& cp){
	NLA::TSuperLong::number = cp;
}

void NLA::TSuperLong::Print(){
	for(int i = 0; i < number.size(); ++i){
		std::cout.fill('0');
		if(i != 0)
			std::cout << std::setw(NLA::DISCHARGE) << number[i];
		else
			std::cout << number[i];
		if(i != number.size() - 1){
			std::cout << '\'';
		}
	}
	std::cout << "\n\n";
}

NLA::TSuperLong NLA::TSuperLong::operator+(const NLA::TSuperLong& rhs) const{
	std::vector<uint32_t> sum;
	bool isNeedToAddOne = false; // Один в уме
	int sz1 = NLA::TSuperLong::numSize,
		sz2 = rhs.numSize; // Берем размеры двух чисел
	for(; sz1 > 0 || sz2 > 0; --sz1, --sz2){
		int currentSum = isNeedToAddOne;
		if(sz1 > 0){
			currentSum += number[sz1 - 1];
		}
		if(sz2 > 0){
			currentSum += rhs.number[sz2 - 1];
		}
		
		if(currentSum > NLA::MAX_DIS_NUM){
			isNeedToAddOne = true;
			currentSum -= NLA::MAX_DIS_NUM + 1;
		}
		else{
			isNeedToAddOne = false;
		}
		
		sum.push_back(currentSum);
	}
	
	if(isNeedToAddOne){
		sum.push_back(1);
	}
	
	reverse(sum.begin(), sum.end());
	NLA::TSuperLong result(sum);
	return result;
}

NLA::TSuperLong NLA::TSuperLong::operator-(const NLA::TSuperLong& rhs) const{
	std::vector<uint32_t> min;
	bool isNeedToMinOne = false; // Один в уме
	int sz1 = NLA::TSuperLong::numSize,
		sz2 = rhs.numSize; // Берем размеры двух чисел
	if(sz1 < sz2){ // Если первое больше второго по размерам
		throw std::runtime_error("Error");
	}
		
	for(; sz1 > 0 || sz2 > 0; --sz1, --sz2){
		int currentSum = 0, takeLhs = 0, takeRhs = 0;
		if(sz1 > 0){
			takeLhs = number[sz1 - 1];
			if(isNeedToMinOne)
				--takeLhs;
		}
		if(sz2 > 0){
			takeRhs = rhs.number[sz2 - 1];
		}
		
		if(takeLhs < takeRhs){
			isNeedToMinOne = true;
			takeLhs += NLA::MAX_DIS_NUM + 1;
		}
		else{
			isNeedToMinOne = false;
		}
		
		int curResult = takeLhs - takeRhs; // Проверяем на ведущие нули
		if(!(curResult == 0) || !(sz1 == 1)){
			min.push_back(curResult);
		}
	}
	
	if(isNeedToMinOne){ // Если от первого нужно забрать единичку, когда уже все разряды кончились
		throw std::runtime_error("Error");
	}
	reverse(min.begin(), min.end());
	NLA::TSuperLong result(min);
	return result;
}

/*
111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222223
*/