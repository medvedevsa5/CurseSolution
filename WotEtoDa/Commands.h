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
	void operator()(const std::string& fileName);
};

class Decode
{
public:
	void operator()(const std::string& fileName);
};

class Analyze
{
public:
	void operator()(const std::string& fileName);
};

#endif