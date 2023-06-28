// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>

#include "StreamScanner.h"
#include "FmtGuard.h"
#include "EncodingTable.h"
#include "Constants.h"

void EncodingTable::encode(std::vector<char>& orig, std::vector<char>& dest, StreamScanner& scanner)
{
	std::vector<char> tmpVector;
	double compressionRatio = calculateCompressionRatio(scanner);
	tmpVector.reserve(orig.size() * (1 - compressionRatio) + 1);

	size_t bitCount = 0;

	for(auto& ch : orig)
	{
		std::vector<bool>& code = codeTable_.at(ch);
		
		for (const auto& bit : code)
		{
			if (bit == 1)
			{
				if ((bitCount / 8) >= tmpVector.size())
				{
					tmpVector.push_back((char)1 << (bitCount % 8));
				}
				else
				{
					tmpVector[bitCount / 8] |= (char)1 << (bitCount % 8);
				}
			}
			bitCount++;
		}
	}

	dest.swap(tmpVector);
}

void EncodingTable::insertCode(char ch, std::vector<bool>& code)
{
	codeTable_[ch] = code;
}

void EncodingTable::getCode(char ch, std::vector<bool>& code) const
{
	auto found = codeTable_.find(ch);
	if (found != codeTable_.end())
	{
		code = found->second;
	}
}

double EncodingTable::getExpectancy(StreamScanner& scanner) const
{
	return calculateExpectancy(scanner);
}

size_t EncodingTable::getMapSize() const
{
	return codeTable_.size();
}

// тнплюр:
// (char) яхлбнк | (short) дкхмю йндю | (short) йнд
void EncodingTable::serializeMap(std::vector<char>& out)
{
	std::vector<char> serializedMap;
	serializedMap.reserve(sizeof(codeTable_));

	auto appendData = 
		[&serializedMap](const char* data, size_t size) 
	{
		serializedMap.insert(serializedMap.end(), data, data + size);
	};

	for (const auto& entry : codeTable_)
	{
		appendData(reinterpret_cast<const char*>(&entry.first), sizeof(entry.first));

		short codeSize = (short)entry.second.size();
		appendData(reinterpret_cast<const char*>(&codeSize), sizeof(codeSize));

		short codeBit = 0;
		for (size_t i = 0; i < codeSize; ++i)
		{
			if (entry.second[i])
			{
				codeBit |= (1 << i);
			}
		}
		appendData(reinterpret_cast<const char*>(&codeBit),sizeof(codeBit));
	}

	out.swap(serializedMap);
}

double EncodingTable::calculateExpectancy(StreamScanner& scanner) const
{
	double result = 0;
	for (auto& var : codeTable_)
	{
		result +=
			(double)scanner.getProbability(var.first) / scanner.getCharCount() * var.second.size();
	}
	return result;
}

double EncodingTable::calculateCompressionRatio(StreamScanner& scanner) const
{
	double expectedValue = calculateExpectancy(scanner);
	return (ASCII_SIZE - expectedValue) / ASCII_SIZE;
}
