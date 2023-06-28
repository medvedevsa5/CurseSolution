#pragma once
#ifndef _COMMANDS_
#define _COMMANDS_

#include <string>

enum Commands
{
	EncodeNum,
	DecodeNum,
	AnalyzeNum
};

class Encode
{
public:
	std::string operator()(const std::string& fileName);
};

class Decode
{
public:
	std::string operator()(const std::string& fileName);
};

class Analyze
{
public:
	std::string operator()(const std::string& fileName);
};

#endif