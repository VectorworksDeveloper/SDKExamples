//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include <stdarg.h>
#include <string>

#if _MINICAD_
	#define GS_STRING_API	GS_COMP_API
#else
	#define GS_STRING_API	GS_API
#endif

// For Unicode string literal
#if GS_WIN
	#define txu(string) L##string
	#define txuc(string) L##string
#else
	#define txu(string) (const UCChar*)u##string
	#define txuc(ch) (const UCChar)u##ch
#endif

class TXString;
class TXStringArray;

enum ECharacterType {
    eSingle,
    eLead,
    eTrail,
    eIllegal
};

/* Constants */
/* --------- */
/* For comparison and search routines */
const bool	kDoIgnoreCase   = true;
const bool	kDontIgnoreCase = false;
const bool	kFindFwd = true;
const bool	kFindRev = false;


/* Types */
/* ----- */
/* Character encoding standard--uses platform-specific values */
typedef Uint32			GSTextEncoding;


void NNAUppercaseText(char* textPtr, Sint32 len, int scriptCode);
void NNANumToString(Sint32 num, unsigned char* str, size_t strSize);
void NNANumToString(Sint32 num, TXString& str);
void NNAStringToNum(const unsigned char * theString, Sint32 *theNum);
void NNAParseName(const TXString& name, int& numbParts, TXStringArray& parts);

/*============================================================================*/
double_gs str2num(const char *s);


/**************************************************/
/* Unicode Character String Manipulation Routines */
/**************************************************/

/* Unicode Encoding Converter Routines */
size_t	StringToUnicodeMaxChars (size_t srcLen);
bool	StringToUnicode (GSTextEncoding srcEncoding, const char* srcArray,
			 size_t srcLen, UCCharPtr dstUCArray, size_t maxDstChars,
			 size_t* pDstLen);
bool	StringToUnicode (GSTextEncoding srcEncoding, const char* srcStr,
             UCStrPtr dstUCStr, size_t maxDstChars, size_t* pDstLen);
bool	StringToUnicode (GSTextEncoding srcEncoding, ConstGSStr255Param srcStr,
             UCStrPtr dstUCStr, size_t maxDstChars, size_t* pDstLen);
size_t	UnicodeToStringMaxChars (size_t srcLen);
bool	UnicodeToString (GSTextEncoding dstEncoding,
			ConstUCCharPtr srcUCArray, size_t srcLen,
			char* dstArray, size_t maxDstBytes, size_t* pDstLen);
bool	UnicodeToString (GSTextEncoding dstEncoding, ConstUCStrPtr srcUCStr,
			char* dstStr, size_t maxDstBytes, size_t* pDstLen);
bool	UnicodeToString (GSTextEncoding dstEncoding, ConstUCStrPtr srcUCStr,
			GSStringPtr dstStr, size_t maxDstBytes, size_t* pDstLen);

/* Unicode String Manipulation Routines */
size_t	StringLength (ConstUCStrPtr ucString);
bool		StringEqual (ConstUCStrPtr str1, ConstUCStrPtr str2, bool ignoreCase);
bool		StringEqual (ConstUCCharPtr chars1, size_t len1,
			              ConstUCCharPtr chars2, size_t len2, bool ignoreCase);
void		StringCopy (ConstUCStrPtr srcStr, UCStrPtr dstStr, size_t maxDstBytes);
void		StringCopy (ConstUCStrPtr srcStr, wchar_t * dstStr, size_t maxDstBytes);
bool		FindCharClusterBreak (ConstUCCharPtr charArray, size_t length,
		             size_t startPos, bool forward, size_t* pBreakPos);

// Trims invalid multi byte characters at the end of a string
void	TrimInvalidCharsFromMultiByteEncodedCString(char*          buffer, size_t bufferSize);	// For C string
void	TrimInvalidCharsFromMultiByteEncodedPString(unsigned char* buffer, size_t bufferSize);	// For Pascal string

// Creates an array that identifies each type of char in a mac encoded string
// Only used for translation of strings during reverse translation, and a few other special cases.
// Do not use this without talking to Payne or Ian first.
void	GetFarEastCharacterTypeArray(const char *pStr, ECharacterType *pCharByteType, size_t strLength);

// Determines if the current system locale is running in a multi byte language.  This should only be used during translation
Boolean IsMultiByteLanguage( );


/*============================================================================*/
/*============================================================================*/
/***********************************************************************/
/* Non-Unicode Pascal and C String Manuipulation Routines and Classes */
/***********************************************************************/


////////////////////////////////////////////////////////////////////////////////
// OS-Specific Character Encoding Routines

enum EStringExpansion {
	eAllowStringExpansion,
	eDontAllowStringExpansion
};

#if GS_WIN
extern Boolean	gl_MapUpperChars;	// Where is this defined?
#endif // GS_WIN

// System Encoding Retrieval Routines
GSTextEncoding	GetSystemEncoding ();


////////////////////////////////////////////////////////////////////////////////
#if __cplusplus

/*
	For complete documentation on the things in this section, see the
	Graphsoft String Library document.
	
	Most of the routines here are overloaded to accept any mix of Pascal-
	style (unsigned char *) and C-style (char *) strings.  In any function
	that takes a string size (i.e. StringCopy and StringCat), the size is
	the total number of bytes occupied by the string, which is one greater
	than the maximum character length.  We do this so you can pass sizeof(T)
	as the length.  For example, to copy a string into a GSStr255, you would
	say "StringCopy(someString, aStr255, sizeof(GSStr255))".
	
	All of the functions can accept "unusual" input values, i.e. null pointers
	and negative lengths.  An input of a null pointer or non-positive string
	length is interpreted like an empty string, if given as an output, nothing
	will be written to it.
*/


////////////////////////////////////////
// Length tests: GetLength (formerly length), IsEmpty.

//   NOTE: IsEmpty(s) is faster than GetLength(s) == 0, particularly for C-style strings.
inline Uint8	GetLength(ConstGSStr255Param s)		{ return s ? s[0] : 0; }
inline size_t	GetLength(const char *s)			{ return s ? strlen(s) : 0; }
inline Bool8	IsEmpty(ConstGSStr255Param s)		{ return !s || s[0] == 0; }
inline Bool8	IsEmpty(const char *s)				{ return !s || s[0] == '\0'; }


////////////////////////////////////////
// SetLength

inline void SetLength(GSStringPtr s, Uint8 len)	{ if (s) s[0] = len; }
inline void SetLength(char *s, size_t len)		{ if (s) s[len] = '\0'; }


////////////////////////////////////////
// StringCopy

// These functions all return void now to get around a bug in the Visual C++ 4.1 & 4.2 linker. [DMB 12/4/96]
void GS_STRING_API StringCopy(ConstGSStr255Param src, GSStringPtr dst, size_t sizeofDst);
void GS_STRING_API StringCopy(const char *src, GSStringPtr dst, size_t sizeofDst);
void GS_STRING_API StringCopy(const void *src, size_t len, GSStringPtr dst, size_t sizeofDst);
void GS_STRING_API StringCopy(ConstGSStr255Param src, char *dst, size_t sizeofDst);
void GS_STRING_API StringCopy(const char *src, char *dst, size_t sizeofDst);
void GS_STRING_API StringCopy(const void *src, size_t len, char *dst, size_t sizeofDst);


////////////////////////////////////////
// StringCat

GSStringPtr GS_STRING_API StringCat(GSStringPtr dst, ConstGSStr255Param src, size_t sizeofDst);
GSStringPtr GS_STRING_API StringCat(GSStringPtr dst, const char *src, size_t sizeofDst);
GSStringPtr GS_STRING_API StringCat(GSStringPtr dst, const void *src, size_t len, size_t sizeofDst);
char GS_STRING_API * StringCat(char *dst, ConstGSStr255Param src, size_t sizeofDst);
char GS_STRING_API * StringCat(char *dst, const char *src, size_t sizeofDst);
char GS_STRING_API * StringCat(char *dst, const void *src, size_t len, size_t sizeofDst);

