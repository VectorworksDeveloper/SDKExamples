//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING FIRST NON-COMMENT LINE.  [DMB, 10/30/95]

#include <stdarg.h>
#include <time.h>
#if _WINDOWS
#include <process.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif

#ifdef _MINICAD_
	#include "rapidjson/rapidjson.h"
	#include "rapidjson/document.h"
	#include "rapidjson/stringbuffer.h"
	#include "rapidjson/writer.h"
	#include "File.X.h"
	#include "ApplicationFolders.h"
    #include "AppProtection.h"
    #include "ApplicationUpdater.h"
    #include "UVersionNumber.h"
	#include "Singleton.X.h"
	#include "TMutex.X.h"
	#include "../../../../../Core/Source/ProjectSharingServer.h"
	// from Builtins.h/.cpp
	double GetSecondsSinceLaunch(void);
    double GetTimeAtLaunch(void);
	long long GetStartupTime(void);
	double gLogTime = 0.0;
#elif _WINDOWS
	//
#endif

#if _WINDOWS
#include "..\..\..\..\..\ShellWin\Resource.h"
#include "..\..\..\..\..\Include\URegKey.h"
#endif

#if _WINDOWS
#include "..\..\..\..\..\ShellWin\Resource.h"
#include "..\..\..\..\..\Include\URegKey.h"
#endif

// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE


Boolean _setmember(Sint32 c, ...)
/*
	Tests if c == any of the following parameters.  The parameter
	list is zero-terminated, so c == 0 must be tested separately.
*/
{
	va_list	ap;
	Sint32		i;

	va_start(ap, c);

	while ((i = va_arg(ap, Sint32)) != 0) {
		if (c == i) { va_end(ap); return true; }
	}
	va_end(ap);
	return false;
}

IntegerSet::IntegerSet()
{
	for (short i = numLongs-1; i >= 0; i--) this->bits[i] = 0;
}

IntegerSet::IntegerSet(short i0, short i1, short i2, short i3,
							short i4, short i5, short i6, short i7,
							short i8, short i9)
{
	for (short i = numLongs-1; i >= 0; i--) this->bits[i] = 0;
	if (i0 >= 0) *this += i0;
	if (i1 >= 0) *this += i1;
	if (i2 >= 0) *this += i2;
	if (i3 >= 0) *this += i3;
	if (i4 >= 0) *this += i4;
	if (i5 >= 0) *this += i5;
	if (i6 >= 0) *this += i6;
	if (i7 >= 0) *this += i7;
	if (i8 >= 0) *this += i8;
	if (i9 >= 0) *this += i9;
}

IntegerSet::IntegerSet(const IntegerSet &s)
{
	for (short i = numLongs-1; i >= 0; i--) this->bits[i] = s.bits[i];
}

void IntegerSet::operator +=(short i)
{
	if (i < 0 || i > maxElement) {
		#if 0
		DebugStr("\p### Set element out of range.");
		#endif
		return;
	}
	this->bits[i / 32] |= 1L << (i % 32);
}

Boolean IntegerSet::contains(short i) const
{
	if (i < 0 || i > maxElement) {
		#if 0
		DebugStr("\p### Set element out of range.");
		#endif
		return false;
	}
	return ((this->bits[i / 32] & (1L<<(i % 32))) != 0);
}

void IntegerSet::operator -=(short i)
{
	if (i < 0 || i > maxElement) {
		#if 0
		DebugStr("\p### Set element out of range.");
		#endif
		return;
	}
	this->bits[i / 32] &= ~(1L << (i % 32));
}

void IntegerSet::operator +=(const IntegerSet &s)
{
	for (short i = numLongs-1; i >= 0; i--)
		this->bits[i] |= s.bits[i];
}

void IntegerSet::operator -=(const IntegerSet &s)
{
	for (short i = numLongs-1; i >= 0; i--)
		this->bits[i] &= ~s.bits[i];
}

#ifdef _MINICAD_

Boolean OSIsMetric()
//
// Description:
//   This function determines if the operating system is set to use metric units.
//
// Returns:
//   Boolean - whether it is set to metric.
//
// Created by Bruce Ferguson on 10/29/02.  Moved to this file on 10/24/05.
//
{
	Boolean isMetric;

#if GS_WIN
	const short kCharBufSize = 2;	// 1-character string plus 1 for null char
	wchar_t buffer[kCharBufSize];

	GetRegistryValue(HKEY_CURRENT_USER, IDS_REGKEY_INTERNATIONAL, IDS_REGVAL_MEASURE, &buffer, kCharBufSize * 2);
	isMetric = (buffer[0] == '0');
#else
	isMetric = IsMetric();
#endif
	return isMetric;
}
#endif

/////////////////////////
// Cross-Platform byte swapping functions
/////////////////////////

// ByteSwapDWORD swaps 4 consecutive bytes (msb to lsb)

#if 0
void GS_API ByteSwapLONG(Sint32 *pl)
{
	char t;
	char* p1 = (char*)pl;
	char* p2 = p1 + 3;

	t = *p1;
	*p1 = *p2;
	*p2 = t;

	++p1; --p2;

	t = *p1;
	*p1 = *p2;
	*p2 = t;
}
#endif

TJsonType::TJsonType(){
	fStringData = "";
	fNonStringData.uint32_val = 0;
	fDataType = EJsonTypeTypes::EString;
}

TJsonType::TJsonType(const TXString& msg){
    fStringData = msg;
	fNonStringData.uint32_val = 0;
	fDataType = EJsonTypeTypes::EString;
}

TJsonType::TJsonType(const char* msg) {
	fStringData = msg;
	fNonStringData.uint32_val = 0;
	fDataType = EJsonTypeTypes::EString;
}

TJsonType::TJsonType(Sint64 val){
    fStringData = "";
	fNonStringData.sint64_val = val;
	fDataType = EJsonTypeTypes::ESint64;
}


TJsonType::TJsonType(Sint32 val){
    fStringData = "";
    fNonStringData.sint32_val = val;
	fDataType = EJsonTypeTypes::ESint32;
}

TJsonType::TJsonType(Uint64 val){
    fStringData = "";
    fNonStringData.uint64_val = val;
	fDataType = EJsonTypeTypes::EUint64;
}

TJsonType::TJsonType(Uint32 val){
    fStringData = "";
    fNonStringData.uint32_val = val;
	fDataType = EJsonTypeTypes::EUint32;
}


TJsonType::TJsonType(double val){
    fStringData = "";
    fNonStringData.double_val = val;
	fDataType = EJsonTypeTypes::EDouble;
}

TJsonType::TJsonType(long val){
    fStringData = "";
    fNonStringData.long_val = val;
    fDataType = EJsonTypeTypes::ELong;
}

TJsonType::TJsonType(unsigned long val){
    fStringData = "";
    fNonStringData.ulong_val = val;
    fDataType = EJsonTypeTypes::EULong;
}

