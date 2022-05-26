//
//	Copyright (c) Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// TXString class implementation.
//


/* Includes */
/* -------- */
#include "StdHeaders.h"

#define _GSString_X_

#include <ctype.h>  // Do not change to <cctype> to avoid platform conflict on
                    //  whether toupper and tolower are in the "std" namespace
#include <stdarg.h>

#include <iostream>
#include <codecvt>
#include <iomanip>

#if _WINDOWS
	
	#include <Usp10.h>
#else
	#include <ctype.h>
#endif

#if _WINDOWS
	#include "Shlwapi.h"
#endif

#if GS_WIN
	// For Unicode normalization form (precomposed v.s. decomposed)
	#include <WinNls.h>
#endif

#if GS_MAC
#include <CoreFoundation/CoreFoundation.h>
#endif

#if GS_WIN	// Windows
	#include <Windows.h>  
	#include <MBCType.h>
	#include <MBString.h>
#else	// Mac
	#include <Carbon/Carbon.h>
#endif


#if _MINICAD_
# define GS_CORE_BUILD 1
#endif

#if _MINICAD_
	#include "../../../../../Include/CoreAPI.X.h"
#else
	#define ASSERTCLASS(kEveryone, charSet)

    #ifdef NEW_NOTHROW
    #undef NEW_NOTHROW
    #endif

	#define NEW_NOTHROW new
#endif

// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE


inline void utf32ToTXCharBuffer(char32_t input, TXChar* output);
inline size_t utf32BufferToTXCharBuffer(const char32_t* input, size_t inputLen, TXChar* output);
inline void txCharBufferToUtf32Buffer(const TXChar* input, size_t inputLen, char32_t* output, size_t outputLen);
inline size_t utf8BufferToTXCharBuffer(const char* input, size_t inputLen, TXChar* output);


//#######################################################################################
// TXString class
//#######################################################################################

//***********************************************************************************
// Constructors and destructor
//***********************************************************************************

//=======================================================================================
// Default constructor
TXString::TXString()
	: charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Copy constructor
TXString::TXString(const TXString& src)
	: stdUStr(src.stdUStr)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Move constructor
TXString::TXString(TXString&& src)
	: stdUStr(std::move(src.stdUStr))
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Copy constructor from StdUstr
TXString::TXString(const StdUStr& src)
	: stdUStr(src)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Move constructor from StdUStr
TXString::TXString(StdUStr&& src)
	: stdUStr(std::move(src))
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Construct from a std string. On Windows, invalid chars are replaced with replacement
// characters. On Mac, the string is empty if there is any invalid chars.
TXString::TXString(const std::string& src,
				   ETXEncoding e)		// ETXEncoding::eUTF8
	: charPtr(nullptr)
	, charBufSize(0)
{
	SetStdUStrFromCharBuffer(src.data(), src.length(), e);
}

//=======================================================================================
// Construct from a std wstring.
#if GS_WIN

TXString::TXString(const std::wstring& src)
	: charPtr(nullptr)
	, charBufSize(0)
	, stdUStr(src.data())
{
}

#else

TXString::TXString(const std::wstring& src)
	: charPtr(nullptr)
	, charBufSize(0)
{
	stdUStr.resize(src.length() * 2);
	size_t len = utf32BufferToTXCharBuffer((const char32_t*)src.data(), src.length(), &stdUStr[0]);
	stdUStr.resize(len);
}

#endif

//=======================================================================================
// Construct from CFStringRef&
#if GS_MAC
TXString::TXString(const CFStringRef& src)
	: charPtr(nullptr)
	, charBufSize(0)
{
	// Get number of characters.
	CFIndex len = CFStringGetLength(src);
	
	// Resize stdUStr
	stdUStr.resize(len);
	
	// Copy string data to UniChar buffer.
	CFStringGetCharacters(src, CFRangeMake(0, len), &stdUStr[0]);
}

#endif

//=======================================================================================
// Construct with initial size. size_t version.
TXString::TXString(size_t nInitialSize)
	: stdUStr(nInitialSize, 0)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Construct with initial capacity. int version.
TXString::TXString(int nInitialSize)
	: stdUStr(nInitialSize, 0)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Construct from a char buffer. On Windows, invalid chars are replaced with replacement
// characters. On Mac, the string is empty if there is any invalid chars.
TXString::TXString(const char* src,
				   ETXEncoding e)		// ETXEncoding::eUTF8
	: charPtr(nullptr)
	, charBufSize(0)
{
	if (src)
	{
		SetStdUStrFromCharBuffer(src, strlen(src), e);
	}
}

//=======================================================================================
// Construct from a char buffer. On Windows, invalid chars are replaced with replacement
// characters. On Mac, the string is empty if there is any invalid chars.
TXString::TXString(const char* src,
				   size_t lenInBytes,
				   ETXEncoding e)		// ETXEncoding::eUTF8
	: charPtr(nullptr)
	, charBufSize(0)
{
	if (src && lenInBytes != (size_t)-1)
	{
		SetStdUStrFromCharBuffer(src, lenInBytes, e);
	}
}

//=======================================================================================
// Construct from unsigned char buffer. UTF-8 is the default encoding.
TXString::TXString(const unsigned char* src,
				   ETXEncoding e)		// ETXEncoding::eUTF8
	: charPtr(nullptr)
	, charBufSize(0)
{
	if(src && *src != 0)
	{
		SetStdUStrFromCharBuffer((const char *)src + 1, src[0], e);
	}
}

//=======================================================================================
// Construct from an unsiged short buffer.
TXString::TXString(const UCChar* src)
	: charPtr(nullptr)
	, charBufSize(0)
	, stdUStr(src ? (const TXChar *) src : txu(""))
{
}

//=======================================================================================
// Construct from an untrusted UCChar buffer, which may or may not be terminated.
// maxUCChars is typically the maximum size of the buffer, but could be the string length.
// If eLengthCheck is eYes, assume the worst and search for size of the string.
// If eLengthCheck is eNo, assume the string is exactly max in length.
TXString::TXString(const UCChar* src, size_t maxUCChars, ELengthCheck eLengthCheck)
	: charPtr(nullptr)
	, charBufSize(0)
	, stdUStr(
		src && eLengthCheck == ELengthCheck::eNo ? (const TXChar *)src : txu(""), 
		src && eLengthCheck == ELengthCheck::eNo ? maxUCChars : 0)
{
#if RBerge
	if (src && maxUCChars > std::numeric_limits<Uint16>::max()-1) { // arbitrarily too large size for a string
		DSTOP((kRBerge, "suspiciously large TXString buffer; we may soon crash\n"));
	}
#endif

	if (src && eLengthCheck == ELengthCheck::eYes)
	{
		size_t length = 0;
		while (length < maxUCChars && src[length] != 0) ++length;

		stdUStr.assign((const TXChar*)src, length);
	}
}

//=======================================================================================
// Construct from a wchar_t buffer.
#if GS_WIN

TXString::TXString(const wchar_t* src)
	: charPtr(nullptr)
	, charBufSize(0)
	, stdUStr(src ? src : txu(""))
{
}

#else	// Mac

TXString::TXString(const wchar_t* src)
	: charPtr(nullptr)
	, charBufSize(0)
{
	if(src)
	{
		stdUStr.resize(wcslen(src) * 2);	// Allocate enough memory.
		size_t len = utf32BufferToTXCharBuffer((const char32_t*)src, wcslen(src), &stdUStr[0]);
		stdUStr.resize(len);				// Set correct length.
	}
}

#endif

//=======================================================================================
// Construct from an untrusted wchar_t buffer, which may or may not be terminated.
// maxWChars is typically the maximum size of the buffer, but could be the string length.
// If eLengthCheck is eYes, assume the worst and search for size of the string.
// If eLengthCheck is eNo, assume the string is exactly max in length.
#if GS_WIN

TXString::TXString(const wchar_t* src, size_t maxWChars, ELengthCheck eLengthCheck)
	: charPtr(nullptr)
	, charBufSize(0)
	, stdUStr(
		src && eLengthCheck == ELengthCheck::eNo ? src : txu(""), 
		src && eLengthCheck == ELengthCheck::eNo ? maxWChars : 0)
{
#if RBerge
	if (src && maxWChars > std::numeric_limits<Uint16>::max()-1) { // arbitrarily too large size for a string
		DSTOP((kRBerge, "suspiciously large TXString buffer; we may soon crash\n"));
	}
#endif
	
	if (src && eLengthCheck == ELengthCheck::eYes)
	{
		size_t length = 0;
		while (length < maxWChars && src[length] != 0) ++length;

		stdUStr.assign((const TXChar*)src, length);
	}
}

#else	// Mac

TXString::TXString(const wchar_t* src, size_t maxWChars, ELengthCheck eLengthCheck)
	: charPtr(nullptr)
	, charBufSize(0)
{
#if RBerge
	if (src && maxWChars > std::numeric_limits<Uint16>::max()-1) { // arbitrarily too large size for a string
		DSTOP((kRBerge, "suspiciously large TXString buffer; we may soon crash\n"));
	}
#endif
	
	if (src)
	{
		size_t length = maxWChars;

		if (eLengthCheck == ELengthCheck::eYes)
		{
			length = 0;
			while (length < maxWChars && src[length] != 0) ++length;
		}

		stdUStr.resize(length * 2);
		size_t len = utf32BufferToTXCharBuffer((const char32_t*)src, length, &stdUStr[0]);
		stdUStr.resize(len);
	}
}

#endif

//=======================================================================================
// Fill the string with "count" number of "ch"
TXString::TXString(char ch, size_t count /* 1 */)
	: stdUStr(count, (unsigned char)ch)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Fill the string with "count" number of "ch"
TXString::TXString(unsigned char ch, size_t count /* 1 */)
	: stdUStr(count, ch)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Fill the string with "count" number of "ch"
TXString::TXString(UCChar ch, size_t count /* 1 */)
	: stdUStr(count, ch)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

//=======================================================================================
// Fill the string with "count" number of "ch"
#if GS_WIN

TXString::TXString(wchar_t ch, size_t count /* 1 */)
	: stdUStr(count, ch)
	, charPtr(nullptr)
	, charBufSize(0)
{
}

#else

TXString::TXString(wchar_t w, size_t count /* 1 */)
	: charPtr(nullptr)
	, charBufSize(0)
{
	if((int)w <= 0xffff)
	{
		stdUStr.assign(count, (TXChar) w);
	}
	else
	{
		UCChar u[3];
		utf32ToTXCharBuffer((char32_t)w, u);

		for(int i = 0; i < count; ++i)
		{
			stdUStr.append(u);
		}
	}
}

#endif

//=======================================================================================
// Destructor
TXString::~TXString()
{
	if(charPtr) gVWMM->TXStringDeallocate(charPtr);
}


//***********************************************************************************
// Assignments
//***********************************************************************************

//=======================================================================================
// Copy assignment operator
TXString& TXString::operator=(const TXString& src)
{
	stdUStr = src.stdUStr;
	return *this;
}

//=======================================================================================
// Move assignment operator
TXString& TXString::operator=(TXString&& src)
{
	stdUStr = std::move(src.stdUStr);
	return *this;
}

//=======================================================================================
// Assignment operator from std::string
TXString& TXString::operator=(const std::string& src)
{
	SetStdUStrFromCharBuffer(src.data(), src.length());
	return *this;
}

//=======================================================================================
// Assignment operator from std::wstring
TXString& TXString::operator=(const std::wstring& src)
{
#if GS_WIN
	stdUStr = src.data();
#else
	stdUStr.resize(src.length() * 2);
	size_t len = utf32BufferToTXCharBuffer((const char32_t*)src.data(), src.length(), &stdUStr[0]);
	stdUStr.resize(len);
#endif
	return *this;
}

#if GS_MAC
//=======================================================================================
// Construct from CFStringRef&
TXString& TXString::operator=(const CFStringRef& src)
{
	// Get number of characters.
	CFIndex len = CFStringGetLength(src);
	
	// Resize stdUStr.
	stdUStr.resize(len);
	
	// Copy string data to UniChar buffer.
	CFStringGetCharacters(src, CFRangeMake(0, len), &stdUStr[0]);
	
	// Return self reference.
	return *this;
}

#endif