//======================================
// String equality
Bool8 GS_STRING_API StringEqual(const TXString& a, const TXString& b);				// Case sensitive
Bool8 GS_STRING_API	StringEqualIgnoringCase(const TXString& a, const TXString& b);	// Case insensitive

//======================================
// String comparison
short GS_STRING_API StringCompare(const TXString& a, const TXString& b);				// Case sensitive
short GS_STRING_API StringCompareIgnoringCase(const TXString& a, const TXString& b);	// Case insensitive


////////////////////////////////////////
// StringInsert

void GS_STRING_API StringInsert(ConstGSStr255Param src, GSStringPtr dst, Uint8 index);


////////////////////////////////////////
// StringDelete

void GS_STRING_API StringDelete(GSStringPtr s, Uint8 start, Uint8 count);
void GS_STRING_API StringDelete(char *s, size_t start, size_t count);


////////////////////////////////////////
// StringPos

#ifdef _MINICAD_
short GS_STRING_API StringPos (ConstGSStr255Param findStr, ConstGSStr255Param str);
#endif



//=======================================================================================
// SortStringsUsingOS
//
// To use, implement GetStringForSorting(const Type &obj) for your Type

template<class Type>
const TXString& GetStringForSorting(const Type &obj);

//----------------------------------------------------------------------------------------
// This class can greatly improve the performance of OSStringCompare(...) on Mac when 
// OSStringCompare(...) is inside a loop with many iterations. To use this class, create
// an instance of COSStringCompare before the loop and replace OSStringCompare(...) with
// COSStringCompare::Compare(...) inside the loop.
// On Windows, COSStringCompare::Compare(...) is almost identical to OSStringCompare(...).
class COSStringCompare
{
public:
#if GS_MAC
	CFMutableStringRef cfStr1;
	CFMutableStringRef cfStr2;
	
	COSStringCompare();
	~COSStringCompare();
	CFComparisonResult Compare(const CFMutableStringRef cfStr1, const CFMutableStringRef cfStr2);
#endif

	short Compare(const TXString& txStr1, const TXString& txStr2, bool bDashTreatedSpecially = false);
};

//----------------------------------------------------------------------------------------
// If OSStringCompare(...) is inside a loop and the code is iterated many times, please
// consider creating an instance of COSStringCompare before the loop and replace
// OSStringCompare(...) with COSStringCompare::Compare(...) to improve performance.
short GS_STRING_API OSStringCompare(const TXString& string1, const TXString& string2, bool bDashTreatedSpecially = false);

//----------------------------------------------------------------------------------------
// No case comparison; Uses OS and current locale to compare strings; in VW code used to compare File/Folder names
int GS_STRING_API OSStringCompareEx(const TXString& string1, const TXString& string2);

//========================================================================================
// On Mac, eight comparison methods of TXString are slow. They include CompareNoCase(...),
// EqualNoCase(...), ==operator(...), !=operator(...), >operator(...), <operator(...), 
// >=operator(...), and <=operator(...). If your code uses any of these methods repeatedly
// and performance is an issue, you can create one CTXStringNoCase instance and uses its
// methods repeatedly in a thread. 
// 
// On Windows, using CTXStringNoCase is almost identical to using TXString methods.
// 
// Example:
// Slow Code:
// for(int i = 0; i < 1000000; ++i) {
//		...
//		if(txStr1 > txStr2)
//			...
// }
//
// Fast Code:
// CTXStringNoCase txStringNoCase;
// for(int i = 0; i < 1000000; ++i) {
//		...
//		if(txStringNoCase.Compare(txStr1, txStr2) > 0)
//			...
// }
//
class CTXStringNoCase
{
public:
	
#if GS_MAC
	CFMutableStringRef cfStr1;
	CFMutableStringRef cfStr2;
	
	CTXStringNoCase();
	~CTXStringNoCase();
	
#endif
	
	bool	Equal(const TXString& txStr1, const TXString& txStr2);		// EqualNoCase equivalent
	short	Compare(const TXString& txStr1, const TXString& txStr2);	// CompareNoCase equivalent
};

//========================================================================================
template<class Type>
class OSComparator
{
public:
	bool operator()(const Type& s1, const Type& s2)
	{
		return OSStringCompare(GetStringForSorting(s1), GetStringForSorting(s2)) < 0;
	}
};

template<typename IteratorType>
inline void SortStringsUsingOS(IteratorType begin, IteratorType end)
{
	std::sort(begin, end, OSComparator<typename IteratorType::value_type>());
}


//=======================================================================================
// Truncate (formerly trunc)

inline void Truncate(GSStringPtr s, Uint8 len)		{ if (s && GetLength(s) > len) SetLength(s, len); }
inline void Truncate(char *s, size_t len)		{ if (s) s[len] = '\0'; }


////////////////////////////////////////
// str*cmp

#if !_WINDOWS
Sint32 stricmp(const char *a, const char *b);
Sint32 strnicmp(const char *a, const char *b, size_t max);
#endif // !_WINDOWS


////////////////////////////////////////
/* USAGE FOR NULLSTR, DUMMYSTR, _ccp, _cucp:

	Since IBM PC compilers don't generally know about the \p convention for strings,
	you should avoid the use of string literals in your code.  If you need an empty
	string, use NULLSTR.  If you need an innocuous but non-empty string, use DUMMYSTR.
	(This case usually turns up with AppendMenu, which treats certain characters
	specially.  DUMMYSTR is not guaranteed to be anything in particular, but is
	guaranteed to not make AppendMenu do something strange.)
	
	If you need your own string literal, define it like this: _cucp "\011my string".
	You must encode the length byte explicitly, since the IBM PC compilers can't handle
	\p; the _cucp (shorthand for "const unsigned char pointer"), casts the string
	to the standard type for Pascal-style string literals; const unsigned char *.
	_ccp (const char *) casts to a standard C-style string

	_ccp  == (ConstGSCStrPtr)
	_cucp == (ConstGSStringPtr)
*/
#define _ccp		   (const char *)
#define _cucp	       (const unsigned char *)
#if GS_MAC
	#define NULLSTR   ((const unsigned char *) "\p")
	#define DUMMYSTR  ((const unsigned char *) "\px")
#else
	#define NULLSTR   ((const unsigned char *) "\0")
	#define DUMMYSTR  ((const unsigned char *) "\001x")
#endif



////////////////////////////////////////////////////////////////////////////////
// - PStr<>

template <size_t maxCharLen>
class PStr {
#if GS_WIN
	friend class PStr<maxCharLen>;  // Updated for CW Pro 6
#endif
	
	private:
		Uint8 buf[maxCharLen+1 + ((maxCharLen+1)%2)];
	
	public:
		/* - Constructors
		*/
		PStr()											{ buf[0] = 0; }
		PStr(const PStr &s)								{ StringCopy(s.buf, buf, maxCharLen+1); }
		PStr(ConstGSStringPtr s)						{ StringCopy(s, buf, maxCharLen+1); }
		PStr(const char *s)								{ StringCopy(s, buf, maxCharLen+1); }
		PStr(const void *s, size_t size)				{ StringCopy(s, size, buf, maxCharLen+1); }
		PStr(const TXString& s);
		

		template <size_t maxCharLen2>
		PStr(const PStr<maxCharLen2>& s) { StringCopy(s, buf, maxCharLen+1);  }

		
		/* - Assignment operators
		*/
		PStr& operator=(ConstGSStringPtr s)				{ StringCopy(s, buf, maxCharLen+1); return *this; }
		PStr& operator=(const char *s)					{ StringCopy(s, buf, maxCharLen+1); return *this; }

		template <size_t maxCharLen2>
		PStr& operator=(const PStr<maxCharLen2>& s){
			StringCopy(s, buf, maxCharLen+1); 
			return *this; 
		}
		
		PStr& operator=(const TXString& s);

		void CopyToStr(unsigned char* s) const 			{ StringCopy(buf, s, maxCharLen+1); }

