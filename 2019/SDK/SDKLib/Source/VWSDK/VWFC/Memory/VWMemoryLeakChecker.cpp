#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VectorWorks::Filing;
using namespace VWFC::Memory;

VWMemoryLeakChecker* VWMemoryLeakChecker::instance_ = nullptr;

VWMemoryLeakChecker& VWMemoryLeakChecker::Instance() {
    if ( instance_ == nullptr ) {
        instance_ = new VWMemoryLeakChecker();
        std::atexit(Destroy);
    }
    return *instance_;
}
	
VWMemoryLeakChecker::VWMemoryLeakChecker()
{
	m_bIsRunning = false; 
	m_bInitialized = false;
	m_pbeforeBlocks = NULL; 
	m_pafterBlocks = NULL; 
	m_pdiffBlocks = NULL;
}

void VWMemoryLeakChecker::Destroy()
{
	delete instance_;
	instance_ = nullptr;
}

void VWMemoryLeakChecker::Init()
{
	m_pbeforeBlocks = (void **) new void*[MML_BLOCK_COUNT]();
	m_pafterBlocks = (void **) new void*[MML_BLOCK_COUNT]();
	m_pdiffBlocks = (void **) new void*[MML_BLOCK_COUNT]();

	m_bInitialized = true;
}

void VWMemoryLeakChecker::Reset()
{
	if (m_bInitialized){
		gVWMM->EnableStackTraceInfo(false);
		m_bIsRunning = false;

		if (m_pdiffBlocks)
			delete [] m_pdiffBlocks;

		if (m_pafterBlocks)
			delete [] m_pafterBlocks;

		if (m_pbeforeBlocks)
			delete [] m_pbeforeBlocks;

		m_bInitialized = false;
	}
}

void VWMemoryLeakChecker::Start()
{
	if (m_bInitialized){
		// record all blocks before
		gVWMM->GetAllBlocks(m_pbeforeBlocks, MML_BLOCK_COUNT);
		gVWMM->EnableStackTraceInfo(true);
		m_bIsRunning = true;
	}
}

bool VWMemoryLeakChecker::Stop(MemoryLeakResults& results)
{
	if (m_bInitialized && m_bIsRunning) {

		m_bIsRunning = false;
		gVWMM->GetAllBlocks(m_pafterBlocks, MML_BLOCK_COUNT);

		size_t numDiffBlocks = gVWMM->SubtractBlockArrays(m_pafterBlocks, MML_BLOCK_COUNT, m_pbeforeBlocks, MML_BLOCK_COUNT, m_pdiffBlocks, MML_BLOCK_COUNT);
		const size_t kTrace_size = 256 * gVWMM->fStackTraceDepth;
		results.m_totalLeakedBytes = 0;
		for (size_t i = 0; i < numDiffBlocks && i < MML_BLOCK_COUNT; ++i)
		{
			char* stackTrace = (char*)malloc(kTrace_size);
            if (stackTrace) {
                stackTrace[0] = '\0';
                size_t blockSize = gVWMM->GetBlockSize(m_pdiffBlocks[i]);
                results.m_totalLeakedBytes += blockSize;
                gVWMM->GetBlockStackTrace(m_pdiffBlocks[i], stackTrace, kTrace_size);
                MemoryLeak leak;
                leak.m_size = blockSize;
                leak.m_callstack = TXString(stackTrace);
                results.m_results.insert(leak);
                free(stackTrace);
            }
		}
		delete[] m_pdiffBlocks;
		delete[] m_pafterBlocks;
		delete[] m_pbeforeBlocks;

		gVWMM->EnableStackTraceInfo(false);
		m_bInitialized = false;
		return true;
	}
	else
		return false;
}

bool VWFC::Memory::VWMemoryLeakChecker::StopAndDump(VectorWorks::Filing::IFileIdentifierPtr file)
{
	bool success = false;
	if (m_bInitialized && m_bIsRunning)
	{
		MemoryLeakResults results;
		success = this->Stop(results);
		this->WriteReport(file, results);
	}
	return success;
}

bool VWFC::Memory::VWMemoryLeakChecker::StopAndDumpToUserData()
{
	bool success = false;
	if (m_bInitialized && m_bIsRunning)
	{
		IApplicationFoldersPtr appFolders(IID_ApplicationFolders);
		IFolderIdentifierPtr logFolder;
		if (VCOM_SUCCEEDED(appFolders->GetFolder(EFolderSpecifier::kAppDataFolder, &logFolder, false))) {
			TXString newFileName;
			IFileIdentifierPtr reportFile(IID_FileIdentifier);

			Sint32 count = 0;
			bool fileexists = false;
				
			do {
				newFileName = "VWLeakReport";
				if (count > 0)
					newFileName << count;
				newFileName << ".txt";

				IFileIdentifierPtr trialFile(IID_FileIdentifier);
				trialFile->Set(logFolder, newFileName);

				trialFile->ExistsOnDisk(fileexists);
				if (fileexists) {
					count += 1;
				}
				else {
					reportFile = trialFile;
				}
					
			} while (fileexists);
			success = this->StopAndDump(reportFile);
		}
	}
	return success;
}

