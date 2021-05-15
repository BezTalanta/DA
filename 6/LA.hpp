#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

namespace NLA{
	const int DISCHARGE = 6, MAX_DIS_NUM = 999'999;
	class TSuperLong{
		private:
			std::vector<uint32_t> number;
			int numSize;
		public:
			TSuperLong(const std::string& str);
			TSuperLong(const std::vector<uint32_t>& cp);
			void Print();
			TSuperLong operator+(const TSuperLong& lhs) const;
			TSuperLong operator-(const TSuperLong& lhs) const;
	};
}