		/* - Casts
		*/
		operator GSStringPtr() 							{ return buf; }
//		operator ConstGSStr255Param() const				{ return buf; }
		operator ConstGSStringPtr() const				{ return buf; }

		/* - String length
		*/
		Uint8 GetLength() const							{ return buf[0]; }
		static Uint8 GetMaxLength()						{ return (Uint8) maxCharLen; }
		static Uint8 MaxLength()						{ return (Uint8) maxCharLen; }
		void SetLength(Uint8 len)						{ buf[0] = len; }
		void Truncate(Uint8 len)						{ if (GetLength() > len) SetLength(len); }
		Bool8 IsEmpty() const							{ return GetLength() == 0; }
		void Clear()									{ buf[0] = 0; }
		
		/* - Subscript operators
		*/
		#if 0
		// Both Mac and Win compilers find these operators ambiguous when
		// you say aString[i], due to being able to implicitly cast to char*.
		unsigned char& operator[](Uint8 i)				{ return buf[i]; }
		unsigned char operator[](Uint8 i) const			{ return buf[i]; }
		#endif
		
		/* - Comparison operators
		*/
		Bool8 operator==(ConstGSStringPtr s) const 		{ return StringEqualIgnoringCase(buf, s); }
		// TODO template <size_t maxCharLen>
		Bool8 operator==(const PStr<maxCharLen>& s) const 	{ return StringEqualIgnoringCase(buf, s); }

