//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#ifndef _GS_LOGGING_
#define _GS_LOGGING_

#pragma once

#include "GSTypes.h"
#include "GSString.X.h"

const Uint16 kLogLight = 2;
const Uint16 kLogVerbose = 5;
const Uint16 kLogBeta = 15;

const Uint16 kInfoLog = 0;
const Uint16 kWarnLog = 1;
const Uint16 kErrorLog = 2;

class TLogEnum{
public:
	TLogEnum(Uint16 level, Uint16 type, const char* cat){
		fCat = cat;
		fLevel = level;
		fType = type;
	}

	TXString GetCategory()    const	{return fCat;}
	Uint16 GetLevel()	      const	{return fLevel;}
	Uint16 GetType()		  const	{return fType;}

private:
	TXString fCat;
	Uint16 fLevel;
	Uint16 fType;
};

#ifdef _MINICAD_
#if GS_BETA_PROGRAM_SUPPORT
const Uint16 kDefaultLoggingLevel = kLogBeta;
#else
const Uint16 kDefaultLoggingLevel = kLogLight;
#endif

double LocalLog_GetLoggingTime();
void LocalLog_SetLoggingInitialized(bool isInitialized);
void LocalLog_SetLogBuffering(bool isBuffering);
Uint16 LocalLog_GetLoggingLevel();
void LocalLog_SetLoggingLevel(Uint16 level);
bool LocalLog_StageLogFiles(const TXString& stageLogBaseName, const TXString& ext = ".txt");
void LocalLog_CopyToMainLogFile(const TXString& destLogName);
void LocalLog_SetInitialUploadMode(bool enabled);
#endif //_MINICAD_

//Implemented in GSUtil.cpp
union UJsonPrimitives{
    Sint64 sint64_val;
    Sint32 sint32_val;
    Sint16 sint16_val;
    Sint8 sint8_val;
    Uint64 uint64_val;
    Uint32 uint32_val;
    Uint16 uint16_val;
    Uint8 uint8_val;
    double double_val;
    bool bool_val;
};

class TJsonType : public TDebugObject
{
public:
    TJsonType();
    TJsonType(const TXString& msg);
    TJsonType(const char* msg);
    TJsonType(Sint64 val);
    TJsonType(Sint32 val);
    TJsonType(Sint16 val);
    TJsonType(Sint8 val);
    TJsonType(long val);
    TJsonType(Uint64 val);
    TJsonType(Uint32 val);
    TJsonType(Uint16 val);
    TJsonType(Uint8 val);
    TJsonType(unsigned long val);
    TJsonType(double val);
    TJsonType(bool value);
    TJsonType(std::nullptr_t val);
    ~TJsonType();
    TXString GetJsonFormattedValue();

private:
    void SetType(const char* typeName);
    TXString GetJsonFormattedString();
    TXString fStringData;
    UJsonPrimitives fNonStringData;
    bool fIsStr;
    bool fIsSint64;
    bool fIsSint32;
    bool fIsSint16;
    bool fIsSint8;
    bool fIsUint64;
    bool fIsUint32;
    bool fIsUint16;
    bool fIsUint8;
    bool fIsDouble;
    bool fIsBool;
    bool fIsNull;
};

typedef std::pair<TXString, TJsonType> TJsonKeyPair;
typedef std::map<TXString, TJsonType> TJsonLogDataMap;

TJsonKeyPair GSDEBUG_EXPORT CreateJsonKeyPair(const TXString & key, TJsonType value);

//Legacy Logging Calls
void GSDEBUG_EXPORT LocalLogStrTight(Uint16 level, const char *description);
Sint32  GSDEBUG_EXPORT LocalLogTight(Uint16 level, const char *format, ...);
Sint32  GSDEBUG_EXPORT LocalLogTiming(Uint16 level, double timing, const char *format, ...);
void GSDEBUG_EXPORT LocalLogStr(Uint16 level, const char *description);
Sint32  GSDEBUG_EXPORT LocalLog(Uint16 level, const char *format, ...);

//Logging calls for just a message that doesn't need a format string
void GSDEBUG_EXPORT LocalLogTiming(Uint16 level, Uint16 type, double timing, const TXString& cat, const TXString& message);
void GSDEBUG_EXPORT LocalLog(Uint16 level, Uint16 type, const TXString& cat, const TXString& message);

//Logging calls for just a message with a "cat" and "message"
void GSDEBUG_EXPORT LocalLogTiming(Uint16 level, Uint16 type, double timing, const TXString& cat, const char* format, ...);
void GSDEBUG_EXPORT LocalLog(Uint16 level, Uint16 type, const TXString& cat, const char* format, ...);

//Logging calls for a log with custom data fields
void GSDEBUG_EXPORT LocalLogTiming(Uint16 level, Uint16 type, double timing, const TXString& cat, TJsonLogDataMap customData);
void GSDEBUG_EXPORT LocalLog(Uint16 level, Uint16 type, const TXString& cat, TJsonLogDataMap customData);

//Logging calls for logging calls that use enumerated level, type, and category with a message that doesn't need to be formatted
void GSDEBUG_EXPORT LocalLogTiming(const TLogEnum& logEnum, double timing, const TXString& message);
void GSDEBUG_EXPORT LocalLog(const TLogEnum& logEnum, const TXString& message);

//Logging calls for logging calls that use enumerated level, type, and category with a formatted message
void GSDEBUG_EXPORT LocalLogTiming(const TLogEnum& logEnum, double timing, const char* format, ...);
void GSDEBUG_EXPORT LocalLog(const TLogEnum& logEnum, const char* format, ...);

//Logging calls for logging calls that use enumerated level, type, and category with custom data fields
void GSDEBUG_EXPORT LocalLogTiming(const TLogEnum& logEnum, double timing, TJsonLogDataMap customData);
void GSDEBUG_EXPORT LocalLog(const TLogEnum& logEnum, TJsonLogDataMap customData);

#define REMOTELOGF(parms)			LocalLog parms;
#define REMOTELOGTIGHTF(parms)		LocalLogTight parms;
#define REMOTELOGTIMINGF(parms)		LocalLogTiming parms;
#if GS_BETA_PROGRAM_SUPPORT
    #define REMOTELOGBETAF(parms)	LocalLogTight parms;
#else
    #define REMOTELOGBETAF(parms)	DEBUG_DO_NOTHING
#endif

#define KEYPAIR(key, value)	CreateJsonKeyPair(key, TJsonType(value))

class TFractionalTimer;		// forward decl from GSUtil.h

/** Use this to time a scope's execution with microsecond precision and log the result
 *
 *	{ 
 *     TLogTimer timer(kLogBeta, "Timing something interesting");
 *     ...
 *	   TLogTimer timer(kLogVerbose, "Timing something important", 0.01);	// logs only if > 10 ms.
 *     ...
 *  }
 */
class TLogTimer {
public:
	TLogTimer(Uint16 level, const char* context, double logThreshhold = 0.0);
	~TLogTimer();
private:
	Uint16 fLevel;
	const char* fContext;	// keeping this lightweight passthru. It can migrate to TXString if necessary.
	double fLogThreshhold;
	std::unique_ptr<TFractionalTimer> timer;
};

#endif //_GS_LOGGING_
