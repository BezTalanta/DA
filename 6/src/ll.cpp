#include "ll.hpp"

namespace NSupalg{
    TSuperLong::TSuperLong(const std::string& get){
        size_t half = get.size() % RADIX, full = get.size() / RADIX;

        bool foundNotZero = false;

        if(half != 0){
            uint32_t firstNum = 0;
            for (size_t i = 0; i < half; i++){
                firstNum *= 10;
                firstNum += get[i] - '0';
            }

            if(firstNum != 0 || full == 0){
                nums.push_back(firstNum);
                foundNotZero = true;
            }
        }
        
        for (size_t i = 0; i < full; i++)
        {
            uint32_t currentNum = 0;
            for (size_t j = 0; j < RADIX; j++)
            {
                currentNum *= 10;
                currentNum += get[i * RADIX + half + j] - '0';
            }

            if(currentNum == 0 && (foundNotZero || (i + 1 == full)))
                nums.push_back(currentNum);
            else if(currentNum != 0){
                nums.push_back(currentNum);
                foundNotZero = true;
            }
        }
    }

    TSuperLong::TSuperLong(const std::vector<uint32_t>& v){
        if(v.size() == 0)
            nums.clear();

        std::vector<uint32_t> newV;
        bool isFound = false;
        for (size_t i = 0; i + 1 < v.size(); i++)
            if(v[i] != 0 || (v[i] == 0 && isFound)){
                newV.push_back(v[i]);
                isFound = true;
            }
        
        newV.push_back(v[v.size() - 1]);
        nums = newV;
    }

    std::ostream& operator<<(std::ostream& out, const TSuperLong& rhs){
        for (size_t i = 0; i < rhs.nums.size(); i++)
        {
            if(i != 0)
                out << std::setw(NSupalg::TSuperLong::RADIX) << std::setfill('0') << rhs.nums[i]; //<< (i == rhs.nums.size() - 1 ? "" : "\'");
            else
                //out << rhs.nums[i] << (i == rhs.nums.size() - 1 ? "" : "\'");
                out << rhs.nums[i];
        }
        return out;
    }

    std::istream& operator>>(std::istream& in, TSuperLong& rhs){
        std::string input; in >> input;
        rhs = (input);
        return in;
    }

    TSuperLong TSuperLong::operator+(const TSuperLong& rhs) const{
        std::vector<uint32_t> result;
        int thisSz = nums.size() - 1, rhsSz = rhs.nums.size() - 1;
        bool isOneUp = false;
        while(thisSz >= 0 || rhsSz >= 0){
            uint32_t sum = 0;
            sum += (thisSz >= 0 ? nums[thisSz] : 0) + (rhsSz >= 0 ? rhs.nums[rhsSz] : 0);
            sum += (isOneUp ? 1 : 0);
            
            if(sum >= BASE){
                isOneUp = true;
                sum -= BASE;
            }
            else{
                isOneUp = false;
            }

            result.push_back(sum);

            --thisSz;
            --rhsSz;
        }

        if(isOneUp)
            result.push_back({1});
        
        std::reverse(result.begin(), result.end());
        return (result);
    }

    TSuperLong& TSuperLong::operator+=(const TSuperLong& rhs){
        std::vector<uint32_t> result;
        int thisSz = nums.size() - 1, rhsSz = rhs.nums.size() - 1;
        bool isOneUp = false;
        while(thisSz >= 0 || rhsSz >= 0){
            uint32_t sum = 0;
            sum += (thisSz >= 0 ? nums[thisSz] : 0) + (rhsSz >= 0 ? rhs.nums[rhsSz] : 0);
            sum += (isOneUp ? 1 : 0);
            
            if(sum >= BASE){
                isOneUp = true;
                sum -= BASE;
            }
            else{
                isOneUp = false;
            }

            result.push_back(sum);

            --thisSz;
            --rhsSz;
        }

        if(isOneUp)
            result.push_back({1});
        
        std::reverse(result.begin(), result.end());
        nums = result;
        return *this;
    }

    TSuperLong TSuperLong::operator-(const TSuperLong& rhs) const{
        if(*this < rhs)
            throw std::runtime_error("Error");

        std::vector<uint32_t> result;
        int thisSz = nums.size() - 1, rhsSz = rhs.nums.size() - 1;
        bool isOneDown = false;
        while(thisSz >= 0 || rhsSz >= 0){
            int32_t minus = nums[thisSz] - (isOneDown ? 1 : 0);
            minus -= (rhsSz >= 0 ? rhs.nums[rhsSz] : 0);

            if(minus < 0){
                isOneDown = true;
                minus += BASE;
            }
            else{
                isOneDown = false;
            }

            result.push_back(minus);

            --thisSz;
            --rhsSz;
        }
        
        std::reverse(result.begin(), result.end());
        return (result);
    }

