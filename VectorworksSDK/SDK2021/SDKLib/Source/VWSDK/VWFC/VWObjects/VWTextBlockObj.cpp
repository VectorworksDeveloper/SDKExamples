//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::Tools;
using namespace VWFC::VWObjects;

const short kKludgeTextLineStarts = 7001;
const short kKludgeTextStyles = 7002;
const short kKludgeTextRuns = 7003;
const short kKludgeTextTabStops = 7004;
const short kKludgeTextCharWidths = 7005;

VWTextBlockObj::VWTextBlockObj(const TXString& strText)
{
	fOriginPt.SetPoint( 0, 0 );

	size_t			textLen	= strText.GetLength();
	if ( textLen == 0 )
	{
		fhObject	= gSDK->CreateTextBlock( TXString("_"), fOriginPt, false, 0 );
		gSDK->DeleteText( fhObject, 0, 1 );
	}
	else
	{
		// Note 'AddTextFromBuffer' doesnt work if 'GS_CreateTextBlock' creates empty text!
		// That is why we add extra space at the end just to create the text block, and then delete it
		// NOTE! You cannot extract the last char and use it with CreateTextBlock
		//	because that breaks Japaneese string drawing (see B059678)
		fhObject	= gSDK->CreateTextBlock( TXString("_"), fOriginPt, false, 0 );
		gSDK->DeleteText( fhObject, 0, 1 );
		
		// now add the text in the text object
		VERIFYN( kVStanev, gSDK->AddTextFromBuffer( fhObject, 0, (const UCChar*) strText, DemoteTo<Sint32>( kVStanev, strText.GetLength() ) ) );
	}

	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create text block" );
}

VWTextBlockObj::VWTextBlockObj(const TXString& strText, const VWPoint2D& originPt)
{
	fOriginPt		= originPt;

	size_t			textLen	= strText.GetLength();
	if ( textLen == 0 )
	{
		fhObject	= gSDK->CreateTextBlock( TXString("_"), fOriginPt, false, 0 );
		gSDK->DeleteText( fhObject, 0, 1 );
	}
	else
	{
		// Note 'AddTextFromBuffer' doesnt work if 'GS_CreateTextBlock' creates empty text!
		// That is why we add extra space at the end just to create the text block, and then delete it
		// NOTE! You cannot extract the last char and use it with CreateTextBlock
		//	because that breaks Japaneese string drawing (see B059678)
		fhObject	= gSDK->CreateTextBlock( TXString("_"), fOriginPt, false, 0 );
		gSDK->DeleteText( fhObject, 0, 1 );
		
		// now add the text in the text object
		VERIFYN( kVStanev, gSDK->AddTextFromBuffer( fhObject, 0, (const UCChar*) strText, DemoteTo<Sint32>( kVStanev, strText.GetLength() ) ) );
	}

	VWFC_ASSERT( fhObject );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create text block" );
}

