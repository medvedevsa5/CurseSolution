#pragma once
#ifndef _HUFFMAN_TABLE_
#define _HUFFMAN_TABLE_

#include <iosfwd>
#include <vector>
#include <string>
#include <unordered_map>

#include "StreamScanner.h"

class EncodingTable
{
public:
	// https://stackoverflow.com/questions/14856344/when-should-stdmove-be-used-on-a-function-return-value
	// https://habr.com/ru/companies/vk/articles/666330/
	// https://pvs-studio.com/en/blog/terms/6516/
	// https://en.cppreference.com/w/cpp/language/copy_elision NOTES
	void encode(std::vector<char>& orig, std::vector<char>& dest, StreamScanner& scanner);

	void insertCode(char ch, std::vector<bool>& code);
	void getCode(char ch, std::vector<bool>& code) const;

	double getExpectancy(StreamScanner& scanner) const;
	size_t getMapSize() const;

	void serializeMap(std::vector<char>& out);
public:
	std::unordered_map<char, std::vector<bool>> codeTable_;

	// https://en.wikipedia.org/wiki/Expected_value
	double calculateExpectancy(StreamScanner& scanner) const;
	double calculateCompressionRatio(StreamScanner& scanner) const;
};

#endif // _HUFFMAN_TABLE_