		Bool8 operator!=(const PStr &s)					{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(ConstGSStringPtr s)	 		{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(ConstGSStringPtr s) const 		{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator==(const char * const s) const	{ return StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(const char * s) const			{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(const char * s)				{ return !StringEqualIgnoringCase(buf, s); }

		Bool8 operator==(char c) const					{ return GetLength() == 1 && ((const char *) buf)[1] == c; }
		Bool8 operator!=(char c) const					{ return GetLength() != 1 || ((const char *) buf)[1] != c; }
		Bool8 operator<(ConstGSStringPtr s) const		{ return StringCompare(buf, s) < 0; }
		Bool8 operator<(const char *s) const			{ return StringCompare(buf, s) < 0; }
		
		template<size_t maxCharLen2>
		Bool8 operator==(const PStr<maxCharLen2> &s) const			{ return StringEqualIgnoringCase(buf, s); }
		
		/* - Append operators
		*/
		PStr& operator<<(ConstGSStr255Param s)			{ StringCat(buf, s, maxCharLen+1); return *this; }
		PStr& operator<<(const char *s)					{ StringCat(buf, s, maxCharLen+1); return *this; }
		PStr& operator<<(Sint32 n);
        PStr& operator<<(Sint64 n);
		PStr& operator<<(short n)						{ return (*this << (Sint32) n); } 
		PStr& operator<<(char c)						{ if (buf[0] < maxCharLen) buf[++buf[0]] = c; return *this; }
		PStr& operator<<(unsigned char c)				{ if (buf[0] < maxCharLen) buf[++buf[0]] = c; return *this; }

		template <size_t maxCharLen2>
		PStr& operator<<(const PStr<maxCharLen2>& s)	{ return *this << (ConstGSStr255Param) s; }

		//PStr& operator<<(float_param f);				// NOT IMPLEMENTED!
		//PStr& operator<<(double_param d);				// NOT IMPLEMENTED!
		
		/* - Searching
		*/
		Sint32 Find(char ch) const							{ return Find(1, ch); }
		Sint32 Find(Uint8 start, char ch) const;
		Sint32 ReverseFind(char ch) const					{ return ReverseFind(GetLength(), ch); }
		Sint32 ReverseFind(Uint8 start, char ch) const;
		
		/* - Substrings
		*/
		PStr Left(Uint8 count) const						{ Uint8 len = GetLength(); if (count > len) count = len; return PStr<maxCharLen>(&buf[1], count); }
		PStr Right(Uint8 count) const					{ Uint8 len = GetLength(); if (count > len) count = len; return PStr<maxCharLen>(&buf[len - count + 1], count); }
		PStr Mid(Uint8 start, Uint8 count = 255) const;
		
		/* - Formatted output
		*/
		Uint8 Format(ConstGSStr255Param format, ...);
		Uint8 Format(const char *format, ...);
};




////////////////////////////////////////////////////////////////////////////////
// - CStr<>

template <size_t maxCharLen>
class CStr : public TDebugObject {
	private:
		char buf[maxCharLen+1 + ((maxCharLen+1)%2)];
	
	public:
		/* - Constructors
		*/
		CStr()											{ buf[0] = 0; }
		CStr(const CStr &s)								{ StringCopy(s.buf, buf, maxCharLen+1); }
		CStr(ConstGSStr255Param s)						{ StringCopy(s, buf, maxCharLen+1); }
		CStr(const char *s)								{ StringCopy(s, buf, maxCharLen+1); }
		CStr(const void *s, size_t size)				{ StringCopy(s, size, buf, maxCharLen+1); }
		// TODO template <size_t maxCharLen>
		CStr(const PStr<maxCharLen>& s)					{ StringCopy(s, buf, maxCharLen+1); }
		
		/* - Assignment operators
		*/
		CStr& operator=(const CStr& s)					{ StringCopy(s.buf, buf, maxCharLen+1); return *this; }
		CStr& operator=(ConstGSStr255Param s)			{ StringCopy(s, buf, maxCharLen+1); return *this; }
		CStr& operator=(const char *s)					{ StringCopy(s, buf, maxCharLen+1); return *this; }
		
		// TODO template <size_t maxCharLen>
		CStr& operator=(const PStr<maxCharLen>& s)		{ StringCopy(s, buf, maxCharLen+1); return *this; }
		
		/* - Casts
		*/
		operator char *()								{ return buf; }
		operator const char *() const					{ return buf; }

		/* - String length
		*/
		size_t GetLength() const						{ return strlen(buf); }
		static size_t GetMaxLength()					{ return maxCharLen; }
		void SetLength(size_t len)						{ if (VERIFYN(kChris, len <= maxCharLen)) buf[len] = '\0'; }
		void Truncate(size_t len)						{ if (len <= maxCharLen) buf[len] = '\0'; }
		Bool8 IsEmpty() const							{ return buf[0] == '\0'; }
		void Clear()									{ buf[0] = '\0'; }
		
		/* - Subscript operators
		*/
		#if 0
		// Both Mac and Win compilers find these operators ambiguous when
		// you say aString[i], due to being able to implicitly cast to char*.
		char& operator[](size_t i)						{ return buf[i]; }
		char operator[](size_t i) const					{ return buf[i]; }
		#endif
		
		/* - Comparison operators
		*/
		Bool8 operator==(ConstGSStr255Param s) const 	{ return StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(ConstGSStr255Param s) const 	{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator==(const char *s) const			{ return StringEqualIgnoringCase(buf, s); }
		Bool8 operator!=(const char *s) const			{ return !StringEqualIgnoringCase(buf, s); }
		Bool8 operator==(char c) const					{ return buf[0] == c && buf[1] == '\0'; }
		Bool8 operator!=(char c) const					{ return buf[0] != c || buf[1] != '\0'; }
		Bool8 operator<(ConstGSStr255Param s) const		{ return StringCompare(buf, s) < 0; }
		Bool8 operator<(const char *s) const			{ return StringCompare(buf, s) < 0; }
		Bool8 operator==(const CStr &s) const			{ return s == buf; }
		
		/* - Append operators
		*/
		CStr& operator<<(ConstGSStr255Param s)			{ StringCat(buf, s, maxCharLen+1); return *this; }
		CStr& operator<<(const char *s)					{ StringCat(buf, s, maxCharLen+1); return *this; }
		CStr& operator<<(Sint32 n);						
		CStr& operator<<(short n)						{ return (*this << (Sint32) n); }
		CStr& operator<<(char c)						{ size_t pos = strlen(buf); if (pos < maxCharLen) { buf[pos] = c; buf[pos+1] = '\0'; } return *this; }
		CStr& operator<<(unsigned char c)				{ size_t pos = strlen(buf); if (pos < maxCharLen) { buf[pos] = c; buf[pos+1] = '\0'; } return *this; }
		//CStr& operator<<(float_param f);				// NOT IMPLEMENTED!
		//CStr& operator<<(double_param d);				// NOT IMPLEMENTED!
		
		/* - Searching
		*/
		Sint32 Find(char ch) const							{ return Find(0, ch); }
		Sint32 Find(size_t start, char ch) const;
		Sint32 ReverseFind(char ch) const					{ return ReverseFind(GetLength() - 1, ch); }
		Sint32 ReverseFind(size_t start, char ch) const;
		
		/* - Substrings
		*/
		CStr Left(size_t count) const					{ size_t len = GetLength(); if (count > len) count = len; return CStr<maxCharLen>(&buf[0], count); }
		CStr Right(size_t count) const					{ size_t len = GetLength(); if (count > len) count = len; return CStr<maxCharLen>(&buf[len - count], count); }
		CStr Mid(size_t start, size_t count = 1024) const;
		
		/* - Formatted output
		*/
		Sint32 Format(ConstGSStr255Param format, ...);
		Sint32 Format(const char *format, ...);

		/* - Debugging
		*/
		DECLARE_CLASS_DEBUGGING
};

template <size_t maxCharLen>
CStr<maxCharLen>& CStr<maxCharLen>::operator<<(Sint32 n)
{ 
	const std::string s = std::to_string(n);
	StringCat(buf, s.c_str(), maxCharLen+1);
	return *this; 
}

template <size_t maxCharLen>
Sint32 CStr<maxCharLen>::Find(size_t start, char ch) const
{
	size_t i; const char *p;
	
	for (i = start, p = &buf[i]; i <= maxCharLen && *p != '\0'; i++, p++)
		if (*p == ch) return (Sint32) i; 
	return -1;
}

template <size_t maxCharLen>
Sint32 CStr<maxCharLen>::ReverseFind(size_t start, char ch) const
{
	Sint32 i; const char *p;
	
	for (i = (Sint32) start, p = &buf[i]; i >= 0 && *p != '\0'; i--, p--) 
		if (*p == ch) return i;
	return -1;
}

template <size_t maxCharLen>
CStr<maxCharLen> CStr<maxCharLen>::Mid(size_t start, size_t count) const
{
	if (start > GetLength())
		count = 0;
	else if (start + count - 1 > GetLength())
		count = GetLength() - start + 1;
	
	return CStr<maxCharLen>(&buf[start], count);
}

template <size_t maxCharLen>
Sint32 CStr<maxCharLen>::Format(ConstGSStr255Param format, ...)
{
	Sint32 result;
	va_list ap;
	va_start(ap, format);

	char szFormat[256];
	StringCopy(format, szFormat, 256);

	result = vsprintf(this->buf, szFormat, ap);

	va_end(ap);
	return result;
}

template <size_t maxCharLen>
Sint32 CStr<maxCharLen>::Format(const char *format, ...)
{
	Sint32 result;
	va_list ap;
	va_start(ap, format);

	result = vsprintf(this->buf, format, ap);

	va_end(ap);
	return result;
}


////////////////////////////////////////////////////////////////////////////////

#define STRINGTYPE_INTERFACE(maxCharLen) typedef PStr<maxCharLen> PStr##maxCharLen


typedef CStr<7>		CStr7;
typedef CStr<8>		CStr8;
typedef CStr<15>	CStr15;
typedef CStr<20>	CStr20;
typedef CStr<27>	CStr27;
typedef CStr<31>	CStr31;
typedef CStr<63>	CStr63;
typedef CStr<255>	CStr255;
typedef CStr<256>	CStr256;
typedef CStr<512>	CStr512;


#endif  // __cplusplus


//---------------------------------------------------------------------------------------
// For unit tests
namespace SystemTests
{
	class TXStringSystemTest;
}

//---------------------------------------------------------------------------------------
// EEmptyStringResourceHandling - how do we deal with warning about empty string resources.
//
enum EEmptyStringResourceHandling {
	eDontWarnAboutEmptyStringResult = 1,
	eWarnAboutEmptyStringResult = 2
};


enum EEmptyHandling {
	eAllowEmptyResult = eDontWarnAboutEmptyStringResult,
	eDontAllowEmptyResult = eWarnAboutEmptyStringResult 
};

// Enum to specify whether length checking should be performed for constructors with 
// UCChar and wchar_t buffers. Constructors with length check are slower.
enum class ELengthCheck {
	eYes,
	eNo
};


// Used to specify the encoding of TXString (char buffer).
enum class ETXEncoding {
    eMacEncoded,
    eWinEncoded,
	eSysEncoded,	// use Windows encoding on Windows and Mac encoding on Mac
    eUTF8,
	eUTF16,			// UTF-16 little endian
	eUnkown
};

// TXString character type
#if GS_WIN
typedef wchar_t TXChar;
#else
typedef UniChar TXChar;
#endif

// StdUStr definition
#if GS_WIN
// Allocator for StdUStr
template <typename T>
class TXAlloc
{
public:
	// Type definitions
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;
	typedef T*				pointer;
	typedef const T*		const_pointer;
	typedef T&				reference;
	typedef const T&		const_reference;
	typedef T				value_type;

	// Rebind allocator to type U
	template <typename U>
	struct rebind {
		typedef TXAlloc<U> other;
	};

	// Return address of values
	pointer			address(reference value) const { return &value; }
	const_pointer	address(const_reference value) const { return &value; }

	// Constructors and distructors
	TXAlloc() throw() {}
	TXAlloc(const TXAlloc&) throw() {}
	template <typename U> TXAlloc(const TXAlloc<U>&) throw() {}
	~TXAlloc() throw() {}

	// Max size
	size_type max_size() const throw() { return (size_type)(-1) / sizeof(T); }

	// Allocation
	pointer allocate(size_type num, const void* hint = 0)
	{
		return (pointer) gVWMM->TXStringAllocate(num * sizeof(T));
	}
  
	// Deallocation
	void deallocate(pointer p, size_type) 
	{
		gVWMM->TXStringDeallocate(p);
	}

	// Construction
	void construct(pointer p, const_reference value) { new (p) T(value); }

	// Destruction
	void destroy(pointer p) { p->~T(); }

	inline bool operator==(TXAlloc const&) throw() { return true; }
    inline bool operator!=(TXAlloc const&) throw() { return false; }
};

template <typename T>
bool operator==(const TXAlloc<T>& lhs, const TXAlloc<T>& rhs) throw() {
	return true;
}

// StrUStr definition
typedef std::basic_string<TXChar, std::char_traits<TXChar>, TXAlloc<TXChar>> StdUStr;

#else	// Mac
typedef std::basic_string<TXChar> StdUStr;
#endif


//#######################################################################################
// TXString class
// Please refer to GSString.X.cpp for more detailed descriptions. [PChang]
//#######################################################################################
class GS_COMP_API GS_HIDDEN_VISIBILITY TXString : public TDebugObject
{
public:
	
	//***********************************************************************************
	// Constructors and destructor
	//***********************************************************************************
	
	TXString();									// Default constructor
	TXString(const TXString& src);				// Copy constructor
	TXString(TXString&& src);					// Move constructor
	TXString(const StdUStr& src);				// Copy constructor from StdUStr
	TXString(StdUStr&& src);					// Move constructor from StdUStr

	// From other string type
	TXString(const std::string& src, ETXEncoding e = ETXEncoding::eUTF8);
	TXString(const std::wstring& src);
#if GS_MAC
	TXString(const CFStringRef& src);			// Construct from CFStringRef&
#endif

	// Specify initial size
	explicit TXString(size_t nInitialSize);		// Specify size (size_t version)
	explicit TXString(int nInitialSize);		// Specify size	(int version)

	// From a buffer
	TXString(const char* src, ETXEncoding e = ETXEncoding::eUTF8);
	TXString(const char* src, size_t len, ETXEncoding e = ETXEncoding::eUTF8);

	TXString(const unsigned char* src, ETXEncoding e = ETXEncoding::eUTF8);

	TXString(const UCChar* src);
	TXString(const UCChar* src, size_t len, ELengthCheck eLengthCheck = ELengthCheck::eYes);

	TXString(const wchar_t* src);
	TXString(const wchar_t* src, size_t len, ELengthCheck eLengthCheck = ELengthCheck::eYes);
	
	// From a character
	explicit TXString(char ch, size_t count = 1);
	explicit TXString(unsigned char ch, size_t count = 1);
	explicit TXString(UCChar ch, size_t count = 1);
	explicit TXString(wchar_t ch, size_t count = 1);
	
	// Destructor
	virtual ~TXString();
	
	
	//***********************************************************************************
	// Assignments
	//***********************************************************************************
	
	TXString& operator=(const TXString& src);		// Copy assignment operator
	TXString& operator=(TXString&& src);			// Move assignment operator
	TXString& operator=(const std::string& src);	// Assignment from std::string
	TXString& operator=(const std::wstring&src);	// Assignment from std::wstring
#if GS_MAC
	TXString& operator=(const CFStringRef& src);	// Assignment from CFStringRef&
#endif
	
	// From a buffer
	TXString& operator=(const char *src);
	TXString& operator=(const unsigned char* src);
	TXString& operator=(const UCChar* src);
	TXString& operator=(const wchar_t* src);
	
	// From single character
	TXString& operator=(char ch);
	TXString& operator=(unsigned char ch);
	TXString& operator=(UCChar ch);
	TXString& operator=(wchar_t ch);
	TXString& operator=(int codePoint);		// For example: txString = 0x27
	
	
	//***********************************************************************************
	// Length related functions
	//***********************************************************************************
	
	size_t GetLength() const;
	size_t GetByteSize() const;
	size_t GetEncodingLength(ETXEncoding e) const;
	
	bool IsEmpty() const;
	
	TXString& SetLength(size_t len);
	TXString& SetLength(size_t len, TXChar ch);
	TXString& Truncate(size_t len);
	TXString& Clear();
	
	
	//***********************************************************************************
	// Element access
	//***********************************************************************************
	
	TXChar& operator[](ptrdiff_t nIndex);
	TXChar operator[](ptrdiff_t nIndex) const;
	TXChar& GetAt(size_t nIndex);
	TXChar GetAt(size_t nIndex) const;
	TXChar& GetLast();
	TXChar GetLast() const;
	TXString& SetAt(size_t nIndex, TXChar ch);
	
	
	//***********************************************************************************
	// Concatenation
	//***********************************************************************************
	
	// Extends string from another TXString object
	TXString& operator+=(const TXString& src);
	
	// Extends string from character buffer
	TXString& operator+=(const char* src);			// UTF-8
	TXString& operator+=(const unsigned char* src);	// UTF-8
	TXString& operator+=(const UCChar* src);
	TXString& operator+=(const wchar_t* src);
	
	// Extends string by one character
	TXString& operator+=(char ch);
	TXString& operator+=(unsigned char ch);
	TXString& operator+=(UCChar ch);
	TXString& operator+=(wchar_t ch);
	TXString& operator+=(int n);		// Unicode code point, for example: 0x63
	
	// String concatenation by using '<<'
	TXString& operator<<(const TXString& src);
	
	// Extends string from character buffer
	TXString& operator<<(const char *src);			// UTF-8
	TXString& operator<<(const unsigned char* src);	// UTF-8
	TXString& operator<<(const UCChar* src);
	TXString& operator<<(const wchar_t* src);
	
	// Extends string by one character
	TXString& operator<<(char ch);
	TXString& operator<<(unsigned char ch);
	TXString& operator<<(UCChar ch);
	TXString& operator<<(wchar_t ch);
	
	// Append a number as string
	TXString& operator<<(Sint32 number);
	TXString& operator<<(Sint64 number);
	TXString& operator<<(Uint32 number);
	TXString& operator<<(Uint64 number);
	TXString& operator<<(double number);
#if GS_MAC
	TXString& operator<<(size_t number); // size_t is different from Uint64 on the mac
#endif
	TXString& operator<<(const GSHandle h); // as number
	
	
	//***********************************************************************************
	// Insertion and deletion
	//***********************************************************************************
	
	// Insert another TXString at position 'pos'.
	TXString& Insert(size_t pos, const TXString& src);
	
	// Insert one buffer at position 'pos'.
	TXString& Insert(size_t pos, const char* src);
	TXString& Insert(size_t pos, const unsigned char* src);		// UTF-8
	TXString& Insert(size_t pos, const UCChar* src);
	TXString& Insert(size_t pos, const wchar_t* src);
	
	// Insert one character 'ch' at position 'pos'.
	TXString& Insert(size_t pos, char ch);
	TXString& Insert(size_t pos, unsigned char ch);
	TXString& Insert(size_t pos, UCChar ch);
	TXString& Insert(size_t pos, wchar_t ch);
	TXString& Insert(size_t pos, int ch);						// e.g. 0xA5, '¥'
	
	// Delete characters starting from 'pos' for 'len' characters.
	TXString& Delete(size_t pos, size_t len = (size_t) -1);
	
	// Delete the last character
	TXString& DeleteLast();
	
	// Trims white spaces (' ', '\t') or invalid chars
	TXString& TrimLeft();
	TXString& TrimRight();
	TXString& Trim();

	TXString& TrimLeftInvalidCharacter();
	TXString& TrimRightInvalidCharacter();
	TXString& TrimInvalidCharacters();
	
	
	//***********************************************************************************
	// Replacement, case conversion, reversion, Unicode normalization form conversion
	//***********************************************************************************
	
	// Replaces all 'oldStr' with 'newSTr'.
	TXString& Replace(const TXString& oldStr, const TXString& newStr, bool bIgnoreCase = false);
	
	// Upper case and lower case conversion
	TXString& MakeUpper();
	TXString& MakeLower();
	
	// Reverse the string.
	TXString& MakeReverse();
	
	// Conversion to a Unicode normalization form
	TXString& ToPrecomposed();
	TXString& ToDecomposed();
	
	
	//***********************************************************************************
	// Getting data and casting
	//***********************************************************************************
	
	// Returns const pointer to the TXChar buffer.
	const TXChar* GetData() const;
	const TXChar* GetTXCharPtr() const;
	
	// Casting operators
	operator const char*() const;				// UTF-8
	operator const unsigned char*() const;		// UTF-8
	operator const UCChar*() const;				// Unsigned short, UTF-16
	operator const wchar_t*() const;			// wchar_t: Win:UTF-16, Mac:UTF-32
	
	// Casting operators in function form.
	const char* GetCharPtr() const { return (operator const char*()); }
	const unsigned char* GetUCharPtr() const { return (operator const unsigned char*()); }
	const UCChar* GetUCCharPtr() const { return (operator const UCChar*()); }
	const wchar_t* GetWCharPtr() const { return (operator const wchar_t*()); }
	
	// Returns a std string or wstring
	std::string GetStdString(ETXEncoding e = ETXEncoding::eUTF8) const;
	std::wstring GetStdWString() const;
private:
	const std::u16string & GetConstU16String() const;	// For hash function only.
	friend std::hash<TXString>;
public:
#if GS_MAC
	CFStringRef GetCFStringRef() const;
#endif
	
	
	//***********************************************************************************
	// Copying data into external buffer
	//
	// Note: 'bufSize' is the size of the buffer in bytes. For example, "xyz" needs four bytes to include '\0' at the end.
	//
	//***********************************************************************************
	void CopyInto(char* dst,
				  size_t bufSize,
				  ETXEncoding e = ETXEncoding::eUTF8) const;

	void CopyInto(unsigned char* ps,
				  size_t bufSize,
				  ETXEncoding e = ETXEncoding::eUTF8) const;
	
	void CopyInto(UCChar* dst, size_t bufElemSize) const;

	void CopyInto(wchar_t* dst, size_t bufElemSize) const;
	
	
	//***********************************************************************************
	// Searching functions
	//***********************************************************************************
	ptrdiff_t Find(const TXString &subStr, size_t posFirst = 0, bool bIgnoreCase = false) const;
	ptrdiff_t Find(int ch, size_t posFirst = 0, bool bIgnoreCase = false) const;
	ptrdiff_t Find(char ch, size_t posFirst = 0, bool bIgnoreCase = false) const;
	
	ptrdiff_t ReverseFind(const TXString &subStr, size_t posLast = -1, bool bIgnoreCase = false) const;
	ptrdiff_t ReverseFind(int ch, size_t posLast = -1, bool bIgnoreCase = false) const;
	ptrdiff_t ReverseFind(char ch, size_t posLast = -1, bool bIgnoreCase = false) const;
	
	ptrdiff_t FindOneOf(const TXString &charSet, size_t posFirst = 0) const;
	ptrdiff_t ReverseFindOneOf(const TXString &charSet, size_t posLast = -1) const;
	
	ptrdiff_t FindNotOneOf(const TXString &charSet, size_t posFirst = 0) const;
	ptrdiff_t ReverseFindNotOneOf(const TXString &charSet, size_t posLast = -1) const;
	
	
	//***********************************************************************************
	// Surrogate functions
	//***********************************************************************************
	bool SurrogatePairAt(size_t nIndex) const;
	bool HasSurrogatePair() const;
	
	
	//***********************************************************************************
	// Creating substrings
	//***********************************************************************************
	TXString Mid(size_t nFirst, size_t len = -1) const;
	TXString Left(size_t len) const;
	TXString Right(size_t len) const;
	
	
	//***********************************************************************************
	// Conversion to and from numerics
	//***********************************************************************************
	Sint32 atoi() const;
	Sint64 atoi64() const;
	Real64 atof() const;
	TXString& itoa(Sint64 value);
	TXString& ftoa(Real64 value);
	TXString& ftoa(Real64 value, Sint32 precision);
	static TXString	ToStringInt(Sint64 value);
	static TXString	ToStringInt(Sint64 value, Sint32 width, wchar_t paddingChar);
	static TXString	ToStringReal(Real64 value);
	static TXString	ToStringReal(Real64 value, Sint32 precision, bool fixed=true);
	template<typename T>
	static TXString ToString(T value);
	template<typename T>
	static TXString ToStringHex(T value, bool upperCase = true, size_t symbolsCnt = size_t(-1));
	static bool ToDouble(const TXString& inString, double& outDouble, bool useOSLocale = false);
	
	
	//***********************************************************************************
	// Checking TXChar types
	//***********************************************************************************
	static bool IsPunctuation(TXChar aTXChar);
	static bool IsWhitespace(TXChar aTXChar);

	
	//***********************************************************************************
	// Comparison and plus operator
	//***********************************************************************************
	
	// Equality functions
	bool Equal(const TXString &str) const;
	bool EqualNoCase(const TXString &str) const;
	
	// Comparison functions
	Sint32 Compare(const TXString &str) const;
	Sint32 CompareNoCase(const TXString &str) const;

	// Comparison operators
	friend bool operator==(const TXString& lhs, const TXString& rhs);
	friend bool operator==(const TXString& lhs, const char* rhs);
	friend bool operator==(const char* lhs, const TXString& rhs);
	friend bool operator==(const TXString& lhs, const TXChar* rhs);
	friend bool operator==(const TXChar* lhs, const TXString& rhs);

	friend bool operator!=(const TXString& lhs, const TXString& rhs);
	friend bool operator!=(const TXString& lhs, const char* rhs);
	friend bool operator!=(const char* lhs, const TXString& rhs);
	friend bool operator!=(const TXString& lhs, const TXChar* rhs);
	friend bool operator!=(const TXChar* lhs, const TXString& rhs);

	friend bool operator<=(const TXString& lhs, const TXString& rhs);
	friend bool operator>=(const TXString& lhs, const TXString& rhs);

	friend bool operator<(const TXString& lhs, const TXString& rhs);
	friend bool operator>(const TXString& lhs, const TXString& rhs);
	
	// Plus operator
	friend TXString operator+(const TXString& lhs, const TXString& rhs);
	friend TXString operator+(const TXString& lhs, TXChar rhs);
	friend TXString operator+(TXChar lhs, const TXString& rhs);
	friend TXString operator+(const TXString& lhs, const TXChar* rhs);
	friend TXString operator+(const TXChar* lhs, const TXString& rhs);
	
	
	//***********************************************************************************
	// Formatting
	//***********************************************************************************
	
	// Strict type formatting functions to replace the Format function
	// It will substitute any %x in the string with the specified value. NOTE: No modifies supported
	// These use std::wstringstream and operator << to concatenate to the string
	// VisualStudio 2010 doesnt support variadic templates still, so i'm forced in doing this
	TXString&	Format(const TXString& format);
	template<typename T0>
	TXString&	Format(const TXString& format, const T0& val0);
	template<typename T0, typename T1>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1);
	template<typename T0, typename T1, typename T2>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2);
	template<typename T0, typename T1, typename T2, typename T3>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3);
	template<typename T0, typename T1, typename T2, typename T3, typename T4>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9, const T10& val10);
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
	TXString&	Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9, const T10& val10, const T11& val11);

	// static tool functions: Formatted
	template<typename T0>
	static TXString		Formatted(const TXString& format, const T0& val0)																											{ return TXString().Format( format, val0 ); }
	template<typename T0, typename T1>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1)																							{ return TXString().Format( format, val0, val1 ); }
	template<typename T0, typename T1, typename T2>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2)																			{ return TXString().Format( format, val0, val1, val2 ); }
	template<typename T0, typename T1, typename T2, typename T3>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3)															{ return TXString().Format( format, val0, val1, val2, val3 ); }
	template<typename T0, typename T1, typename T2, typename T3, typename T4>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4)											{ return TXString().Format( format, val0, val1, val2, val3, val4 ); }
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5)							{ return TXString().Format( format, val0, val1, val2, val3, val4, val5 ); }
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	static TXString		Formatted(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6)			{ return TXString().Format( format, val0, val1, val2, val3, val4, val5, val6 ); }

	//***********************************************************************************
	// Swap function
	//***********************************************************************************
	void swap(TXString& rhs)
    {
        std::swap(this->stdUStr, rhs.stdUStr);
    }
	
