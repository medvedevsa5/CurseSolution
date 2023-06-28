#include "DecodingTable.h"
#include <sstream>
#include <iostream>
#include <fstream>

void DecodingTable::deserialize(std::ifstream& data, size_t keyCount)
{
    std::unordered_map<std::vector<bool>, char> tmpVector;

    for (size_t i = 0; i < keyCount; ++i)
    {
        char ch = 0;
        data.read(reinterpret_cast<char*>(&ch), sizeof(ch));

        short codeSize = 0;
        data.read(reinterpret_cast<char*>(&codeSize), sizeof(codeSize));

        short codeRaw = 0;
        data.read(reinterpret_cast<char*>(&codeRaw), sizeof(codeRaw));

        std::vector<bool> code;
        code.reserve(codeSize);

        for (size_t j = 0; j < codeSize; ++j)
        {
            bool bit = ((codeRaw >> j) & 1) != 0;
            code.push_back(bit);
        }

        tmpVector[code] = ch;
    }

    codeTable_.swap(tmpVector);
}

void DecodingTable::decode(const std::vector<char>& code, std::vector<char>& result, size_t fileSize) const
{
	std::vector<char> tmpVector;
	result.reserve(fileSize);

	std::vector<bool> translatedChar;
	translatedChar.reserve(8);

	int num = code.size() * 8;

	for (size_t i = 0; i < num - 6; i++)
	{
		if ((code[i / 8] >> (i % 8)) & 1)
		{
			translatedChar.push_back(1);
		}
		else
		{
			translatedChar.push_back(0);
		}
		auto codeIter = codeTable_.find(translatedChar);
		if (codeIter != codeTable_.cend())
		{
			tmpVector.push_back(codeIter->second);
			translatedChar.clear();
		}
	}

	result.swap(tmpVector);
}