TJsonType::TJsonType(bool val){
    fStringData = "";
    fNonStringData.bool_val = val;
	fDataType = EJsonTypeTypes::EBoolean;
}

TJsonType::TJsonType(std::nullptr_t val){
    fStringData = "";
	fDataType = EJsonTypeTypes::ENull;
}

#ifdef _MINICAD_
const TXString noLogTagPlaceholder = txu("\"sn\":\"\"");
TXString ReplaceSerialNumberToLog(const TXString & logEntryIn){
	TXString logEntry = logEntryIn;
    //If N/A is not even in the log just return
    if(logEntry.Find(noLogTagPlaceholder) == -1){
        return logEntry;
    }

    TXString sn = TAppProtection::MaskSerialNumber(TAppProtection::GetCurrentSerialNumber(), true);
    TXString buffer;
    buffer += txu("\"sn\":\"");
    buffer += sn;
    buffer += txu("\"");
    logEntry.Replace(noLogTagPlaceholder, buffer);
    return logEntry;
}

template<typename T>
T addToAtomic(std::atomic<T> *obj, T arg) {
	T expected = obj->load();
	while (!atomic_compare_exchange_weak(obj, &expected, expected + arg))
		;
	return expected;
}

TXString GetNextLogStageFileName(const TXString& logFolderPath, const TXString& baseName, const TXString& ext) {
	TFolderIdentifier logFolder(logFolderPath);
	TXString nextName = "";
	TXString stageLogName;
	TFileIdentifier logFileStageHandle;
	Sint32 count = 0;
	// Add a 30s failsafe, so there's no way we hit some infinite loop
	double startTime = ::GetSecondsSinceLaunch();
	double endTime = 0;
	bool fileExists = true;
	// Find the last Staging file and save the log file as that + 1;
	do {
		stageLogName = baseName;
		if (count > 0)
			stageLogName << count;
		stageLogName << ext;
		TFileIdentifier trialFile(logFolder, (const char*)stageLogName);
		if (trialFile.ExistsOnDisk()) {
			count += 1;
		}
		else {
			fileExists = false;
			nextName = stageLogName;
		}

		endTime = ::GetSecondsSinceLaunch();
		if (fileExists && endTime - startTime >= kLogStageFetchTimeout) {
			fileExists = false;
			nextName = "";
		}
	} while (fileExists);
	return nextName;
}

typedef std::vector<std::pair<Uint16, TXString> > TLogBufferList;
/*
 TApplicationLogger is a singleton that controls the logging variables as well as the logging file.
 */
class TApplicationLogger : public TSingleton<TApplicationLogger>
{
public:
	~TApplicationLogger();
	void SendToLogFile(Uint16 level, const TXString & message);
	void CloseLog();
	bool StageLogFiles(const TXString& stageLogBaseName, const TXString& ext);
	bool IsLoggingInitialized();
	void SetLoggingInitialized(bool initialized);
	bool IsLoggingBuffering();
	void SetLogBuffering(bool isBuffering);
	Uint16 GetLoggingLevel();
	void SetLoggingLevel(Uint16 level);
    double GetLoggingTime();
	void CopyToMainLogFile(TFileIdentifier& logFileHandle, TFileIdentifier& stageFileHandle);
	void SetInitialUploadMode(bool enabled);
	bool GetInitialUploadMode() { return fInitialUploadMode; };
protected:
	friend class TSingleton<TApplicationLogger>;
	TApplicationLogger();
private:
	FILE* fLogFile;
    TMutex fLogFileGuard;
	bool fIsLoggingInitialized;
	std::atomic<bool> fAreLogsBuffering;
	std::atomic<bool> fIsBufferFlushed;
	std::atomic<bool> fInitialUploadMode;
	TLogBufferList fLogBuffer;
	std::atomic<Uint16> fLoggingLevel;
	std::atomic<double> fLoggingTime;
	void SendToLogBuffer(Uint16 level, const TXString & message);
	void WriteToLogFile(Uint16 level, const TXString & message);
	void FlushLogBuffer();
};

TApplicationLogger::TApplicationLogger(){
	fLogFile = NULL;
	fIsLoggingInitialized = false;
	fAreLogsBuffering.store(true);
	fInitialUploadMode.store(false);
	fLoggingLevel.store(kDefaultLoggingLevel);
	fLoggingTime.store(0.0);
	fIsBufferFlushed.store(false);
}

TApplicationLogger::~TApplicationLogger(){
	CloseLog();
}

//Renames log file to a staging file then touches a new log file
//That is blank. This allows us to upload the log in the background
//By working on a file separate from the log file being written to
bool TApplicationLogger::StageLogFiles(const TXString& stageLogBaseName, const TXString& ext = ".txt") {
	TFolderIdentifier logFolder;
	bool success = false;
	if (GetAppDataFolder(logFolder)) {
		TMutex::TAutoLock autoLock(&fLogFileGuard);
		this->CloseLog();
		TFileIdentifier logFileHandle(logFolder, (const char*)kUserLogFileName);
		TXString stageLogName = GetNextLogStageFileName(logFolder.GetFolderPath(), stageLogBaseName, ext);
		if (stageLogName.GetLength() > 0) {
			TFileIdentifier logFileStageHandle(logFolder, stageLogName);

			TFile logFile;
			//If there isn't a log file create one to prevent crashes


			if (!logFileHandle.ExistsOnDisk()) {
				logFile.OpenNewWrite(logFileHandle);
				logFile.Close();
			}
			if (logFileHandle.RenameOnDisk(logFileStageHandle.GetFileName())) {
				logFileHandle.Set(logFolder, (const char*)kUserLogFileName);
				if (logFile.OpenNewWrite(logFileHandle)) {
					logFile.Close();
					success = true;
				}
			}
		}
	}
	return success;
}

void TApplicationLogger::CopyToMainLogFile(TFileIdentifier& logFileHandle, TFileIdentifier& stageFileHandle) {
	if (stageFileHandle.ExistsOnDisk() && logFileHandle.ExistsOnDisk()) {
		TMutex::TAutoLock autoLock(&fLogFileGuard);
		TFile logFile;
		TFile stageFile;
		logFile.OpenReadWrite(logFileHandle, false, false);
		stageFile.OpenRead(stageFileHandle, false);
		if (logFile.IsOpen() && stageFile.IsOpen()) {
			logFile.SeekToEnd();
			stageFile.SeekToStart();
			bool eof = false;
			char* buffer = NULL;
			buffer = new char[50000];
			Uint64 bytesLeft = 0;
			stageFile.GetBytesLeft(bytesLeft);
			while (bytesLeft > sizeof(buffer) && stageFile.Read(sizeof(buffer), buffer)) {
				logFile.Write(sizeof(buffer), buffer);
				stageFile.AtEndOfFile(eof);
				if (eof)
					break;
				stageFile.GetBytesLeft(bytesLeft);
			}

			if (!eof && bytesLeft > 0 && bytesLeft < sizeof(buffer) && stageFile.Read((Uint32)bytesLeft, buffer)) {
				logFile.Write((Uint32)bytesLeft, buffer);
			}
			logFile.Close();
			stageFile.Close();
			stageFileHandle.DeleteOnDisk();
			delete[] buffer;
			buffer = NULL;
		}
	}
}