#if 1
	//***********************************************************************************
	// Methods we want to get rid of
	//***********************************************************************************
	// PStr
	template <size_t maxCharLen>
	TXString(const PStr<maxCharLen>& src)
		: charPtr(nullptr)
		, charBufSize(0)
	{
		char temp[256];
		strncpy(temp, (const char *)((const unsigned char *)src) + 1, src.GetLength());
		temp[src[0]] = 0;
		*this = temp;
	}
	
	template <size_t maxCharLen>
	TXString& operator=(const PStr<maxCharLen>& src)
	{
		char temp[256];
		strncpy(temp, (const char *)((const unsigned char *)src) + 1, src.GetLength());
		temp[src[0]] = 0;
		*this = temp;
		return *this;
	}
	
	template <size_t maxCharLen>
	const TXString& operator+=(const PStr<maxCharLen>& src)
	{
		char temp[256];
		strncpy(temp, (const char *)((const unsigned char *)src) + 1, src.GetLength());
		temp[src[0]] = 0;
		*this += temp;
		return *this;
	}
	
	template <size_t maxCharLen>
	TXString& operator<<(const PStr<maxCharLen>& src)
	{
		char temp[256];
		strncpy(temp, (const char *)((const unsigned char *)src) + 1, src.GetLength());
		temp[src[0]] = 0;
		*this += temp;
		return *this;
	}
	
