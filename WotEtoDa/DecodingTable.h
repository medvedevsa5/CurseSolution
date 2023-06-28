#pragma once

#include <vector>
#include <unordered_map>

class DecodingTable
{
public:
	void deserialize(std::ifstream& data, size_t keyCount);

	void decode(const std::vector<char>& code, std::vector<char>& result, size_t fileSize) const;
private:
	std::unordered_map<std::vector<bool>, char> codeTable_;
};