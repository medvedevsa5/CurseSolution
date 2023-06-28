#include "Commander.h"
#include "Commands.h"
#include "Exceptions.h"

void Commander::setCommand(Commands cmd)
{
	switch (cmd)
	{
	case EncodeNum:
		command_ = [this]() { return Encode()(this->fileName_); };
		break;
	case DecodeNum:
		command_ = [this]() { return Decode()(this->fileName_); };
		break;
	case AnalyzeNum:
		command_ = [this]() { return Analyze()(this->fileName_); };
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

std::string Commander::invoke() const
{
	if (command_ == nullptr)
	{
		throw CommandNotFoundException();
	}
	return command_();
}