#endif
	
	//***********************************************************************************
	// Private members
	//***********************************************************************************
private:
	StdUStr stdUStr;
	
	void SetStdUStrFromCharBuffer(const char* src, size_t len, ETXEncoding e = ETXEncoding::eUTF8);
	
	// For char buffer. TXString might be better to return a std::string instead of
	// returning const char* in the future.
	mutable char* charPtr;
	mutable int charBufSize;
	void PrepareCharBuffer(ETXEncoding e = ETXEncoding::eUTF8) const;

#if GS_MAC
	mutable std::wstring wStr;
#endif

	// Unit tests
	friend class SystemTests::TXStringSystemTest;
};


// Comparison operators
bool operator==(const TXString& lhs, const TXString& rhs);
bool operator==(const TXString& lhs, const char* rhs);
bool operator==(const char* lhs, const TXString& rhs);
bool operator==(const TXString& lhs, const TXChar* rhs);
bool operator==(const TXChar* lhs, const TXString& rhs);

bool operator!=(const TXString& lhs, const TXString& rhs);
bool operator!=(const TXString& lhs, const char* rhs);
bool operator!=(const char* lhs, const TXString& rhs);
bool operator!=(const TXString& lhs, const TXChar* rhs);
bool operator!=(const TXChar* lhs, const TXString& rhs);

