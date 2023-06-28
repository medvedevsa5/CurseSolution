#pragma once

#include "Commander.h"
#include "Commands.h"

void Commander::setCommand(Commands cmd)
{
	switch (cmd)
	{
	case EncodeNum:
		command_ = [this]() { Encode()(this->fileName_); };
		break;
	case DecodeNum:
		command_ = [this]() { Decode()(this->fileName_); };
		break;
	case AnalyzeNum:
		command_ = [this]() { Analyze()(this->fileName_); };
		break;
	default:
		command_ = nullptr;
		break;
	}
}

void Commander::setFileName(const std::string& fileName)
{
	fileName_ = fileName;
}

void Commander::invoke()
{
	if (command_ == nullptr)
	{
		//throw
	}
	command_();
}