    TSuperLong& TSuperLong::operator-=(const TSuperLong& rhs){
        if(*this < rhs)
            throw std::runtime_error("Error");

        std::vector<uint32_t> result;
        int thisSz = nums.size() - 1, rhsSz = rhs.nums.size() - 1;
        bool isOneDown = false;
        while(thisSz >= 0 || rhsSz >= 0){
            int32_t minus = nums[thisSz] - (isOneDown ? 1 : 0);
            minus -= (rhsSz >= 0 ? rhs.nums[rhsSz] : 0);

            if(minus < 0){
                isOneDown = true;
                minus += BASE;
            }
            else{
                isOneDown = false;
            }

            result.push_back(minus);

            --thisSz;
            --rhsSz;
        }
        
        std::reverse(result.begin(), result.end());
        nums = result;
        return *this;
    }

	TSuperLong TSuperLong::operator*(const TSuperLong& rhs) const{
        size_t maxSize = std::max(nums.size(), rhs.nums.size());
        std::vector<uint32_t> result(nums.size() + rhs.nums.size(), 0u);
        for (size_t i = nums.size(); i > 0; --i)
        {
            // May be faster
            std::vector<uint32_t> currentMultiply(maxSize + 1, 0);
            for (size_t j = rhs.nums.size(), index = maxSize; j > 0; j--, --index)
            {
                uint64_t tmpMultiply = 
                    (uint64_t)nums[i - 1] * (uint64_t)rhs.nums[j - 1] + (uint64_t)currentMultiply[index];
                currentMultiply[index] = tmpMultiply % BASE;
                currentMultiply[index - 1] = tmpMultiply / BASE;
            }

            size_t offset = result.size() - 1 - (nums.size() - i);
            for (size_t j = currentMultiply.size(); j > 0; --j)
            {
                uint32_t sum = result[offset] + currentMultiply[j - 1];
                if(sum >= BASE && offset > 0)
                    ++result[offset - 1];
                result[offset] = sum % BASE;

                if(offset)
                    --offset;
            }
        }

        return (result);
    }

    TSuperLong& TSuperLong::operator*=(const TSuperLong& rhs){
        size_t maxSize = std::max(nums.size(), rhs.nums.size());
        std::vector<uint32_t> result(nums.size() + rhs.nums.size(), 0);
        for (size_t i = nums.size(); i > 0; --i)
        {
            std::vector<uint32_t> currentMultiply(maxSize + 1, 0);
            for (size_t j = rhs.nums.size(), index = maxSize; j > 0; j--, --index)
            {
                uint64_t tmpMultiply = 
                    (uint64_t)nums[i - 1] * (uint64_t)rhs.nums[j - 1] + (uint64_t)currentMultiply[index];
                currentMultiply[index] = tmpMultiply % BASE;
                currentMultiply[index - 1] = tmpMultiply / BASE;
            }

            size_t offset = result.size() - 1 - (nums.size() - i);
            for (size_t j = currentMultiply.size(); j > 0; j--, --offset)
            {
                uint32_t sum = result[offset] + currentMultiply[j - 1];
                if(sum >= BASE && offset > 0)
                    ++result[offset - 1];
                result[offset] = sum % BASE;
            }
        }

        std::vector<uint32_t> deleteZeroes;
        bool wasFound = false;
        for (size_t i = 0; i < result.size(); i++)
        {
            if(result[i] != 0){
                deleteZeroes.push_back(result[i]);
                wasFound = true;
            }
            else
                if(!wasFound && i == result.size() - 1)
                    deleteZeroes.push_back(0);
                else if(wasFound)
                    deleteZeroes.push_back(0);
        }
        
        nums = deleteZeroes;
        return *this;
    }

    TSuperLong TSuperLong::operator^(TSuperLong rhs) const{
        if(nums.size() == 0 || rhs.nums.size() == 0)
            return {};
        if(nums.size() == 1 && nums[0] == 0 &&
            rhs.nums.size() == 1 && rhs.nums[0] == 0)
            throw std::runtime_error("Error");
        if(rhs.nums.size() == 1 && rhs.nums[0] == 0)
            return (std::vector<uint32_t>{1});
        if(nums.size() == 1 && nums[0] == 0)
            return (std::vector<uint32_t>{0});
        
        suplong first = (suplong)"1", second = *this;
        while(!(rhs.nums.size() == 1 && rhs.nums[0] == 1)){
            if(!rhs.isEven()){
                rhs -= (suplong)"1";
                first *= second;
            }

            rhs = rhs / (suplong)"2";
            second *= second;
        }

        return first * second;
    }

