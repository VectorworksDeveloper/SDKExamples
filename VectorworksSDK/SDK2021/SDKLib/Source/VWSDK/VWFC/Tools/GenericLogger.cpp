//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"


using namespace VWFC::Tools;
using namespace VectorWorks::Filing;

static std::mutex	gFlushBarrier;

// --------------------------------------------------------------------------------------------------
CGenericLogger::CGenericLogger(EFolderSpecifier folderSpec, const TXString& logFileName)
	: fLogFileID( IID_FileIdentifier )
	, fScriptPrefix( "PythonScript: " )
	, fScriptHadErrors( false )
{
	IFolderIdentifierPtr outputFolderID( IID_FolderIdentifier );
	outputFolderID->Set( folderSpec, true );
	fLogFileID->Set( outputFolderID, logFileName );
}

CGenericLogger::CGenericLogger(IFolderIdentifier* outputFolderID, const TXString& logFileName)
	: fLogFileID( IID_FileIdentifier )
	, fScriptPrefix( "PythonScript: " )
	, fScriptHadErrors( false )
{
	fLogFileID->Set( outputFolderID, logFileName );
}

CGenericLogger::~CGenericLogger()
{
	this->Flush();
}

void CGenericLogger::Flush()
{
	std::lock_guard<std::mutex> block_threads_until_finish_this_job( gFlushBarrier );

	IStdFilePtr	logFile( IID_StdFile );
	logFile->AppendLines( fLogFileID, false, fLogLines );
	fLogLines.Clear();
}

bool CGenericLogger::HadScriptErrors() const
{
	return fScriptHadErrors;
}

void CGenericLogger::AddLogLine(const TXString& msg)
{
	std::time_t result = std::time(nullptr);
	TXString time = std::asctime(std::localtime(&result));
	time.Replace( "\n", "" );

	TXString line = time;
	line += " ";
	if ( farrPrefix.size() > 0 )
		line += farrPrefix.back();
	line += msg;

	NNA_SCOPE {
		std::lock_guard<std::mutex> block_threads_until_finish_this_job( gFlushBarrier );
		fLogLines.Append( line );
	}
}

void CGenericLogger::AddLogLine(const std::exception& e)
{
	this->AddLogLine( TXString("EXCEPTION: ") + e.what() );
}

void CGenericLogger::LogStdOut(const char* msg)
{
	this->AddLogLine( fScriptPrefix + L"StdOut: " + msg );
}

void CGenericLogger::LogStdErr(const char* msg)
{
	this->AddLogLine( fScriptPrefix + L"StdErr: " + msg );
	fScriptHadErrors = true;
}
