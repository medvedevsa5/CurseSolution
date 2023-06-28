#pragma once

#include <functional>
#include <string>

#include "Commands.h"

class Commander
{
public:
	void setCommand(Commands cmd);
	void setFileName(const std::string& fileName);

	void invoke();

private: // CHANGE!!!
	std::function<void()> command_;
	std::string fileName_;
};