//=======================================================================================
// Assignment from a const char buffer. UTF-8 is the encoding. If 'src' is 
// nullptr, the string is cleared.
TXString& TXString::operator=(const char* src)
{
	if(src)
	{
		SetStdUStrFromCharBuffer(src, strlen(src));
	}
	else
	{
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Assignment from a const unsigned char buffer. UTF-8 encoding is assumed. If 'src' is
// nullptr, the string is cleared.
TXString& TXString::operator=(const unsigned char* src)
{
	if(src && *src != 0)
	{
		SetStdUStrFromCharBuffer((const char *)src + 1, src[0]);
	}
	else
	{
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Assignment from a const UCChar buffer. If 'src' is nullptr, the string is cleared.
TXString& TXString::operator=(const UCChar* src)
{
	if(src)
	{
		stdUStr = (const TXChar*) src;
	}
	else
	{
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Assignment from a const wchar_t buffer. If 'src' is nullptr, the string is cleared.
TXString& TXString::operator=(const wchar_t* src)
{
	if(src)
	{
#if GS_WIN
		stdUStr = src;
#else
		stdUStr = std::move(TXString(src).stdUStr);
#endif
	}
	else
	{
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Assignment from a char
TXString& TXString::operator=(char ch)
{
	// On Windows, char to wchar_t conversion is not what is expected. Thus, char is
	// converted to unsigned char.
	stdUStr = (unsigned char) ch;
	return *this;
}

//=======================================================================================
// Assignment from an unsigned char
TXString& TXString::operator=(unsigned char ch)
{
	stdUStr = ch;
	return *this;
}

//=======================================================================================
// Assignment from an UCChar
TXString& TXString::operator=(UCChar ch)
{
	stdUStr = (TXChar) ch;
	return *this;
}

//=======================================================================================
// Assignment from an wchar_t
TXString& TXString::operator=(wchar_t w)
{
#if GS_WIN
	stdUStr = w;
#else
	if((int) w <= 0xffff)
	{
		stdUStr = (TXChar) w;
	}
	else
	{
		UCChar u[3];
		utf32ToTXCharBuffer((char32_t)w, u);
		stdUStr = u;
	}
#endif

	return *this;
}

//=======================================================================================
// Assignment from a Unicode code point. For example: txString = 0x27.
TXString& TXString::operator=(int n)
{
	if(n < 0 || n > 0x10FFFF)
	{
		stdUStr.clear();
	}
	else
	{
		if(n <= 0xffff)
		{
			stdUStr = (TXChar) n;
		}
		else
		{
			TXChar u[3];
			utf32ToTXCharBuffer((char32_t)n, u);
			stdUStr = u;
		}
	}

	return *this;
}


//***********************************************************************************
// Length related functions
//***********************************************************************************

//=======================================================================================
// Returns the number of characters. The terminal null character is NOT included.
size_t TXString::GetLength() const
{
	return stdUStr.length();
}

//=======================================================================================
// Return the size in bytes. Terminal character is not counted.
size_t TXString::GetByteSize() const
{
	return (stdUStr.length() * sizeof(TXChar));
}

//=======================================================================================
// Returns the number of bytes when encoding is Mac, Win, Sys, or UTF-8. Returns the 
// number of UTF-16 code points when the encoding is UTF-16. UTF-16 encoding is added to 
// support LenEncoding(...) VS function. To get the number of UTF-16 code points in C++
// code, TXString::GetLength() should be used. Terminal character is not counted.
size_t TXString::GetEncodingLength(ETXEncoding e) const
{
	size_t encodingLen = 0;

	if(e == ETXEncoding::eUTF16)
	{
		encodingLen = stdUStr.length();
	}
	else
	{
		PrepareCharBuffer(e);
		encodingLen = strlen(charPtr);
	}

	return encodingLen;
}

//=======================================================================================
// Return true if string is empty. Return false otherwise.
bool TXString::IsEmpty() const
{
	return stdUStr.empty();
}

//======================================================================================= 
// Resize to 'len' characters. If len is longer than the content, '\0' is padded to the 
// end. Return TXString itself.
TXString& TXString::SetLength(size_t len)
{
	stdUStr.resize(len);
	TrimRightInvalidCharacter();

	return *this;
}

//=======================================================================================
// Resize to 'len' characters. If len is longer than the content, 'ch' is padded to the 
// end. Return TXString itself.
TXString& TXString::SetLength(size_t len, TXChar ch)
{
	stdUStr.resize(len, ch);
	TrimRightInvalidCharacter();
	
	return *this;
}

//=======================================================================================
// Keep 'len' number of characters and reduce the length to 'len'. Null character is not
// counted in 'len'. If len is not less than the current length, does nothing.
TXString& TXString::Truncate(size_t len)
{
	if (len < stdUStr.length())
	{
		stdUStr.resize(len);
		TrimRightInvalidCharacter();
	}

	return *this;
}

//=======================================================================================
// Erase the contents. TXString becomes empty and length is zero.
TXString& TXString::Clear()
{
	stdUStr.clear();

	return *this;
}


//***********************************************************************************
// Element access
//***********************************************************************************

//=======================================================================================
// Return the reference of character at 'nIndex'. If 'nIndex' is invalid, a reference to
// a static TXChar (zero) is returned.
TXChar& TXString::operator[](ptrdiff_t nIndex)
{
	if(nIndex >= 0 && nIndex < (ptrdiff_t)stdUStr.length())
	{
		return stdUStr[nIndex];
	}
	else
	{
		static TXChar zero;
		zero = 0;
		return zero;
	}
}

//=======================================================================================
// Return a copy of character at index 'nIndex'. If nIndex is out of range, 0 is returned.
TXChar TXString::operator[](ptrdiff_t nIndex) const
{
	if(nIndex >= 0 && nIndex < (ptrdiff_t)stdUStr.length())
	{
		return stdUStr[nIndex];
	}
	else
	{
		return 0;
	}
}

//=======================================================================================
// Return a reference of the character at index 'nIndex'. If nIndex is out of range, a 
// reference to a static TXChar (zero) is returned.
TXChar& TXString::GetAt(size_t nIndex)
{
	if(nIndex < stdUStr.length())
	{
		return stdUStr[nIndex];
	}
	else
	{
		static TXChar zero;
		zero = 0;
		return zero;
	}
}

//=======================================================================================
// Return a copy of the character at index 'nIndex'. If nIndex is out of range, 0 is
// returned.
TXChar TXString::GetAt(size_t nIndex) const
{
	if(nIndex < stdUStr.length())
	{
		return stdUStr[nIndex];
	}
	else
	{
		return 0;
	}
}

//=======================================================================================
// Return a reference of the last character. If this string is empty, returns dummy ref.
TXChar& TXString::GetLast()
{
	if(stdUStr.empty())
	{
		static TXChar zero;
		zero = 0;
		return zero;
	}
	else
	{
		return stdUStr.back();
	}
}

//=======================================================================================
// Return a copy of the last character. If this string is empty, returns 0.
TXChar TXString::GetLast() const
{
	if(stdUStr.empty())
	{
		return 0;
	}
	else
	{
		return stdUStr.back();
	}
}

//=======================================================================================
// Set character at index 'nIndex' to 'ch'. If nIndex is out of range, does nothing.
TXString& TXString::SetAt(size_t nIndex, TXChar ch)
{
	if(nIndex < stdUStr.length())
	{
		stdUStr[nIndex] = ch;
	}
	
	return *this;
}


//***************************************************************************************
// Concatenation
//***************************************************************************************

//=======================================================================================
// Extends string by appending another TXString object
TXString& TXString::operator+=(const TXString& src)
{
	stdUStr += src.stdUStr;
	return *this;
}

//=======================================================================================
// Concatenate const char buffer (UTF-8). If 'src' is nullptr, does nothing.
TXString& TXString::operator+=(const char* src)
{
	if(src != nullptr)
	{
		stdUStr += TXString(src).stdUStr;
	}
	
	return *this;
}

//=======================================================================================
// Concatenate const unsigned char buffer (UTF-8). If 'src' is nullptr, does nothing.
TXString& TXString::operator+=(const unsigned char *src)
{
	if(src && *src != 0)
	{
		stdUStr += TXString(src).stdUStr;
	}

	return *this;
}

//=======================================================================================
// Concatenate const UCChar buffer. If 'src' is nullptr, does nothing.
TXString& TXString::operator+=(const UCChar* src)
{
	if(src != nullptr)
	{
		stdUStr += (const TXChar*) src;
	}
	
	return *this;
}

//=======================================================================================
// Concatenate const wchar_t buffer. If 'src' is nullptr, does nothing.
TXString& TXString::operator+=(const wchar_t* src)
{
	if(src != nullptr)
	{
#if GS_WIN
		stdUStr += src;
#else
		stdUStr += TXString(src).stdUStr;
#endif
	}
	
	return *this;
}

//=======================================================================================
// Appends one char
TXString& TXString::operator+=(char ch)
{
	stdUStr += (unsigned char)ch;	// The casting is necessary on Windows.
	return *this;
}

//=======================================================================================
// Appends one unsigned char
TXString& TXString::operator+=(unsigned char ch)
{
	stdUStr += (TXChar)ch;
	return *this;
}

//=======================================================================================
// Appends one UCChar
TXString& TXString::operator+=(UCChar ch)
{
	stdUStr += (TXChar)ch;
	return *this;
}

//=======================================================================================
// Appends one wchar_t
TXString& TXString::operator+=(wchar_t w)
{
#if GS_WIN
	stdUStr += w;
#else
	if((int) w <= 0xffff)
	{
		stdUStr += (TXChar) w;
	}
	else
	{
		UCChar u[3];
		utf32ToTXCharBuffer(w, u);
		stdUStr += u;
	}
#endif

	return *this;
}

//=======================================================================================
// Appends one Unicode code number. If 'w' is not in the valid range, does nothing.
TXString& TXString::operator+=(int n)
{
	if(n >= 0 && n <= 0x10ffff)
	{
		if(n <= 0xffff)
		{
			stdUStr += (TXChar) n;
		}
		else
		{
			TXChar u[3];
			utf32ToTXCharBuffer(n, u);
			stdUStr += u;
		}
	}

	return *this;
}

//=======================================================================================
// Concatenates another TXString object
TXString& TXString::operator<<(const TXString& src)
{
	return (*this += src);
}

//=======================================================================================
// Concatenates char buffer (UTF-8). If 'src' is nullptr, does nothing.
TXString& TXString::operator<<(const char* src)
{
	return (*this += src);
}

//=======================================================================================
// Concatenates unsigned char buffer (UTF-8). If 'src' is nullptr, does nothing.
TXString& TXString::operator<<(const unsigned char *src)
{
	return (*this += src);
}

//=======================================================================================
// Concatenates UCChar buffer. If 'src' is nullptr, does nothing.
TXString& TXString::operator<<(const UCChar* src)
{
	return (*this += src);
}

//=======================================================================================
// Concatenates wchar_t buffer. If 'src' is nullptr, does nothing.
TXString& TXString::operator<<(const wchar_t* src)
{
	return (*this += src);
}

//=======================================================================================
// Appends one char
TXString& TXString::operator<<(char ch)
{
	return (*this += ch);
}

//=======================================================================================
// Appends one unsigned char
TXString& TXString::operator<<(unsigned char ch)
{
	return (*this += ch);
}

//=======================================================================================
// Appends one UCChar
TXString& TXString::operator<<(UCChar ch)
{
	return (*this += ch);
}

//=======================================================================================
// Appends one wchar_t
TXString& TXString::operator<<(wchar_t ch)
{
	return (*this += ch);
}

//=======================================================================================
// Appends signed int 32 number as string
TXString& TXString::operator<<(Sint32 n)
{
	return (*this += std::to_string(n).data());
}

//=======================================================================================
// Appends one signed int 64 number as string
TXString& TXString::operator<<(Sint64 n)
{
	return (*this += std::to_string(n).c_str());
}

//=======================================================================================
// Appends unsigned int 32 number as string
TXString& TXString::operator<<(Uint32 n)
{
	return (*this += std::to_string(n).c_str());
}

//=======================================================================================
// Appends one unsigned int 64 number as string
TXString& TXString::operator<<(Uint64 n)
{
	return (*this += std::to_string(n).c_str());
}

//=======================================================================================
// Appends one real number
TXString& TXString::operator<<(double number)
{
	return (*this += std::to_string(number).c_str());
}

//=======================================================================================
// Appends one size_t number as string
#if GS_MAC // Uint64 is different than size_t on the mac
TXString& TXString::operator<<(size_t n)
{
	return (*this += std::to_string(n).c_str());
}
#endif

//=======================================================================================
// Appends one handle as a string
TXString& TXString::operator<<(const GSHandle h) // as a string
{
	return (*this += std::to_string((size_t)h).c_str());
}


//***************************************************************************************
// Insertion and deletion
//***************************************************************************************

//=======================================================================================
// Insert another TXString at position 'pos'. If pos is larger than length, the new
// string is append to the end.
TXString& TXString::Insert(size_t pos, const TXString& src)
{
	if(pos < stdUStr.length())
	{
		stdUStr.insert(pos, src.stdUStr);
	}
	else
	{
		stdUStr.append(src.stdUStr);
	}

	return *this;
}

//=======================================================================================
// Insert one const char buffer at position 'pos'. If pos is larger than length, the new
// string is append to the end. UTF-8 is assumed.
TXString& TXString::Insert(size_t pos, const char* src)
{
	if(src != nullptr)
	{
		Insert(pos, TXString(src));
	}
	
	return *this;
}

//=======================================================================================
// Insert unsigned char buffer at position 'pos'. If pos is larger than length, the new
// string is append to the end. UTF-8 is assumed.
TXString& TXString::Insert(size_t pos, const unsigned char* src)
{
	if(src != nullptr)
	{
		Insert(pos, TXString(src));
	}
	
	return *this;
}

//=======================================================================================
// Insert UCChar buffer at position 'pos'. If pos is larger than length, the new
// string is append to the end.
TXString& TXString::Insert(size_t pos, const UCChar* src)
{
	if(src != nullptr)
	{
		if(pos < stdUStr.length())
		{
			stdUStr.insert(pos, (const TXChar*) src);
		}
		else
		{
			stdUStr.append((const TXChar*) src);
		}
	}

	return *this;
}

//=======================================================================================
// Insert wchar_t buffer at position 'pos'. If pos is larger than length, the new
// string is append to the end.
TXString& TXString::Insert(size_t pos, const wchar_t* src)
{
	if(src != nullptr)
	{
#if GS_WIN
		if(pos < stdUStr.length())
		{
			stdUStr.insert(pos, src);
		}
		else
		{
			stdUStr.append(src);
		}
#else
		if(pos < stdUStr.length())
		{
			stdUStr.insert(pos, TXString(src).stdUStr);
		}
		else
		{
			stdUStr.append(TXString(src).stdUStr);
		}
#endif
	}

	return *this;
}

//=======================================================================================
// Insert one character 'ch' at position 'pos'. If pos is larger than length, the new
// character is append to the end.
TXString& TXString::Insert(size_t pos, char ch)
{
	if(pos < stdUStr.length())
	{
		stdUStr.insert(pos, 1, (unsigned char) ch);	// The casting is necessary.
	}
	else
	{
		stdUStr.append(1, (unsigned char) ch);
	}

	return *this;
}

//=======================================================================================
// Insert one character 'ch' at position 'pos'. If pos is larger than length, the new
// character is append to the end.
TXString& TXString::Insert(size_t pos, unsigned char ch)
{
	if(pos < stdUStr.length())
		stdUStr.insert(pos, 1, ch);
	else
		stdUStr.append(1, ch);

	return *this;
}

//=======================================================================================
// Insert one character 'ch' at position 'pos'. If pos is larger than length, the new
// character is append to the end.
TXString& TXString::Insert(size_t pos, UCChar ch)
{
	if(pos < stdUStr.length())
		stdUStr.insert(pos, 1, (TXChar) ch);
	else
		stdUStr.append(1, (TXChar) ch);

	return *this;
}

//=======================================================================================
// Insert one character 'ch' at position 'pos'. If pos is larger than length, the new
// character is append to the end.
TXString& TXString::Insert(size_t pos, wchar_t w)
{
#if GS_WIN
	if(pos < stdUStr.length())
	{
		stdUStr.insert(pos, 1, w);
	}
	else
	{
		stdUStr.append(1, w);
	}
	
#else
	if((int) w <= 0xffff)
	{
		if(pos < stdUStr.length())
		{
			stdUStr.insert(pos, 1, (TXChar) w);
		}
		else
		{
			stdUStr.append(1, (TXChar) w);
		}
	}
	else
	{
		UCChar u[3];
		utf32ToTXCharBuffer(w, u);
		
		if(pos < stdUStr.length())
		{
			stdUStr.insert(pos, u);
		}
		else
		{
			stdUStr.append(u);
		}
	}
#endif

	return *this;
}

//=======================================================================================
// Insert one character 'ch' at position 'pos'. If pos is larger than length, the new
// character is append to the end.
TXString& TXString::Insert(size_t pos, int n)
{
	if(n <= 0xffff)
	{
		if(pos < stdUStr.length())
		{
			stdUStr.insert(pos, 1, (TXChar) n);
		}
		else
		{
			stdUStr.append(1, (TXChar) n);
		}
	}
	else
	{
		TXChar u[3];
		utf32ToTXCharBuffer(n, u);
		
		if(pos < stdUStr.length())
		{
			stdUStr.insert(pos, u);
		}
		else
		{
			stdUStr.append(u);
		}
	}

	return *this;
}

//=======================================================================================
// Erases characters starting from 'pos' for 'len' characters. If 'pos' is greater than
// the length, nothing happens. If 'len' is larger than the number of characters could be
// removed, it erases characters from 'pos' to the end.
TXString& TXString::Delete(size_t pos, size_t len /* -1 */)
{
	if(pos < stdUStr.length())
	{
		stdUStr.erase(pos, len);
	}

	return *this;
}

//=======================================================================================
// Delete the last character. Does nothing if the string is empty.
TXString& TXString::DeleteLast()
{
	if(!stdUStr.empty())
	{
		stdUStr.pop_back();
	}
	
	return *this;
}

//=======================================================================================
// Trims white spaces (' ', '\t') at left end.
TXString& TXString::TrimLeft()
{
	ptrdiff_t pos = FindNotOneOf(" \t");

	if (pos >= 0)
	{
		stdUStr.erase(0, pos);
	}
	else
	{
		// Everything in the string is either a space or a tab, so remove everything.
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Trims white spaces (' ', '\t') at right end.
TXString& TXString::TrimRight()
{
	ptrdiff_t pos = ReverseFindNotOneOf(" \t");

	if (pos >= 0)
	{
		stdUStr.erase(pos + 1);
	}
	else
	{
		// Everything in the string is either a space or a tab, so remove everything.
		stdUStr.clear();
	}

	return *this;
}

//=======================================================================================
// Trims white spaces (' ', '\t') at both ends.
TXString& TXString::Trim()
{
	TrimLeft();
	TrimRight();

	return *this;
}

//=======================================================================================
// Trims invalid chars at the left end. When the string is changed or created, such as
// Right(...), it is possible that the first or the last character is part of a pair of
// UTF-16 surrogates. This function remove invalid character at the left end so they won't
// appear like garbage character there.
TXString& TXString::TrimLeftInvalidCharacter()
{
	if(!stdUStr.empty())
	{
		// Trim left end
		if(stdUStr[0] >= 0xDC00 && stdUStr[0] <= 0xDFFF)
		{
			stdUStr.erase(0, 1);
		}
	}

	return *this;
}

//=======================================================================================
// This function remove invalid character at the right end.
TXString& TXString::TrimRightInvalidCharacter()
{
	if(!stdUStr.empty())
	{
		// Trim right end
		if(stdUStr.back() >= 0xD800 && stdUStr.back() <= 0xDBFF)
		{
			stdUStr.pop_back();
		}
	}

	return *this;
}

//=======================================================================================
// Trims invalid chars at both ends.
TXString& TXString::TrimInvalidCharacters()
{
	if(!stdUStr.empty())
	{
		// Trim left end
		TrimLeftInvalidCharacter();

		// Trim right end
		TrimRightInvalidCharacter();
	}

	return *this;
}


//***************************************************************************************
// Replacement, case conversion, reversion
//***************************************************************************************

//=======================================================================================
// Replaces all 'oldStr' with 'newSTr'. If 'bIgnoreCase' is true, case is ignored.
// If 'oldStr' is empty, does nothing.
TXString& TXString::Replace(const TXString& oldStr, const TXString& newStr, bool bIgnoreCase /* false */)
{
	// Only manipulate the string if 'oldStr' is not empty.
	if(oldStr.IsEmpty() != true)
	{
		int dstStartPos = 0;

		if(bIgnoreCase)
		{
			TXString lowerSrcStr(*this);
			lowerSrcStr.MakeLower();

			TXString lowerOldStr(oldStr);
			lowerOldStr.MakeLower();

			int srcStartPos = 0;

			// For keeping the position in the destination
			const int delta = (int)newStr.stdUStr.length() - (int)oldStr.stdUStr.length();
			int deltaSum = 0;

			while((srcStartPos = (int)lowerSrcStr.stdUStr.find(lowerOldStr.stdUStr, srcStartPos)) != StdUStr::npos)
			{
				dstStartPos = srcStartPos + deltaSum;
				stdUStr.replace(dstStartPos, oldStr.stdUStr.length(), newStr.stdUStr);
				deltaSum += delta;
				srcStartPos += (int)oldStr.stdUStr.length();
			}
		}
		else
		{
			while((dstStartPos = (int)stdUStr.find(oldStr.stdUStr, dstStartPos)) != StdUStr::npos)
			{
				stdUStr.replace(dstStartPos, oldStr.stdUStr.length(), newStr.stdUStr);
				dstStartPos += (int)newStr.stdUStr.length();
			}
		}
	}

	return *this;
}

//=======================================================================================
// Convert all characters to upper case.
TXString& TXString::MakeUpper()
{
#if GS_WIN
	CharUpperBuffW((LPWSTR)stdUStr.data(), (DWORD)stdUStr.size());	// LCMapStringEx
#else
	// Create an empty mutable CFString
	CFMutableStringRef cfUniStr = CFStringCreateMutable(kCFAllocatorDefault, 0);

	if (cfUniStr) 
	{
		// Copy characters from this TXString to the mutable CFString.
		CFStringAppendCharacters(cfUniStr, stdUStr.data(), stdUStr.size());
		
		// If there is issue with nil, try CFLocaleCopyCurrent or CFLocaleCopyPreferredLanguages
		CFStringUppercase(cfUniStr, nil);
		
		// Copy characters from the mutable CFString to the TXString.
		*this = cfUniStr;
		
		// Release the mutable CFString.
		CFRelease(cfUniStr);
	}
#endif

	return *this;
}

//=======================================================================================
// Convert all characters to lower case.
TXString& TXString::MakeLower()
{
#if GS_WIN
	CharLowerBuffW((LPWSTR)stdUStr.data(), (DWORD)stdUStr.size());	// LCMapStringEx
#else
	size_t len = stdUStr.size();

	CFMutableStringRef	cfUniStr = CFStringCreateMutableWithExternalCharactersNoCopy(
		kCFAllocatorDefault, 
		(UniChar*)stdUStr.data(), 
		len, 
		len, 
		kCFAllocatorNull);

	if (cfUniStr) 
	{
		// If there is issue with nil, try CFLocaleCopyCurrent or CFLocaleCopyPreferredLanguages
		CFStringLowercase(cfUniStr, nil);
		CFRelease(cfUniStr);
	}
#endif

	return *this;
}

//=======================================================================================
// Reverse the string.
TXString& TXString::MakeReverse()
{
	if(stdUStr.length() > 0)
	{
		for (size_t i = 0, j = stdUStr.length() - 1; i < j; ++i,--j)
		{
			TXChar ch = stdUStr[i];
			stdUStr[i] = stdUStr[j];
			stdUStr[j] = ch;
		}
	}

	return *this;
}

//=======================================================================================
// Make sure the string is in precomposed form. Return itself.
TXString& TXString::ToPrecomposed()
{
#if GS_WIN
	if(!IsNormalizedString(NormalizationC, stdUStr.data(), -1))
	{	// Here, the string needs normalization.
		StdUStr original = stdUStr;
		int len = NormalizeString(NormalizationC, original.data(), (int)original.length(), &stdUStr[0], (int)stdUStr.length());
		stdUStr.resize(len);
	}
	
#else	// Mac
	NSString *oriStr = [NSString stringWithCharacters:stdUStr.data()
											   length:stdUStr.length()];
	
	NSString *precomposedStr = [oriStr precomposedStringWithCanonicalMapping];
	
	NSUInteger length = [precomposedStr length];
	
	stdUStr.resize(length);
	
	[precomposedStr getCharacters:&stdUStr[0]];
	
#endif
	
	return *this;
}

//=======================================================================================
// Makek sure the string is in decomposed form. Return itself.
TXString& TXString::ToDecomposed()
{
#if GS_WIN
	if(!IsNormalizedString(NormalizationD, stdUStr.data(), -1))
	{	// Here, the string needs normalization.
		StdUStr original = stdUStr;
		stdUStr.resize(stdUStr.length() * 2);	// Allocate enough memory.
		int len = NormalizeString(NormalizationD, original.data(), (int)original.length(), &stdUStr[0], (int)stdUStr.length() * 2);
		stdUStr.resize(len);
	}

#else	// Mac
	NSString *oriStr = [NSString stringWithCharacters:stdUStr.data()
											   length:stdUStr.length()];
	
	NSString *decomposedStr = [oriStr decomposedStringWithCanonicalMapping];
	
	NSUInteger length = [decomposedStr length];
	
	stdUStr.resize(length);
	
	[decomposedStr getCharacters:&stdUStr[0]];
	
#endif
	
	return *this;
}


//***************************************************************************************
// Getting data and casting
//***************************************************************************************

//=======================================================================================
// Returns const pointer to the TXChar buffer.
const TXChar* TXString::GetData() const
{
	return stdUStr.data();
}

//=======================================================================================
// Returns const pointer to the TXChar buffer.
const TXChar* TXString::GetTXCharPtr() const
{
	return stdUStr.data();
}

//=======================================================================================
// Returns a pointer to const UTF-8 char buffer.
TXString::operator const char*() const
{
	PrepareCharBuffer();
	return charPtr;
}

//=======================================================================================
// Returns a pointer to const UTF-8 unsigned char buffer.
TXString::operator const unsigned char*() const
{
	PrepareCharBuffer();

	size_t len = strlen(charPtr);

	if (len > 255)
		len = 255;

	memmove(charPtr + 1, charPtr, len);

	charPtr[0] = (char)len;

	return (const unsigned char*)charPtr;
}

//=======================================================================================
// Returns a pointer to const UCChar buffer.
TXString::operator const UCChar*() const
{
	return (const UCChar*)stdUStr.c_str();
}

//=======================================================================================
// Returns a pointer to const wchar_t buffer. On Mac, returns a pointer to a TEMPORARY
// wchar_t buffer.
TXString::operator const wchar_t*() const
{
#if GS_WIN
	return stdUStr.c_str();
#else
    wStr = GetStdWString();
    
    return wStr.data();
#endif
}

//=======================================================================================
// Returns a std::string object with 'e' encoding
std::string TXString::GetStdString(ETXEncoding e) const	// Default: eUTF8
{
	PrepareCharBuffer(e);

	return std::string(charPtr);
}

//=======================================================================================
// Returns a std::wstring object
std::wstring TXString::GetStdWString() const
{
#if GS_WIN
	return std::wstring(stdUStr.c_str());
#else
	std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> converter;

	return converter.from_bytes((const char*)stdUStr.data(), (const char*)(stdUStr.data() + stdUStr.length()));
#endif
}

//=======================================================================================
// Returns a const std::u16string reference
const std::u16string & TXString::GetConstU16String() const
{
	// C style casting and reinterpret_cast are not able to cast StdUStr to std::u16string.
	// Pointer casting is used here to work around it.
	return *(std::u16string *)(& stdUStr);
}

//=======================================================================================
// Returns a CFStringRef. The client is responsible of releasing the returned ref.
#if GS_MAC
CFStringRef TXString::GetCFStringRef() const
{
	return CFStringCreateWithCharacters(NULL, stdUStr.data(), stdUStr.length());
}
#endif

//***************************************************************************************
// Copying data into external buffer
//***************************************************************************************

//=======================================================================================
// 'bufSize' is the size of the buffer in bytes. For example, "xyz" needs four bytes to
// include '\0' at the end.
void TXString::CopyInto(char *dst,
						size_t bufSize,
						ETXEncoding e) const	// ETXEncoding::eUTF8
{
	if(dst && bufSize > 0)
	{
		PrepareCharBuffer(e);
		
		size_t len = strlen(charPtr);
		
		if(len >= bufSize)
		{
			len = bufSize - 1;
		}
		
		strncpy(dst, charPtr, len);
		dst[len] = '\0';
	}
}

//=======================================================================================
// Copy string data into 'dst' unsigned char buffer based on 'e' encoding.
// bufSize is the size of the buffer.
void TXString::CopyInto(unsigned char* ps,
						size_t bufSize,
						ETXEncoding e) const	// ETXEncoding::eUTF8
{
	if(ps && bufSize > 0)
	{
		PrepareCharBuffer(e);

		size_t len = strlen(charPtr);

		if(len > bufSize - 1)
			len = bufSize - 1;

		if(len > 255)
			len = 255;

		strncpy((char *)ps + 1, charPtr, len);

		ps[0] = (unsigned char)len;
	}
}

//=======================================================================================
// Copy string data into 'dst' UCChar buffer. bufElemNum is the number of elements in
// the buffer. '\0' will be added to the end of string even if buffer is not big enough.
void TXString::CopyInto(UCChar* dst, size_t bufElemSize) const
{
	if(dst && bufElemSize != 0)
	{
		size_t len = stdUStr.length();

		if(len < bufElemSize)
		{
			// Buffer is large enough to store the string.
			stdUStr.copy((TXChar*)dst, len);
			dst[len] = 0;
		}
		else
		{
			// Buffer is NOT large enough to store the string.
			stdUStr.copy((TXChar*)dst, bufElemSize - 1);
			dst[bufElemSize - 1] = 0;
		}
	}
}

//=======================================================================================
// Copy string data into 'dst' wchar_t buffer. bufElemNum is the number of elements in
// the buffer. '\0' will be added to the end of string even if buffer is not big enough.
void TXString::CopyInto(wchar_t* dst, size_t bufElemSize) const
{
	if(dst && bufElemSize != 0)
	{
#if GS_WIN
		size_t len = stdUStr.length();

		if(len < bufElemSize)
		{
			// Buffer is large enough to store the string.
			stdUStr.copy(dst, len);
			dst[len] = 0;
		}
		else
		{
			// Buffer is NOT large enough to store the string.
			stdUStr.copy(dst, bufElemSize - 1);
			dst[bufElemSize - 1] = 0;
		}
#else
		txCharBufferToUtf32Buffer(stdUStr.data(), stdUStr.length(), (char32_t*)dst, bufElemSize);
#endif
	}
}


//***************************************************************************************
// Find functions
//***************************************************************************************

//=======================================================================================
// Return the position of the first found 'sub' in the string. The search starts from
// position 'posFirst'. If 'bIgnoreCase' is true, case insensitive search is performed. If
// TXString or 'sub' is empty, returns -1.
ptrdiff_t TXString::Find(const TXString &sub,
						 size_t posFirst,			// 0
						 bool bIgnoreCase) const	// false
{
	if(sub.GetLength() == 0) return -1;

	size_t pos;

	if(bIgnoreCase)
	{
		// Ignore case is more expensive.
		TXString srcStr(*this);
		srcStr.MakeLower();

		TXString subStr(sub);
		subStr.MakeLower();

		pos = srcStr.stdUStr.find(subStr.stdUStr, posFirst);
	}
	else
	{
		pos = stdUStr.find(sub.stdUStr, posFirst);
	}

	if(pos == stdUStr.npos) pos = -1;
	
	return pos;
}

//=======================================================================================
// Return the position of the first found 'ch' in the string. The search starts from
// position 'posFirst'. If 'bIgnoreCase' is true, case insensitive search is performed.
// 'ch' can be type of unsigned char, UCChar, or wchar_t.
ptrdiff_t TXString::Find(int ch, 
						 size_t posFirst,			// 0
						 bool bIgnoreCase) const	// false
{
	size_t pos;

	if(bIgnoreCase)
	{	// Ignore case is more expensive.
		TXString strCh((TXChar)ch);
		strCh.MakeLower();
		
		TXString strCopy(*this);
		strCopy.MakeLower();
		
		pos = strCopy.stdUStr.find(strCh.stdUStr[0], posFirst);
	}
	else
	{
		pos = stdUStr.find(ch, posFirst);
	}

	if(pos == stdUStr.npos) pos = -1;
	
	return pos;
}

//=======================================================================================
// Return the position of the first found 'ch' in the string. The search starts from
// position 'posFirst'. If 'bIgnoreCase' is true, case insensitive search is performed.
ptrdiff_t TXString::Find(char ch, 
						 size_t posFirst,			// 0
						 bool bIgnoreCase) const	// false
{
	return Find((unsigned char) ch, posFirst, bIgnoreCase);
}

//=======================================================================================
// Searches from right to left. Returns the starting index of a sub-string.
// posLast is the position of the last character to be considered in the search.
// If 'bIgnoreCase' is true, case insensitive search is performed.
// Return -1 if not found.
ptrdiff_t TXString::ReverseFind(const TXString &sub, 
								size_t posLast,			// -1
								bool bIgnoreCase) const	// false
{
	if(sub.GetLength() == 0) return -1;

	size_t pos;

	if(bIgnoreCase)
	{	// Ignore case is more expensive.
		TXString srcStr(*this);
		srcStr.MakeLower();

		TXString subStr(sub);
		subStr.MakeLower();

		pos = srcStr.stdUStr.rfind(subStr.stdUStr, posLast);
	}
	else
	{
		pos = stdUStr.rfind(sub.stdUStr, posLast);
	}

	if(pos == stdUStr.npos) pos = -1;
	
	return pos;
}

//=======================================================================================
// Searches from right to left. Returns the position of the first found 'ch'.
// 'posLast' is the last possible found position.
// If 'bIgnoreCase' is true, case is ignored.
// The type of 'ch' can be unsigned char, UCChar, wchar_t.
ptrdiff_t TXString::ReverseFind(int ch, 
								size_t posLast,			// -1
								bool bIgnoreCase) const	// false
{
	size_t pos;

	if(bIgnoreCase)
	{	// Ignore case is more expensive.
		TXString srcStr(*this);
		srcStr.MakeLower();
		
		TXString chStr((TXChar)ch);
		chStr.MakeLower();
		
		pos = srcStr.stdUStr.rfind(chStr.stdUStr[0], posLast);
	}
	else {
		pos = stdUStr.rfind(ch, posLast);
	}

	if(pos == stdUStr.npos) pos = -1;
	
	return pos;
}

//=======================================================================================
// Searches from right to left. Returns the position of the first found 'ch'.
// posLast is the position of the last character to be considered in the search.
// If 'bIgnoreCase' is true, case is ignored.
ptrdiff_t TXString::ReverseFind(char ch, 
								size_t posLast,			// -1
								bool bIgnoreCase) const	// false
{
	return ReverseFind((unsigned char) ch, posLast, bIgnoreCase);
}

//=======================================================================================
// Return the position of the first found character in charSet. 
// 'posFirst'is the first character to be considered in the search.
// Return -1 if none is found.
ptrdiff_t TXString::FindOneOf(const TXString &charSet,
							  size_t posFirst) const	// 0
{
	size_t pos = stdUStr.find_first_of(charSet.stdUStr, posFirst);

	if(pos == stdUStr.npos) pos = -1;
	
	return pos;
}

//=======================================================================================
// Return the position of the last character in the string that matchs one of the
// characters in 'charSet'. 
// 'posLast'is the last character to be considered in the search.
// Return -1 if no match.
ptrdiff_t TXString::ReverseFindOneOf(const TXString &charSet,
									 size_t posLast) const		// -1
{
	size_t pos = stdUStr.find_last_of(charSet.stdUStr, posLast);

	if(pos == stdUStr.npos) pos = -1;
	
	return pos;
}

//=======================================================================================
// Return the position of the first found character NOT in charSet. 
// 'posFirst'is the first character to be considered in the search.
// Return -1 if none is found.
ptrdiff_t TXString::FindNotOneOf(const TXString &charSet,
								 size_t posFirst) const	// 0
{
	size_t pos = stdUStr.find_first_not_of(charSet.stdUStr, posFirst);

	if(pos == stdUStr.npos) pos = -1;
	
	return pos;
}

//=======================================================================================
// Return the position of the last character in the string that does NOT match any of
// the characters in 'charSet'. 
// 'posLast'is the last character to be considered in the search.
// Return -1 if none found.
ptrdiff_t TXString::ReverseFindNotOneOf(const TXString &charSet,
										size_t posLast) const	// -1
{
	size_t pos = stdUStr.find_last_not_of(charSet.stdUStr, posLast);

	if(pos == stdUStr.npos) pos = -1;
	
	return pos;
}

bool TXString::SurrogatePairAt(size_t nIndex) const
{
	bool isSurrogatePair = false;
	
	if (nIndex < (GetLength() - 1))
	{
		TXChar firstChar = GetAt(nIndex);
		TXChar secondChar = GetAt(nIndex+1);
		isSurrogatePair = inrange<TXChar,TXChar,TXChar>(firstChar, 0xD800, 0xDBFF) &&
		    inrange<TXChar,TXChar,TXChar>(secondChar, 0xDC00, 0xDFFF);
	}
	
	return isSurrogatePair;
}

bool TXString::HasSurrogatePair() const
{
	bool hasSurrogatePair = false;
	
	if (GetLength() > 1)
	{
		for (size_t nIndex = 0; nIndex < (GetLength() - 1) && ! hasSurrogatePair; nIndex++)
		{
			if (SurrogatePairAt(nIndex))
			{
				hasSurrogatePair = true;
				break;
			}
		}
	}
	
	return hasSurrogatePair;
}

//***************************************************************************************
// Creating sub-string
//***************************************************************************************

//=======================================================================================
// Returns a copy of sub-string containing 'len' characters starting from 'nFirst'.
// If 'len' is greater than the length, characters from 'nFirst' to the end is returned.
TXString TXString::Mid(size_t nFirst, size_t len) const
{
	if (nFirst >= stdUStr.length())
	{
		return TXString();
	}

	if (nFirst + len > stdUStr.length())
	{
		len = stdUStr.length() - nFirst;
	}

	return TXString(stdUStr.substr(nFirst, len)).TrimInvalidCharacters();
}

//=======================================================================================
// Returns a copy of string containing the left 'len' number of characters. If 'len'
// is greater than the length, the whole string is returned.
TXString TXString::Left(size_t len) const
{
	return TXString(stdUStr.substr(0, len)).TrimRightInvalidCharacter();
}

//=======================================================================================
// Returns a copy of string containing the right 'len' number of characters. If 'len'
// is greater than the length, the whole string is returned.
TXString TXString::Right(size_t len) const
{
	if(len >= stdUStr.length()) return *this;

	return TXString(stdUStr.substr(stdUStr.length() - len)).TrimLeftInvalidCharacter();
}


//***************************************************************************************
// Convertion to and from numerics
//***************************************************************************************

//=======================================================================================
// Returns Sint32 value based on the string. If the string is not valid to converted to
// an integer, returns 0. White spaces in the beginning are ignored. The first valid
// number is returned. e.g. " 123 123 " returns 123.
Sint32 TXString::atoi() const
{
	return ::atoi(*this);
}

//=======================================================================================
// Returns Sint64 value based on the string. If the string is not valid to be converted
// to an integer, returns 0. White spaces in the beginning are ignored. The first valid
// number is returned. e.g. " 123 123 " returns 123.
Sint64 TXString::atoi64() const
{
	return ::atoi(*this);
}

//=======================================================================================
// Returns double value based on the string. If the string is not valid to be converted,
// returns 0. White spaces in the beginning are ignored. The first valid number is
// returned.
Real64 TXString::atof() const
{
	return ::atof(*this);
}

//=======================================================================================
// Sets the current string to the input value
TXString& TXString::itoa(Sint64 value)
{
	return (*this = std::to_string(value));
}

//=======================================================================================
// Sets the current string to the input value
TXString& TXString::ftoa(Real64 value)
{
	return (*this = std::to_string(value));
}

//=======================================================================================
// Sets the current string to the input value
TXString& TXString::ftoa(Real64 value, Sint32 precision)
{
	return (*this = TXString::ToStringReal( value, precision ));
}

//=======================================================================================
/*static*/ TXString TXString::ToStringInt(Sint64 value)
{
	return std::to_string(value);
}

//=======================================================================================
/*static*/ TXString TXString::ToStringInt(Sint64 value, Sint32 width, wchar_t paddingChar)
{
	std::wstringstream out;
	out << std::setfill(paddingChar) << std::setw(width) << value;
	return out.str();
}

//=======================================================================================
/*static*/ TXString TXString::ToStringReal(Real64 value)
{
	return std::to_string(value);
}

//=======================================================================================
/*static*/ TXString TXString::ToStringReal(Real64 value, Sint32 precision, bool fixed)
{
	std::wstringstream out;
	if ( fixed )
		out << std::fixed;
	out << std::setprecision(precision);
	out << value;
	out << std::setprecision(0);	// restore
	return out.str();
}

bool TXString::ToDouble(const TXString& inString, double& outDouble, bool useOSLocale /* = false */)
{
	bool result = false;

    if (useOSLocale) {
#if GS_WIN
        wchar_t localeNameBuf[LOCALE_NAME_MAX_LENGTH];
        result = (GetUserDefaultLocaleName(localeNameBuf, LOCALE_NAME_MAX_LENGTH) > 0);
        
        if (result) {           
			_locale_t osLocale = _wcreate_locale(LC_ALL, localeNameBuf);

			if (VERIFYN(kSWilliams, osLocale)) {
				result = (_swscanf_l(inString.GetData(), L"%lf", osLocale, &outDouble) > 0);
				_free_locale(osLocale);
			}
        }
#else
        if (VERIFYN(kSWilliams, inString.GetData())) {
            NSScanner* scanner = [NSScanner localizedScannerWithString:[[NSString alloc] initWithCharactersNoCopy:(TXChar*)inString.GetData()
                                                                                                           length:inString.GetLength()
                                                                                                     freeWhenDone:NO]];
            result = [scanner scanDouble:&outDouble];
        }
#endif
    }
    
	// OS locale not desired, or localized parse failed
    if (!result) {
        result = true;
        
        try {
            outDouble = std::stod(inString.GetStdString());
        }
        catch (...) {
            result = false;
        }
    }
    
	return result;
}

//=======================================================================================
/*static*/ bool TXString::IsPunctuation(TXChar aTXChar)
{
#if GS_WIN
	return iswpunct(aTXChar);
#else
	return [[NSCharacterSet punctuationCharacterSet] characterIsMember:aTXChar];
#endif
}

//=======================================================================================
/*static*/ bool TXString::IsWhitespace(TXChar aTXChar)
{
#if GS_WIN
	return iswspace(aTXChar);
#else
	return [[NSCharacterSet whitespaceCharacterSet] characterIsMember:aTXChar];
#endif
}


//***********************************************************************************
// Comparison
//***********************************************************************************

//=======================================================================================
// Return true if this euqals str. This is CASE SENSITIVE.
bool TXString::Equal(const TXString &str) const
{
	return (stdUStr == str.stdUStr);
}

//=======================================================================================
// Return true if this euqals str. This is CASE INSENSITIVE.
bool TXString::EqualNoCase(const TXString &str) const
{
	if(stdUStr.length() != str.stdUStr.length())
	{
		return false;
	}
	
	return (this->CompareNoCase(str) == 0);
}

//=======================================================================================
// Compares this string with str. This comparison is case sensitive.
Sint32 TXString::Compare(const TXString &str) const
{
	return stdUStr.compare(str.stdUStr);
}

//=======================================================================================
// Compares this string with str. This comparision is case insensitive.
Sint32 TXString::CompareNoCase(const TXString &str) const
{
	
#if GS_WIN
	return lstrcmpiW(stdUStr.c_str(), str.stdUStr.c_str());
	
#else
	CFStringRef cs1 = CFStringCreateWithCharactersNoCopy(kCFAllocatorDefault,
														 stdUStr.data(),
														 stdUStr.length(),
														 kCFAllocatorNull);
	
	CFStringRef cs2 = CFStringCreateWithCharactersNoCopy(kCFAllocatorDefault,
														 str.stdUStr.data(),
														 str.stdUStr.length(),
														 kCFAllocatorNull);
	
	if(cs1 && cs2)
	{
		CFComparisonResult result = CFStringCompare(cs1, cs2, kCFCompareCaseInsensitive);
		CFRelease(cs1);
		CFRelease(cs2);
		return result;
	}
	
	if(cs1) CFRelease(cs1);
	if(cs2) CFRelease(cs2);
	
	// If there is an error converting to CFString, use regular Compare as backup.
    return Compare(str);
	
#endif
	
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive.
bool operator==(const TXString& lhs, const TXString& rhs)
{
	return (lhs.EqualNoCase(rhs));
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive.
bool operator==(const TXString& lhs, const char* rhs)
{
	if(rhs == nullptr)
	{
		if(lhs.stdUStr.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return (lhs.EqualNoCase(rhs));
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive.
bool operator==(const char* lhs, const TXString& rhs)
{
	if(lhs == nullptr)
	{
		if(rhs.stdUStr.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return (rhs.EqualNoCase(lhs));
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive.
bool operator==(const TXString& lhs, const TXChar* rhs)
{
	if(rhs == nullptr)
	{
		if(lhs.stdUStr.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return (lhs.EqualNoCase(rhs));
}

//=======================================================================================
// '==' comparison operator. This comparison is case insensitive.
bool operator==(const TXChar* lhs, const TXString& rhs)
{
	if(lhs == nullptr)
	{
		if(rhs.stdUStr.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return (rhs.EqualNoCase(lhs));
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive.
bool operator!=(const TXString& lhs, const TXString& rhs)
{
	return !(lhs == rhs);
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive.
bool operator!=(const TXString& lhs, const char* rhs)
{
	return !(lhs == rhs);
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive.
bool operator!=(const char* lhs, const TXString& rhs)
{
	return !(lhs == rhs);
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive.
bool operator!=(const TXString& lhs, const TXChar* rhs)
{
	return !(lhs == rhs);
}

//=======================================================================================
// '!=' comparison operator. This comparison is case insensitive.
bool operator!=(const TXChar* lhs, const TXString& rhs)
{
	return !(lhs == rhs);
}

//=======================================================================================
// '>=' comparison operator. This comparison is case insensitive. 
bool operator>=(const TXString& lhs, const TXString& rhs)
{
	return (lhs.CompareNoCase(rhs) >= 0);
}

//=======================================================================================
// '<=' comparison operator. This comparison is case insensitive. 
bool operator<=(const TXString& lhs, const TXString& rhs)
{
	return (lhs.CompareNoCase(rhs) <= 0);
}

//=======================================================================================
// '>' comparison operator. This comparison is case insensitive. 
bool operator>(const TXString& lhs, const TXString& rhs)
{
	return (lhs.CompareNoCase(rhs) > 0);
}

//=======================================================================================
// '<' comparison operator. This comparison is case insensitive. 
bool operator<(const TXString& lhs, const TXString& rhs)
{
	return (lhs.CompareNoCase(rhs) < 0);
}

//=======================================================================================
// '+' operator
TXString operator+(const TXString& lhs, const TXString& rhs)
{
	return TXString(lhs.stdUStr + rhs.stdUStr);
}

//=======================================================================================
// '+' operator
TXString operator+(const TXString& lhs, TXChar rhs)
{
	if(rhs == 0) return lhs;
	return TXString(lhs.stdUStr + rhs);
}

//=======================================================================================
// '+' operator
TXString operator+(TXChar lhs, const TXString& rhs)
{
	if(lhs == 0) return rhs;
	return TXString(lhs + rhs.stdUStr);
}

//=======================================================================================
// '+' operator
TXString operator+(const TXString& lhs, const TXChar* rhs)
{
	if(rhs == nullptr) return lhs;
	return TXString(lhs.stdUStr + rhs);
}

//=======================================================================================
// '+' operator
TXString operator+(const TXChar* lhs, const TXString& rhs)
{
	if(lhs == nullptr) return rhs;
	return TXString(lhs + rhs.stdUStr);
}

//=======================================================================================
// literal operator
TXString operator""_txs(const char* src, size_t len)
{
	return { src, len };
}

//=======================================================================================
// literal operator
TXString operator""_txs(const wchar_t* src, size_t len)
{
	return { src, len };
}

//=======================================================================================
TXString& TXString::Format(const TXString& format)
{
	*this = format;
	return *this;
}

//=======================================================================================
// Prepare char buffer based on "encoding" encoding.
void TXString::PrepareCharBuffer(ETXEncoding encoding) const
{
    if(stdUStr.empty()) // Special handling for empty string.
    {
        // If char buffer size is zero, allocates one byte to charPtr.
        if(charBufSize == 0)
        {
            charBufSize = 1;
            charPtr = (char*) gVWMM->TXStringAllocate(charBufSize);;
        }

        *charPtr = txuc('\0');
    }
    else
    {
        
#if GS_WIN

        // Determine copde page.
        UINT codePage = CP_UTF8;

        if (encoding == ETXEncoding::eMacEncoded)
        {
            codePage = CP_MACCP;
        }
        else if (encoding == ETXEncoding::eWinEncoded || encoding == ETXEncoding::eSysEncoded)
        {
            codePage = CP_ACP;
        }

        // Length of the char buffer. Four bytes for each character is enough. 1 for terminal character.
        int len = (int)stdUStr.length() * 4 + 1;

        if(len > charBufSize)
        {
            charBufSize = len;
            if(charPtr) gVWMM->TXStringDeallocate(charPtr);
            charPtr = (char*) gVWMM->TXStringAllocate(charBufSize);;
        }

        // (CodePage, Flags, WideCharStr, WideCharCount, MultiByteStr, MultiByteCount, DefaultChar, UsedDefaultChar)
        WideCharToMultiByte(codePage, 0, stdUStr.c_str(), -1, charPtr, len, (codePage == CP_UTF8) ? NULL : "?", NULL);


#else	// Mac

        // Prepare enough memory for all cases
        if(charBufSize < 4 * stdUStr.length() + 1) {
            charBufSize = 4 * (int)stdUStr.length() + 1;	// 1 is reserved for terminal character.
            if(charPtr) gVWMM->TXStringDeallocate(charPtr);
            charPtr = (char*) gVWMM->TXStringAllocate(charBufSize);;
        }

        // Create a CFString to do the conversion
        CFStringRef cfStr = CFStringCreateWithCharactersNoCopy(kCFAllocatorDefault,
            stdUStr.data(),
            stdUStr.length(),
            kCFAllocatorNull);

        if(cfStr)
        {
            CFStringEncoding cfStrEncoding = kCFStringEncodingUTF8;	// Default for eUTF8 and eUnknown
            
            if(encoding == ETXEncoding::eMacEncoded || encoding == ETXEncoding::eSysEncoded)
            {
                cfStrEncoding = CFStringGetSystemEncoding();
            }
            else if(encoding == ETXEncoding::eWinEncoded)
            {
                static const bool bIsFarEast = [[[NSLocale preferredLanguages] objectAtIndex:0] hasPrefix:@"ja"]
                                            || [[[NSLocale preferredLanguages] objectAtIndex:0] hasPrefix:@"zh-Hans"];

                if(bIsFarEast)	// Win and Mac encodings are the same in Japanese and Chinese environments.
                {
                    cfStrEncoding = CFStringGetSystemEncoding();
                }
                else
                {
                    cfStrEncoding = kCFStringEncodingWindowsLatin1;
                }
            }

            CFIndex usedBufLen = 0;
            
            CFStringGetBytes(cfStr,
                             CFRangeMake(0, CFStringGetLength(cfStr)),
                             cfStrEncoding,
                             '?',
                             false,
                             (UInt8*)charPtr,
                             charBufSize - 1,	// Reserved one byte for terminal character
                             &usedBufLen);
            
            charPtr[usedBufLen] = 0;			// Add terminal character to the end.
            
            CFRelease(cfStr);
        }

#endif
    }
}

//=======================================================================================
// Set stdUStr from 'src' based on "encoding". 'srcLenToUse' does NOT include the
// terminating character.
void TXString::SetStdUStrFromCharBuffer(const char* src, size_t strLen, ETXEncoding encoding)
{
	if(strLen == 0 || src == nullptr || *src == '\0') {
		stdUStr.clear();
		return;
	}

#if GS_WIN

	if(encoding == ETXEncoding::eUTF8)	// UTF-8
	{
		stdUStr.resize(strLen);
		size_t len = utf8BufferToTXCharBuffer(src, strLen, &stdUStr[0]);
		stdUStr.resize(len);
	}
	else
	{
		UINT codePage = CP_ACP;			// Windows ANSI encoding.

		if (encoding == ETXEncoding::eMacEncoded)
		{
			codePage = CP_MACCP;		// Mac encoding.
		}

		stdUStr.resize(strLen + 1);
		int newLen = MultiByteToWideChar(codePage, MB_PRECOMPOSED, src, (int)strLen, &stdUStr[0], int(strLen + 1));
		stdUStr.resize(newLen);
	}


#else	// Mac

	if(encoding == ETXEncoding::eUTF8)
	{
		stdUStr.resize(strLen);
		size_t len = utf8BufferToTXCharBuffer(src, strLen, &stdUStr[0]);
		stdUStr.resize(len);
	}
	else
	{
		CFStringEncoding selectedEncoding = CFStringGetSystemEncoding();

		if(encoding == ETXEncoding::eWinEncoded)
		{
			selectedEncoding = kCFStringEncodingWindowsLatin1;
		}

		CFStringRef cfStr = CFStringCreateWithBytes(kCFAllocatorDefault,
			(const UInt8*)src,
			strLen,
			selectedEncoding,
			false);

		if (cfStr)
		{
			CFIndex cfStrLen = CFStringGetLength(cfStr);
			CFRange cfStrRange = CFRangeMake(0, cfStrLen);

			stdUStr.resize(cfStrLen);
			CFStringGetCharacters(cfStr, cfStrRange, &stdUStr[0]);
			
			CFRelease(cfStr);
		}
	}
#endif
}


//=======================================================================================
// http://unicode.org/faq/utf_bom.html#utf16-3

static const UCChar LEAD_OFFSET = 0xD800 - (0x10000 >> 10);

// UTF-32 to UTF-16 conversion. 'output' should be TXChar[3].
// Null character is at the end of the UTF-16 string.
inline void utf32ToTXCharBuffer(char32_t input, TXChar* output)
{
	if (input <= 0xFFFFUL)
	{
		*output++ = (TXChar)input;
	}
	else if (input <= 0x10FFFFUL)
	{
		*output++ = LEAD_OFFSET + (TXChar)(input >> 10);
		*output++ = 0xDC00 + (input & 0x3FF);
	}
	else
	{
		*output++ = '?';
	}

	*output = 0;	// Terminal character.
}

//=======================================================================================
// Convert char32_t bufer to TXChar buffer.
size_t utf32BufferToTXCharBuffer(const char32_t* input, size_t inputLen, TXChar* output)
{
	size_t outputLen = 0;
	const char32_t * const inputEnd = input + inputLen;

	while (input < inputEnd)
	{
		if (*input <= 0xFFFFUL)
		{
			*output++ = (TXChar)(*input);
			++outputLen;
		}
		else if (*input <= 0x10ffffUL)
		{
			*output++ = LEAD_OFFSET + (TXChar)(*input >> 10);
			*output++ = 0xDC00 + (*input & 0x3FF);
			outputLen += 2;
		}
		else
		{
			*output++ = '?';
			++outputLen;
		}

		++input;
	}

	return outputLen;
}

//=======================================================================================
// TXChar* to char32_t*
static const char32_t SURROGATE_OFFSET = 0x10000 - (0xD800 << 10) - 0xDC00;

inline void txCharBufferToUtf32Buffer(const TXChar* input, size_t inputLen, char32_t* output, size_t outputLen)
{
	const TXChar * const inputEnd = input + inputLen;
	const char32_t * const outputEnd = output + outputLen;
	TXChar oneTXChar;

	while (input < inputEnd && output < outputEnd)
	{
		oneTXChar = *input++;

		if (oneTXChar < 0xD800 || oneTXChar > 0xDFFF)
		{
			// One UTF-16 code unit for one UTF-32 code unit
			*output++ = oneTXChar;
		}
		else
		{
			// Two UTF-16 code units for one UTF-32 code unit
			if (oneTXChar < 0xdc00 && input < inputEnd && (*input) >= 0xdc00 && (*input) <= 0xdfff)
			{
				*output++ = (oneTXChar << 10) + (*input++) + SURROGATE_OFFSET;
			}
			else
			{
				*output++ = '?';
			}
		}
	}

	if (output < outputEnd)
	{
		*output = 0;
	}
	else
	{
		*(--output) = 0;
	}
}

//=======================================================================================
// UTF-8 buffer to TXChar buffer. 'inputLen' is the number of input characters.
inline size_t utf8BufferToTXCharBuffer(const char* input, size_t inputLen, TXChar* output)
{
	TXChar u[3];
	char32_t w;
	size_t outputLen = 0;
	const char * const inputEnd = input + inputLen;

	while(input < inputEnd)
	{
		if((*input & 0x80) == 0)	// 1 byte
		{
			*output++ = *input++;
			++outputLen;
		}
		else if((*input & 0xE0) == 0xC0)	// 2 bytes
		{
			if((input + 1) >= inputEnd) break;

			w = ((*input & 0x1F) << 6)
				+ (*(input + 1) & 0x3F);

			utf32ToTXCharBuffer(w, u);
			*output++ = u[0];
			++outputLen;

			if (u[1])
			{
				// Two UTF-16 characters.
				*output++ = u[1];
				++outputLen;
			}

			input += 2;
		}
		else if((*input & 0xF0) == 0xE0)	// 3 bytes
		{
			if((input + 2) >= inputEnd) break;

			w = ((*(input) & 0x0F) << 12)
				+ ((*(input + 1) & 0x3F) << 6)
				+ (*(input + 2) & 0x3F);

			utf32ToTXCharBuffer(w, u);
			*output++ = u[0];
			++outputLen;

			if (u[1])
			{
				// Two UTF-16 characters.
				*output++ = u[1];
				++outputLen;
			}

			input += 3;
		}
		else if((*input & 0xF8) == 0xF0)	// 4 bytes
		{
			if((input + 3) >= inputEnd) break;

			w =   ((*(input) & 0x07) << 18)
				+ ((*(input + 1) & 0x3F) << 12)
				+ ((*(input + 2) & 0x3F) << 6)
				+  (*(input + 3) & 0x3F);

			utf32ToTXCharBuffer(w, u);
			*output++ = u[0];
			++outputLen;

			if (u[1])
			{
				// Two UTF-16 characters.
				*output++ = u[1];
				++outputLen;
			}

			input += 4;
		}
		else	// Invalid byte.
		{
			*output++ = '?';
			++outputLen;
			++input;
		}
	}

	while(input++ < inputEnd)
	{
		*output++ = '?';
		++outputLen;
	}

	return outputLen;
}


//#######################################################################################
// TXStringArray
//#######################################################################################

//=======================================================================================
// Default constructor. The array has 'nInitialSize' empty TXString objects.
TXStringArray::TXStringArray(size_t nInitialSize /* 0 */)
	: strVec(nInitialSize, TXString())
{
}

//=======================================================================================
// List initialization constructor. This "copies" from an initialization list, and exists
// to avoid having to call "Append" multiple times.
TXStringArray::TXStringArray(std::initializer_list<TXString> src) {
	strVec = src;
}

//=======================================================================================
// Copy constructor
TXStringArray::TXStringArray(const TXStringArray &src)
	: strVec(src.strVec)
{
}

//=======================================================================================
// Move constructor
TXStringArray::TXStringArray(TXStringArray &&src)
	: strVec(std::move(src.strVec))
{
}

//=======================================================================================
// Destructor
TXStringArray::~TXStringArray()
{
}

//=======================================================================================
// Copy assignment operator
TXStringArray& TXStringArray::operator=(const TXStringArray &src)
{
	strVec = src.strVec;
	return *this;
}

//=======================================================================================
// Move assignment operator
TXStringArray& TXStringArray::operator=(TXStringArray&& src)
{
	strVec = std::move(src.strVec);
	return *this;
}

//=======================================================================================
// List initializer assignment operator. Syntactic sugar for an existing TXStringArray
TXStringArray& TXStringArray::operator=(std::initializer_list<TXString> src)
{
	strVec = src;
	return *this;
}


//=======================================================================================
// Set the size of the array. The array is polulated with empty TXString objects. True is
// always returned.
TXStringArray& TXStringArray::SetSize(size_t nSize)
{
	strVec.resize(nSize);

	return *this;
}

//=======================================================================================
// Return the size of the array.
size_t TXStringArray::GetSize() const
{
	return strVec.size();
}

//=======================================================================================
// Return true if the array is empty. Return true otherwise.
bool TXStringArray::IsEmpty() const
{
	return strVec.empty();
}

//=======================================================================================
// If 'nIndex' is less than the size, element at 'nIndex' is replaced with 'string'. 
// Otherwise, 'string' is appended to the end.
TXStringArray& TXStringArray::SetAt(size_t nIndex, const TXString &string)
{
	if (nIndex < strVec.size())
	{
		strVec[nIndex] = string;
	}
	else
	{
		strVec.push_back(string);
	}
	
	return *this;
}

//=======================================================================================
// Return the const reference to the element at 'nIndex'. If 'nIndex' is out of range, an
// excepton is thrown.
const TXString& TXStringArray::GetAt(size_t nIndex) const
{
	return strVec[nIndex];
}

//=======================================================================================
// Return a reference to the element at 'nIndex'. If 'nIndex' is out of range, an
// excepton is thrown.
TXString& TXStringArray::GetAt(size_t nIndex)
{
	return strVec[nIndex];
}

//=======================================================================================
// Return the const reference to the element at 'nIndex'. If 'nIndex' is out of range, an
// excepton is thrown.
const TXString& TXStringArray::operator[](size_t nIndex) const
{
	return strVec[nIndex];
}

//=======================================================================================
// Return a reference to the element at 'nIndex'. If 'nIndex' is out of range, an
// excepton is thrown.
TXString& TXStringArray::operator[](size_t nIndex)
{
	return strVec[nIndex];
}

//=======================================================================================
// Append 'string' to the end. Always return true.
TXStringArray& TXStringArray::Append(const TXString &string)
{
	strVec.push_back(string);
	return *this;
}

//=======================================================================================
// Append another array 'src' to the end. Always return true.
TXStringArray& TXStringArray::Append(const TXStringArray &src)
{
	for(const auto& oneString : src.strVec)
		strVec.push_back(oneString);

	return *this;
}

//=======================================================================================
// Prepend 'string' to the front. Always return true.
TXStringArray& TXStringArray::Prepend(const TXString &string)
{
	strVec.emplace(strVec.begin(), string);
	return *this;
}

//=======================================================================================
// Erase 'nCount' elements starting from 'nIndex'. If 'nIndex' is out of range, it does
// nothing. If 'nCount' is larger than the size, it will erase to the end.
TXStringArray& TXStringArray::Erase(size_t nIndex, size_t nCount)
{
	if (nIndex < strVec.size() && nCount > 0) {
		if(nIndex + nCount >= strVec.size())
		{
			strVec.erase(strVec.begin() + nIndex, strVec.end());
		}
		else
		{
			strVec.erase(strVec.begin() + nIndex, strVec.begin() + nIndex + nCount);
		}
	}
	
	return *this;
}

//=======================================================================================
// Clear the array. The size will be zero.
TXStringArray& TXStringArray::Clear()
{
	strVec.clear();
	
	return *this;
}

//=======================================================================================
// Return the index of the first found string. Return -1 if not found. If 'bIgnoreCase'
// is true, case is ignored.
ptrdiff_t TXStringArray::Find(const TXString& str, bool bIgnoreCase /* false */) const
{
	for(size_t i = 0; i < strVec.size(); i++)
	{
		if( bIgnoreCase )
		{
			if(this->GetAt(i).EqualNoCase(str))
			{
				return i;
			}
		}
		else
		{
			if(this->GetAt(i).Equal(str) )
			{
				return i;
			}
		}
	}

	return -1;
}

//=======================================================================================
// Sort the TXStringArray by case insensitive ascending order if sortFunction is not
// provided. Otherwise, use sortFunction to sort the TXStringArray.
TXStringArray& TXStringArray::Sort(std::function<bool (const TXString&, const TXString&)> sortFunction)
{
	StrVec::iterator it1 = strVec.begin();
	StrVec::iterator it2 = strVec.end();

	if(sortFunction)
	{
		std::sort(it1, it2, sortFunction);
	}
	else
	{
		std::sort(it1, it2);	// Default: ascending, case insensitive.
	}
	
	return *this;
}

//=======================================================================================
StrVec::iterator TXStringArray::begin()
{
	return strVec.begin();
}

//=======================================================================================
StrVec::iterator TXStringArray::end()
{
	return strVec.end();
}

//=======================================================================================
StrVec::const_iterator TXStringArray::begin() const
{
	return strVec.begin();
}

//=======================================================================================
StrVec::const_iterator TXStringArray::end() const
{
	return strVec.end();
}

//=======================================================================================
char* TXGenericArray_Allocate(char& memoryCode, size_t sz)
{
	char*	newBuf	= NULL;

#if _MINICAD_
	memoryCode	= 1;
	newBuf		= (char*) Mem_NewPtr( sz );
#else
	memoryCode	= gCBP ? 1 : 0;
	if ( gCBP )	newBuf	= (char*) ::GS_NewPtr( gCBP, sz );
	else		newBuf	= (char*) malloc( sz );
#endif

	return newBuf;
}

void TXGenericArray_Dispose(char memoryCode, char* pTheData)
{
#if _MINICAD_
	if ( memoryCode == 1 ) {
		Mem_DisposePtr( (Ptr) pTheData );
	}
#else
	if ( memoryCode == 1 ) {
		// XXX Vlado
		// this may produce leaks when it was marked to use CBP
		// but now the CBP is NULL
		ASSERTN( kVStanev, gCBP );
		if ( gCBP ) ::GS_DisposePtr( gCBP, pTheData );
	}
	else {
		free( pTheData );
	}
#endif
}

/*============================================================================*/
/*============================================================================*/

#if _MINICAD_
#else
struct CallBackBlock;

void GS_GetResourceString(CallBackBlock*, short id, short index, TXString& theString, Boolean lookOnlyInCurrentFile, EEmptyStringResourceHandling debugWarning)
{
    theString = TXLegacyResource( id, index, (EEmptyHandling)debugWarning);
}
#endif

// --------------------------------------------------------------------------------------------------
TXResource::TXResource(const char* resourceIdentifier, const char* resourceStringIdentifier, EEmptyHandling allowEmpty)
{
	gSDK->GetVWResourceString( fString, resourceIdentifier, resourceStringIdentifier, allowEmpty );
	fResource	= NULL;
}

TXResource::TXResource(const char* resourceIdentifier)
{
	fResource	= gSDK->GetVWResource( resourceIdentifier );
}

TXResource::TXResource(const TXResource& src)
{
	this->operator= ( src );
}

TXResource::~TXResource()
{
	if ( fResource )
	{
		gSDK->GSDisposeHandle( fResource );
		fResource	= NULL;
	}
}

TXResource& TXResource::operator = (const TXResource& src)
{
	DSTOP((kVStanev, "not implemented and this should be hidden"));
	return *this;
}

TXResource::operator const TXString&()
{
	if ( fResource && fString.IsEmpty() )
	{
		if ( VERIFYN( kVStanev, fResource && *fResource ) )
		{
			size_t	size;
			gSDK->GSGetHandleSize( fResource, size );
			fString = size > 0 ? TXString( (const char*) *fResource, size ) : "";
		}
	}

	return fString;
}

const char* TXResource::c_str()
{
	return this->operator const TXString&();
}

size_t TXResource::Size() const
{
	size_t result = 0;
	gSDK->GSGetHandleSize( fResource, result );
	return result;
}

const void* TXResource::Buffer() const
{
	return fResource ? *fResource : NULL;
}

GSHandle TXResource::GetHandle()
{
	return fResource;
}

inline bool EndsIn(const char *str, const char *ending, const int strLen, const int endingLen)
{
	if (strLen < endingLen)
		return false;

	return (strcmp(str + strLen - endingLen, ending) == 0);
}

TXResStr::TXResStr(const char* fileName /* typically wihout path or ".vwstrings" extension*/, 
				   const char* resourceStringIdentifier, EEmptyHandling allowEmpty)
{
	static const char *vwsExt = ".vwstrings";
	static const int vwsExtLen = (int) strlen(vwsExt);

	char resourceIdentifier[256];
	int fileLen = (int) strlen(fileName);

    if (fileLen == 0)
    {
        ; // no op
    }
	else if (fileName[fileLen - 1] == '*')
	{
		sprintf(resourceIdentifier, "%s/Strings/%s", DEFAULTVWRIDENTIFIER, fileName);
		gSDK->GetVWResourceString(fString, resourceIdentifier, resourceStringIdentifier, allowEmpty);

	}
	else if (!EndsIn(fileName, vwsExt, fileLen, vwsExtLen))
	{
		sprintf(resourceIdentifier, "%s/Strings/%s.vwstrings", DEFAULTVWRIDENTIFIER, fileName);
		gSDK->GetVWResourceString(fString, resourceIdentifier, resourceStringIdentifier, allowEmpty);

	}
	else /* assume if fileName already ends in ".vwstrings" that it specifies a full VWR identifier */
	{
		gSDK->GetVWResourceString(fString, fileName, resourceStringIdentifier, allowEmpty);

	}
}

TXResStr::operator const TXString&()
{
	return fString;
}

// --------------------------------------------------------------------------------------------------
TXLegacyResource::TXLegacyResource(short stringResID, short indexID, EEmptyHandling allowEmpty)
{
	const char* szDefaultResourceIdentifier	= DEFAULTVWRIDENTIFIER;

	if (stringResID < 10000)							// The general rule before VWR resources were in place was that 
		szDefaultResourceIdentifier = "Vectorworks";	//  plug-in strings were supposed to be in >= 10000 range, "Core" strings in < 10000 range

	char resourceIdentifier[128];
	sprintf(resourceIdentifier, "%s/Strings/%d *", szDefaultResourceIdentifier, stringResID );

	char stringIdentifier[16];
	sprintf(stringIdentifier, "%d", indexID );

#if _MINICAD_
	 ::GetResourceString( fString, resourceIdentifier, stringIdentifier, allowEmpty );
#else
	gSDK->GetVWResourceString( fString, resourceIdentifier, stringIdentifier, allowEmpty );
#endif
	fResource	= NULL;
}

TXLegacyResource::TXLegacyResource(const char* defaultResourceIdentifier, short stringResID, short indexID, EEmptyHandling allowEmpty)
{
	TXString	resourceIdentifier;
	resourceIdentifier.Format( "%s/Strings/%d *", defaultResourceIdentifier, stringResID );

	TXString	stringIdentifier;
	stringIdentifier.Format( "%d", indexID );

	gSDK->GetVWResourceString( fString, resourceIdentifier, stringIdentifier, allowEmpty );
	fResource	= NULL;
}

TXLegacyResource::TXLegacyResource(short textResID)
{
	TXString	resourceIdentifier;
	resourceIdentifier.Format( "%s/Strings/HelpText.vwstrings", DEFAULTVWRIDENTIFIER );

	TXString	stringIdentifier;
	stringIdentifier.Format( "%d", textResID );

	gSDK->GetVWResourceString( fString, resourceIdentifier, stringIdentifier, eAllowEmptyResult );
	fResource	= NULL;
}

TXLegacyResource::TXLegacyResource(const char* resourceType, short resourceID)
{
	const char* szDefaultResourceIdentifier	= DEFAULTVWRIDENTIFIER;

	TXString	resourceIdentifier;
	resourceIdentifier.Format( "%s/%s/%d *", szDefaultResourceIdentifier, resourceType, resourceID );

	fResource	= gSDK->GetVWResource( resourceIdentifier );
}

TXLegacyResource::TXLegacyResource(short stringResID, short indexID, TXString& outString)
{
	const char* szDefaultResourceIdentifier	= DEFAULTVWRIDENTIFIER;

	TXString	resourceIdentifier;
	resourceIdentifier.Format( "%s/Strings/%d *", szDefaultResourceIdentifier, stringResID );

	TXString	stringIdentifier;
	stringIdentifier.Format( "%d", indexID );

	gSDK->GetVWResourceString( fString, resourceIdentifier, stringIdentifier, eDontAllowEmptyResult );
	fResource	= NULL;

	outString	= fString;
}

TXLegacyResource::TXLegacyResource(const TXLegacyResource& src)
{
	this->operator= ( src );
}

TXLegacyResource::~TXLegacyResource()
{
	if ( fResource )
	{
		gSDK->GSDisposeHandle( fResource );
		fResource	= NULL;
	}
}

TXLegacyResource& TXLegacyResource::operator = (const TXLegacyResource& src)
{
	DSTOP((kVStanev, "not implemented and this should be hidden"));
	return *this;
}

TXLegacyResource::operator const TXString&()
{
	if ( fResource && fString.IsEmpty() )
	{
		if ( VERIFYN( kVStanev, fResource && *fResource ) )
		{
			size_t	size;
			gSDK->GSGetHandleSize( fResource, size );
			fString = size > 0 ? TXString( (const char*) *fResource, size, ETXEncoding::eMacEncoded ) : "";
		}
	}

	return fString;
}

const char* TXLegacyResource::c_str()
{
	return this->operator const TXString&();
}

size_t TXLegacyResource::Size() const
{
	size_t result = 0;
	gSDK->GSGetHandleSize( fResource, result );
	return result;
}

const void* TXLegacyResource::Buffer() const
{
	return fResource ? *fResource : NULL;
}

GSHandle TXLegacyResource::GetHandle()
{
	return fResource;
}

// --------------------------------------------------------------------------------------------------
TXLegacyDialogResource::TXLegacyDialogResource(short dialogResourceID)
{
	const char* szDefaultResourceIdentifier	= DEFAULTVWRIDENTIFIER;
	gSDK->Kludge(3602, (void *)szDefaultResourceIdentifier, NULL); 

	fString.Format( "%s/DialogLayout/%d *", szDefaultResourceIdentifier, dialogResourceID ); 
}

TXLegacyDialogResource::operator const char*()
{
	return fString;
}

// --------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Implementation of class CFormatString
// ----------------------------------------------------------------------------
CFormatString::CFormatString(const TXString& format)
	: fStrToFormat( format )
{
}

CFormatString::~CFormatString()
{
}

template<typename T>
static TXString _SafeFormat(const TXString& format, T marker)
{
	static const size_t kBufferSize = 1024;
	wchar_t localBuffer[kBufferSize];

	Sint32 len = swprintf( localBuffer, kBufferSize, format, marker);

	TXString	result( localBuffer, len );
	return result;	
}

TXString CFormatString::Format()
{
	fOutBuffer.Clear();

	const TXChar* from = fStrToFormat;

	static bool bIsFirstTime = true;
	static std::vector<TXChar> mapDelimiters;

	if(bIsFirstTime)
	{
		mapDelimiters.push_back('d');
		mapDelimiters.push_back('i');
		mapDelimiters.push_back('u');
		mapDelimiters.push_back('o');
		mapDelimiters.push_back('x');
		mapDelimiters.push_back('X');
		mapDelimiters.push_back('f');
		mapDelimiters.push_back('F');
		mapDelimiters.push_back('e');
		mapDelimiters.push_back('E');
		mapDelimiters.push_back('g');
		mapDelimiters.push_back('G');
		mapDelimiters.push_back('a');
		mapDelimiters.push_back('A');
		mapDelimiters.push_back('c');
		mapDelimiters.push_back('s');
		mapDelimiters.push_back('p');
		mapDelimiters.push_back('n');

		bIsFirstTime = false;
	}

	enum EState
	{
		state_running,
		state_param
	};

	EState		state	= state_running;
	TXString	currentFormatSpec;
	size_t		paramIndex = 0;

	// Loop through the format, copying plain characters and parsing format specifications
	while ( true )
	{
		if (state == state_running)
		{
			if (*from == 0)
			{
				// reached out the end of the source
				break;
			}
			else if (*from == '%')
			{
				// potential parameter
				currentFormatSpec = *from;
				state = state_param;
			}
			else
			{
				// plain characters
				fOutBuffer += *from;
			}
		}
		else if (state == state_param)
		{
			if (*from == '%' ||
				*from == ' ' ||
				*from == 0)
			{
				// just print to output
				size_t	count = currentFormatSpec.GetLength();
				if (count > 0)
				{
					fOutBuffer += currentFormatSpec;
				}

				currentFormatSpec.Clear();	// reset current format specifier storage
				state = state_running;		// transition the state machine

				// reached out the end of the source
				if (*from == 0)
					break;
			}
			else
			{
				if (*from)
					currentFormatSpec += *from;

				// search for a type specifier as delimiter
				if (std::find( mapDelimiters.begin(), mapDelimiters.end(), *from ) != mapDelimiters.end() )
				{
					if (paramIndex < farrParams.size())
					{
						// current input parameter to process
						const SParameter& param = farrParams[paramIndex];

						// the parameter type matches the format specifier
						// preformat the parameter value based on the format specifier and print to output
						switch ( param.fType )
						{
							case EParamType::PT_SHORT:		fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueShort() );		break;
							case EParamType::PT_INT:		fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueInt() );			break;
							case EParamType::PT_LONG:		fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueLong() );			break;
							case EParamType::PT_LONGLONG:	fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueLongLong() );		break;
							case EParamType::PT_USHORT:		fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueUShort() );		break;
							case EParamType::PT_UINT:		fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueUInt() );			break;
							case EParamType::PT_ULONG:		fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueULong() );		break;
							case EParamType::PT_ULONGLONG:	fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueULongLong() );	break;
							case EParamType::PT_REAL:		fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueReal() );			break;
							case EParamType::PT_VOIDPTR:	fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueVoidPtr() );		break;

							case EParamType::PT_STRING:
								fOutBuffer += param.GetValueString();
								break;

							case EParamType::PT_CHAR:
								if ( currentFormatSpec == "%c" || currentFormatSpec == "%s" )
									fOutBuffer += param.GetValueChar();
								else
									fOutBuffer += ::_SafeFormat( currentFormatSpec, param.GetValueInt() );
								break;

							default:
								if ( currentFormatSpec.GetLength() )
									fOutBuffer += currentFormatSpec;
								break;
						}

						paramIndex++;  // move to the next parameter
					}
					else
					{
						// something went wrong, we've run out of parameters
						// just print to output
						size_t	count = currentFormatSpec.GetLength();
						if (count > 0)
						{
							fOutBuffer += currentFormatSpec;
						}
					}

					currentFormatSpec = "";    // reset current format specifier storage
					state = state_running;     // transition the state machine
				}
			}
		}

		from++;  // advance the source
	}

	return fOutBuffer;
}

CFormatString& CFormatString::Param(short value)
{
	SParameter param;
	param.fType 	= EParamType::PT_SHORT;
	param.fValShort	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(int value)
{
	SParameter param;
	param.fType 	= EParamType::PT_INT;
	param.fValInt 	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(long value)
{
	SParameter param;
	param.fType 	= EParamType::PT_LONG;
	param.fValLong 	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(long long value)
{
	SParameter param;
	param.fType 		= EParamType::PT_LONGLONG;
	param.fValLongLong 	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(unsigned short value)
{
	SParameter param;
	param.fType 		= EParamType::PT_USHORT;
	param.fValUShort 	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(unsigned int value)
{
	SParameter param;
	param.fType 	= EParamType::PT_UINT;
	param.fValUInt 	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(unsigned long value)
{
	SParameter param;
	param.fType 	= EParamType::PT_ULONG;
	param.fValULong = value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(unsigned long long value)
{
	SParameter param;
	param.fType 		= EParamType::PT_ULONGLONG;
	param.fValULongLong = value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(double value)
{
	SParameter param;
	param.fType 	= EParamType::PT_REAL;
	param.fValReal 	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(char value)
{
	TXString	str( value, 1 );

	SParameter param;
	param.fType 	= EParamType::PT_CHAR;
	param.fValChar 	= str.GetLength() > 0 ? *str.operator const wchar_t *() : 0;
	param.fValInt	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(const char* value)
{
	SParameter param;
	param.fType 	= EParamType::PT_STRING;
	param.fValStr 	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(wchar_t value)
{
	SParameter param;
	param.fType 	= EParamType::PT_CHAR;
	param.fValChar 	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(const wchar_t* value)
{
	SParameter param;
	param.fType 	= EParamType::PT_STRING;
	param.fValStr 	= value;
	farrParams.push_back(param);

	return *this;
}


CFormatString& CFormatString::Param(const void* value)
{
	SParameter param;
	param.fType 	= EParamType::PT_VOIDPTR;
	param.fValVoid 	= value;
	farrParams.push_back(param);

	return *this;
}

CFormatString& CFormatString::Param(const TXString& value)
{
	SParameter param;
	param.fType 	= EParamType::PT_STRING;
	param.fValStr 	= value;
	farrParams.push_back(param);

	return *this;
}

short CFormatString::SParameter::GetValueShort() const
{
	short result = 0;

	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<short>(fValShort);			break;
		case EParamType::PT_INT:		result = static_cast<short>(fValInt);	 		break;
		case EParamType::PT_LONG:		result = static_cast<short>(fValLong);		 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<short>(fValLongLong);		break;
		case EParamType::PT_USHORT:		result = static_cast<short>(fValUShort);		break;
		case EParamType::PT_UINT:		result = static_cast<short>(fValUInt);	 		break;
		case EParamType::PT_ULONG:		result = static_cast<short>(fValULong);		 	break;
		case EParamType::PT_ULONGLONG:	result = static_cast<short>(fValULongLong);		break;
		case EParamType::PT_REAL:		result = static_cast<short>(fValReal);			break;
		case EParamType::PT_CHAR:		result = static_cast<short>(fValChar);			break;
		default: break;
	}

	return result;
}

int CFormatString::SParameter::GetValueInt() const
{
	int result = 0;
	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<int>(fValShort);			break;
		case EParamType::PT_INT:		result = static_cast<int>(fValInt);	 			break;
		case EParamType::PT_LONG:		result = static_cast<int>(fValLong);		 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<int>(fValLongLong);		break;
		case EParamType::PT_USHORT:		result = static_cast<int>(fValUShort);			break;
		case EParamType::PT_UINT:		result = static_cast<int>(fValUInt);	 		break;
		case EParamType::PT_ULONG:		result = static_cast<int>(fValULong);		 	break;
		case EParamType::PT_ULONGLONG:	result = static_cast<int>(fValULongLong);		break;
		case EParamType::PT_REAL:		result = static_cast<int>(fValReal);			break;
		case EParamType::PT_CHAR:		result = static_cast<int>(fValChar);			break;
		default: break;
	}

	return result;
}

long CFormatString::SParameter::GetValueLong() const
{
	long result = 0;

	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<long>(fValShort);			break;
		case EParamType::PT_INT:		result = static_cast<long>(fValInt);	 		break;
		case EParamType::PT_LONG:		result = static_cast<long>(fValLong);		 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<long>(fValLongLong);		break;
		case EParamType::PT_USHORT:		result = static_cast<long>(fValUShort);			break;
		case EParamType::PT_UINT:		result = static_cast<long>(fValUInt);	 		break;
		case EParamType::PT_ULONG:		result = static_cast<long>(fValULong);		 	break;
		case EParamType::PT_ULONGLONG:	result = static_cast<long>(fValULongLong);		break;
		case EParamType::PT_REAL:		result = static_cast<long>(fValReal);			break;
		case EParamType::PT_CHAR:		result = static_cast<long>(fValChar);			break;
		default: break;
	}

	return result;
}

long long CFormatString::SParameter::GetValueLongLong() const
{
	long long result = 0;

	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<long long>(fValShort);			break;
		case EParamType::PT_INT:		result = static_cast<long long>(fValInt);	 		break;
		case EParamType::PT_LONG:		result = static_cast<long long>(fValLong);		 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<long long>(fValLongLong);		break;
		case EParamType::PT_USHORT:		result = static_cast<long long>(fValUShort);		break;
		case EParamType::PT_UINT:		result = static_cast<long long>(fValUInt);	 		break;
		case EParamType::PT_ULONG:		result = static_cast<long long>(fValULong);		 	break;
		case EParamType::PT_ULONGLONG:	result = static_cast<long long>(fValULongLong);		break;
		case EParamType::PT_REAL:		result = static_cast<long long>(fValReal);			break;
		case EParamType::PT_CHAR:		result = static_cast<long long>(fValChar);			break;
		default: break;
	}

	return result;
}

unsigned short CFormatString::SParameter::GetValueUShort() const
{
	unsigned short result = 0;

	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<unsigned short>(fValShort);		break;
		case EParamType::PT_INT:		result = static_cast<unsigned short>(fValInt);	 		break;
		case EParamType::PT_LONG:		result = static_cast<unsigned short>(fValLong);		 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<unsigned short>(fValLongLong);		break;
		case EParamType::PT_USHORT:		result = static_cast<unsigned short>(fValUShort);		break;
		case EParamType::PT_UINT:		result = static_cast<unsigned short>(fValUInt);	 		break;
		case EParamType::PT_ULONG:		result = static_cast<unsigned short>(fValULong);	 	break;
		case EParamType::PT_ULONGLONG:	result = static_cast<unsigned short>(fValULongLong);	break;
		case EParamType::PT_REAL:		result = static_cast<unsigned short>(fValReal);			break;
		case EParamType::PT_CHAR:		result = static_cast<unsigned short>(fValChar);			break;
		default: break;
	}

	return result;
}

unsigned CFormatString::SParameter::GetValueUInt() const
{
	unsigned	result = 0;

	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<unsigned>(fValShort);			break;
		case EParamType::PT_INT:		result = static_cast<unsigned>(fValInt);	 		break;
		case EParamType::PT_LONG:		result = static_cast<unsigned>(fValLong);		 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<unsigned>(fValLongLong);		break;
		case EParamType::PT_USHORT:		result = static_cast<unsigned>(fValUShort);			break;
		case EParamType::PT_UINT:		result = static_cast<unsigned>(fValUInt);	 		break;
		case EParamType::PT_ULONG:		result = static_cast<unsigned>(fValULong);		 	break;
		case EParamType::PT_ULONGLONG:	result = static_cast<unsigned>(fValULongLong);		break;
		case EParamType::PT_REAL:		result = static_cast<unsigned>(fValReal);			break;
		case EParamType::PT_CHAR:		result = static_cast<unsigned>(fValChar);			break;
		default: break;
	}

	return result;
}

unsigned long CFormatString::SParameter::GetValueULong() const
{
	unsigned long	result = 0;

	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<unsigned long>(fValShort);			break;
		case EParamType::PT_INT:		result = static_cast<unsigned long>(fValInt);	 		break;
		case EParamType::PT_LONG:		result = static_cast<unsigned long>(fValLong);		 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<unsigned long>(fValLongLong);		break;
		case EParamType::PT_USHORT:		result = static_cast<unsigned long>(fValUShort);		break;
		case EParamType::PT_UINT:		result = static_cast<unsigned long>(fValUInt);	 		break;
		case EParamType::PT_ULONG:		result = static_cast<unsigned long>(fValULong);		 	break;
		case EParamType::PT_ULONGLONG:	result = static_cast<unsigned long>(fValULongLong);		break;
		case EParamType::PT_REAL:		result = static_cast<unsigned long>(fValReal);			break;
		case EParamType::PT_CHAR:		result = static_cast<unsigned long>(fValChar);			break;
		default: break;
	}

	return result;
}

unsigned long long CFormatString::SParameter::GetValueULongLong() const
{
	unsigned long long	result = 0;

	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<unsigned long long>(fValShort);		break;
		case EParamType::PT_INT:		result = static_cast<unsigned long long>(fValInt);	 		break;
		case EParamType::PT_LONG:		result = static_cast<unsigned long long>(fValLong);		 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<unsigned long long>(fValLongLong);		break;
		case EParamType::PT_USHORT:		result = static_cast<unsigned long long>(fValUShort);		break;
		case EParamType::PT_UINT:		result = static_cast<unsigned long long>(fValUInt);	 		break;
		case EParamType::PT_ULONG:		result = static_cast<unsigned long long>(fValULong);		break;
		case EParamType::PT_ULONGLONG:	result = static_cast<unsigned long long>(fValULongLong);	break;
		case EParamType::PT_REAL:		result = static_cast<unsigned long long>(fValReal);			break;
		case EParamType::PT_CHAR:		result = static_cast<unsigned long long>(fValChar);			break;
		default: break;
	}

	return result;
}

double CFormatString::SParameter::GetValueReal() const
{
	double	result = 0;

	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<double>(fValShort);		break;
		case EParamType::PT_INT:		result = static_cast<double>(fValInt);	 		break;
		case EParamType::PT_LONG:		result = static_cast<double>(fValLong);		 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<double>(fValLongLong);		break;
		case EParamType::PT_USHORT:		result = static_cast<double>(fValUShort);		break;
		case EParamType::PT_UINT:		result = static_cast<double>(fValUInt);	 		break;
		case EParamType::PT_ULONG:		result = static_cast<double>(fValULong);		break;
		case EParamType::PT_ULONGLONG:	result = static_cast<double>(fValULongLong);	break;
		case EParamType::PT_REAL:		result = static_cast<double>(fValReal);			break;
		case EParamType::PT_CHAR:		result = static_cast<double>(fValChar);			break;
		default: break;
	}

	return result;
}

wchar_t CFormatString::SParameter::GetValueChar() const
{
	wchar_t result  = 0;

	switch ( fType )
	{
		case EParamType::PT_SHORT:		result = static_cast<wchar_t>(fValShort);		break;
		case EParamType::PT_INT:		result = static_cast<wchar_t>(fValInt); 		break;
		case EParamType::PT_LONG:		result = static_cast<wchar_t>(fValLong);	 	break;
		case EParamType::PT_LONGLONG:	result = static_cast<wchar_t>(fValLongLong);	break;
		case EParamType::PT_USHORT:		result = static_cast<wchar_t>(fValUShort);		break;
		case EParamType::PT_UINT:		result = static_cast<wchar_t>(fValUInt);		break;
		case EParamType::PT_ULONG:		result = static_cast<wchar_t>(fValULong);		break;
		case EParamType::PT_ULONGLONG:	result = static_cast<wchar_t>(fValULongLong);	break;
		case EParamType::PT_REAL:		result = static_cast<wchar_t>(fValReal);		break;
		case EParamType::PT_CHAR:		result = static_cast<wchar_t>(fValChar);		break;
		case EParamType::PT_STRING:		result = fValStr.GetLength() > 0 ? (*fValStr.operator const wchar_t *()) : 0;	break;
		default: break;
	}

	return result;
}

const void* CFormatString::SParameter::GetValueVoidPtr() const
{
	const void* result = nullptr;
	if ( fType == EParamType::PT_VOIDPTR )
		result = fValVoid;

	return result;
}

TXString CFormatString::SParameter::GetValueString() const
{
	switch ( fType )
	{
		case EParamType::PT_STRING:		return fValStr;
		default:						return TXString();
	}
}

//=======================================================================================

void swap(TXString& lhs, TXString& rhs)
{
	lhs.swap(rhs);
}

//=======================================================================================

/*============================================================================*/
/*============================================================================*/

void NNAUppercaseText(char* textPtr, Sint32 len, int scriptCode)
{
	// This function does not support Unicode and should not be used.
	DSTOP((kPChang, "NNAUppercaseText is deprecated. Please don't use it."));
	
#if GS_MAC
	CFStringRef nonUppercaseString = CFStringCreateWithBytes(NULL,
															 (Uint8*)textPtr,
															 len,
															 kCFStringEncodingUTF8,
															 false);
	
	if (!VERIFYN(kEveryone, nonUppercaseString != NULL))
		return;
	
	CFMutableStringRef candidateString = CFStringCreateMutableCopy(NULL,
																   len,
																   nonUppercaseString);
	
	CFRelease(nonUppercaseString);
	if (!VERIFYN(kEveryone, nonUppercaseString != NULL))
		return;
	
	CFStringUppercase(candidateString, CFLocaleGetSystem());
	
	CFStringGetBytes(candidateString,
					 CFRangeMake(0, len),
					 kCFStringEncodingUTF8,
					 0,
					 false,
					 (Uint8*)textPtr,
					 len,
					 NULL);
	
	CFRelease(candidateString);
#else
	LCID locale = LOCALE_SYSTEM_DEFAULT;
	if (scriptCode == -2)
	{
		locale = LOCALE_USER_DEFAULT;
	}

	// Non-Unicode
	LCMapStringA(locale, LCMAP_UPPERCASE, textPtr, len, textPtr, len);
#endif
}



void NNANumToString(Sint32 num, unsigned char* str, size_t strSize)
{
	TXString::ToStringInt(num).CopyInto(str, strSize);
}

void NNANumToString(Sint32 num, TXString& str)
{
	str = TXString::ToStringInt(num);
}

void NNAStringToNum(const unsigned char * theString, Sint32 *theNum)
{
	if (!VERIFYN(kEveryone, theNum != NULL))
		return;

	TXString candidateString(theString);
	*theNum = candidateString.atoi();
}

void NNAParseName(const TXString& name, int& numbParts, TXStringArray& parts)
{
	const int kMaxLevels = 4;
	numbParts = 1;
	ptrdiff_t charIndex = 0;
	ptrdiff_t dashIndex = name.Find('-', charIndex);
	if (dashIndex == charIndex) {
		dashIndex = name.Find('-', charIndex + 1);
		if (dashIndex == charIndex + 1)
			dashIndex = name.Find('-', charIndex + 2);
	}
	while (dashIndex != -1 && dashIndex < (ptrdiff_t)(name.GetLength() - 1) && numbParts < kMaxLevels)
	{
		parts.Append(name.Mid(charIndex, dashIndex - charIndex)); //-V106
		numbParts++;
		charIndex = dashIndex + 1;
		dashIndex = name.Find('-', charIndex); //-V106
		if (dashIndex == charIndex) {
			dashIndex = name.Find('-', charIndex + 1); //-V106
			if (dashIndex == charIndex + 1)
				dashIndex = name.Find('-', charIndex + 2); //-V106
		}
	}
	if (numbParts == 1)
		parts.Append(name);
	else
		parts.Append(name.Mid(charIndex)); //-V106
	
}

/**************************************************/
/* Unicode Character String Manipulation Routines */
/**************************************************/


/***************************************/
/* Unicode Encoding Converter Routines */
/***************************************/

//*****************************************************************************
//
// Function Name:  StringToUnicodeMaxChars
//
// Description:
//	Returns the maximum number of Unicode characters (with a terminating NULL
//	word) required to represent a non-Unicode C- or Pascal-style string of the
//	specified number of character bytes.  Note that this is completely
//	simplistic, is based only on the length of the string and ignores its
//	encoding.
//
// Parameters:
//	srcLen - Number of character bytes in the C- or Pascal-style string to be
//	          converted (simply call strlen or GetLength on the string)
//
// Return Value:
//	Maximum number of Unicode characters (including NULL terminator) required
//	to represent a string of the specified length in a non-Unicode encoding
//
// Created by:  Michael Hartman, January 2005
//
//*****************************************************************************

size_t StringToUnicodeMaxChars (size_t srcLen)
{
	return(srcLen + 1);
} // StringToUnicodeMaxChars


//*****************************************************************************
//
// Function Name:  StringToUnicode (character array version)
//
// Description:
//	Converts the characters of the specified encoding in a character array to
//	an array of Unicode characters in UTF-16 encoding form.  Precomposed
//	Unicode characters are preferred in the converted string (but the
//	Macintosh does not permit specifying this as of OS X 10.3.7).
//	A terminating NULL word is NOT added following the converted characters.
//
// Parameters:
//	srcEncoding - Platform-specific text encoding value for the source
//	               string's characters
//	srcArray    - Pointer to an array containing the characters to be
//	               converted; these may be 8- or 16-bit depending on encoding
//	srcLen      - Number of 8-bit bytes (always) in srcArray containing
//	               characters to be converted
//	dstUCArray  - Pointer to an array of 16-bit words for the converted
//	               Unicode characters to be returned in (no terminator added)
//	maxDstChars - Maximum number of 16-bit words that dstUCArray can hold (note
//	               that surrogate and decomposed characters are > 16 bits)
//	pDstLen     - Returns the number of 16-bit words the converted characters
//	               occupy in dstUCArray
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination array; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringToUnicode (GSTextEncoding srcEncoding, const char* srcArray,
                       size_t srcLen, UCCharPtr dstUCArray,
                       size_t maxDstChars, size_t* pDstLen)
{
	bool	success = false;
	
	/* Check the Destination Array Provided */
	/* ------------------------------------ */
	if (maxDstChars == 0) {
		*pDstLen = 0;
		return(false);
	}
	if (!VERIFYPOINTER(kMike, dstUCArray, (maxDstChars*sizeof(UCChar)))) {
		*pDstLen = 0;
		return(false);
	}
	
	/* Convert the Supplied Characters to Unicode */
	/* ------------------------------------------ */
	if (srcLen == 0) {
		/* Source Array Is Empty */
		/* --------------------- */
		dstUCArray[0] = NULL;  // Just for grins; room available in this case
		*pDstLen = 0;
		success = true;
		}
	else {
		/* Source Array Is Not Empty */
		/* ------------------------- */
#if GS_WIN
		/* Convert the Source Text in the Specified */
		/*  Encoding to Unicode and Check for Error */
		// Non-zero options are a problem for some encodings, but we don't
		// want accented Unicode characters becoming two characters, so
		// we use MB_PRECOMPOSED unless srcEncoding is CP_SYMBOL; if this
		// is changed, a corresponding change should be made to the
		// WideCharToMultiByte call in UnicodeToString below
		DWORD mapOptions;
		if (srcEncoding == CP_SYMBOL || srcEncoding == CP_UTF8)
			mapOptions = 0;
		else
			mapOptions = MB_PRECOMPOSED;
		*pDstLen = MultiByteToWideChar(srcEncoding, mapOptions, 
		                 srcArray, (int)srcLen, (LPWSTR) dstUCArray, (int)maxDstChars);
		success = (*pDstLen != 0);  // Zero always returned on failure, unlike Mac
#else
        // This was sometimes called with strings that weren't null-terminated.
        // Just to be sure, create temporary string and append null.
        char tempString[srcLen+1];
        strncpy(tempString, srcArray, srcLen);
        tempString[srcLen] = '\0';
        CFStringRef cfStr = CFStringCreateWithCString(NULL, tempString, srcEncoding);
        if (cfStr)
        {
            CFIndex len = CFStringGetLength(cfStr);
            if (len)
            {
                CFStringGetBytes(cfStr, CFRangeMake(0, len), kCFStringEncodingUnicode, '?', false, (UInt8 *)dstUCArray, maxDstChars * sizeof(UCChar), (CFIndex*)pDstLen);
                *pDstLen /= sizeof(UniChar);
                success = true;
            }
			else
			{
				*pDstLen = 0;
				success = false;
			}
            CFRelease(cfStr);
        }
#endif  // GS_WIN
	}
	return(success);
} // StringToUnicode


//*****************************************************************************
//
// Function Name:  StringToUnicode (C string version)
//
// Description:
//	Converts the characters of the specified encoding in a C-style string to
//	an array of Unicode characters in UTF-16 encoding form.  Precomposed
//	Unicode characters are preferred in the converted string (but the
//	Macintosh does not permit specifying this as of OS X 10.3.7).
//	A terminating NULL word is added following the converted characters.
//
// Parameters:
//	srcEncoding - Platform-specific text encoding value for the source
//	               string's characters
//	srcStr      - Pointer to a C-style string containing the characters to be
//	               converted
//	dstUCStr    - Pointer to an array of 16-bit words for the converted
//	               Unicode characters to be returned in (NULL-word terminated)
//	maxDstChars - Maximum number of 16-bit words that dstUCStr can hold (note
//	               that surrogate and decomposed characters are > 16 bits);
//	               to handle all encodings safely, this must be:
//	               maxDstChars = (strlen(srcStr) * 3) + 1
//	pDstLen     - Returns the number of 16-bit words the converted string
//	               occupies in dstUCStr, not including the NULL-word terminator
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination array; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringToUnicode (GSTextEncoding srcEncoding, const char* srcStr,
              UCStrPtr dstUCStr, size_t maxDstChars, size_t* pDstLen)
{
	bool	success;
	
	/* Call the Character Array Version and Append   */
	/*  a NULL-Word Terminator to the Returned Array */
	success = StringToUnicode(srcEncoding, srcStr, strlen(srcStr),
	                           dstUCStr, (maxDstChars-1), pDstLen);
	if (success || (*pDstLen < maxDstChars))
	  dstUCStr[*pDstLen] = NULL;
	return(success);
} // StringToUnicode


//*****************************************************************************
//
// Function Name:  StringToUnicode (Pascal string version)
//
// Description:
//	Converts the characters of the specified encoding in a Pascal-style string
//	to an array of Unicode characters in UTF-16 encoding form.  Precomposed
//	Unicode characters are preferred in the converted string (but the
//	Macintosh does not permit specifying this as of OS X 10.3.7).
//	A terminating NULL word is added following the converted characters.
//	Note that this routine simply converts the source string to C-style and
//	calls its routine.
//
// Parameters:
//	srcEncoding - Platform-specific text encoding value for the source
//	               string's characters
//	srcStr      - Pascal-style string containing the characters to be converted
//	dstUCStr    - Pointer to an array of 16-bit words for the converted
//	               Unicode characters to be returned in (NULL-word terminated)
//	maxDstChars - Maximum number of 16-bit words that dstUCStr can hold (note
//	               that surrogate and decomposed characters are > 16 bits);
//	               to handle all encodings safely, this must be:
//	               maxDstChars = (GetLength(srcStr) * 3) + 1
//	pDstLen     - Returns the number of 16-bit words the converted string
//	               occupies in dstUCStr, not including the NULL-word terminator
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination array; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringToUnicode (GSTextEncoding srcEncoding, ConstGSStr255Param srcStr,
              UCStrPtr dstUCStr, size_t maxDstChars, size_t* pDstLen)
{
	bool	success;
	
	/* Call the Character Array Version and Append   */
	/*  a NULL-Word Terminator to the Returned Array */
	success = StringToUnicode(srcEncoding, (char*)&srcStr[1], GetLength(srcStr),
	                           dstUCStr, (maxDstChars-1), pDstLen);
	if (success || (*pDstLen < maxDstChars))
	  dstUCStr[*pDstLen] = NULL;
	return(success);
} // StringToUnicode


//*****************************************************************************
//
// Function Name:  UnicodeToStringMaxChars
//
// Description:
//	Returns the maximum number of UTF-8 bytes in a C- or
//	Pascal-style string (with a terminating NULL character or preceding length
//	byte) required to represent the specified number of Unicode characters.
//	Note that this calculates
//	the worst case.  But using this and reallocating the string buffer
//	after calling UnicodeToString should usually be faster than doing the
//	conversion an extra time beforehand to get the character count.
//
// Parameters:
//	srcLen - Number of characters in the Unicode string to be converted
//
// Return Value:
//	Maximum number of UTF-8 bytes (including NULL terminator
//	or preceding length byte) required to represent a Unicode string of the
//	specified length in UTF-8 encoding
//
// Created by:  Michael Hartman, January 2005
//
//*****************************************************************************

size_t UnicodeToStringMaxChars (size_t srcLen)
{
	return((size_t)(srcLen * 4) + 1);
} // UnicodeToStringMaxChars


//*****************************************************************************
//
// Function Name:  UnicodeToString (character array version)
//
// Description:
//	Converts the characters of Unicode encoding and UTF-16 form in an array to
//	a character array in the specified encoding.  A terminating NULL byte is
//	NOT added following the converted characters.
//
// Parameters:
//	dstEncoding - Platform-specific text encoding value for the destination
//	               string's characters
//	srcUCArray  - Pointer to an array of 16-bit words containing the Unicode
//	               characters to be converted
//	srcLen      - Number of words in srcUCArray containing characters to be
//	               converted
//	dstArray    - Pointer to an array for the converted characters to be
//	               returned in (may be 8- or 16-bit depending on encoding)
//	maxDstBytes - Maximum number of 8-bit bytes (always) that dstArray can
//	               hold; to handle all encodings, this must be:
//	               maxDstChars = (srcLen * 1.5) + 1
//	               (just call UnicodeToStringMaxChars)
//	pDstLen     - Returns the number of 8-bit bytes the converted characters
//	               occupy in dstArray
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination string; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool UnicodeToString (GSTextEncoding dstEncoding, ConstUCCharPtr srcUCArray,
      size_t srcLen, char* dstArray, size_t maxDstBytes, size_t* pDstLen)
{
	/* Check the Destination String Provided */
	/* ------------------------------------- */
	if (maxDstBytes == 0) return(false);
	if (!VERIFYPOINTER(kMike, dstArray, maxDstBytes)) {
		*pDstLen = 0;
		return(false);
	}
	
	if (srcLen == 0) {
		/* Source Array Is Empty */
		/* --------------------- */
		dstArray[0] = NULL;  // Just for grins; room available in this case
		*pDstLen = 0;
		return(true);
	}
	else {
		/* Source Array Is Not Empty */
		/* ------------------------- */
#if GS_WIN
		
		/* Convert the Unicode Text to the Specified */
		/*  Destination Encoding and Check for Error */
		// Non-zero mapping options are a problem with some encodings,
		//  but we don't want accented Unicode characters becoming two
		*pDstLen = WideCharToMultiByte(dstEncoding, WC_COMPOSITECHECK, (LPCWSTR) srcUCArray, 
		            (int)srcLen, dstArray, (int)maxDstBytes, NULL, NULL);
		
		if (*pDstLen == 0)
			return false;

		return true;
#else
        bool success = false;
		CFStringRef cfStr = CFStringCreateWithCharacters(NULL, srcUCArray, srcLen);
        if (cfStr)
        {
            int len = CFStringGetLength(cfStr);
            CFRange fullRange = CFRangeMake(0, len);            
            if (CFStringGetBytes(cfStr, fullRange, dstEncoding, '?', 0, (UInt8 *)dstArray, maxDstBytes, (CFIndex *)pDstLen))
                success = true;
            
            CFRelease(cfStr);
        }
        
        return success;
#endif  // GS_WIN
	}
} // UnicodeToString


//*****************************************************************************
//
// Function Name:  UnicodeToString (C string version)
//
// Description:
//	Converts the characters of Unicode encoding and UTF-16 form in an array to
//	a C-style string in the specified encoding.
//
// Parameters:
//	dstEncoding - Platform-specific text encoding value for the destination
//	               string's characters
//	srcUCStr    - Pointer to an array of 16-bit words containing the Unicode
//	               characters to be converted, terminated with a NULL word
//	dstStr      - Pointer to a C-style string for the converted characters
//	               to be returned in
//	maxDstBytes - Maximum number of 8-bit bytes that dstStr can hold
//	               (including the terminating NULL); to handle all
//	               encodings, this must be:
//	               maxDstChars = (StringLength(srcUCStr) * 1.5) + 1
//	               (just call UnicodeToStringMaxChars)
//	pDstLen     - Returns the number of 8-bit bytes the converted characters
//	               occupy in dstStr, not including the terminating NULL byte
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination string; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool UnicodeToString (GSTextEncoding dstEncoding, ConstUCStrPtr srcUCStr,
                       char* dstStr, size_t maxDstBytes, size_t* pDstLen)
{
	bool		success;
	
	/* Call the Character Array Version and Append   */
	/*  a NULL-Byte Terminator to the Returned Array */
	success = UnicodeToString(dstEncoding, srcUCStr, StringLength(srcUCStr),
	                           dstStr, (maxDstBytes-1), pDstLen);
	if (success || (*pDstLen < maxDstBytes))
	  dstStr[*pDstLen] = NULL;
	return(success);
} // UnicodeToString


//*****************************************************************************
//
// Function Name:  UnicodeToString (Pascal string version)
//
// Description:
//	Converts the characters of Unicode encoding and UTF-16 form in an array to
//	a Pascal-style string in the specified encoding.  Note that this routine
//	simply calls the C-style routine and converts its result to Pascal-style.
//
// Parameters:
//	dstEncoding - Platform-specific text encoding value for the destination
//	               string's characters
//	srcUCStr    - Pointer to an array of 16-bit words containing the Unicode
//	               characters to be converted, terminated with a NULL word
//	dstStr      - Pointer to a Pascal-style string for the converted characters
//	               to be returned in
//	maxDstBytes - Maximum number of 8-bit bytes that dstStr can hold
//	               (including the preceding length byte); to handle all
//	               encodings, this must be:
//	               maxDstChars = (StringLength(srcUCStr) * 1.5) + 1
//	               (just call UnicodeToStringMaxChars)
//	pDstLen     - Returns the number of 8-bit bytes the converted characters
//	               occupy in dstStr, not including the preceding length byte
//
// Return Value:
//	Whether the conversion was successful.  Failures include not enough space
//	in the destination string; source characters that can't be converted are
//	not considered a failure [a richer return type could be considered].
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool UnicodeToString (GSTextEncoding dstEncoding, ConstUCStrPtr srcUCStr,
                       GSStringPtr dstStr, size_t maxDstBytes, size_t* pDstLen)
{
	bool	success;
	char	dstCStr[256];
	
	/* Call the C-String Version and Copy a  */
	/*  Successful Result to a Pascal String */
	ASSERTN(kMike, (maxDstBytes <= 256));
	success = UnicodeToString(dstEncoding, srcUCStr, dstCStr, sizeof(dstCStr),
	                           pDstLen);
	if (success) {
		StringCopy(dstCStr, dstStr, maxDstBytes);
		if (strlen(dstCStr) > (maxDstBytes - 1)) success = false;
		}
	else {
		SetLength(dstStr, 0);
	}
	*pDstLen = GetLength(dstStr);
	return(success);
} // UnicodeToString


/*============================================================================*/
/****************************************/
/* Unicode String Manipulation Routines */
/****************************************/


//*****************************************************************************
//
// Function Name:  StringLength
//
// Description:
//	Determines the number of 16-bit words that contain characters in a Unicode
//	string.  For our purposes, a Unicode string is an array of UTF-16
//	characters that is terminated with a NULL word (not included in length).
//	This is thus a syntactic rather than semantic character count
//	(e.g. a decomposed character counts per code-point, not as one character,
//	and a surrogate pair counts as two words, not as one character).
//
// Parameters:
//	ucString - Pointer to a UTF-16 string (NULL-word terminated UCChar array)
//
// Return Value:
//	Whether a cluster break was located
//
// Created by:  Michael Hartman, February 2005
//
//*****************************************************************************

size_t StringLength (ConstUCStrPtr ucString)
{
	size_t	len;
	
	len = 0;
	while (ucString[len] != 0) {
		len++;
	}
	return(len);
} // StringLength


//*****************************************************************************
//
// Function Name:  StringEqual (terminated string version)
//
// Description:
//	Determines whether the two strings of UTF-16 characters are equivalent
//	according to Unicode rules (as implemented in the underlying OS).  This
//	means, for example, that precomposed and decomposed versions of a character
//	are equal.  The comparison can be specified as case-insensitive or not.
//
// Parameters:
//	str1 - Pointer to a UTF-16 string (NULL-word terminated UCChar array)
//	str2 - Pointer to a UTF-16 string (NULL-word terminated UCChar array)
//
// Return Value:
//	Whether the two strings are equivalent by Unicode rules
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringEqual (ConstUCStrPtr str1, ConstUCStrPtr str2, bool ignoreCase)
{
	return(StringEqual(str1, StringLength(str1), str2, StringLength(str2),
	        ignoreCase));
} // StringEqual


//*****************************************************************************
//
// Function Name:  StringEqual (character array version)
//
// Description:
//	Determines whether the two arrays of UTF-16 characters are equivalent
//	according to Unicode rules (as implemented in the underlying OS).  This
//	means, for example, that precomposed and decomposed versions of a character
//	are equal.  The comparison can be specified as case-insensitive or not.
//
// Parameters:
//	chars1 - Pointer to an array of 16-bit words containing the UTF-16
//	          characters to be compared
//	len1   - Number of 16-bit words in 1 containing characters to be compared
//	chars2 - Pointer to an array of 16-bit words containing the UTF-16
//	          characters to be compared
//	len2   - Number of 16-bit words in 2 containing characters to be compared
//
// Return Value:
//	Whether the two arrays of characters are equivalent by Unicode rules
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool StringEqual (ConstUCCharPtr chars1, size_t len1,
                   ConstUCCharPtr chars2, size_t len2, bool ignoreCase)
{
	bool	equalResult;
	
	if ((len1 == 0) || (len2 == 0)) return(len1 == len2);
	
#if GS_WIN
	Uint32	compareFlags;
	Sint32	orderResult;
	
	compareFlags = NORM_IGNOREWIDTH | SORT_STRINGSORT;
	if (ignoreCase) compareFlags |= NORM_IGNORECASE;
	orderResult = CompareStringW(LOCALE_USER_DEFAULT, compareFlags,
	                              (LPCWSTR) chars1, (int)len1, (LPCWSTR) chars2, (int)len2);
	equalResult = (orderResult == CSTR_EQUAL);  // If error, != more probable
	
#else  /* Macintosh */
	
	CFStringRef str1 = CFStringCreateWithCharacters(NULL, chars1, len1);
	CFStringRef str2 = CFStringCreateWithCharacters(NULL, chars2, len2);
	
	int compareResult = 0;
	
	if(ignoreCase)
		compareResult = CFStringCompare(str1, str2, kCFCompareLocalized | kCFCompareCaseInsensitive);
	else
		compareResult = CFStringCompare(str1, str2, kCFCompareLocalized);
	
	CFRelease(str1);
	CFRelease(str2);
	 	
	if(compareResult == 0)
		equalResult = true;
	else
		equalResult = false;
	
#endif  // GS_WIN
	
	return(equalResult);
} // StringEqual


//*****************************************************************************
//
// Function Name:  StringCopy (terminated string version)
//
// Description:
//	Copies one string of UTF-16 characters to another string variable.  If the
//	length of the source string exceeds the specified size of the destination
//	string, the copy is truncated at a character cluster break.
//
// Parameters:
//	srcStr      - Pointer to a UTF-16 string to be copied from
//	dstStr      - Pointer to a UTF-16 string to be copied into
//	maxDstBytes - Size in bytes of the destination string parameter (in bytes
//	               rather than characters so can call sizeof(dstStr) to get;
//	               if instead have a character count (including NULL term)
//	               for an allocated buffer, multiply that by sizeof(UCChar)
//
// Return Value:
//	None
//
// Created by:  Michael Hartman, February 2005
//
//*****************************************************************************

void StringCopy (ConstUCStrPtr srcStr, UCStrPtr dstStr, size_t maxDstBytes)
{
	size_t	srcLen, maxDstChars, charsToCopy;
	bool		success;
	
	/* Determine How Many Characters from the String Will Fit, */
	/*  Making Sure to Truncate the Copy on a Cluster Boundary */
	srcLen = StringLength(srcStr);
	maxDstChars = (size_t) (maxDstBytes / sizeof(UCChar));
	if (maxDstChars > srcLen)
		charsToCopy = srcLen;
	else {
		charsToCopy = maxDstChars - 1;
		success = FindCharClusterBreak(srcStr, srcLen, charsToCopy, kFindRev,
		                                &charsToCopy);
	}
	
	/* Copy the Source Characters that Fit to the Destination String */
	if (!VERIFYPOINTER(kMike, dstStr, ((charsToCopy+1)*sizeof(UCChar))))
		dstStr[0] = NULL;
	else {
		memcpy(dstStr, srcStr, (charsToCopy*sizeof(UCChar)));
		dstStr[charsToCopy] = NULL;
	}
} // StringCopy

void StringCopy (ConstUCStrPtr srcStr, wchar_t * dstStr, size_t maxDstBytes)
{
	size_t	srcLen, maxDstChars, charsToCopy;
	bool		success;
	
	/* Determine How Many Characters from the String Will Fit, */
	/*  Making Sure to Truncate the Copy on a Cluster Boundary */
	srcLen = StringLength(srcStr);
	maxDstChars = (size_t) (maxDstBytes / sizeof(UCChar));
	if (maxDstChars > srcLen)
		charsToCopy = srcLen;
	else {
		charsToCopy = maxDstChars - 1;
		success = FindCharClusterBreak(srcStr, srcLen, charsToCopy, kFindRev,
		                                &charsToCopy);
	}
	
	/* Copy the Source Characters that Fit to the Destination String */
	if (!VERIFYPOINTER(kMike, dstStr, ((charsToCopy+1)*sizeof(UCChar))))
		dstStr[0] = NULL;
	else {
		memcpy(dstStr, srcStr, (charsToCopy*sizeof(UCChar)));
		dstStr[charsToCopy] = NULL;
	}
} // StringCopy


//*****************************************************************************
//
// Function Name:  FindCharClusterBreak
//
// Description:
//	Finds the Unicode character cluster break at or nearest the specified
//	position in the character array, looking in the direction specified.
//	Note that the starting position specified and the cluster position
//	returned of "n" ask/state that a cluster ends with the character at (n-1).
//	The caller should always pass a pointer to the beginning of the character
//	array being scanned and its full length rather than simply a pointer to
//	(or trimmed length of) the starting position, because it is assumed that
//	the character array as specified begins and ends on a cluster break.
//
// Parameters:
//	charArray - Pointer to an array of 16-bit words containing the UTF-16
//	             characters to be searched for the cluster break;
//               it is assumed that this begins and ends on a cluster break
//	length    - Number of 16-bit words in charArray that contain characters
//	             to be searched
//	startPos  - Zero-based starting position to search for a cluster break;
//	             note that the value of "length" is valid when moving backwards
//	forward   - Whether to move forward or backward from startPos if
//	             it is not at a cluster break
//	pBreakPos - Returns the nearest-found character position that is the
//	             boundary between clusters (this character starts new cluster);
//	             if an error occurs, startPos is returned as the best guess
//
// Return Value:
//	Whether a cluster break was located
//
// Created by:  Michael Hartman, December 2004
//
//*****************************************************************************

bool FindCharClusterBreak (ConstUCCharPtr charArray, size_t length,
		             size_t startPos, bool forward, size_t* pBreakPos)
{
	bool		success = false;
	
	/* Return Result Immediately for Trivial Cases */
	/*  (Assume Array Contains Complete Clusters)  */
	/* ------------------------------------------- */
	if (startPos > length) startPos = length;
	if ((startPos == 0) || (startPos == length)) {
		*pBreakPos = startPos;
		return(true);
	}
	
	/* Look for the Nearest Character Cluster Break Either */
	/*  At, Following or Preceding the Specified Position  */
	/* --------------------------------------------------- */
#if GS_WIN
	const	Uint32	kMaxCombine = 4;  // Guessed maximum of combining chars
	const	Sint32  kBadStartValue = -99;
	
	ptrdiff_t		searchPos, numCharsCheck, pos;
	SCRIPT_ITEM		scriptItems[kMaxCombine*4];
	SCRIPT_LOGATTR	scriptAttrs[kMaxCombine*4];
	Sint32				numScriptItems;
	Sint32			itemWithStart, item;
	bool			found;
	HRESULT			err;

	itemWithStart = kBadStartValue;
	
	/* Parse an Area of Twice the Expected Combining Characters around */
	/*  the Specified Start Position (for Speed and Memory Reasons)    */
	success = false;
	*pBreakPos = startPos;
	searchPos = std::max((startPos-(kMaxCombine*2)), (size_t)0);
	numCharsCheck  = std::min((startPos+(kMaxCombine*2)), length) - searchPos + 1;
	
	/* Determine the Individually Shapeable Runs (by Text Direction or  */
	/*  Glyph Shaping Engine), and Find the One with the Start Position */
	err = ScriptItemize((const WCHAR *) &charArray[searchPos], (int)numCharsCheck,
	             (sizeof(scriptItems)/sizeof(SCRIPT_ITEM)), NULL, NULL,
	             scriptItems, &numScriptItems);
	if (err == S_OK) {
		for (item = 0; item < (numScriptItems-1); item++) {
			if ((scriptItems[item].iCharPos <= (Sint32)startPos) &&
			 ((Sint32)startPos <= scriptItems[item+1].iCharPos)) {
			 	itemWithStart = item;
				break;
			}
		}
	}
	
	/* Get the Attributes for the Characters in that Run, then */
	/*  Search for a Cluster Break in the Specified Direction; */
	/*  We Can Limit Our Search to the One Run Because a Run   */
	/*  Must Begin With and Be Followed By a Cluster Break     */
	if (err == S_OK && itemWithStart != kBadStartValue) {
		searchPos = scriptItems[itemWithStart].iCharPos;
		numCharsCheck = scriptItems[itemWithStart+1].iCharPos - searchPos;
		err = ScriptBreak((const WCHAR *) &charArray[searchPos],(int) numCharsCheck,
		                   &scriptItems[itemWithStart].a, scriptAttrs);
		if (err == S_OK) {
			found = false;
			if (forward) {
				for (pos = (startPos-searchPos); pos < numCharsCheck; pos++) {
					if (scriptAttrs[pos].fCharStop == 1) {
						*pBreakPos = pos + searchPos;
						break;
					}
				}
				if (!found) *pBreakPos = numCharsCheck + searchPos;  // Okay
			}
			else {
				for (pos = (startPos-searchPos); pos >= 0; pos--) {
					if (scriptAttrs[pos].fCharStop == 1) {
						*pBreakPos = pos + searchPos;
						break;
					}
				}
				if (!found) *pBreakPos = searchPos;  // Should never happen
			}
			success = true;
		}
	}
	
#else  /* Macintosh */
    CFStringRef cfs = CFStringCreateWithCharacters(NULL, charArray, length);
    if (cfs && startPos < length)
    {
        CFRange r = CFStringGetRangeOfComposedCharactersAtIndex(cfs, startPos);
		
        if (forward)
        {
            if (startPos == r.location)
                *pBreakPos = r.location;
            else
                *pBreakPos = r.location + r.length;
        }
        else
            *pBreakPos = r.location;
    }
    else
    {
        *pBreakPos = startPos;
        success = false;
    }
    
    if(cfs)
        CFRelease(cfs);
	
#endif  // GS_WIN
	
	return(success);
} // FindCharClusterBreak


/*============================================================================*/
/*============================================================================*/
/***********************************************************************/
/* Non-Unicode Pascal and C String Manuipulation Routines and Classes */
/***********************************************************************/


/*============================================================================*/
// System and Application Encoding Retrieval Routines


//*****************************************************************************
//
// Function Name:  GetSystemEncoding
//
// Description:
//	Returns the encoding to use in Unicode conversion functions for text
//	that is in the current "system" encoding.  This actually reflects the
//	choice of the user in the "International" system configuration preferences.
//	Note that the meaning of the encoding value returned is defined by the
//	Macintosh and Windows platforms independently (platform constants).
//
// Parameters:
//	None
//
// Return Value:
//	Platform-defined value specifying the current default "system" (user-set)
//	character encoding
//
// Created by:  Robert McBride, ????
//
//*****************************************************************************

GSTextEncoding GetSystemEncoding ()
{
	static bool isFirstExec = true;
	static GSTextEncoding encoding;
	
	if(isFirstExec)
	{
	
#if GS_WIN
		encoding = GetACP();
	
#else
		// note that CFStringGetSystemEncoding does not return Icelandic in MacOS 10.10 and later
		// -- this is a workaround replacement
		bool isIcelandic = [[[NSLocale preferredLanguages] objectAtIndex:0] hasPrefix:@"is"];

		encoding = isIcelandic ? kCFStringEncodingMacIcelandic : CFStringGetSystemEncoding();
		
#endif
		
		isFirstExec = false;
	}
	
#if VCS_CLOUD_BUILD
	VectorWorks::IDirigiblePluginPtr dirigiblePtr( VectorWorks::IID_DirigiblePlugin );
	if ( dirigiblePtr ) 
	{
		encoding	= (GSTextEncoding) dirigiblePtr->GetTranslateLocale();
	}
#endif

	return(encoding);
}


// ===========================================================================
// == Strings
// ==

// ---------------------------------------------------------------------------
// -- StringCopy

void StringCopy(ConstGSStr255Param src, GSStringPtr dst, size_t n)
// Pascal- to Pascal-style string copy. Includes length byte so
// to copy m characters n should be m + 1. Example: to copy to
// Str255, n = 256 or sizeof(Str255).
{
	if (n == 0 || !dst) 
		return /*dst*/;
	if (!src || src[0] == 0) { 
		*dst = 0;
		return /*dst*/;
	}
	
	ASSERTN(kChao, n <= 256);
		
	size_t		i = (((size_t)(*src + 1) < n) ? *src : n - 1);
	
	//IFPRINT(*src > n - 1, "### StringCopy - source too Sint32; truncating to fit.");

	*dst = (unsigned char) i;
	dst++; src++;
	for (; i > 0; i--) 
		*dst++ = *src++;
	
	return /*d*/;
}

void StringCopy(const char *src, GSStringPtr dst, size_t n)
// C- to Pascal-style string copy. Includes length byte so
// to copy m characters n should be m + 1. Example: to copy to
// Str255, n = 256 or sizeof(Str255).
{
	size_t				l = 0;				// Length counter.
	const GSStringPtr	d = dst;			// Save original dst pointer.
	
	if (n <= 0 || !dst)
		return /*dst*/;
		
	ASSERTN(kChao, n <= 256);
	if (n > 256) n = 256;
				
	if (src) {
		dst++;								// Skip over length byte.
		while (l < n - 1 && (*dst++ = *src++) != 0) // Copy characters, keeping track of how many.
			l++;
	}
	*d = (unsigned char) l;					// Set length byte.
	return /*d*/;
}

void StringCopy(const void *src, size_t len, GSStringPtr dst, size_t n)
// Raw storage to Pascal-style string copy. Includes length byte so
// to copy m characters n should be m + 1. Example: to copy to
// Str255, n = 256 or sizeof(Str255) and len is up to 255 (bigger len
// is ok but will be truncated).
{
	if (!dst || n == 0) 
		return /*dst*/;
	
	if (src) {
		const char *		src_p = (const char *) src;
	
		ASSERTN(kChao, n <= 256);
		
		n = Min(n-1, len);
		*dst++ = (unsigned char) n;
		for (; n > 0; n--) 
			*dst++ = *src_p++;
		return;
	}
	else {
		*dst = 0;
		return;
	}
}

void StringCopy(ConstGSStr255Param src, char *dst, size_t n)
// Pascal- to C-style string copy. Includes length byte/null terminator so
// to copy m characters n should be m + 1. Example: to copy from
// Str255 to a char[256], n = 256.
{
	if (n <= 0 || !dst) return /*dst*/;
	
	if (src) {
		ASSERTN(kChao, n <= 256);
		
		size_t sl = Min((size_t) src[0], n-1);
		dst[sl] = '\0';	// Terminate destination, since strncpy won't do it.
		if (sl)
			/*return*/ strncpy(dst, (const char *) &src[1], sl);
		return;
	}
	else {
		*dst = '\0';
		return /*dst*/;
	}
}

void StringCopy(const char *src, char *dst, size_t n)
// C- to C-style string copy. Includes null terminator so
// to copy m characters n should be m + 1.
{
	// NOTE: This function is NOT the same as strncpy, because strncpy
	// won't necessarily null-terminate the destination, and doesn't
	// handle null string pointers!
	
	if (n <= 0 || !dst) 
		return /*dst*/;
	
	if (src) {
		size_t sl = Min(strlen(src), n-1);
		dst[sl] = '\0';
		if (sl)
			/*return*/ strncpy(dst, src, sl);
		return;
	}
	else {
		*dst = '\0';
		return /*dst*/;
	}
}

void StringCopy(const void *src, size_t len, char *dst, size_t n)
// Raw storage to C-style string copy. Includes null terminator so
// to copy m characters n should be m + 1. 
{
	if (!dst || n <= 0) 
		return /*dst*/;

	if (src) {
		//char * const		d = dst;
		const char *		src_p = (const char *) src;

		n = Min(n-1, len);
		for (; n > 0; n--) 
			*dst++ = *src_p++;
		*dst = '\0';
		return /*d*/;
	}
	else {
		*dst = '\0';
		return /*dst*/;
	}
}

// ---------------------------------------------------------------------------
// -- StringCat

GSStringPtr StringCat(GSStringPtr dst, ConstGSStr255Param src, size_t n)
	// ## Catenate Pascal- to Pascal-style string.
{
	if (n <= (size_t) (GetLength(dst) + 1) || !dst || !src) return dst;
	
	const GSStringPtr	d = dst;
	size_t				copylen = ((size_t)(*dst + *src + 1) <= n) ? *src : n - *dst - 1;
	
	#if 0
	IFPRINT(copylen != *src, "### StringCat - result would be too Sint32; truncating to fit.");
	#endif
	
	dst += *dst + 1;	// Step to end of destination string.
	src++;				// Skip past length byte of source.
	*d += (Uchar) copylen;		// Increment length of destination.
	for (; copylen > 0; copylen--) *dst++ = *src++;	// Do the copy.
	
	return d;
}

GSStringPtr StringCat(GSStringPtr dst, const char *src, size_t n)
	// ## Catenate C- to Pascal-style string.
{
	if (n <= (size_t) GetLength(dst) + 1 || !dst || !src) return dst;
	
	const GSStringPtr	d = dst;
	size_t				copylen = n - GetLength(dst) - 1;
	
	for (dst += *dst + 1; copylen > 0 && *src; copylen--) {
		(*d)++; *dst++ = *src++;
	}
	return d;
}

GSStringPtr StringCat(GSStringPtr dst, const void *src, size_t len, size_t n)
	// ## Catenate raw storage to Pascal-style string.
{
	if (n <= (size_t) GetLength(dst) + 1 || !dst || !src) return dst;
	
	const GSStringPtr	d = dst;
	const char		   *src_p = (const char *) src;
	size_t				copylen = Min(n - GetLength(dst) - 1, len);
	
	for (dst += *dst + 1; copylen > 0; copylen--) {
		(*d)++; *dst++ = *src_p++;
	}
	return d;
}

char * StringCat(char *dst, ConstGSStr255Param src, size_t n)
	// ## Catenate Pascal- to C-style string.
{
	if (n > 0 && src && dst) {
		size_t dl = strlen(dst);
		char *dst2 = dst+dl;
		StringCopy(src, dst2, n > dl ? n-dl : 0);
		return dst2;
	}
	return dst;
}

char * StringCat(char *dst, const char *src, size_t n)
	// ## Catenate C- to C-style string.
{
	if (n > 0 && src && dst) {
		size_t dl = strlen(dst);
		StringCopy(src, dst+dl, n > dl ? n-dl : 0);
	}
	return dst;
}

char * StringCat(char *dst, const void *src, size_t len, size_t n)
	// ## Catenate raw storage to Pascal-style string.
{
	if (n > 0 && src && dst) {
		size_t dl = strlen(dst);
		StringCopy((const char *) src, len, dst+dl, n > dl ? n-dl : 0);
	}
	return dst;
}

// ---------------------------------------------------------------------------
// -- StringEqual

Bool8 StringEqual(const TXString& a, const TXString& b)
{
	return (a.Equal(b));
}

// ---------------------------------------------------------------------------
// -- StringEqualIgnoringCase
Bool8 StringEqualIgnoringCase(const TXString& a, const TXString& b)
{
	return (a.EqualNoCase(b));
}


// ---------------------------------------------------------------------------
// -- StringCompare
short StringCompare(const TXString& str1, const TXString& str2)
{
	return str1.Compare(str2);
}


// ---------------------------------------------------------------------------
// -- StringCompareIgnoringCase

short StringCompareIgnoringCase(const TXString& a, const TXString& b)
{
	return a.CompareNoCase(b);
}


// ---------------------------------------------------------------------------
// -- StringInsert

void StringInsert(ConstGSStr255Param src, GSStringPtr dst, Uint8 index)
{
	/* NOTE: In the event that the full result is bigger than 255
		characters, StringInsert will preserve all of dst in preference
		to inserting all of src.  E.g., if you ask to insert a string
		of 255 x's in the middle of "foobar", you'll get "foo<249 x's>bar",
		not "foo<252 x's>".
	*/
	
	if (!src || !dst) return;
	if (!inrange(index, 1, 255)) return;
	
	ptrdiff_t	copylen = (*src + *dst > 255) ? 255 - *dst : *src;
	ptrdiff_t	x = (ptrdiff_t)index + copylen;
	
	memmove(&dst[x], &dst[index], 255 - x);
	memmove(&dst[index], &src[1], copylen);
	
	dst[0] += (unsigned char) copylen;
}

// ---------------------------------------------------------------------------
// -- StringDelete

void StringDelete(GSStringPtr s, Uint8 start, Uint8 count)
{
	if (!s) return;
	if (start > *s) return;
	
	if (start + count - 1 > *s) count = *s - start;
	
	GSStringPtr	src = s + start + count, dst = s + start;
	short		copylen = *s - start - count + 1;

	*s -= count;
	for (; copylen > 0; copylen--) *dst++ = *src++;
}	

void StringDelete(char *s, size_t start, size_t count)
{
	if (!s) return;
	
	size_t		len = strlen(s);
	
	if (start > len) return;
	if (start + count > len) count = len - start;
	if (count < 1) return;
	
	memmove(s + start, s + start + count, len - start - count + 1);
}


#ifdef _MINICAD_

// ---------------------------------------------------------------------------
// -- StringPos

short StringPos (ConstGSStr255Param findStr, ConstGSStr255Param str)
/* Searches for the first occurrence of findStr within str, and returns */
/*  its starting position.  If findStr is not found, 0 is returned.     */
/*  The comparison is case and diacritical sensitive, and may not yield */
/*  the proper result with 2-byte script systems.                       */
{
	size_t foundPos = 0;
	size_t findLen = GetLength(findStr);
	size_t strLen  = GetLength(str);
	void *buf = (void *) (&str[1]);
	void *pat = (void *) (&findStr[1]);
	if ((findLen > 0) && (strLen > 0) && (findLen <= strLen)) {
		void *loc = VWMM::Partition::MemMem(buf, strLen, pat, findLen);
		if (loc != NULL)
		{
			foundPos = (((size_t) loc) - ((size_t) buf));
			++foundPos;	// zero-based to one-based.
		}
	}

	return((short)foundPos);
}

#endif // _MINICAD_

//========================================================================================
// Methods of COSStringCompare
#if GS_MAC

//----------------------------------------------------------------------------------------
COSStringCompare::COSStringCompare()
{
	cfStr1 = nil;
	cfStr2 = nil;
}

//----------------------------------------------------------------------------------------
COSStringCompare::~COSStringCompare()
{
	if(cfStr1 != nil)
	{
		CFRelease(cfStr1);
	}
	
	if(cfStr2 != nil)
	{
		CFRelease(cfStr2);
	}
}

//----------------------------------------------------------------------------------------
CFComparisonResult COSStringCompare::Compare(const CFMutableStringRef cfStr1, const CFMutableStringRef cfStr2)
{
	CFComparisonResult compareResult = kCFCompareEqualTo;
	
    compareResult = CFStringCompare(cfStr1, cfStr2,
                                       kCFCompareCaseInsensitive | kCFCompareDiacriticInsensitive | kCFCompareNumerically);
        
    if (compareResult == kCFCompareEqualTo)
        compareResult = CFStringCompare(cfStr1, cfStr2, kCFCompareCaseInsensitive | kCFCompareNumerically);
        
    if (compareResult == kCFCompareEqualTo)
        compareResult = CFStringCompare(cfStr1, cfStr2, kCFCompareCaseInsensitive);

	return compareResult;
}

#endif	// #if GS_MAC

//----------------------------------------------------------------------------------------
short COSStringCompare::Compare(const TXString& txStr1, const TXString& txStr2, bool bDashTreatedSpecially)
{
	
#if GS_WIN
	
	return OSStringCompare(txStr1, txStr2, bDashTreatedSpecially);
	
#else	// Mac
	
	if (txStr1.IsEmpty() && txStr2.IsEmpty())
	{
		// Return 0 if both strings are empty.
		return 0;
	}
	else if (txStr1.IsEmpty() && !txStr2.IsEmpty())
	{
		// Return 1 if only txStr1 is empty.
		return 1;
	}
	else if (!txStr1.IsEmpty() && txStr2.IsEmpty())
	{
		// Return -1 if only txStr2 is empty.
		return -1;
	}
	
	// Create cfStr1 lazily.
	if(cfStr1 == nil)
	{
		cfStr1 = CFStringCreateMutableWithExternalCharactersNoCopy(kCFAllocatorDefault,
																   NULL, 
																   0, 
																   0,
																   kCFAllocatorNull);
	}
	
	// Create cfStr2 lazily.
	if(cfStr2 == nil)
	{
		cfStr2 = CFStringCreateMutableWithExternalCharactersNoCopy(kCFAllocatorDefault,
																   NULL, 
																   0, 
																   0,
																   kCFAllocatorNull);
	}
	
	CFComparisonResult compareResult = kCFCompareEqualTo;
	
	if (bDashTreatedSpecially)
	{
		// Substring positions
		ptrdiff_t sub1Pos = 0;
		ptrdiff_t sub2Pos = 0;
		
		// Substring lengths
		size_t sub1Len = 0;
		size_t sub2Len = 0;
		
		// Dash positions
		ptrdiff_t dash1Pos = 0;
		ptrdiff_t dash2Pos = 0;
		
		while(true)
		{
			dash1Pos = txStr1.Find(txu("-"), sub1Pos);
			dash2Pos = txStr2.Find(txu("-"), sub2Pos);
			
			if(dash1Pos == -1)
				// If one of the substring does not contain dash, compare whole substring.
				sub1Len = txStr1.GetLength() - sub1Pos;
			else
				sub1Len = dash1Pos - sub1Pos;
			if(dash2Pos == -1)
				sub2Len = txStr2.GetLength() - sub2Pos;
			else
				sub2Len = dash2Pos - sub2Pos;
			
			// Set cfStr1 content without creating internal butter.
			CFStringSetExternalCharactersNoCopy(cfStr1, 
												(UniChar*)&(txStr1.GetData()[sub1Pos]),
												sub1Len, 
												sub1Len);
			
			// Set cfStr2 content without creating internal butter.
			CFStringSetExternalCharactersNoCopy(cfStr2, 
												(UniChar*)&(txStr2.GetData()[sub2Pos]),
												sub2Len, 
												sub2Len);
			
			// Compare
			compareResult = Compare(cfStr1, cfStr2 );
			
			// If the comparison result is not 0 or both of the substrings do not contain
			// dash, the comparison result is final. No further comparison is required.
			if(compareResult != kCFCompareEqualTo || (dash1Pos == -1 && dash2Pos == -1))
			{
				break;
			}
			// If the first substring does not have another dash (for example first substring
			// is Wall and second is Wall-interior), return less than
			else if (dash1Pos == -1) {
				compareResult = kCFCompareLessThan;
				break;
			}
			// If the second substring does not have another dash, return greater than
			else if (dash2Pos == -1) {
				compareResult = kCFCompareGreaterThan;
				break;
			}
			
			sub1Pos = dash1Pos + 1;
			sub2Pos = dash2Pos + 1;
		}
	}
	else
	{
		CFStringSetExternalCharactersNoCopy(cfStr1, (UniChar*)txStr1.GetData(), txStr1.GetLength(), txStr1.GetLength());
		CFStringSetExternalCharactersNoCopy(cfStr2, (UniChar*)txStr2.GetData(), txStr2.GetLength(), txStr2.GetLength());
		
		compareResult = Compare(cfStr1, cfStr2 );
	}
	
	return compareResult;
	
#endif	// Mac
	
}

//========================================================================================
// Use OS to compare strings.
short OSStringCompare(const TXString& string1, const TXString& string2, bool treatDashSpecial)
{
	
#if _WINDOWS
	
	short compareValue = 0;

	if(string1.IsEmpty() && string2.IsEmpty())
	{
		compareValue = 0; // Equal.
	}
	else if (string1.IsEmpty())
	{
		compareValue = 1; // Greater than.
	}
	else if (string2.IsEmpty())
	{
		compareValue = -1; // Less than.
	}
	else
	{
		// StrCmpLogicalW ignores dash characters, which causes a problem
		// when this is used to sort classes. So for the sorting, convert
		// all dashes to exclamation points.
		// It also seems to ignore control characters, which also causes
		// a problem when used to sort classes, so convert any of these
		// characters to exclamation points also.
		if (treatDashSpecial)
		{
			TXString str1 = string1;
			TXString str2 = string2;
			size_t len1 = str1.GetLength();
			size_t len2 = str2.GetLength();
			
			for (int i = 0; i < len1; i++)
			{
				if (str1[i] == '-' || str1[i] < 0x20)
					str1[i] = '!';
			}
			
			for (int j = 0; j < len2; j++)
			{
				if (str2[j] == '-' || str2[j] < 0x20)
					str2[j] = '!';
			}

			compareValue = StrCmpLogicalW(str1.GetData(), str2.GetData());
		}
		else
		{
			compareValue = StrCmpLogicalW(string1.GetData(), string2.GetData());
		}
	}
	
	return compareValue;
	
#else	// Mac

	COSStringCompare osStringCompare;
	return osStringCompare.Compare(string1, string2, treatDashSpecial);
	
#endif
	
}

// Uses OS and current locale to compare strings; in VW code used to compare File/Folder names
int OSStringCompareEx(const TXString& string1, const TXString& string2)
{

#if GS_WIN

	int result = CompareStringEx(LOCALE_NAME_USER_DEFAULT, LINGUISTIC_IGNORECASE | SORT_DIGITSASNUMBERS, string1.GetData(), (int)string1.GetLength(), string2.GetData(), (int)string2.GetLength(), NULL, NULL, 0);

	return (result == CSTR_LESS_THAN) ? -1 : ((result == CSTR_EQUAL) ? 0 : 1);

#else

	NSString* str3 = [NSString stringWithCharacters : string1.GetData() length : string1.GetLength()];
	NSString* str4 = [NSString stringWithCharacters : string2.GetData() length : string2.GetLength()];

	NSRange stringRange = NSMakeRange(0, str3.length);
	return[str3 compare : str4 options : NSNumericSearch | NSCaseInsensitiveSearch
		range : stringRange locale : [NSLocale currentLocale]];
#endif


}

//========================================================================================
// Methods of CTXStringNoCase
#if GS_MAC

//----------------------------------------------------------------------------------------
CTXStringNoCase::CTXStringNoCase()
{
	cfStr1 = nil;
	cfStr2 = nil;
}

//----------------------------------------------------------------------------------------
CTXStringNoCase::~CTXStringNoCase()
{
	if(cfStr1 != nil)
	{
		CFRelease(cfStr1);
	}
	
	if(cfStr2 != nil)
	{
		CFRelease(cfStr2);
	}
}

#endif	// #if GS_MAC

//----------------------------------------------------------------------------------------
short CTXStringNoCase::Compare(const TXString &txStr1, const TXString &txStr2)
{
#if GS_WIN
	return lstrcmpiW(txStr1.GetData(), txStr2.GetData());
	
#else
	if(txStr1.IsEmpty() && txStr2.IsEmpty())
	{
		return 0;
	}
	
	if(txStr1.IsEmpty() && !txStr2.IsEmpty())
	{
		return -1;
	}
	
	if(!txStr1.IsEmpty() && txStr2.IsEmpty())
	{
		return 1;
	}
	
	short result = 0;
	
	if(cfStr1 == nil)
	{
		cfStr1 = CFStringCreateMutableWithExternalCharactersNoCopy(kCFAllocatorDefault,			// Allocator
																   (UniChar*)txStr1.GetData(), 	// UniChar *chars
																   txStr1.GetLength(), 			// CFIndewx numChars
																   txStr1.GetLength(),			// CFIndex capacity
																   kCFAllocatorNull);			// External characters allocator
	}
	else
	{
		CFStringSetExternalCharactersNoCopy(cfStr1, 
											(UniChar*)txStr1.GetData(), 
											txStr1.GetLength(), 
											txStr1.GetLength());
	}
	
	if(cfStr2 == nil)
	{
		cfStr2 = CFStringCreateMutableWithExternalCharactersNoCopy(kCFAllocatorDefault,			// Allocator
																   (UniChar*)txStr2.GetData(), 	// UniChar *chars
																   txStr2.GetLength(), 			// CFIndewx numChars
																   txStr2.GetLength(),			// CFIndex capacity
																   kCFAllocatorNull);			// External characters allocator
	}
	else
	{
		CFStringSetExternalCharactersNoCopy(cfStr2, 
											(UniChar*)txStr2.GetData(), 
											txStr2.GetLength(), 
											txStr2.GetLength());
	}
	
	if(cfStr1 && cfStr2)
	{
		result = CFStringCompare(cfStr1, cfStr2, kCFCompareCaseInsensitive);
	}
	
	return result;
	
#endif
}

//----------------------------------------------------------------------------------------
bool CTXStringNoCase::Equal(const TXString &txStr1, const TXString &txStr2)
{
	return (Compare(txStr1, txStr2) == 0);
}

//========================================================================================
// -- Other functions

#if !_WINDOWS

Sint32 stricmp(const char *a, const char *b)
{
	char ua, ub;
	for (; *a && *b; ++a, ++b) {
		ua = toupper(*a);
		ub = toupper(*b);
		if (ua != ub)
			return (ua < ub ? -1 : 1);
	}
	// At this point at least one of *a or *b is equal to 0.
	return (*a == *b) ? 0 : (*a ? 1 : -1);
}

Sint32 strnicmp(const char *a, const char *b, size_t max)
{
	char ua, ub;
	size_t n;
	for (n=0; *a && *b && n<max; ++a, ++b, ++n) {
		ua = toupper(*a);
		ub = toupper(*b);
		if (ua != ub)
			return (ua < ub ? -1 : 1);
	}
	// At this point, either we have reached 'max' or at least one of *a or *b is equal to 0.
	return (*a == *b || n >= max) ? 0 : (*a ? 1 : -1);
}


#endif // !_WINDOWS

/*============================================================================*/

//=======================================================================================
Boolean IsMultiByteLanguage( )
{
	static bool isFirstTimeExecution = true;
	static bool isMultibyteLanguage = false;
	
	// The following block is only executed once.
	if(isFirstTimeExecution)
	{
#if GS_WIN
		if(GetACP() == 932 || GetACP() == 936)	// Japanese and simplified Chinese
		{
			isMultibyteLanguage = true;
		}
#else
		CFStringEncoding cfStringEncoding = CFStringGetSystemEncoding();
		
		if (cfStringEncoding == kCFStringEncodingMacJapanese		// Japanese
			|| cfStringEncoding == kCFStringEncodingMacChineseSimp)	// Simplified Chinese
		{
			isMultibyteLanguage = true;
		}
#endif
		
		isFirstTimeExecution = false;
	}

	return isMultibyteLanguage;
}


//=======================================================================================
// Required for translation of strings
//
// Used for a few other special cases also.  Do not use this without talking to Payne or Ian first.
//
void GetFarEastCharacterTypeArray(const char *pStr, ECharacterType *pCharByteType, size_t strLength)
    //
    // Description:
    // Populate char byte type array based on the source.
    //
{
	if (pStr && pCharByteType)
	{
		if(!IsMultiByteLanguage())
		{	// This is not multi-byte string.
			for (size_t i = 0; i < strLength; i++)
			{
				pCharByteType[i] = eSingle;
			}
		}
		else
		{	// This is multi-byte string.
		 
#if GS_WIN	// Windows
			Sint32 lastType = _MBC_SINGLE;
			Sint32 thisType;
			
			for (size_t i = 0; i < strLength; i++)
			{
				thisType = _mbbtype(pStr[i], lastType );
				lastType = thisType;
				
				if(thisType == _MBC_SINGLE)
				{
					pCharByteType[i] = eSingle;
				}
				else if(thisType == _MBC_LEAD)
				{
					pCharByteType[i] = eLead;
				}
				else if(thisType == _MBC_TRAIL)
				{
					pCharByteType[i] = eTrail;
				}
				else
				{
					pCharByteType[i] = eSingle;
				}
			}
			
#else		// Mac
			{
				int strLen = 0;	// NSString length
				
				for(int i = 0; i < strLength; ++i)
				{
					// Create a two-byte string.
                    NSString *nsStr = [[NSString alloc] initWithBytes:(void*)(pStr + i)
                                                               length:2
                                                             encoding:[NSString defaultCStringEncoding]];
                    
                    if (i == (strLength - 1) && nsStr == nil)
                    {
                        // The last byte is part of a multi byte character but the NSString can't be constructed from
                        // an invalid string so it's nil.  A nil string will return a length of 0, so we need to handle
                        // this as a special case here instead of handling it lower.
                        pCharByteType[i] = eLead;
                    }
                    else
                    {
                        // Get the length of the string.
                        strLen = [nsStr length];
                        
                        if(strLen == 0)	// The first byte is a one-byte character. The second byte is a leading byte.
                        {
                            pCharByteType[i] = eSingle;
                        }
                        else if(strLen == 1)	// charLen == 1: one two-byte character
                        {
                            pCharByteType[i] = eLead;
                            ++i;
                            
                            if(i < strLength)
                            {
                                pCharByteType[i] = eTrail;
                            }
                        }
                        else	// charLen == 2: two single byte characters.
                        {
                            pCharByteType[i] = eSingle;
                            ++i;
                            
                            if(i < strLength)
                            {
                                pCharByteType[i] = eSingle;
                            }
                        }
                    }
				}
			}
#endif
		}
	}
}

// This function will check if the last byte of a multi-byte encoded string is the start of a new multi byte character.
// If it is, we want to remove that byte because it isn't valid.  Leaving this byte can corrupt the string.
// This is currently only used during reverse translation.

// For C string
void TrimInvalidCharsFromMultiByteEncodedCString(char* buffer, size_t bufferSize)
{
	// Process it only if in multi-byte language and the buffer is not empty.
	if (IsMultiByteLanguage() && bufferSize > 0)
	{
		ECharacterType *charTypeArr = new ECharacterType[bufferSize];
		GetFarEastCharacterTypeArray(buffer, charTypeArr, bufferSize);

		// Make sure the C string is null terminated.
		buffer[bufferSize - 1] = '\0';
		
		// If the byte before the terminal byte is a lead, remove it.
		if (bufferSize > 1 && charTypeArr[bufferSize - 2] == eLead) {
				buffer[bufferSize - 2] = '\0';
		}

		delete[] charTypeArr;
	}
}

// For Pascal string
void TrimInvalidCharsFromMultiByteEncodedPString(unsigned char* buffer, size_t bufferSize)
{
	// Process it only if in multi-byte language and the buffer is not empty.
	if (IsMultiByteLanguage() && bufferSize >= 2)
	{
		ECharacterType *charTypeArr = new ECharacterType[bufferSize - 1];
		
		// The first byte is the lenght. Skip it.
		GetFarEastCharacterTypeArray((const char*)(buffer + 1), charTypeArr, bufferSize - 1);
		
		// If the last byte is a lead, remove it.
		if (charTypeArr[bufferSize - 2] == eLead) {
			buffer[bufferSize - 1] = '\0';
		}
		
		delete[] charTypeArr;
	}
}


