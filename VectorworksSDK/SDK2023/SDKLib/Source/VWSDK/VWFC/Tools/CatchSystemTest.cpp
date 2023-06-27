#include "StdHeaders.h"
#include "VectorworksSDK.h"
//#define CATCH_CONFIG_RUNNER	// only defined in a single .cpp file that includes catch.hpp
#include "VWFC/Tools/CatchSystemTest.h"

VectorWorks::Debug::ISystemTestEnvironment* gTestEnv = nullptr;
//Catch::Session gCatchSession;		// only one, and only use it in this cpp file.

#ifdef _MINICAD_
std::vector<std::function<bool(EStandardInterfaceManagerMapState, SStandardInterfaceManagerMapData&)>>& CatchTests()
{
	static std::vector<std::function<bool(EStandardInterfaceManagerMapState, SStandardInterfaceManagerMapData&)>> gCatchTests;
	return gCatchTests;
}
#else
std::vector<std::function<void(Sint32 action, void* moduleInfo, const VWIID& iid, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)>>& CatchTests()
{
	static std::vector<std::function<void(Sint32 action, void* moduleInfo, const VWIID& iid, IVWUnknown*& inOutInterface, CallBackPtr cbp, Sint32& reply)>> gCatchTests;
	return gCatchTests;
}
#endif

TEST_OpenDocument::TEST_OpenDocument()
{
	fOpened = gSDK->OpenDocumentPath(nullptr, false/*inbShowErrorMessages*/);
}

TEST_OpenDocument::TEST_OpenDocument(const std::string& relativeFilePath, bool inbShowErrorMessages/*=false*/)
{
	using namespace VectorWorks::Filing;
	IFolderIdentifierPtr testFolder(IID_FolderIdentifier);
	IFileIdentifierPtr testFile(IID_FileIdentifier);

	size_t pos = relativeFilePath.rfind('/');
	std::string relativeFolderPath = pos != relativeFilePath.npos ? relativeFilePath.substr(0, pos+1) : "";

	gTestEnv->GetTestFileDirectory(testFolder);
	
	testFile->Set(testFolder, relativeFilePath);
	fOpened = gSDK->OpenDocumentPath(testFile, inbShowErrorMessages);

	TXString filepath; 
	testFolder->GetFullPath(filepath); 
	filepath += relativeFolderPath;
#if GS_WIN
	filepath.Replace("/", "\\");
#endif
	fAbsoluteFolderPath = filepath;
}

TEST_OpenDocument::~TEST_OpenDocument()
{
	if( fOpened )
		gSDK->CloseDocument();
}

bool TEST_OpenDocument::IsOpened() 
{ 
	return fOpened; 
}

std::string TEST_OpenDocument::AbsoluteFolderPath() 
{ 
	return fAbsoluteFolderPath; 
}

VectorWorks::Debug::ISystemTestEnvironment* GetAutomatedSystemTestEnv()
{
	return gTestEnv;
}

