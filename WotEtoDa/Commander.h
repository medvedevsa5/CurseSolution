#pragma once

#include <functional>
#include <string>

#include "Commands.h"

class Commander
{
public:
	void setCommand(Commands cmd);
	void setFileName(const std::string& fileName);

	std::string invoke() const;

private:
	std::function < std::string() > command_;
	std::string fileName_;
};