//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;


// --------------------------------------------------------------------------------------------------
/*static*/ void TXStringExt::Tokenize(const TXString& string, TXStringSTLArray& outArray, const TXString& tokens)
{
	outArray.clear();

	size_t	tokensLen = tokens.GetLength();

	TXString	currToken;

	size_t	strLen	= string.GetLength();
	for(size_t i=0; i<strLen; i++) {
		UCChar	ch		= string.GetAt( i );

		bool	isToken	= false;
		for(size_t j=0; j<tokensLen; j++) {
			if ( tokens[j] == ch ) {
				isToken		= true;
				break;
			}
		}

		if ( isToken ) {
			outArray.push_back( currToken );
			currToken.Clear();
		}
		else {
			currToken		+= ch;
		}
	}

	// put the last item if any
	if ( ! currToken.IsEmpty() ) {
		outArray.push_back( currToken );
		currToken.Clear();
	}
}

/*static*/ void TXStringExt::TokenizeQuotation(const TXString& string, TXStringSTLArray& outArray, const TXString& tokens, wchar_t quotationToken)
{
	outArray.clear();

	size_t	tokensLen = tokens.GetLength();

	TXString	currToken;

	bool	insideQuotation = false;

	size_t	strLen	= string.GetLength();
	for(size_t i=0; i<strLen; i++)
	{
		UCChar	ch		= string.GetAt( i );

		bool	isToken	= false;
		if ( insideQuotation )
		{
			if ( ch == quotationToken )
				insideQuotation = false;
		}
		else if ( ch == quotationToken )
		{
			insideQuotation = true;
		}
		else
		{
			for(size_t j=0; j<tokensLen; j++)
			{
				if ( tokens[j] == ch ) {
					isToken		= true;
					break;
				}
			}
		}

		if ( isToken )
		{
			outArray.push_back( currToken );
			currToken.Clear();
		}
		else
		{
			currToken		+= ch;
		}
	}

	// put the last item if any
	if ( ! currToken.IsEmpty() ) {
		outArray.push_back( currToken );
		currToken.Clear();
	}
}

/*static*/ void TXStringExt::Lines(const TXString& string, TXStringSTLArray& outArray)
{
	outArray.clear();

	TXString	currToken;

	size_t	strLen	= string.GetLength();
	for(size_t i=0; i<strLen; i++) {
		UCChar	ch		= string.GetAt( i );
		
		if(ch == '\n' || ch == '\r')
		{
			outArray.push_back( currToken );
			currToken.Clear();
			if(i+1 < strLen)
			{
				UCChar chnext = string.GetAt( i+1 );
				if((ch == '\n' && chnext == '\r') || (ch == '\r' && chnext == '\n'))
					i++;
			}			
		}
		else {
			currToken		+= ch;
		}
	}

	// put the last item if any
	if ( ! currToken.IsEmpty() ) {
		outArray.push_back( currToken );
		currToken.Clear();
	}
}

/*static*/ bool TXStringExt::IsSpace(UCChar c)
{
	return ( ((c) == ' ') || ((c) == '\t') || ((c) == '\n') || ((c) == '\r') );
}

/*static*/ bool TXStringExt::IsDigit(UCChar c)
{
	return ( (((c) >= '0') && ((c) <= '9')) );
}

/*static*/ bool TXStringExt::IsAlpha(UCChar c)
{
	return ( (((c) >= 'a') && ((c) <= 'z')) ) || ( (((c) >= 'A') && ((c) <= 'Z')) );
}

/*static*/ bool TXStringExt::IsDigitOrAlpha(UCChar c)
{
	return TXStringExt::IsDigit( c ) || TXStringExt::IsAlpha( c ) || ((c) == '_');
}

