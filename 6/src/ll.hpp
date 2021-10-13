#include <vector>
#include <iostream>
#include <string>
#include <ostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

namespace NSupalg{
	class TSuperLong{
	private:
			static const int BASE = 100'000;
			static const int RADIX = 5;

			std::vector<uint32_t> nums;
	public:
			TSuperLong() = default;
			TSuperLong(const std::string& get);
			TSuperLong(const std::vector<uint32_t>& v);
			~TSuperLong() = default;

			TSuperLong operator+(const TSuperLong& rhs) const;
			TSuperLong& operator+=(const TSuperLong& rhs);
			TSuperLong operator-(const TSuperLong& rhs) const; // throw
			TSuperLong& operator-=(const TSuperLong& rhs); // throw
			TSuperLong operator*(const TSuperLong& rhs) const;
			TSuperLong& operator*=(const TSuperLong& rhs);
			TSuperLong operator^(TSuperLong rhs) const; // throw
			TSuperLong operator^(const uint32_t& degree) const; // throw
			TSuperLong operator/(const TSuperLong& rhs) const; // throw

			// TODO: code all operators
			bool operator<(const TSuperLong& rhs) const;
			bool operator>(const TSuperLong& rhs) const;
			bool operator>=(const TSuperLong& rhs) const;
			bool operator==(const TSuperLong& rhs) const;

			TSuperLong& expand(const size_t& count);
			TSuperLong powten(const size_t& count) const;

			void push_back(const uint32_t& input);
			bool isEven() const;

			friend std::ostream& operator<<(std::ostream& out, const TSuperLong& rhs);
			friend std::istream& operator>>(std::istream& in, TSuperLong& rhs);
	};
}

using suplong = NSupalg::TSuperLong;