bool operator<=(const TXString& lhs, const TXString& rhs);
bool operator>=(const TXString& lhs, const TXString& rhs);

bool operator<(const TXString& lhs, const TXString& rhs);
bool operator>(const TXString& lhs, const TXString& rhs);

// Plus operator
TXString operator+(const TXString& lhs, const TXString& rhs);
TXString operator+(const TXString& lhs, TXChar rhs);
TXString operator+(TXChar lhs, const TXString& rhs);
TXString operator+(const TXString& lhs, const TXChar* rhs);
TXString operator+(const TXChar* lhs, const TXString& rhs);

// Literal operators
TXString operator""_txs(const char* src, size_t len);
TXString operator""_txs(const wchar_t* src, size_t len);

// Non-member swap function
void swap(TXString& lhs, TXString& rhs);

namespace std
{
	// std::swap<TXString> specialization
	template<>
	inline void swap<TXString>(TXString& lhs, TXString& rhs)
    {
        lhs.swap(rhs);
    }

	// std::hash<TXString> specialization
	template<>
	struct hash<TXString>
	{
		size_t operator()(const TXString & str) const
		{
			return std::hash<std::u16string>{}(str.GetConstU16String());
		}
	};

}


//#######################################################################################
// TXStringArray
// Please refer to GSString.X.cpp for more detailed descriptions. [PChang]
//#######################################################################################

#if GS_WIN
typedef std::vector<TXString, TXAlloc<TXString>> StrVec;
#else
typedef std::vector<TXString> StrVec;
#endif

class TXStringArray
{
public:

	// Constructors and destructor
					TXStringArray(size_t nInitialSize = 0);				// Default constructor
					TXStringArray(std::initializer_list<TXString>);		// List initialization
					TXStringArray(const TXStringArray &src);			// Copy constructor
					TXStringArray(TXStringArray &&src);					// Move constructor
	virtual			~TXStringArray();									// Destructor

	// Assignment operators
	TXStringArray&	operator=(const TXStringArray &src);			// Copy assignment
	TXStringArray&	operator=(TXStringArray &&src);					// Move assignment
	TXStringArray&	operator=(std::initializer_list<TXString>);		// List assignment

	// Size related functions
	TXStringArray&	SetSize(size_t size);
	size_t			GetSize() const;
	bool			IsEmpty() const;

	// Element access
	TXStringArray&	SetAt(size_t nIndex, const TXString &string);
	const TXString&	GetAt(size_t nIndex) const;
	TXString&		GetAt(size_t nIndex);
	const TXString&	operator[](size_t nIndex) const;
	TXString&		operator[](size_t nIndex);

	// Append
	TXStringArray&	Append(const TXString &string);
	TXStringArray&	Append(const TXStringArray &src);

	// Prepend
	TXStringArray&	Prepend(const TXString &string);


	// Erase and clear
	TXStringArray&	Erase(size_t nIndex, size_t nCount = 1);
	TXStringArray&	Clear();

	// Find
	ptrdiff_t		Find(const TXString& str, bool bIgnoreCase = false) const;

	// Sort
	TXStringArray&	Sort(std::function<bool (const TXString&, const TXString&)> sortFunction = nullptr);

	// traversing functions to be used with C++11 for(auto it : arr)
	StrVec::iterator		begin();
	StrVec::iterator		end();
	StrVec::const_iterator	begin() const;
	StrVec::const_iterator	end() const;

private:
	StrVec			strVec;

	// Unit tests
	friend class SystemTests::TXStringSystemTest;
};


//---------------------------------------------------------------------------------------
// Replaces format specifiers (%d, %s, %.20s, %02d, etc.) with given parameters in a given string.
// Iterates through a list of parameters and for each one searches the original string
// for a format specifier that matches the parameter type.
// If no match is found, the format specifier is copied "as is" in the output result.
// The formating continues until end of source is reached.
//
// NOTES:
// 1. The order and type of the parameters need to match between what is expected and what is passed in.
// For example:
//    opstext.text1 = "This is a %s string and number = %d"
//
//    Unsafe code:
//       char buffer[100];
//       snprintf_Safe( buffer, sizeof(buffer), opstext.text1, "test", 123 );
//       snprintf_Safe( buffer, sizeof(buffer), "%s", opstext.text1 );
//       buffer = "This is a test string and number = 123"
//
//    Safe code - right way to use it:
//       char buffer[100];
//       CFormatString( opstext.text1, buffer, sizeof(buffer)).Param("test").Param(123).Format();
//       buffer = "This is a test string and number = 123"
//    Safe code - wrong way to use it:
//       char buffer[100];
//       CFormatString( opstext.text1, buffer, sizeof(buffer)).Param(123).Param("test").Format();
//       buffer = "This is a %s string and number = %d"
// NOTE:
// The following is not a supported scenario:
//    If the width specification is an asterisk(*), an int argument from the argument list supplies the value.
//    The width argument must precede the value that's being formatted in the argument list, as shown in this example:
//    printf("%0*f", 5, 3); /* 00003 is output */
//---------------------------------------------------------------------------------------
class CFormatString
{
public:
				CFormatString(const TXString& format);
	virtual		~CFormatString();

	TXString	Format();

	CFormatString&	Param(short value);
	CFormatString&	Param(int value);
	CFormatString&	Param(long value);
	CFormatString&	Param(long long value);
	CFormatString&	Param(unsigned short value);
	CFormatString&	Param(unsigned int value);
	CFormatString&	Param(unsigned long value);
	CFormatString&	Param(unsigned long long value);
	CFormatString&	Param(double value);
	CFormatString&	Param(const char value);
	CFormatString&	Param(const char* value);
	CFormatString&	Param(const wchar_t value);
	CFormatString&	Param(const wchar_t* value);
	CFormatString&	Param(const void* value);
	CFormatString&	Param(const TXString& value);

private:
	enum class EParamType
	{
		  PT_SHORT
		, PT_INT
		, PT_LONG
		, PT_LONGLONG
		, PT_USHORT
		, PT_UINT
		, PT_ULONG
		, PT_ULONGLONG
		, PT_REAL
		, PT_CHAR
		, PT_VOIDPTR
		, PT_STRING
	};

	struct SParameter
	{
		EParamType		fType;

		short				fValShort;
		long				fValLong;
		int					fValInt;
		long long			fValLongLong;
		unsigned short		fValUShort;
		unsigned int		fValUInt;
		unsigned long		fValULong;
		unsigned long long	fValULongLong;
		double				fValReal;
		wchar_t				fValChar;
		const void*			fValVoid;
		TXString			fValStr;

		SParameter()
		{
			fType			= EParamType::PT_INT;
			fValShort		= 0;
			fValLong		= 0;
			fValInt			= 0;
			fValLongLong	= 0;
			fValUShort		= 0;
			fValUInt		= 0;
			fValULong		= 0;
			fValULongLong	= 0;
			fValReal		= 0;
			fValChar		= 0;
			fValVoid		= nullptr;
		}

