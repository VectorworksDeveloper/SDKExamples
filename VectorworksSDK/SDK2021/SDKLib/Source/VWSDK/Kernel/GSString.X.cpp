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

#if GS_WIN
	// For Unicode normalization form (precomposed v.s. decomposed)
	#include <WinNls.h>
#endif

#if _MINICAD_
# define GS_CORE_BUILD 1
#endif

#include "VectorworksSDK.h"
#include "Kernel/GSIntTypes.h"

#if _MINICAD_
	#include "../../../../Include/CoreAPI.X.h"
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

#ifdef TEST	// Temporary code to detect misuse of this constructor.
		if (length != maxUCChars)
		{
			DSTOP((kPChang,
				"A terminal character is found in this string. "
				"If the terminal character is intended to be a part of the string, you can ignore this warning. "
				"Otherwise, the passed length parameter could be incorrect. "
				"In this case, please use a constructor without a length parameter to construct the string correctly. "
				"If you have any questions, please contact Payne. Thanks!"));
		}
#endif
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

#ifdef TEST	// Temporary code to detect misuse of this constructor.
		if (length != maxWChars)
		{
			DSTOP((kPChang,
				"A terminal character is found in this string. "
				"If the terminal character is intended to be a part of the string, you can ignore this warning. "
				"Otherwise, the passed length parameter could be incorrect. "
				"In this case, please use a constructor without a length parameter to construct the string correctly. "
				"If you have any questions, please contact Payne. Thanks!"));
		}
#endif
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

#ifdef TEST	// Temporary code to detect misuse of this constructor.
		if (length != maxWChars)
		{
			DSTOP((kPChang,
				"A terminal character is found in this string. "
				"If the terminal character is intended to be a part of the string, you can ignore this warning. "
				"Otherwise, the passed length parameter could be incorrect. "
				"In this case, please use a constructor without a length parameter to construct the string correctly. "
				"If you have any questions, please contact Payne. Thanks!"));
		}
#endif

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
