#pragma once

#include <crtdbg.h>
#include <ostream>
#include <sstream>
#include <stdexcept>

class MemoryTracker
{
private:
	_CrtMemState s1, s2, s3;
	void differState();
public:
	void FirstState();
	void SecondState();
	void Print(std::ostream& out);
	std::string Print();
	MemoryTracker();
	~MemoryTracker();
};

