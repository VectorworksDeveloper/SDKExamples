#pragma once
#include <cstdlib>
#include <iostream>
#include "Interfaces/VectorWorks/Filing/IFileIdentifier.h"
#include "Interfaces/VectorWorks/Debug/ISystemTest.h"
#include <set>

namespace VWFC
{
	namespace Memory
	{
		struct MemoryLeak
		{
			size_t m_size;
			TXString m_callstack;
		};

		inline bool operator==(const MemoryLeak& lhs, const MemoryLeak& rhs) { return (lhs.m_size == rhs.m_size) && (lhs.m_callstack == rhs.m_callstack); }
		inline bool operator!=(const MemoryLeak& lhs, const MemoryLeak& rhs) { return !operator==(lhs, rhs); }
		inline bool operator< (const MemoryLeak& lhs, const MemoryLeak& rhs) { return (lhs.m_size < rhs.m_size); }
		inline bool operator> (const MemoryLeak& lhs, const MemoryLeak& rhs) { return  operator< (rhs, lhs); }
		inline bool operator<=(const MemoryLeak& lhs, const MemoryLeak& rhs) { return !operator> (lhs, rhs); }
		inline bool operator>=(const MemoryLeak& lhs, const MemoryLeak& rhs) { return !operator< (lhs, rhs); }

		struct cmpStruct
		{
			bool operator() (MemoryLeak const & lhs, MemoryLeak const & rhs) const
			{
				return lhs > rhs;
			}
		};

		struct MemoryLeakResults
		{
			size_t m_totalLeakedBytes;
			//This is sorted so that the largest memory leaks appear first.  
			std::set<MemoryLeak, cmpStruct> m_results;
		};

        //When turned on, Vectorworks will slow down significantly, but will collect stack trace information for each memory allocation
		class VWMemoryLeakChecker
		{
#define MML_BLOCK_COUNT (100000)
		public:
			static VWMemoryLeakChecker& Instance();

			void Init();
			void Start();
			//Returns memory blocks that have not been freed with their stack trace
			bool Stop(MemoryLeakResults& results);

			void WriteReport(VectorWorks::Filing::IFileIdentifierPtr file, const MemoryLeakResults& results);
			//Dumps leaked memory blocks to a file
			bool StopAndDump(VectorWorks::Filing::IFileIdentifierPtr file);
			//Dumps leaked memory blocks to a file called "VWLeakReport.txt" in the users' app data folder
			bool StopAndDumpToUserData();
			void Reset();
			bool IsRunning() { return m_bIsRunning; }
			bool Initialized() { return m_bInitialized; }
			size_t GetStacktraceDepth() { return gVWMM->fStackTraceDepth; }
			void SetStacktraceDepth(size_t depth) {
				if (depth > MEMORY_BLOCK_STACKTRACE_FRAME_COUNT_LIMIT)
					depth = MEMORY_BLOCK_STACKTRACE_FRAME_COUNT_LIMIT;
				gVWMM->fStackTraceDepth = depth; 
			}

		private:
			static void Destroy();

		private:

			static VWMemoryLeakChecker* instance_;

			std::vector<void*> m_pbeforeBlocks;
			std::vector<void*> m_pafterBlocks;
			std::vector<void*> m_pdiffBlocks;

			bool m_bInitialized;
			bool m_bIsRunning;

			VWMemoryLeakChecker();
			~VWMemoryLeakChecker() {};
			VWMemoryLeakChecker(VWMemoryLeakChecker const& copy) {};
			VWMemoryLeakChecker& operator=(VWMemoryLeakChecker const& copy) { return *this; }
		};
	}
}

namespace SystemTests
{
	// {087B4192-DFDD-4B59-9264-1F96D349936D}
	static const VWIID IID_MemoryLeakTest = { 0x87b4192, 0xdfdd, 0x4b59,{ 0x92, 0x64, 0x1f, 0x96, 0xd3, 0x49, 0x93, 0x6d } };

	using namespace VectorWorks::Debug;
	class MemoryLeakTest : public VCOMImmediateImpl<ISystemTest>
	{
		CPPUNIT_TEST_SUITE2(MemoryLeakTest, "Memory Leak Checker", "swilcox@vectorworks.net", ESystemTestType::SpecialRun);
		CPPUNIT_TEST(test_Leaks, "Leaks");
		CPPUNIT_TEST_SUITE_END();

		void setUp();
		void tearDown();

		void test_Leaks();
	};
}
