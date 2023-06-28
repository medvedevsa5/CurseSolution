#pragma once
#ifndef _FMT_GUARD_
#define _FMT_GUARD_

#include <iostream>

// Нужен, чтобы сохранять настройки потока и возвращать их при вызове ~.
class FmtGuard
{
public:
	FmtGuard(std::basic_ios<char>& s);
	~FmtGuard();

private:
	std::basic_ios<char>& s_;
	char fill_;
	std::streamsize precision_;
	std::basic_ios<char>::fmtflags fmt_;
};

#endif // _FMT_GUARD_
