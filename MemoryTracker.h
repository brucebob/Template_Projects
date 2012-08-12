#pragma once

#include <crtdbg.h>
#include <ostream>
#include <sstream>
#include <stdexcept>
/*
*
* Memory Tracker used to keep track of what is allocated during the first and second state.
*
*/
class MemoryTracker
{
private:
	_CrtMemState s1, s2, s3;
	// used to differ the first and second states 
	// throws if first and second state are not used
	void differState();
public:
	void FirstState();
	void SecondState();
	void Print(std::ostream& out);
	int FreeBlocks(); 
	int CRTBlocks();
	int IgnoreBlocks(); 
	int ClientBlocks();
	int NormalBlocks();
	std::string Print();
	MemoryTracker();
	~MemoryTracker();
};