void VWMemoryLeakChecker::WriteReport(VectorWorks::Filing::IFileIdentifierPtr file, const MemoryLeakResults& results)
{
	TXString filePath;
	file->GetFileFullPath(filePath);
    std::ofstream reportFile(filePath.GetCharPtr(), std::fstream::out | std::fstream::trunc);
    
	if (reportFile.is_open())
	{
		//Get start date and time
		TXString dateTimeString = gSDK->GetFormattedDateTimeString(EDateTimeFormat::DDMMYY_TIME);

		size_t totalMBBytesSize = results.m_totalLeakedBytes/(1024*1024) ;
        
        std::ostringstream headerstream;
		if (results.m_totalLeakedBytes == 0 && results.m_results.size() == 0)
		{
			headerstream << "No Vectorworks memory leaks detected." << std::endl;
			std::string headstr = headerstream.str();
			reportFile.write(headstr.c_str(), headstr.length());
		}
		else
		{
			headerstream << "VECTORWORKS MEMORY LEAK DETECTED!" << std::endl;
			headerstream << "*****************************************************************************************" << std::endl;
			headerstream << "**********************       Memory Leak Report: " << (const char*)dateTimeString << std::endl;
			headerstream << "**********************       Number of leaked blocks: " << results.m_results.size() << std::endl;
			headerstream << "**********************       Total Leaked Memory: " << results.m_totalLeakedBytes << " (Bytes) == " << totalMBBytesSize << " (MB) " << std::endl;
			headerstream << "*****************************************************************************************" << std::endl;
			std::string headstr = headerstream.str();
			reportFile.write(headstr.c_str(), headstr.length());

			for (auto it = results.m_results.begin(); it != results.m_results.end(); it++)
			{
				std::ostringstream tracestream;
				tracestream << std::endl;
				tracestream << "---------------------Persistent Block: (size= " << it->m_size << " ) StackTrace:" << std::endl;
				tracestream << it->m_callstack.GetStdString() << std::endl;
				tracestream << "---------------------" << std::endl;

				std::string tracestr = tracestream.str();
				reportFile.write(tracestr.c_str(), tracestr.length());
			}
		}
		reportFile.close();
	}
}

void SystemTests::MemoryLeakTest::setUp()
{
	CPPUNIT_ASSERT(gSDK->OpenDocumentPath(nullptr, false));
}

void SystemTests::MemoryLeakTest::tearDown()
{
	CPPUNIT_ASSERT(gSDK->CloseDocument() == false);
}

void SystemTests::MemoryLeakTest::test_Leaks()
{
	{	//Check to make sure it doesn't pick up anything when we don't do anything
		VWMemoryLeakChecker& checker = VWMemoryLeakChecker::Instance();
		checker.Init();
		checker.Start();
		MemoryLeakResults results;
		checker.Stop(results);
		checker.Reset();
		CPPUNIT_ASSERT(results.m_results.size() == 0);
		CPPUNIT_ASSERT(results.m_totalLeakedBytes == 0);
	}

	{	//Check to make sure it doesn't pick up anything when we free the memory
		VWMemoryLeakChecker& checker = VWMemoryLeakChecker::Instance();
		checker.Init();
		checker.Start();

		void* block = gVWMM->Allocate(1234);
		gVWMM->Deallocate(block);
		MemoryLeakResults results;
		checker.Stop(results);
		checker.Reset();
		CPPUNIT_ASSERT(results.m_results.size() == 0);
		CPPUNIT_ASSERT(results.m_totalLeakedBytes == 0);
	}

	{	//Check to make sure it does pick up a block that's not freed
		VWMemoryLeakChecker& checker = VWMemoryLeakChecker::Instance();
		checker.Init();
		checker.Start();

		void* block = gVWMM->Allocate(1234);

		MemoryLeakResults results;
		checker.Stop(results);
		checker.Reset();
		CPPUNIT_ASSERT(results.m_results.size() == 1);
		CPPUNIT_ASSERT(results.m_totalLeakedBytes == 1234);
		gVWMM->Deallocate(block);
	}
}