void TApplicationLogger::CloseLog(){
    TMutex::TAutoLock autoLock(&fLogFileGuard);
	if(fLogFile){
		fclose(fLogFile);
		fLogFile = NULL;
	}
}

//Buffers Log/writes message to disk regardless of level. Level is checked when writing buffer (Once we load current logging level setting)
void TApplicationLogger::SendToLogFile(Uint16 level, const TXString & message){
	if(fAreLogsBuffering.load()){
		SendToLogBuffer(level, message);
	}
	else{
		if(!fIsBufferFlushed.exchange(true)){
			FlushLogBuffer();
		}
		WriteToLogFile(level, message);
	}
}

bool TApplicationLogger::IsLoggingInitialized(){
	return fIsLoggingInitialized;
}

void TApplicationLogger::SetLoggingInitialized(bool initialized){
	fIsLoggingInitialized = initialized;
}

bool TApplicationLogger::IsLoggingBuffering(){
	return fAreLogsBuffering.load();
}

void TApplicationLogger::SetLogBuffering(bool isBuffering) {
	//If we are setting to false be sure to close the log first
	fAreLogsBuffering.store(isBuffering);
}

void TApplicationLogger::SetInitialUploadMode(bool enabled) {
	fInitialUploadMode.store(enabled);
}

double TApplicationLogger::GetLoggingTime(){
	return fLoggingTime.load();
}

Uint16 TApplicationLogger::GetLoggingLevel(){
	return fLoggingLevel.load();
}

void TApplicationLogger::SetLoggingLevel(Uint16 level){
#if GS_BETA_PROGRAM_SUPPORT
    fLoggingLevel.store(kDefaultLoggingLevel);
#else
	fLoggingLevel.store(level);
#endif
}

void TApplicationLogger::SendToLogBuffer(Uint16 level, const TXString & message){
	fLogBuffer.push_back(std::make_pair(level, message));
}

void TApplicationLogger::FlushLogBuffer(){
	if(fLogBuffer.size() > 0){
		for(Uint32 i=0; i < fLogBuffer.size(); i++)
		{
			if (fLogBuffer[i].first <= fLoggingLevel) {
				//Process each log to add the S/N as it is now avaliable
				TXString newLogLine = ReplaceSerialNumberToLog(fLogBuffer[i].second);
				WriteToLogFile(fLogBuffer[i].first, newLogLine);
			}
		}
		fLogBuffer.clear();
	}
	fIsBufferFlushed.store(true);
}

void TApplicationLogger::WriteToLogFile(Uint16 level, const TXString & message){
	if(level <= fLoggingLevel.load()){
		TMutex::TAutoLock autoLock(&fLogFileGuard);
		double startTime = ::GetSecondsSinceLaunch();
		if(!fLogFile){
			TFolderIdentifier logFolder;
				if ( GetAppDataFolder(logFolder) ) {
					TFileIdentifier logFile(logFolder, kUserLogFileName);
					#if GS_MAC
					fLogFile = fopen((const char*) logFile.GetPosixFilePath(), "a+");
					#else
					fLogFile = _wfopen(logFile.GetFilePath().GetData(), L"a+");
					#endif
				}
		}
        if(fLogFile) {
            fprintf(fLogFile, "%s", (const char*) message);
			if (fInitialUploadMode.load()) {
				CloseLog();
			}
			else {
				fflush(fLogFile);
			}
        }
		double endTime = ::GetSecondsSinceLaunch();
		addToAtomic<double>(&fLoggingTime, (endTime - startTime));
	}
}

double LocalLog_GetLoggingTime(){
	return TApplicationLogger::Instance().GetLoggingTime();
}

void LocalLog_SetLoggingInitialized(bool isInitialized){
	TApplicationLogger::Instance().SetLoggingInitialized(isInitialized);
}

void LocalLog_SetLogBuffering(bool isBuffering){
	TApplicationLogger::Instance().SetLogBuffering(isBuffering);
}

bool LocalLog_GetInitialUploadMode() {
	return TApplicationLogger::Instance().GetInitialUploadMode();
}

Uint16 LocalLog_GetLoggingLevel(){
	return TApplicationLogger::Instance().GetLoggingLevel();
}

void LocalLog_SetLoggingLevel(Uint16 level){
#if GS_BETA_PROGRAM_SUPPORT
	TApplicationLogger::Instance().SetLoggingLevel(kDefaultLoggingLevel);
#else
	TApplicationLogger::Instance().SetLoggingLevel(level);
#endif
}

bool LocalLog_StageLogFiles(const TXString& stageLogBaseName, const TXString& ext) {
	return TApplicationLogger::Instance().StageLogFiles(stageLogBaseName, ext);
}

void LocalLog_CopyToMainLogFile(const TXString& destName) {
	TFolderIdentifier logFolder;
	if (GetAppDataFolder(logFolder)) {
		TFileIdentifier logFileHandle(logFolder, (const char*)kUserLogFileName);
		TFileIdentifier stageFileHandle(logFolder, (const char*)destName);
		TApplicationLogger::Instance().CopyToMainLogFile(logFileHandle, stageFileHandle);
	}
}

void LocalLog_SetInitialUploadMode(bool enabled) {
	TApplicationLogger::Instance().SetInitialUploadMode(enabled);
}

//----------------------------------------------
void CheckForBackgroundLogUpload(){
	//Every ~5 minutes spawn a thread. (It's approximiate because its the next log call after 5 minutes.
    //If TErrorReporting is disabled once it is enabled the next staging will flush all of those logs
    //And upload them ALL in the background once it is enabled.
    if (TErrorReporting::Instance().IsEnabled() && !TErrorReporting::Instance().IsUploadInProgress() && TErrorReporting::Instance().IsLaunchUploadComplete()
        && TErrorReporting::Instance().IsTimeForBackgroundUpload()){
        //Prep logs to be uploaded in background
        //Copy them over to a staging file
        //Start thread to upload in background
		TApplicationLogger::Instance().CloseLog(); //Close the log file as staging will not occur
        TErrorReporting::Instance().BeginThreadedLogUpload();
    }
}

#define JSON_TXESCAPE(str)	"\"" + str + "\""
#define JSON_KEY_PAIR(msg, key, val)	msg << "\"";\
                                        msg << txu(key);\
                                        msg << "\"";\
										msg << ":";\
										msg << val;
#if GS_MAC
const TXString kLocalLogOSName = txu("MAC");
#else
const TXString kLocalLogOSName = txu("WIN");
#endif

