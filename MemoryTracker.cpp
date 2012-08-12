
#include "MemoryTracker.h"


MemoryTracker::MemoryTracker()
{
	s1.pBlockHeader = s2.pBlockHeader = s3.pBlockHeader= NULL;
}


MemoryTracker::~MemoryTracker(void)
{

}

void MemoryTracker::FirstState()
{
	_CrtMemCheckpoint( &s1 );
}
void MemoryTracker::SecondState()
{
	_CrtMemCheckpoint( &s2 );
	differState();
}
void MemoryTracker::Print( std::ostream& out )
{
	out << Print();
}

std::string MemoryTracker::Print()
{
	std::stringstream st;
	const unsigned int TotalBlocks = 5;
	const char* states[TotalBlocks] = {"Free", "Normal", "CRT", "Ignore", "Client"};
	
	for (unsigned int block = 0; block < TotalBlocks; block++)
	{
		// "%Id bytes in %Id %hs Blocks.\n"
		st << s3.lSizes[block] << " bytes in " << s3.lCounts[block] << " " << states[block] << " Blocks." << std::endl;
	}
	// "Largest number used: %Id bytes.\n", state->lHighWaterCount
	// "Total allocations: %Id bytes.\n", state->lTotalCount
	st << "Largest number used: " << s3.lHighWaterCount << " bytes." << std::endl;
	st << "Total allocations: " << s3.lTotalCount << " bytes." << std::endl;
	return st.str();
}

void MemoryTracker::differState()
{
	if(s1.pBlockHeader != NULL && s2.pBlockHeader != NULL)
	{
		_CrtMemDifference(&s3, &s1, &s2);
	}
	else
	{
		throw std::exception("MemoryTracker: Check state of either first or second was not used.\n");
	}
}
int MemoryTracker::NormalBlocks()
{
	if(s3.pBlockHeader != nullptr)
	{
		return s3.lSizes[1];
	}
	else
	{
		throw std::exception("MemoryTracker: Check state of either first or second was not used.\n");
	}
}

int MemoryTracker::FreeBlocks()
{
	if(s3.pBlockHeader != nullptr)
	{
		return s3.lSizes[0];
	}
	else
	{
		throw std::exception("MemoryTracker: Check state of either first or second was not used.\n");
	}
}

int MemoryTracker::CRTBlocks()
{
	if(s3.pBlockHeader != nullptr)
	{
		return s3.lSizes[2];
	}
	else
	{
		throw std::exception("MemoryTracker: Check state of either first or second was not used.\n");
	}
}

int MemoryTracker::IgnoreBlocks()
{
	if(s3.pBlockHeader != nullptr)
	{
		return s3.lSizes[3];
	}
	else
	{
		throw std::exception("MemoryTracker: Check state of either first or second was not used.\n");
	}
}

int MemoryTracker::ClientBlocks()
{
	if(s3.pBlockHeader != nullptr)
	{
		return s3.lSizes[4];
	}
	else
	{
		throw std::exception("MemoryTracker: Check state of either first or second was not used.\n");
	}
}