		short				GetValueShort() const;
		int					GetValueInt() const;
		long				GetValueLong() const;
		long long			GetValueLongLong() const;
		unsigned short		GetValueUShort() const;
		unsigned int		GetValueUInt() const;
		unsigned long		GetValueULong() const;
		unsigned long long	GetValueULongLong() const;
		double				GetValueReal() const;
		wchar_t				GetValueChar() const;
		const void*			GetValueVoidPtr() const;
		TXString			GetValueString() const;
	};

	// the string to format
	TXString	fStrToFormat;

	// output buffer and its size
	TXString	fOutBuffer;

	// list of parameters to process
	std::vector<SParameter>	farrParams;
};

template<typename T0>
TXString& TXString::Format(const TXString& format, const T0& val0)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	formatter.Param( val8 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	formatter.Param( val8 );
	formatter.Param( val9 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9, const T10& val10)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	formatter.Param( val8 );
	formatter.Param( val9 );
	formatter.Param( val10 );
	*this = formatter.Format();
	return *this;
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
TXString& TXString::Format(const TXString& format, const T0& val0, const T1& val1, const T2& val2, const T3& val3, const T4& val4, const T5& val5, const T6& val6, const T7& val7, const T8& val8, const T9& val9, const T10& val10, const T11& val11)
{
	CFormatString	formatter( format );
	formatter.Param( val0 );
	formatter.Param( val1 );
	formatter.Param( val2 );
	formatter.Param( val3 );
	formatter.Param( val4 );
	formatter.Param( val5 );
	formatter.Param( val6 );
	formatter.Param( val7 );
	formatter.Param( val8 );
	formatter.Param( val9 );
	formatter.Param( val10 );
	formatter.Param( val11 );
	*this = formatter.Format();
	return *this;
}

// A wrapper of std::to_string(...)
template<typename T>
/*static*/ TXString TXString::ToString(T value)
{
	return std::to_string(value);
}

template<typename T>
/*static*/ TXString TXString::ToStringHex(T value, bool upperCase, size_t symbolsCnt)
{
	static const TXChar arrUpperByteChars[] = { TXChar('0'), TXChar('1'), TXChar('2'), TXChar('3'), TXChar('4'), TXChar('5'), TXChar('6'), TXChar('7'),  TXChar('8'), TXChar('9'), TXChar('A'), TXChar('B'), TXChar('C'), TXChar('D'), TXChar('E'), TXChar('F') };
	static const TXChar arrLowerByteChars[] = { TXChar('0'), TXChar('1'), TXChar('2'), TXChar('3'), TXChar('4'), TXChar('5'), TXChar('6'), TXChar('7'),  TXChar('8'), TXChar('9'), TXChar('a'), TXChar('b'), TXChar('c'), TXChar('d'), TXChar('e'), TXChar('f') };
	const TXChar* arrChars = upperCase ? arrUpperByteChars : arrLowerByteChars;

	TXString result;
	if ( symbolsCnt > 0 )
	{
		const char* p = (const char*)&value;
		p += sizeof(T) - 1;

		bool beginning = true;
		size_t iSymCnt = 2 * sizeof(T);
		if ( symbolsCnt != size_t(-1) && symbolsCnt > iSymCnt )
		{
			for(size_t i=iSymCnt; i<symbolsCnt; i++)
				result += TXChar('0');
			symbolsCnt = iSymCnt;
		}

		for(size_t iByte=0; iByte<sizeof(T); ++iByte, --p)
		{
			if ( beginning && *p == 0 && (symbolsCnt == size_t(-1) || (iSymCnt-2) > symbolsCnt))
			{
				iSymCnt--;
				iSymCnt--;
			}
			else
			{
				beginning = true;

				char ch1 = *p & 0x0F;
				char ch2 = (*p & 0xF0)>>4;
				if ( iSymCnt <= symbolsCnt) result += arrChars[ ch2 ];
				iSymCnt--;
				if ( iSymCnt <= symbolsCnt) result += arrChars[ ch1 ];
				iSymCnt--;
			}
		}
	}

	return result;
}


template <size_t maxCharLen>
PStr<maxCharLen>& PStr<maxCharLen>::operator<<(Sint32 n)
{
	PStr<15> s;
	s.Format("%ld", n);
	StringCat(buf, s, maxCharLen+1);
	return *this;
}

template <size_t maxCharLen>
PStr<maxCharLen>& PStr<maxCharLen>::operator<<(Sint64 n)
{
	PStr<32> s;
	s.Format(PRId64, n);
	StringCat(buf, s, maxCharLen+1);
	return *this;
}

template <size_t maxCharLen>
Sint32 PStr<maxCharLen>::Find(Uint8 start, char ch) const
{
	if (start > 0)
		for (Uint8 i = start; i <= GetLength(); ++i)
			if (buf[i] == ch) return i;
	return 0;
}

template <size_t maxCharLen>
Sint32 PStr<maxCharLen>::ReverseFind(Uint8 start, char ch) const
{
	if (start > GetLength())
		start = GetLength();
	for (Uint8 i = start; i > 0; --i)
		if (buf[i] == ch) return i;
	return 0;
}

template <size_t maxCharLen>
PStr<maxCharLen> PStr<maxCharLen>::Mid(Uint8 start, Uint8 count) const
{
	if (start > GetLength())
		count = 0;
	else if (start + count - 1 > GetLength())
		count = GetLength() - start + 1;
	
	return PStr<maxCharLen>(&buf[start], count);
}

template <size_t maxCharLen>
Uint8 PStr<maxCharLen>::Format(ConstGSStr255Param format, ...)
{
	va_list ap;
	va_start(ap, format);

	char szFormat[256];
	StringCopy(format, szFormat, 256);

	this->buf[0] = vsprintf((char*) &this->buf[1], szFormat, ap);

	va_end(ap);
	return this->buf[0];
}

template <size_t maxCharLen>
Uint8 PStr<maxCharLen>::Format(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	this->buf[0] = vsprintf((char*) &this->buf[1], format, ap);

	va_end(ap);
	return this->buf[0];
}

template <size_t maxCharLen> PStr<maxCharLen>&  PStr<maxCharLen>::operator=(const TXString& s)
{
	StringCopy((const char *)s, buf, maxCharLen+1);
	return *this;
}

template <size_t maxCharLen> PStr<maxCharLen>::PStr(const TXString& s)
{
	StringCopy((const char *)s, buf, maxCharLen+1);
}

/////////////////////////////////////////////////////////////////////////////////////////
// convenicence std library version functions
/////////////////////////////////////////////////////////////////////////////////////////

#if GS_WIN
inline size_t UCStrLen(ConstUCStrPtr s)						{ return wcslen((const wchar_t*)s); }
inline size_t UCStrLen(const wchar_t* s)					{ return wcslen(s); }
inline int    UCStrCmp(ConstUCStrPtr s1, ConstUCStrPtr s2)	{ return wcscmp((const wchar_t*)s1, (const wchar_t*)s2); }
inline void   UCStrCpy(UCStrPtr dest, ConstUCStrPtr src)    { wcscpy((wchar_t*)dest, (const wchar_t*)src); }
#else
inline size_t UCStrLen(ConstUCStrPtr s)						{ return StdUStr((const TXChar*)s).length(); }
inline int    UCStrCmp(ConstUCStrPtr s1, ConstUCStrPtr s2)	{ return StdUStr((const TXChar*)s1).compare((const TXChar*)s2); }
inline void   UCStrCpy(UCStrPtr dest, ConstUCStrPtr src)    { StdUStr in((const TXChar*)src); memcpy(dest, in.c_str(), (in.length() + 1) * 2); }
#endif

inline size_t UCByteLen(ConstUCStrPtr s)					{ return (UCStrLen(s) + 1) * sizeof(UCChar); }