TXString SearchForLogType(const TXString& jsonDescription){
	TXString logType = txu("INFO");
	if(jsonDescription.Find("error", 0, true) != -1 && jsonDescription.Find("ferror", 0, true) == -1)
		logType = txu("ERROR");
	if(jsonDescription.Find("fail", 0, true) != -1)
		logType = txu("ERROR");
	if(jsonDescription.Find("exception", 0, true) != -1)
		logType = txu("ERROR");
	if(jsonDescription.Find("failure", 0, true) != -1)
		logType = txu("ERROR");
	if(jsonDescription.Find("warn", 0, true) != -1)
		logType = txu("WARN");
	if(jsonDescription.Find("warning", 0, true) != -1)
		logType = txu("WARN");
	return logType;
}

rapidjson::Value CreateValueFromTJsonType(const TJsonType& object, rapidjson::Document& document) {
	EJsonTypeTypes type = object.GetType();
	rapidjson::Value value;
	if (type == EJsonTypeTypes::EString) {
		value = rapidjson::Value(rapidjson::kStringType);
		const std::string str = object.GetStringData().GetStdString();
		value.SetString(str.c_str(), static_cast<rapidjson::SizeType>(str.size()), document.GetAllocator());
	}
	else if (type == EJsonTypeTypes::ENull) {
		value = rapidjson::Value(rapidjson::kNullType);
	}
	else if (type == EJsonTypeTypes::EBoolean) {
		bool boolData = object.GetNonStringData().bool_val;
		if (boolData) {
			value = rapidjson::Value(rapidjson::kTrueType);
		}
		else {
			value = rapidjson::Value(rapidjson::kFalseType);
		}
	}
	else {
		value = rapidjson::Value(rapidjson::kNumberType);
		if (type == EJsonTypeTypes::ESint64) {
			value.SetInt64(object.GetNonStringData().sint64_val);
		}
		else if (type == EJsonTypeTypes::EUint64) {
			value.SetUint64(object.GetNonStringData().uint64_val);
		}
		else if (type == EJsonTypeTypes::EDouble) {
			value.SetDouble(object.GetNonStringData().double_val);
		}
		else if (type == EJsonTypeTypes::ESint32) {
			value.SetInt(object.GetNonStringData().sint32_val);
		}
		else {
			value.SetUint(object.GetNonStringData().uint32_val);
		}
	}
	return value;
}

void AddLogFieldsToDocument(const TJsonLogDataMap& logFields, rapidjson::Document& document){
	TJsonLogDataMap::const_iterator mapIterator;
	TXString logMessageFields = "";
	for(mapIterator = logFields.begin(); mapIterator != logFields.end(); mapIterator++){
		const TXString& key = mapIterator->first;
		const TJsonType& second = mapIterator->second;
		rapidjson::Value toInsert = CreateValueFromTJsonType(second, document);
		rapidjson::Value keyVal(key.GetStdString().c_str(), document.GetAllocator());
		document.AddMember(keyVal.Move(), toInsert, document.GetAllocator());
	}
}

rapidjson::Document GetMetaDataDocument(Uint16 level) {
	rapidjson::Document document;
	document.SetObject();
	static const std::string osString = GetUniformOSSystemVersion(false).GetStdString();
	static const char* os = osString.c_str();
	static const rapidjson::SizeType osLen = static_cast<rapidjson::SizeType>(osString.length());
	static const std::string sessionString = TXString::ToStringHex(static_cast<long long>(::GetStartupTime()), false).GetStdString();
	static const char* session = sessionString.c_str();
	static const rapidjson::SizeType sessionLen = static_cast<rapidjson::SizeType>(sessionString.length());
	static const std::string vwVersionString = GetVersionNumberString(eShortWithBuild).GetStdString();
	static const char* vwVersion = vwVersionString.c_str();
	static const rapidjson::SizeType vwVersionLen = static_cast<rapidjson::SizeType>(vwVersionString.length());

	std::string serialNumber;
	if (TAppProtection::IsInViewerMode()) {
		serialNumber = "viewer";
	}
	else if (TAppProtection::IsInDemoMode()) {
		serialNumber = "demo";
	}
	else {
		serialNumber = TAppProtection::MaskSerialNumber(TAppProtection::GetCurrentSerialNumber()).GetStdString();;
	}

	time_t theTime;
	char dateBuffer[255];
	time(&theTime);
	tm* tp = gmtime(&theTime);
	strftime(dateBuffer, 255, "%m/%d/%Y %H:%M:%S", tp);
	TXString dateStr;
	dateStr << dateBuffer;
	dateStr << txu(" ");
	dateStr << ::GetSecondsSinceLaunch();
	dateStr << txu(" +0000");

	// Important this is first for processing
	rapidjson::Value timestampJsonString(rapidjson::kStringType);
	timestampJsonString.SetString((const char*)dateStr, static_cast<rapidjson::SizeType>(dateStr.GetLength()), document.GetAllocator());
	document.AddMember("ts", timestampJsonString, document.GetAllocator());

	rapidjson::Value logLevelJsonNumber(rapidjson::kNumberType);
	logLevelJsonNumber.SetUint(level);
	document.AddMember("log_lvl", logLevelJsonNumber, document.GetAllocator());

	rapidjson::Value serialNumberJson(rapidjson::kStringType);
	serialNumberJson.SetString(serialNumber.c_str(), static_cast<rapidjson::SizeType>(serialNumber.length()), document.GetAllocator());
	document.AddMember("sn", serialNumberJson, document.GetAllocator());

	rapidjson::Value sessionJsonString(rapidjson::kStringType);
	sessionJsonString.SetString(session, sessionLen, document.GetAllocator());
	document.AddMember("session", sessionJsonString, document.GetAllocator());

	rapidjson::Value versionJsonString(rapidjson::kStringType);
	versionJsonString.SetString(vwVersion, vwVersionLen, document.GetAllocator());
	document.AddMember("vw_ver", versionJsonString, document.GetAllocator());

	rapidjson::Value platformJsonString(rapidjson::kStringType);
	platformJsonString.SetString(kLocalLogOSName, 3, document.GetAllocator());
	document.AddMember("platform", platformJsonString, document.GetAllocator());

	rapidjson::Value osVerJsonString(rapidjson::kStringType);
	osVerJsonString.SetString(os, osLen, document.GetAllocator());
	document.AddMember("os_ver", osVerJsonString, document.GetAllocator());
	return document;
}

TXString DocumentToString(rapidjson::Document& document) {
	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
	document.Accept(writer);
	return TXString(sb.GetString()) + "\n";

}