/*static*/ char TXStringExt::ToLower(UCChar c)
{
	return ( (((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c) );
}

/*static*/ char TXStringExt::ToUpper(UCChar c)
{
	return ( (((c) >= 'a') && ((c) <= 'z')) ? ((c) - 'a' + 'A') : (c) );
}

/*static*/ char TXStringExt::ToReverseCase(UCChar c)
{
	if ( ( (((c) >= 'a') && ((c) <= 'z')) ) )
		return TXStringExt::ToUpper( c );
	else
		return TXStringExt::ToLower( c );
}

/*static*/ UCChar TXStringExt::ToHex(Sint32 n, bool upperCase)
{
	static const UCChar arrUpperByteChars[] = { UCChar('0'), UCChar('1'), UCChar('2'), UCChar('3'), UCChar('4'), UCChar('5'), UCChar('6'), UCChar('7'),  UCChar('8'), UCChar('9'), UCChar('A'), UCChar('B'), UCChar('C'), UCChar('D'), UCChar('E'), UCChar('F') };
	static const UCChar arrLowerByteChars[] = { UCChar('0'), UCChar('1'), UCChar('2'), UCChar('3'), UCChar('4'), UCChar('5'), UCChar('6'), UCChar('7'),  UCChar('8'), UCChar('9'), UCChar('a'), UCChar('b'), UCChar('c'), UCChar('d'), UCChar('e'), UCChar('f') };
	const UCChar* arrChars = upperCase ? arrUpperByteChars : arrLowerByteChars;
	return arrChars[ n & 0x0F ]; 
}

/*static*/ Sint32 TXStringExt::FromHex(UCChar c)
{
	if ( (((c) >= '0') && ((c) <= '9')) )
		return c - '0';
	else if ( (((c) >= 'A') && ((c) <= 'F')) )
		return 10 + (c - 'A');
	else if ( (((c) >= 'a') && ((c) <= 'f')) )
		return 10 + (c - 'a');
	else
		return 0;
}

/*static*/ bool TXStringExt::IsDigit(const TXString& string)
{
	size_t	i	= 0;
	if ( i >= string.GetLength() )
		return false;

	if ( string.GetAt(i) == '-' || string.GetAt(i) == '+' || string.GetAt(i) =='.' )
		i++;

	if ( i >= string.GetLength() )
		return false;

	return TXStringExt::IsDigit( string.GetAt(i) );
}

/*static*/ bool TXStringExt::IsNumber(const TXString& string)
{
	bool result = !string.IsEmpty();

	if (	!(	( string.GetAt( 0 ) == '-' || string.GetAt( 0 ) == '+' ) && string.GetLength() > 1 
			||  std::isdigit( string[0] ) ) )
	{
		result = false;
	}

	if( result )
	{
		size_t specialSymbolsCount = 0;

		for( size_t i = 1; i < string.GetLength(); i++ )
		{
			if( string[i] == (TXChar)'.' || string[i] == (TXChar)',' )
			{
				specialSymbolsCount++;
			}

			if( !( std::isdigit( string[i] ) || specialSymbolsCount <= 1 ) )
			{
				result = false;
				break;
			}
		}
	}

	return result;
}

/*static*/ TXString TXStringExt::EncodeString(const TXString& string)
{
	TXString		result;
	TXString		encodedPiece;

	size_t	strLen	= string.GetLength();
	for(size_t i=0; i<strLen; i++) {
		UCChar	ch		= string.GetAt( i );
		if ( TXStringExt::IsDigitOrAlpha( ch ) || ch == '_' || ch > 0xff )
		{
			result	+= ch;
		}
		else
		{
			encodedPiece.Format( "%X", (unsigned char)ch );
			result	+= "%";
			result	+= encodedPiece;
		}
	}

	return result;
}

/*static*/ TXString TXStringExt::DecodeString(const TXString& string)
{
	TXString	result;

	size_t	strLen	= string.GetLength();
	for(size_t i=0; i<strLen; i++) {
		UCChar	ch		= string.GetAt( i );
		if ( ch == '%' )
		{
			char	chResult	= 0;
			for(size_t j=0; j<2 && i<strLen; j++) {
				i++;
				ch					= string.GetAt( i );
				char	thisChar	= TXStringExt::IsDigit( ch ) ? (ch - L'0') : ((TXStringExt::ToUpper(ch) - L'A') + 10);
				chResult			= 16 * chResult + thisChar;
			}

			if ( chResult != 0 )
			{
				result += chResult;
			}
		}
		else
		{
			result	+= ch;
		}
	}

	return result;
}

/*static*/ TXString TXStringExt::CapitalizeEachWord(const TXString& string)
{
	TXString result;
	bool isFirst = true;
	size_t	strLen	= string.GetLength();

	for(size_t i=0; i<strLen; i++) 
	{
		UCChar	ch		= string.GetAt( i );
		if(TXStringExt::IsSpace(ch))
		{
			isFirst = true;
			result += ch;
		}
		else if(isFirst)
		{
			isFirst = false;
			result += TXStringExt::ToUpper(ch);
		}
		else
			result += TXStringExt::ToLower(ch);
	}

	return result;
}


//Utility to search from the end of string. 
/*static*/ ptrdiff_t TXStringExt::FindLastSubString(const TXString& string, const TXString& sub)
{
	ptrdiff_t found, maxFound = -1;
	found = string.Find(sub);
	while(found != -1)
	{
		maxFound = found;
		found = string.Find(sub, found+sub.GetLength());
	}
	return maxFound;
}

/*static*/ bool TXStringExt::ComparePattern(const TXString& value, const TXString& pattern)
{
	bool result = true;

	const UCChar* sz = value;
	const UCChar* szPattern = pattern;
	while ( * sz && * szPattern && result )
	{
		switch ( *szPattern )
		{
		case txuc('?'):
			sz ++;
			szPattern ++;
			break;

		case txuc('*'):
			{
				const UCChar* szAhead = sz;
				const UCChar* szPatternAhead = szPattern;
				while ( *szPatternAhead == txuc('*') || *szPatternAhead == txuc('?') )
				{
					if ( *szPatternAhead == txuc('?') )
						szAhead ++;

					szPatternAhead ++;
				}

				bool	aheadOk = *szAhead && *szPatternAhead;

				UCChar a, b;
				if ( aheadOk )
				{
					a = *szAhead;
					b = *szPatternAhead;

					if ( TXStringExt::IsAlpha(a) ) a = TXStringExt::ToLower( a );
					if ( TXStringExt::IsAlpha(a) ) b = TXStringExt::ToLower( b );
				}

				if ( aheadOk && a == b )
				{
					while ( *szPattern == txuc('*') || *szPattern == txuc('?') )
					{
						if ( *szPattern == txuc('?') )
							sz++;

						szPattern ++;
					}
				}
				else 
				{
					sz ++;
					if ( * sz == 0 )
					{
						while ( *szPattern == txuc('*') || *szPattern == txuc('?') )
						{
							szPattern ++;
						}
					}
				}
			}
			break;

		default:
			{
				UCChar a = *sz;
				UCChar b = *szPattern;

				if ( TXStringExt::IsAlpha(a) ) a = TXStringExt::ToLower( a );
				if ( TXStringExt::IsAlpha(a) ) b = TXStringExt::ToLower( b );

				result = a == b;
				sz ++;
				szPattern ++;
			} break;
		}
	}

	if ( result )
	{
		while ( *szPattern == txuc('*') )
			szPattern++;

		// ensure we are at the end of both
		result = *sz == 0 && *szPattern == 0;
	}

	return result;
}
