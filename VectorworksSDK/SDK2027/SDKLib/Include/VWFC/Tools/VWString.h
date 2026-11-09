//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once
#include <unordered_map>

namespace VWFC
{
#define			STATIC_STRING_SIZE		256

	namespace Tools
	{
		typedef	std::vector<TXString>						TXStringSTLArray;
		typedef	std::map<TXString, TXString>				TXString2TXStringSTLMap;
        typedef	std::unordered_map<TXString, TXString>		TXString2TXStringSTLUnorderedMap;

		// --------------------------------------------------------------------------------------------------
		class TXStringExt
		{
		// utils
		public:
			static void			Tokenize(const TXString& string, TXStringSTLArray& outArray, const TXString& tokens);
			static void			TokenizeQuotation(const TXString& string, TXStringSTLArray& outArray, const TXString& tokens, wchar_t quotationToken=L'"');
			static void			Lines(const TXString& string, TXStringSTLArray& outArray);
			static bool			IsSpace(UCChar c);
			static bool			IsDigit(UCChar c);
			static bool			IsDigit(const TXString& string);
			static bool			IsNumber(const TXString& string);
			static bool			IsAlpha(UCChar c);
			static bool			IsDigitOrAlpha(UCChar c);
			static char			ToLower(UCChar c);
			static char			ToUpper(UCChar c);
			static char			ToReverseCase(UCChar c);
			static UCChar		ToHex(Sint32 n, bool upperCase);
			static Sint32		FromHex(UCChar c);
			static TXString		EncodeString(const TXString& string);
			static TXString		DecodeString(const TXString& string);
			static TXString		CapitalizeEachWord(const TXString& string);
			static ptrdiff_t	FindLastSubString(const TXString& string, const TXString& sub);
			static bool			ComparePattern(const TXString& value, const TXString& pattern);

		};
	}
}