rapidjson::Document LegacyCreateLogDocument(const TXString& description) {
	rapidjson::Document document;
	document.SetObject();
	if (description.GetLength() > 1) {
		//Special Case for OpenGL driver
		//Its message is json so just return it
		bool isBaseJson = false;
		if (description[0] == '{' && description.GetLast() == '}') {
			if (!document.Parse(description.GetStdString().c_str()).HasParseError()) {
				isBaseJson = true;
			}
		}
		rapidjson::Value::ConstMemberIterator itr = document.FindMember("type");
		if (itr == document.MemberEnd()) {
			TXString type = SearchForLogType(description);
			rapidjson::Value typeJsonString(rapidjson::kStringType);
			typeJsonString.SetString((const char*)type, static_cast<rapidjson::SizeType>(type.GetLength()), document.GetAllocator());
			document.AddMember("type", typeJsonString, document.GetAllocator());
		}
		if (!isBaseJson) {
			ptrdiff_t categoryIndex = description.Find(": ");
			TXString jsonLog;
			TXString category;
			if (categoryIndex != -1) {
				category = description.Left(categoryIndex);
			}
			else {
				categoryIndex = description.Find(' ');
				if (categoryIndex != -1) {
					category = description.Left(categoryIndex);
				}
				else {
					category = txu("no_cat");
				}
			}
			rapidjson::Value categoryJsonString(rapidjson::kStringType);
			const std::string strCat = category.GetStdString();
			categoryJsonString.SetString(strCat.c_str(), static_cast<rapidjson::SizeType>(strCat.size()), document.GetAllocator());
			document.AddMember("cat", categoryJsonString, document.GetAllocator());

			rapidjson::Value messageJsonString(rapidjson::kStringType);
			const std::string strDesc = description.GetStdString();
			messageJsonString.SetString(strDesc.c_str(), static_cast<rapidjson::SizeType>(strDesc.size()), document.GetAllocator());
			document.AddMember("message", messageJsonString, document.GetAllocator());
		}
	}
	return document;
}

void LegacyWriteLocalLog(Uint16 level, bool doDebugWindow, const char *description)
{
	// we do not want to respond to log requests at early init time
	if (TApplicationLogger::Instance().IsLoggingInitialized()) {

		// levelzero is defined to output nothing to the log

		// 1-3 should happen on a session frequency
		// 4-6 can happen on a per-user-event frequency
		// 7-10 can happen up to once every few seconds on average
		// > 10 are special purpose and should not be used without
		// prior arrangement - Paul

		ASSERTN(kPaul, level > 0);

		//Check if we're going to write this log before parsing it into a JSON string.
		if (TApplicationLogger::Instance().IsLoggingBuffering() || level <= TApplicationLogger::Instance().GetLoggingLevel()) {
			rapidjson::Document document = GetMetaDataDocument(level);
			rapidjson::Document content = LegacyCreateLogDocument(TXString(description));
			for (rapidjson::Value::MemberIterator itr = content.MemberBegin(); itr != content.MemberEnd(); ++itr) {
				document.AddMember(itr->name, itr->value, document.GetAllocator());
			}
			TXString logMessage = DocumentToString(document);
			TApplicationLogger::Instance().SendToLogFile(level, logMessage);

			if (doDebugWindow) {
				#if !DaveD	// Too much noise in the debug window from resource lists.  -DLD 1/12/2012
					// send to the debug window - in future need to pass time and process also
					DMSG((kEveryone, "%s\n", description));
				#endif	// !DaveD
			}

            CheckForBackgroundLogUpload();
		}
	}
}

void WriteLocalLog(Uint16 level, const TJsonLogDataMap& logFields){
	if (TApplicationLogger::Instance().IsLoggingInitialized()) {
        ASSERTN(kOKadry, level > 0);
		if (TApplicationLogger::Instance().IsLoggingBuffering() || level <= TApplicationLogger::Instance().GetLoggingLevel()) {
			rapidjson::Document document = GetMetaDataDocument(level);
			AddLogFieldsToDocument(logFields, document);
			TXString logMessage = DocumentToString(document);
			TApplicationLogger::Instance().SendToLogFile(level, logMessage);

            CheckForBackgroundLogUpload();

			// Log to project sharing server
			PSServer::LogToServer(logMessage);
        }
    }
}
#endif


static void LegacyRouteLocalLog(Uint16 level, bool doDebugWindow, const char *description)
{

#ifdef _MINICAD_
		// the VCOM interface is not yet registered
		// use default in-place implementation

		LegacyWriteLocalLog(level, doDebugWindow, description);

#else
	using namespace VectorWorks::Debug;
	::GS_InitializeVCOM( gCBP );
	VCOMPtr<IDebugOutputLog> pOutInst( IID_DebugOutputLog );

	if ( pOutInst ) {
		pOutInst->LocalLogStr(level, doDebugWindow, description);
	}
	else {
		// remove log being called before VCOM initialization
		ASSERTN( kVStanev, false );
	}
#endif

}

void LegacyLocalLogStr(Uint16 level, const char *description)
{
	LegacyRouteLocalLog(level, true, description);
}

void LegacyLocalLogStrTight(Uint16 level, const char *description)
{
	LegacyRouteLocalLog(level, false, description);
}

Sint32 LegacyFormatAndWriteLog(Uint16 level, bool doDebugWindow, const char *format, va_list ap)
//
//	Log to local file.  Accept variable arguments.
//	This is similar to the function _Log( ) above.
//	JAK 1/31/05
//
{
	const size_t kBuf_size = 1024;

	static Sint32 r = 0;
	char buf[kBuf_size];
#if GS_MAC
	r = vsnprintf(buf, sizeof(buf), format, ap);
    // result is negative on error, or >= size on truncation.
    if (r >= sizeof(buf))
    {
        // for truncation, adjust return value.
        r = sizeof(buf) - 1;
    }
#else
    errno = 0;
    r = _vsnprintf_s(buf, sizeof(buf), _TRUNCATE, format, ap);
    // result is -1 on error or truncation
    if ((r == -1 && errno == 0) || r >= sizeof(buf))
    {
        // for truncation, adjust return value. for exact length, need to fix null termination.
        r = sizeof(buf) - 1;
        buf[r] = 0;
    }
#endif
    if (r > 0)  // nothing to do with an empty string/erronous result
       LegacyRouteLocalLog(level, doDebugWindow, buf);
	return r;
}

Sint32 LegacyLocalLog(Uint16 level, const char *format, ...)
{
	va_list	ap;
	va_start(ap, format);
	Sint32 result = LegacyFormatAndWriteLog(level, true, format, ap);
	va_end(ap);

	return result;
}

Sint32 LegacyLocalLogTight(Uint16 level, const char *format, ...)
{
	va_list	ap;
	va_start(ap, format);
	Sint32 result = LegacyFormatAndWriteLog(level, false, format, ap);
	va_end(ap);

	return result;
}

