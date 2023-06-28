#include <iostream>

#include "FmtGuard.h"

FmtGuard::FmtGuard(std::basic_ios<char>& s) :
	s_(s),
	fill_(s.fill()),
	precision_(s.precision()),
	fmt_(s.flags())
{}

FmtGuard::~FmtGuard()
{
	s_.fill(fill_);
	s_.precision(precision_);
	s_.flags(fmt_);
}
