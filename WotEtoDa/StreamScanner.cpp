#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>

#include "StreamScanner.h"
#include "FmtGuard.h"

void StreamScanner::scan(std::istream& in, std::vector<char>& vec)
{
	FmtGuard fmtGuard(in);
	in >> std::noskipws;
	
	in.seekg(0, std::ios::end);
	std::streampos fileSize = in.tellg();
	in.seekg(0, std::ios::beg);

	std::vector<char> tmpVector;
	tmpVector.reserve(fileSize);
	char ch = '\0';

	while (in >> ch)
	{
		addProbability(ch);
		tmpVector.push_back(ch);
	}

	fileSize_ = fileSize;

	vec.swap(tmpVector);
}

void StreamScanner::scan(std::istream& in)
{
	FmtGuard fmtGuard(in);
	in >> std::noskipws;

	in.seekg(0, std::ios::end);
	std::streampos fileSize = in.tellg();
	in.seekg(0, std::ios::beg);

	char ch = '\0';

	while (in >> ch)
	{
		addProbability(ch);
	}

	fileSize_ = fileSize;
}

int StreamScanner::getProbability(char ch) const
{
	int frequency = 0;
	auto found = probability_.find(ch);
	if (found != probability_.end())
	{
		frequency = found->second;
	}
    return frequency;
}

void StreamScanner::addProbability(char ch)
{
	charCount_++;
    probability_[ch]++;
}

size_t StreamScanner::getCharCount() const
{
	return charCount_;
}

size_t StreamScanner::getFileSize() const
{
	return fileSize_;
}