Sint32 LegacyLocalLogTiming(Uint16 level, double timing, const char *format, ...)
{
	const size_t kBuf_size = 1124;

	va_list	ap;
	va_start(ap, format);

	char modifiedFormat[kBuf_size];
	sprintf(modifiedFormat, "TIMER: %f sec | %s", timing, format);

	Sint32 result = LegacyFormatAndWriteLog(level, true, modifiedFormat, ap);
	va_end(ap);

	return result;
}

//Route depending on if this is called from the main application or an SDK plugin
void RouteLocalLog(Uint16 level, const TJsonLogDataMap& logFields) {
#ifdef _MINICAD_
	WriteLocalLog(level, logFields);
#else
	using namespace VectorWorks::Debug;
	::GS_InitializeVCOM(gCBP);
	VCOMPtr<IDebugOutputLog> pOutInst(IID_DebugOutputLog);

	if (pOutInst) {
		pOutInst->SendToLogWriter(level, logFields);
	}
#endif
}

//=======================================================================================
// VFormat(...) is used in Format(...). Note the buffer size is 1024.
static void _VFormat(TXString& outString, const char* format, va_list argPtr)
{
	static const Sint32 kBufferSize = 1024;
	char localBuffer[kBufferSize];

	Sint32 len = vsnprintf(localBuffer, kBufferSize, (const char *)format, argPtr);

	ASSERTN(kPChang, len >= 0 && len < kBufferSize);

	if (len >= 0)
		outString = localBuffer;
	else
		outString.Clear();
}

// Start new Logging Calls
const TXString kInfoLogStr = "INFO";
const TXString kErrorLogStr = "ERROR";
const TXString kWarnLogStr = "WARN";
TXString GetLogType(Uint16 logType) {
	if (logType == kErrorLog) {
		return kErrorLogStr;
	}
	if (logType == kWarnLog) {
		return kWarnLogStr;
	}
	return kInfoLogStr;
}

void LocalLog(Uint16 level, Uint16 type, const TXString& cat, const TXString& message){
	TJsonLogDataMap logFields;
    logFields.insert(KEYPAIR("cat", cat));
	TXString typeStr = GetLogType(type);
    logFields.insert(KEYPAIR("type", typeStr));
    logFields.insert(KEYPAIR("message", message));
	DMSG((kEveryone, "%s\n", (const char*)message));
    RouteLocalLog(level, logFields);
}

void LocalLog(Uint16 level, Uint16 type, const TXString& cat, const char* format, ...){
    va_list ap;
    va_start (ap, format);
    TXString formattedMessage;
    ::_VFormat(formattedMessage, format, ap);
    va_end(ap);
	LocalLog(level, type, cat, formattedMessage);
}


void LocalLog(Uint16 level, Uint16 type, const TXString& cat,
                TJsonLogDataMap logFields){
    logFields.insert(KEYPAIR("cat", cat));
    logFields.insert(KEYPAIR("type", GetLogType(type)));
    RouteLocalLog(level, logFields);
}

void LocalLog(const TLogEnum& logEnum, const TXString& message){
	LocalLog(logEnum.GetLevel(), logEnum.GetType(), logEnum.GetCategory(), message);
}

void LocalLog(const TLogEnum& logEnum, const char* format, ...){
	va_list ap;
    va_start (ap, format);
    TXString formattedMessage;
    ::_VFormat(formattedMessage, format, ap);
    va_end(ap);
	LocalLog(logEnum.GetLevel(), logEnum.GetType(), logEnum.GetCategory(), formattedMessage);

}

void LocalLog(const TLogEnum& logEnum, const TJsonLogDataMap customData){
	LocalLog(logEnum.GetLevel(), logEnum.GetType(), logEnum.GetCategory(), customData);
}

void LocalLogTiming(Uint16 level, Uint16 type, double timing, const TXString& cat,
                      const TXString& message){
    TJsonLogDataMap logFields;
    logFields.insert(KEYPAIR("cat", cat));
    logFields.insert(KEYPAIR("type", GetLogType(type)));
    logFields.insert(KEYPAIR("timing", timing));
    logFields.insert(KEYPAIR("message", message));
	DMSG((kEveryone, "TIMER: %f sec | %s\n", timing, (const char*)message));
    RouteLocalLog(level, logFields);
}

void LocalLogTiming(Uint16 level, Uint16 type, double timing, const TXString& cat,
                      const char* format, ...){
    va_list ap;
    va_start (ap, format);
    TXString formattedMessage;
    ::_VFormat(formattedMessage, format, ap);
    va_end(ap);
	LocalLogTiming(level, type, timing, cat, formattedMessage);
}

void LocalLogTiming(Uint16 level, Uint16 type, double timing, const TXString& cat,
                     TJsonLogDataMap logFields){
    logFields.insert(KEYPAIR("cat", cat));
    logFields.insert(KEYPAIR("type", GetLogType(type)));
    logFields.insert(KEYPAIR("timing", timing));
    RouteLocalLog(level, logFields);
}

void LocalLogTiming(const TLogEnum& logEnum, double timing, const TXString& message){
	LocalLogTiming(logEnum.GetLevel(), logEnum.GetType(), timing, logEnum.GetCategory(), message);
}

void LocalLogTiming(const TLogEnum& logEnum, double timing, const char* format, ...){
	va_list ap;
    va_start (ap, format);
    TXString formattedMessage;
    ::_VFormat(formattedMessage, format, ap);
    va_end(ap);
	LocalLogTiming(logEnum.GetLevel(), logEnum.GetType(), timing, logEnum.GetCategory(), formattedMessage);
}

