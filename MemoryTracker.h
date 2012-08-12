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
	int NormalBlocks()
	{
		return s3.lSizes[1];
	}
	std::string Print();
	MemoryTracker();
	~MemoryTracker();
};