VWTextBlockObj::VWTextBlockObj(MCObjectHandle hTextBlock)
{
	VWFC_ASSERT( VWTextBlockObj::IsTextBlockObject( hTextBlock ) );

	if ( ! VWTextBlockObj::IsTextBlockObject( hTextBlock ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );

	fhObject		= hTextBlock;
	VWFC_ASSERT( fhObject != nil );
}

VWTextBlockObj::VWTextBlockObj(const VWTextBlockObj& src)
{
	fhObject		= src.fhObject;
	fOriginPt		= src.fOriginPt;
}

VWTextBlockObj::~VWTextBlockObj()
{
}

VWTextBlockObj& VWTextBlockObj::operator=(const VWTextBlockObj& src)
{
	fhObject		= src.fhObject;
	fOriginPt		= src.fOriginPt;
	return *this;
}

bool VWTextBlockObj::IsTextBlockObject(MCObjectHandle hObj)
{
	short	type = gSDK->GetObjectTypeN( hObj );
	return	( type == kTextNode );
}

VWPoint2D VWTextBlockObj::GetOriginPt() const
{
	WorldPt		locPos;
	VWFC_ASSERT( fhObject );
	gSDK->GetLocusPosition( fhObject, locPos );
	return locPos;
}

void VWTextBlockObj::SetOriginPt(const VWPoint2D& pt)
{
	VWFC_ASSERT( fhObject );
	gSDK->SetLocusPosition( fhObject, pt );
}

bool VWTextBlockObj::InsertText(const TXString& strAdd, size_t beforeIndex /*= 0*/)
{
	// get text block chars to a buffer
	size_t	textLen		= this->GetTextLength();

	bool	bAdded	= false;
	// Note 'GS_AddTextFromBuffer' doesnt work if 'GS_CreateTextBlock' creates empty text!
	if ( textLen == 0 ) {

		size_t	strLen	= strAdd.GetLength();
		if ( strLen > 0 ) {

			// delete current text block
			this->DeleteObject( false );

			// create a new text block
			fhObject	= ::GS_CreateTextBlock( gCBP, strAdd, fOriginPt, false, 0 );

			VWFC_ASSERT( fhObject );
			bAdded	= ( fhObject != NULL );
		}
	}
	else {

		size_t	strLen	= strAdd.GetLength();
		if ( strLen > 0 ) {
			bAdded	= ::GS_AddTextFromBuffer( gCBP, fhObject, (Sint32) beforeIndex, (const UCChar*) strAdd, (Sint32) strLen );
		}
	}

	return bAdded;
}

bool VWTextBlockObj::AppendText(const TXString& strAdd)
{
	return this->InsertText( strAdd, this->GetTextLength() );
}

void VWTextBlockObj::DeletePartOfText(size_t firstIndex, size_t numChars)
{
	size_t	textLen		= this->GetTextLength();
	VWFC_ASSERT( firstIndex < textLen && numChars <= textLen );
	::GS_DeleteText( gCBP, fhObject, (Sint32) firstIndex, (Sint32) numChars ); 
}

void VWTextBlockObj::DeleteText()
{
	this->DeletePartOfText( 0, this->GetTextLength() );
}

bool VWTextBlockObj::SetText(const TXString& text)
{
	size_t	length	= this->GetTextLength();
	bool	added	= this->AppendText( text );

	if ( added )
	{
		this->DeletePartOfText( 0, length );
	}

	return added;
}

size_t VWTextBlockObj::GetTextLength() const
{
	return (size_t) ::GS_GetTextLength( gCBP, fhObject ); 
}

TXString VWTextBlockObj::GetText() const
{
	return gSDK->GetTextChars(fhObject);
}

size_t VWTextBlockObj::GetNearestCharIndex(const VWPoint2D& pt) const
{
	size_t resNum	= (size_t) ::GS_GetCharNumFromPoint( gCBP, fhObject, pt ); 
	VWFC_ASSERT( resNum >= 0 && resNum < this->GetTextLength() );
	return resNum;
}

void VWTextBlockObj::SetTextColor(const CRGBColor& color)
{
	this->SetCharsColor( 0, this->GetTextLength(), color.GetColorIndex() );
}

void VWTextBlockObj::SetTextFontIndex(short textFontIndex)
{
	this->SetCharsFontIndex( 0, this->GetTextLength(), textFontIndex );
}

void VWTextBlockObj::SetTextSize(double dTextSize)
{
	this->SetCharsSize( 0, this->GetTextLength(), dTextSize );
}

void VWTextBlockObj::SetTextSizeByPoint(double dPointSize)
{
	double	dCharSize	= ::GS_PagePointsToCoordLength( gCBP, dPointSize );
	this->SetCharsSize( 0, this->GetTextLength(), dCharSize );
}

void VWTextBlockObj::SetTextStyle(ETextStyle style)
{
	this->SetCharsStyle( 0, this->GetTextLength(), style );
}

CRGBColor VWTextBlockObj::GetCharColor(size_t charNum) const
{
	ColorRef	charColor;
	::GS_GetTextColor( gCBP, fhObject, (Sint32) charNum, charColor ); 
	return	CRGBColor( charColor );
}

short VWTextBlockObj::GetCharFontIndex(size_t charNum) const
{
	short	charFontIndex;
	::GS_GetTextFontIndex( gCBP, fhObject, (Sint32) charNum, charFontIndex ); 
	return	charFontIndex;
}

double	VWTextBlockObj::GetCharSize(size_t charNum) const
{
	double	charSize = 0.0; // Setting default value to 0.0, as otherwise this function might return invalid value.
	::GS_GetTextSize( gCBP, fhObject, (Sint32) charNum, charSize ); 
	return	charSize;
}

ETextStyle VWTextBlockObj::GetCharStyle(size_t charNum) const
{
	unsigned char	charStyle;
	::GS_GetTextStyle( gCBP, fhObject, (Sint32) charNum, charStyle ); 
	return	(ETextStyle) charStyle;
}

void VWTextBlockObj::SetCharsColor(size_t firstIndex, size_t numChars, const CRGBColor& color)
{
	::GS_SetTextColor( gCBP, fhObject, (Sint32) firstIndex, (Sint32) numChars, color.GetColorIndex() ); 
}

void VWTextBlockObj::SetCharsFontIndex(size_t firstIndex, size_t numChars, short fontIndex)
{
	::GS_SetTextFontIndex( gCBP, fhObject, (Sint32) firstIndex, (Sint32) numChars, fontIndex ); 
}

void VWTextBlockObj::SetCharsSize(size_t firstIndex, size_t numChars, double dCharSize)
{
	::GS_SetTextSize( gCBP, fhObject, (Sint32) firstIndex, (Sint32) numChars, dCharSize ); 
}

void VWTextBlockObj::SetCharsSizeByPoint(size_t firstIndex, size_t numChars, double dPointSize)
{
	double	dCharSize	= ::GS_PagePointsToCoordLength( gCBP, dPointSize );
	::GS_SetTextSize( gCBP, fhObject, (Sint32) firstIndex, (Sint32) numChars, dCharSize ); 
}

void VWTextBlockObj::SetCharsStyle(size_t firstIndex, size_t numChars, ETextStyle style)
{
	::GS_SetTextStyle( gCBP, fhObject, (Sint32) firstIndex, (Sint32) numChars, style ); 
}

CRGBColor VWTextBlockObj::GetNearestCharColor(const VWPoint2D& pt) const
{
	size_t	charNum = (size_t) ::GS_GetCharNumFromPoint( gCBP, fhObject, pt ); 
	return	this->GetCharColor( charNum );
}

short VWTextBlockObj::GetNearestCharFontIndex(const VWPoint2D& pt) const
{
	size_t	charNum = (size_t) ::GS_GetCharNumFromPoint( gCBP, fhObject, pt ); 
	return	this->GetCharFontIndex( charNum );
}

double	VWTextBlockObj::GetNearestCharSize(const VWPoint2D& pt) const
{
	size_t	charNum = (size_t) ::GS_GetCharNumFromPoint( gCBP, fhObject, pt ); 
	return	this->GetCharSize( charNum );
}

ETextStyle VWTextBlockObj::GetNearestCharStyle(const VWPoint2D& pt) const
{
	size_t	charNum = (size_t) ::GS_GetCharNumFromPoint( gCBP, fhObject, pt ); 
	return	(ETextStyle) this->GetCharStyle( charNum );
}

ETextHorzAlign VWTextBlockObj::GetTextJustification() const
{
	short	textJust;
	::GS_GetTextJustification( gCBP, fhObject, textJust );
	return	(ETextHorzAlign) textJust;
}

void VWTextBlockObj::SetTextJustification(ETextHorzAlign textJust)
{
	::GS_SetTextJustification( gCBP, fhObject, textJust );
}

void VWTextBlockObj::GetTextOrientation(double& outAngle, bool& outVertFlip)
{
	short		flipState;
	::GS_GetTextOrientationN( gCBP, fhObject, outAngle, flipState );

	outVertFlip		= flipState == kTextVerticalFlip;
}

void VWTextBlockObj::SetTextOrientation(double dAngle, bool bVertFlip)
{
	::GS_SetTextOrientationN( gCBP, fhObject, dAngle, bVertFlip ? kTextVerticalFlip : kTextNoFlip );
}

void VWTextBlockObj::GetLineArray(std::vector<short>& lines) const
{
	gSDK->Kludge(kKludgeTextLineStarts, fhObject, &lines);
}

void VWTextBlockObj::GetStyleArray(std::vector<TextStyleRec>& styles) const
{
	gSDK->Kludge(kKludgeTextStyles, fhObject, &styles);
}

void VWTextBlockObj::GetRunArray(std::vector<TextRunRec>& runs) const
{
	gSDK->Kludge(kKludgeTextRuns, fhObject, &runs);
}

void VWTextBlockObj::GetTabStopArray(std::vector<TextTabStop>& tabStops) const
{
    gSDK->Kludge(kKludgeTextTabStops, fhObject, &tabStops);
}

void VWTextBlockObj::GetCharWidthArray(std::vector<WorldCoord>& charWidths) const
{
    gSDK->Kludge(kKludgeTextCharWidths, fhObject, &charWidths);
}

double VWTextBlockObj::GetTextWidth() const
{
	double	textWidth;
	::GS_GetTextWidth( gCBP, fhObject, textWidth );
	return	textWidth;
}

void VWTextBlockObj::SetTextWidth(double dWidth)
{
	::GS_SetTextWidth( gCBP, fhObject, dWidth );
}

bool VWTextBlockObj::IsTextWrapped() const
{
	Boolean	bWrapped;
	::GS_GetTextWrap( gCBP, fhObject, bWrapped );
	return	bWrapped;
}

void VWTextBlockObj::SetTextWrap(bool bWrapped)
{
	::GS_SetTextWrap( gCBP, fhObject, bWrapped );
}

bool VWTextBlockObj::IsNoteText() const
{
	bool bNoteText = false;
	TVariableBlock value;
	gSDK->GetObjectVariable(fhObject, ovTextIsDimNoteText, value);
	value.GetBoolean(bNoteText);
	return bNoteText;
}

bool VWTextBlockObj::HasTightFill() const
{
	bool bTightFill = false;
	TVariableBlock value;
	gSDK->GetObjectVariable(fhObject, ovTextTightFill, value);
	value.GetBoolean(bTightFill);
	return bTightFill;
}

bool VWTextBlockObj::IsSIAElevationText() const
{
	bool bSIAElev;
	TVariableBlock value;
	gSDK->GetObjectVariable(fhObject, ovTextIsSiaElevText, value);
	value.GetBoolean(bSIAElev);
	return bSIAElev;
}

bool VWTextBlockObj::IsRightToLeftText() const
{
	bool bRightToLeft;
	TVariableBlock value;
	gSDK->GetObjectVariable(fhObject, ovTextIsRightToLeft, value);
	value.GetBoolean(bRightToLeft);
	return bRightToLeft;
}

ETextVertAlign VWTextBlockObj::GetTextVerticalAlignment() const
{
	short	verticalAlignment;
	::GS_GetTextVerticalAlignment( gCBP, fhObject, verticalAlignment );
	return	(ETextVertAlign) verticalAlignment;
}

void VWTextBlockObj::SetTextVerticalAlignment(ETextVertAlign align)
{
	::GS_SetTextVerticalAlignment( gCBP, fhObject, align );
}

void VWTextBlockObj::GetTextVerticalSpacing(ETextVertSpacing& outSpacing, double& outHeight)
{
	short	spcing;
	::GS_GetTextVerticalSpacing( gCBP, fhObject, spcing, outHeight );
	outSpacing		= (ETextVertSpacing) spcing;
}

void VWTextBlockObj::SetTextVerticalSpacing(ETextVertSpacing spacing, double dHeight)
{
	::GS_SetTextVerticalSpacing( gCBP, fhObject, spacing, dHeight );
}

/*static*/ TXString	VWTextBlockObj::GetNewLineSymbol()
{
	return "\r";
}

void VWTextBlockObj::GetTextBoundary(WorldRectVerts& outBoxVerts)
{
	gSDK->GetObjectBoundingBoxVerts( fhObject, outBoxVerts );
}