void LocalLogTiming(const TLogEnum& logEnum, double timing, TJsonLogDataMap customData){
	LocalLogTiming(logEnum.GetLevel(), logEnum.GetType(), timing, logEnum.GetCategory(), customData);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Timers

TFractionalTimer::TFractionalTimer()
: fStartTime { 0,0 }
{
	FetchTime(fStartTime);
}

void TFractionalTimer::FetchTime(TimeBuffer_& buffer)
{
#if _WINDOWS
	ASSERTN(kRBerge, sizeof(TimeBuffer_) >= sizeof(LARGE_INTEGER));
	PLARGE_INTEGER ptr = reinterpret_cast<PLARGE_INTEGER>(buffer);
	QueryPerformanceCounter(ptr);
#else
	ASSERTN(kRBerge, sizeof(TimeBuffer_) >= sizeof(timeval));
	timeval* ptr = reinterpret_cast<timeval*>(&buffer);
	gettimeofday(ptr, nullptr);
#endif
}

double TFractionalTimer::DiffTime(const TimeBuffer_& start, const TimeBuffer_& end)
{

#if _WINDOWS
	const LARGE_INTEGER* s = reinterpret_cast<const LARGE_INTEGER*>(&start);
	const LARGE_INTEGER* e = reinterpret_cast<const LARGE_INTEGER*>(&end);
	Sint64 elapsed = e->QuadPart - s->QuadPart;

	LARGE_INTEGER perSecond;
	QueryPerformanceFrequency(&perSecond);
	double interval = elapsed / (double)perSecond.QuadPart;
#else
	const timeval* s = reinterpret_cast<const timeval*>(&start);
	const timeval* e = reinterpret_cast<const timeval*>(&end);

	timeval elapsed;
	timersub(e, s, &elapsed);
	double interval = elapsed.tv_sec + ((double)(elapsed.tv_usec)/1000000.0);
#endif

	return interval;
}

double TFractionalTimer::GetElapsed(bool reset)
{
	TimeBuffer_ now;
	FetchTime(now);

	double interval = DiffTime(fStartTime, now);

	if (reset) {
		// restart the timer
		*fStartTime = *now;
	}

	return interval;
}

TLogTimer::TLogTimer(Uint16 level, const char* context, double logThreshhold)
	: fLevel(level), fCategory(context), fContext(context), fLogThreshhold(logThreshhold),
	timer(std::make_unique<TFractionalTimer>())
{
}

TLogTimer::~TLogTimer()
{
	double interval = timer->GetElapsed();
	if (interval > fLogThreshhold) {
		REMOTELOGTIMINGF((fLevel, kInfoLog, interval, fCategory, "%s", fContext));
	}
}


//////////////////////////////////////////////////////////////////////////////
// Beginning of SHA256HASH

//----------------------------------------------------------------------------
TSha256Hash::TSha256Hash()
{
	for (size_t i = 0; i < kSha256HashData_NumElements; i++)
		fHashData[i] = 0;
}

//----------------------------------------------------------------------------
TSha256Hash::TSha256Hash(const TSha256HashData& inHashData)
{
	for (size_t i = 0; i < kSha256HashData_NumElements; i++)
		fHashData[i] = inHashData[i];
}

//----------------------------------------------------------------------------
TSha256Hash::TSha256Hash(const TSha256Hash& in)
{
	for (size_t i = 0; i < kSha256HashData_NumElements; i++)
		fHashData[i] = in.fHashData[i];
}

//----------------------------------------------------------------------------
TSha256Hash::TSha256Hash(const void* inpRawData, size_t inDataSize)
{
	TSha256HashGenerator().Generate(inpRawData, inDataSize, fHashData);
}

//----------------------------------------------------------------------------
TXString TSha256Hash::GetAsTXString() const
{
	TXString outStr = "";

	char s[3];

	for (size_t i = 0; i < 32; i++) {
		sprintf(s, "%02x", fHashData[i]);
		outStr += s;
	}

	return outStr;
}

//----------------------------------------------------------------------------
bool TSha256Hash::operator<(const TSha256Hash& in) const
{
	for (size_t i = 0; i < 32; i++) {
		if (fHashData[i] < in.fHashData[i])
			return true;
		if (fHashData[i] > in.fHashData[i])
			return false;
	}
	return false;
}

//----------------------------------------------------------------------------
bool TSha256Hash::operator==(const TSha256Hash& in) const
{
	for (size_t i = 0; i < 32; i++) {
		if (fHashData[i] != in.fHashData[i])
			return false;
	}
	return true;
}

bool TSha256Hash::operator!=(const TSha256Hash& in) const
{
	return ! this->operator==( in );
}

//////////////////////////////////////////////////////////////////////////////
// TSha256HashGenerator implementation
// repackaged version of original implementation by okadry from ApplicationUpdater.cpp
//////////////////////////////////////////////////////////////////////////////
#define DBL_INT_ADD(a,b,c) if (a > 0xffffffff - (c)) ++b; a += c;
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

//----------------------------------------------------------------------------
TSha256HashGenerator::TSha256HashGenerator()
{
	this->Reset();
}

//----------------------------------------------------------------------------
void TSha256HashGenerator::Reset()
{
	this->fDatalen = 0;
	this->fBitlen[0] = 0;
	this->fBitlen[1] = 0;
	this->fState[0] = 0x6a09e667;
	this->fState[1] = 0xbb67ae85;
	this->fState[2] = 0x3c6ef372;
	this->fState[3] = 0xa54ff53a;
	this->fState[4] = 0x510e527f;
	this->fState[5] = 0x9b05688c;
	this->fState[6] = 0x1f83d9ab;
	this->fState[7] = 0x5be0cd19;
}

//----------------------------------------------------------------------------
void TSha256HashGenerator::Update(const void* inpData, size_t inNumBytes)
{
	const Uint8* p = (const Uint8*)inpData;

	for (Uint32 i = 0; i < inNumBytes; ++i) {
		this->fData[this->fDatalen] = p[i];
		this->fDatalen++;

		if (this->fDatalen == 64) {
			this->Transform();
			DBL_INT_ADD(this->fBitlen[0], this->fBitlen[1], 512);
			this->fDatalen = 0;
		}
	}
}

//----------------------------------------------------------------------------
void TSha256HashGenerator::Final(TSha256HashData& outHash)
{
	Uint32 i = this->fDatalen;

	if (this->fDatalen < 56) {
		this->fData[i++] = 0x80;

		while (i < 56)
			this->fData[i++] = 0x00;
	}
	else {
		this->fData[i++] = 0x80;

		while (i < 64)
			this->fData[i++] = 0x00;

		this->Transform();

		memset(this->fData, 0, 56);
	}

	DBL_INT_ADD(this->fBitlen[0], this->fBitlen[1], this->fDatalen * 8);

	this->fData[63] = this->fBitlen[0];
	this->fData[62] = this->fBitlen[0] >> 8;
	this->fData[61] = this->fBitlen[0] >> 16;
	this->fData[60] = this->fBitlen[0] >> 24;
	this->fData[59] = this->fBitlen[1];
	this->fData[58] = this->fBitlen[1] >> 8;
	this->fData[57] = this->fBitlen[1] >> 16;
	this->fData[56] = this->fBitlen[1] >> 24;

	this->Transform();

	for (i = 0; i < 4; ++i) {
		outHash[i]		= (this->fState[0] >> (24 - i * 8)) & 0x000000ff;
		outHash[i + 4]	= (this->fState[1] >> (24 - i * 8)) & 0x000000ff;
		outHash[i + 8]	= (this->fState[2] >> (24 - i * 8)) & 0x000000ff;
		outHash[i + 12]	= (this->fState[3] >> (24 - i * 8)) & 0x000000ff;
		outHash[i + 16]	= (this->fState[4] >> (24 - i * 8)) & 0x000000ff;
		outHash[i + 20]	= (this->fState[5] >> (24 - i * 8)) & 0x000000ff;
		outHash[i + 24]	= (this->fState[6] >> (24 - i * 8)) & 0x000000ff;
		outHash[i + 28]	= (this->fState[7] >> (24 - i * 8)) & 0x000000ff;
	}
}

//----------------------------------------------------------------------------
void TSha256HashGenerator::Transform()
{
	Uint32 a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (this->fData[j] << 24) | (this->fData[j + 1] << 16) | (this->fData[j + 2] << 8) | (this->fData[j + 3]);

	for (; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	a = this->fState[0];
	b = this->fState[1];
	c = this->fState[2];
	d = this->fState[3];
	e = this->fState[4];
	f = this->fState[5];
	g = this->fState[6];
	h = this->fState[7];

	const Uint32 kSha256Constants[64] = {
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
		0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
		0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
		0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
		0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
		0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
	};

	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e, f, g) + kSha256Constants[i] + m[i];
		t2 = EP0(a) + MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	this->fState[0] += a;
	this->fState[1] += b;
	this->fState[2] += c;
	this->fState[3] += d;
	this->fState[4] += e;
	this->fState[5] += f;
	this->fState[6] += g;
	this->fState[7] += h;
}


// End of SHA256HASH
//////////////////////////////////////////////////////////////////////////////



#if _WINDOWS
	// XXX_JDW_ALTURA
	typedef unsigned short      WORD;

	extern "C" __declspec(dllimport) DWORD WINAPI GetSysColor(Sint32 nIndex);

	// Undefine any old color extraction defines
	#ifdef GetRValue
	#undef GetRValue
	#endif
	#ifdef GetGValue
	#undef GetGValue
	#endif
	#ifdef GetBValue
	#undef GetBValue
	#endif

	#define GetRValue(rgb)	((BYTE)(rgb))
	#define GetGValue(rgb)  ((BYTE)(((WORD)(rgb)) >> 8))
	#define GetBValue(rgb)  ((BYTE)((rgb)>>16))
#endif

#if !_WINDOWS
static const unsigned short
	kGrayF = (unsigned short) 0xFFFF,	// 65535 (white)
	kGrayE = (unsigned short) 0xEEEE,	// 61166
	kGrayD = (unsigned short) 0xDDDD,	// 56797
	kGrayC = (unsigned short) 0xCCCC,	// 52428
	kGrayB = (unsigned short) 0xBBBB,	// 48059
	kGrayA = (unsigned short) 0xAAAA,	// 43690
	kGray9 = (unsigned short) 0x9999,	// 39321
	kGray8 = (unsigned short) 0x8888,	// 34952
	kGray7 = (unsigned short) 0x7777,	// 30583
	kGray6 = (unsigned short) 0x6666,	// 26214
	kGray5 = (unsigned short) 0x5555,	// 21845
	kGray4 = (unsigned short) 0x4444,	// 17476
	kGray3 = (unsigned short) 0x3333,	// 13107
	kGray2 = (unsigned short) 0x2222,	//  8738
	kGray1 = (unsigned short) 0x1111,	//  4369
	kGray0 = (unsigned short) 0x0000;	//     0 (black)
#endif

// These are color indexes added by us and not defined by Windows.  We can
// add these because they eventualy map to predefined values under Windows.
#define COLOR_SELECTED				10001
#define COLOR_SELECTEDLITE			10002

enum {
	blackColor                  = 33,                           /*colors expressed in these mappings*/
	whiteColor                  = 30,
	redColor                    = 205,
	greenColor                  = 341,
	blueColor                   = 409,
	cyanColor                   = 273,
	magentaColor                = 137,
	yellowColor                 = 69
};

void GetSysColor(Sint32 index, TRGBColor *rgb, Sint32* qd)
{
	// Check pointers.
	ASSERTN(kDave, rgb || qd);	// Must give us at least one pointer to work with.
	if (rgb) ASSERTPOINTER(kDave, rgb, sizeof(TRGBColor));
	if (qd) ASSERTPOINTER(kDave, qd, sizeof(Sint32));

#if _WINDOWS

	if (qd) {
		// Windows never uses this value, so we'll just assign black to
		// cover our as.. I mean.. cover all the bases.  [DMB, 5/18/95]
		*qd = blackColor;
	}
	if (rgb) {

		if (index == COLOR_SELECTED || index == COLOR_SELECTEDLITE) {

			// Make selected color darker/lighter than normal button face if using
			// shades of gray, leave it untouched if not.
			unsigned short darker = 16;
			if (index == COLOR_SELECTEDLITE)
				darker = -darker;

			// Get individual gray levels.
			DWORD wincolor = GetSysColor(COLOR_BTNFACE);
			rgb->red = GetRValue(wincolor);
			rgb->green = GetGValue(wincolor);
			rgb->blue = GetBValue(wincolor);

			Boolean isGray = (rgb->red == rgb->green && rgb->green == rgb->blue);
			Boolean isInRange = (index == COLOR_SELECTED ? (rgb->red > darker) : (rgb->red < 255+darker));

			if (isGray && isInRange) {
				// Change the gray level.
				rgb->red = (rgb->red - darker) * 256;
				rgb->green = rgb->blue = rgb->red;
			}
			else {
				// Leave color untouched.
	 			rgb->red *= 256;
				rgb->green *= 256;
				rgb->blue *= 256;
			}
		}
		else {
			DWORD wincolor = GetSysColor(index);
			rgb->red = GetRValue(wincolor) * 256;
			rgb->green = GetGValue(wincolor) * 256;
			rgb->blue = GetBValue(wincolor) * 256;
		}
	}

#else
// This is Mac code.
	
	TRGBColor TRGBColor;
	Sint32 qdColor;

	switch (index) {
		case COLOR_BTNFACE: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGrayD;
			qdColor = whiteColor;
			break;
		}
		case COLOR_BTNFACEDISABLED:
		case COLOR_WNDBACKGROUND: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGrayE;
			qdColor = whiteColor;
			break;
		}
		case COLOR_SELECTED:
		case COLOR_HIGHLIGHT: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGrayA;
			qdColor = blackColor;
			break;
		}
		case COLOR_WINDOW:
		case COLOR_SELECTEDLITE:
		case COLOR_BTNHIGHLIGHT: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGrayF;
			qdColor = whiteColor;
			break;
		}
		case COLOR_BTNSHADOW: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGray7;
			qdColor = whiteColor;
			break;
		}
		case COLOR_BTNTEXT: {
			TRGBColor.red = TRGBColor.green = TRGBColor.blue = kGray0;
			qdColor = blackColor;
			break;
		}
		default:
			DSTOP((kDave, "Invalid color index used in \"GetSysColor()\": %d\n", index));
			return;
	}

	if (rgb) *rgb = TRGBColor;
	if (qd) *qd = qdColor;

#endif	// _WINDOWS
}

Boolean GS_API WorldInchesToCoords(CallBackPtr UNUSED(cbp), double_param inches, WorldCoord& coords)
{ 	
	coords = inches * kWorldCoordsPerInch;
	return true; 
} 

double_gs CoordsToWorldInches(CallBackPtr UNUSED(cbp), WorldCoord coords)
{ 	
	return coords / kWorldCoordsPerInch;
} 
