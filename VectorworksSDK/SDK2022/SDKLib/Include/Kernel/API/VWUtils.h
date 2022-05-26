//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


///////////////////////////////////////////////////////////////////////////////

Boolean OSIsMetric();

///////////////////////////////////////////////////////////////////////////////

extern "C" void SysBreak(void);

void GetSysColor(int index, TRGBColor *rgb, Sint32 *qd=nil);

Boolean GS_API WorldInchesToCoords(CallBackPtr cbp, double_param inches, WorldCoord& coords);

double_gs GS_API CoordsToWorldInches(CallBackPtr cbp, WorldCoord coords);

///////////////////////////////////////////////////////////////////////////////

#if GS_MAC
	#define COLOR_WINDOW				5
	#define COLOR_HIGHLIGHT         	13
	#define COLOR_BTNFACE           	15
	#define COLOR_BTNSHADOW         	16
	#define COLOR_GRAYTEXT          	17
	#define COLOR_BTNTEXT           	18
	#define COLOR_BTNHIGHLIGHT      	20


	#if WINVER
		#define COLOR_BTNFACEDISABLED	COLOR_BTNFACE
		#define COLOR_WNDBACKGROUND		COLOR_BTNFACE
	#else
		#define COLOR_BTNFACEDISABLED	10003
		#define COLOR_WNDBACKGROUND		10004
	#endif
#endif

///////////////////////////////////////////////////////////////////////////////

/** Simple interface for elapsed seconds as a double, with probably at least microsecond resolution
 *
 * {
 *    TFractionalTimer timer;
 *    ...
 *    double elapsed = timer.GetElapsed();
 * }
 */
class TFractionalTimer
{
public:
	TFractionalTimer();
	
	double GetElapsed(bool reset=false);	// calculate start to now in seconds
											// optionally reset start = now
	
private:
	typedef Uint64 TimeBuffer_[2];
	TimeBuffer_ fStartTime;
	
	void FetchTime(TimeBuffer_& buffer);
	double DiffTime(const TimeBuffer_& start, const TimeBuffer_& end);
};





//////////////////////////////////////////////////////////////////////////////
#define kSha256HashData_NumElements 32
typedef Uint8 TSha256HashData[kSha256HashData_NumElements];

class TXString;

//////////////////////////////////////////////////////////////////////////////
class TSha256Hash
//////////////////////////////////////////////////////////////////////////////
{
public:
	TSha256Hash();
	TSha256Hash(const TSha256HashData& inHashData);
	TSha256Hash(const TSha256Hash& in); // copy
	TSha256Hash(const void* inpRawData, size_t inDataSize); // generate

	TXString GetAsTXString() const;

	bool operator<(const TSha256Hash& in) const;
	bool operator==(const TSha256Hash& in) const;
	bool operator!=(const TSha256Hash& in) const;

	TSha256HashData fHashData;
};

//////////////////////////////////////////////////////////////////////////////
class TSha256HashGenerator
//////////////////////////////////////////////////////////////////////////////
{
public:
	TSha256HashGenerator();

	void Generate(const void* inpData, size_t inDataSize, TSha256HashData& out)
	// simple interface, if you don't want to fuss with Reset, Update, Final.
	{
		this->Reset();
		this->Update(inpData, inDataSize);
		this->Final(out);
	}

	void Reset();
	void Update(const void* inpData, size_t inNumBytes);
	void Final(TSha256HashData& outHash);

private:
	void Transform();

	Uint8 fData[64];
	Uint32 fDatalen;
	Uint32 fBitlen[2];
	Uint32 fState[8];
};
