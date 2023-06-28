#pragma once
#ifndef _STREAM_SCANNER_
#define _STREAM_SCANNER_

#include <iosfwd>
#include <unordered_map>

#include "Constants.h"

class StreamScanner
{
public:
	void scan(std::istream& in, std::vector<char>& vec);

	int getProbability(char ch) const;
	void addProbability(char ch);

	size_t getCharCount() const;

	size_t getFileSize() const;

private:


	std::unordered_map<char, int> probability_;
	size_t charCount_ = 0;
	size_t fileSize_ = 0;
};

#endif // _STREAM_SCANNER_