    TSuperLong TSuperLong::operator^(const uint32_t& degree) const{
        if(nums.size() == 1 && nums[0] == 0 && degree == 0)
            throw std::runtime_error("Error");
        else if(degree == 0)
            return (std::vector<uint32_t>{1});

        TSuperLong result(*this);
        uint32_t degDynamic = degree;
        while(degDynamic > 1){
            if(degDynamic % 2){
                result *= *this;
                --degDynamic;
            }
            result *= result;
            degDynamic /= 2;
        }

        return result;
    }

    TSuperLong TSuperLong::operator/(const TSuperLong& rhs) const{
        if(rhs.nums.size() == 1 && rhs.nums[0] == 0)
            throw std::runtime_error("Error");
        else if(rhs.nums.size() == 1 && rhs.nums[0] == 1)
            return *this;
        else if(rhs > *this)
            return (suplong)"0";

        // May be faster
        suplong calculate;
        std::vector<uint32_t> result;
        for (size_t i = 0; i < nums.size(); i++)
        {
            calculate.push_back(nums[i]);
            int32_t l = 0, r = BASE - 1;
            suplong msp;
            while(l <= r){
                uint32_t mid = (l + r) >> 1;
                suplong currentSL = rhs * (suplong)(std::vector<uint32_t>{mid});
                if(currentSL == calculate){
                    msp = (suplong)("0");
                    break;
                }
                if(currentSL > calculate){
                    r = mid - 1;
                    continue;
                }

                msp = calculate - currentSL;
                l = mid + 1;
            }

            result.push_back((l + r) / 2);
            calculate = msp;
        }

        return (result);
    }

    TSuperLong& TSuperLong::expand(const size_t& count){
        if(nums.size() == 0){
            nums.push_back(0);
            return *this;
        }
        else if(nums.size() == 1 && nums[0] == 0)
            return *this;

        size_t newsz = nums.size() + count;
        std::vector<uint32_t> newv(newsz);
        for (size_t i = 0; i < newsz; i++)
            if(i < nums.size())
                newv[i] = std::move(nums[i]);
            else
                newv[i] = 0;
        nums = newv;
        return *this;
    }

    TSuperLong TSuperLong::powten(const size_t& count) const{
        if(nums.size() == 0)
            return {0};
        else if(nums.size() == 1 && nums[0] == 0)
            return {0};
        
        size_t newsz = nums.size() + count;
        std::vector<uint32_t> newv(newsz);
        for (size_t i = 0; i < newsz; i++)
            if(i < nums.size())
                newv[i] = std::move(nums[i]);
            else
                newv[i] = 0;

        return (newv);
    }

    void TSuperLong::push_back(const uint32_t& input){
        if(nums.size() == 1 && nums[0] == 0)
            nums[0] = input;
        else
            nums.push_back(input);
    }

    bool TSuperLong::isEven() const{
        if(nums.size() == 0)
            return false;
        
        return !(nums[nums.size() - 1] % 2);
    }

    bool TSuperLong::operator<(const TSuperLong& rhs) const{
        if(nums.size() < rhs.nums.size())
            return true;
        else if(nums.size() > rhs.nums.size())
            return false;
        
        for (size_t i = 0; i < nums.size(); i++)
        {
            if(nums[i] > rhs.nums[i])
                return false;
            else if(nums[i] < rhs.nums[i])
                return true;
        }
        return false;
    }

    bool TSuperLong::operator>(const TSuperLong& rhs) const{
        if(nums.size() < rhs.nums.size())
            return false;
        else if(nums.size() > rhs.nums.size())
            return true;
        
        for (size_t i = 0; i < nums.size(); i++)
        {
            if(nums[i] > rhs.nums[i])
                return true;
            else if(nums[i] < rhs.nums[i])
                return false;
        }
        return false;
    }

    bool TSuperLong::operator>=(const TSuperLong& rhs) const{
        if(nums.size() < rhs.nums.size())
            return false;
        else if(nums.size() > rhs.nums.size())
            return true;
        
        for (size_t i = 0; i < nums.size(); i++)
        {
            if(nums[i] > rhs.nums[i])
                return true;
            else if(nums[i] < rhs.nums[i])
                return false;
        }
        return true;
    }

    bool TSuperLong::operator==(const TSuperLong& rhs) const{
        if(nums.size() != rhs.nums.size())
            return false;
        
        for (size_t i = 0; i < nums.size(); i++)
            if(nums[i] != rhs.nums[i])
                return false;
    
        return true;
    }
}