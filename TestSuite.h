#pragma once

#include <string>
#include <map>
#include <iostream>
#include <cstdlib>

namespace TestSuite 
{
	typedef void(*TestFn)( void );

	struct Error 
	{
		Error( const std::string & cond, const std::string & file, int line ) :mCond( cond ), mFile( file ), mLine( line ) 
		{
		}
		std::string mCond, mFile;
		int mLine;
	};

	class Tester
	{
	private:
		unsigned int mErrors;
		std::map <std::string, TestFn> mTests;

		Tester() : mErrors( 0 ) 
		{
		}

	public:
		static Tester & Instance( )
		{
			static Tester instance;
			return instance;
		}
		void AddTest( const std::string & name, TestFn test ) 
		{
			if ( ! mTests.insert( std::make_pair( name, test ) ).second ) 
			{ 
				std::cerr << "duplicate test name: " << name << std::endl;
				std::exit( -1 );
			}
		}

		void RunTests() 
		{
			std::map<std::string,TestFn>::iterator it = mTests.begin();
			while ( it != mTests.end() ) 
			{
				try 
				{
					std::cout << it->first << ":";
					it->second();
					std::cerr << " passed\n";
				}
				catch( const Error & e ) 
				{
					std::cerr << " failed [ " << e.mCond << " ] is false in " 
						<< e.mFile << " at line " << e.mLine << "\n";
					mErrors++;
				}
				++it;
			}
		}
		unsigned int Errors() const 
		{
			return mErrors;
		}

	};

	struct TestAdder 
	{
		TestAdder(const std::string & name, TestFn fn) 
		{
			Tester::Instance().AddTest(name, fn);
		}
	};

}  

#define TEST_MAIN() 									\
{														\
	TestSuite::Tester::Instance().RunTests( );			\
	return TestSuite::Tester::Instance().Errors();		\
}

#define TEST_ADD(testname)											\
	static void testname();												\
	static TestSuite::TestAdder TA_##testname(#testname, testname);		\
	void testname() 								

#define TEST_CONDITION(cond)								\
	if(!(cond)) 												\
	{															\
		throw TestSuite::Error(#cond, __FILE__, __LINE__ );		\
	}