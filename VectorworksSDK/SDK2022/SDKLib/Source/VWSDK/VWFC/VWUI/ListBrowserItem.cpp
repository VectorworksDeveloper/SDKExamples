//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/ListBrowserItem.h"

using namespace VWFC::VWUI;
using namespace VWFC::Tools;

VWListBrowserItem::VWListBrowserItem(TControlID dialogID, TControlID controlID, short columnID, short rowID)
{
	fDialogID	= dialogID;
	fControlID	= controlID;
	fColumnID	= columnID;
	fRowID		= rowID;
}

VWListBrowserItem::VWListBrowserItem (const VWListBrowserItem& item)
{
	fDialogID	= item.fDialogID;
	fControlID	= item.fControlID;
	fColumnID	= item.fColumnID;
	fRowID		= item.fRowID;
}

VWListBrowserItem::~VWListBrowserItem()
{
}

VWListBrowserItem& VWListBrowserItem::operator=(const VWListBrowserItem& item)
{
	fDialogID	= item.fDialogID;
	fControlID	= item.fControlID;
	fColumnID	= item.fColumnID;
	fRowID		= item.fRowID;
	return *this;
}

void VWListBrowserItem::SetItemText(const TXString& text)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemInfo( gCBP, fDialogID, fControlID, fRowID, fColumnID, text, -1 ) );
}

void VWListBrowserItem::SetItemImage(size_t imageIndex)
{
	TXString		text;
	VERIFYN( kVStanev, ::GS_SetListBrowserItemInfo( gCBP, fDialogID, fControlID, fRowID, fColumnID, text, DemoteTo<short> ( kVStanev, imageIndex ) ) );
}

void VWListBrowserItem::SetItemInfo(const TXString& text, size_t imageIndex)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemInfo( gCBP, fDialogID, fControlID, fRowID, fColumnID, text, DemoteTo<short> ( kVStanev, imageIndex ) ) );
}

TXString VWListBrowserItem::GetItemText() const
{
	TXString	result;

	TXString		text;
	short		imageIndex = -1;
	if ( ::GS_GetListBrowserItemInfo( gCBP, fDialogID, fControlID, fRowID, fColumnID, text, imageIndex ) ) {
		result	= text;
	}

	return result;
}

size_t VWListBrowserItem::GetItemImage() const
{
	size_t		result		= (size_t) -1;

	TXString		text;
	short		imageIndex = -1;
	if ( ::GS_GetListBrowserItemInfo( gCBP, fDialogID, fControlID, fRowID, fColumnID, text, imageIndex ) ) {
		result	= imageIndex;
	}

	return result;
}

bool VWListBrowserItem::GetItemInfo(TXString& outText, size_t& outImage) const
{
	TXString text;
	short  imageIndex = -1;
	if ( ::GS_GetListBrowserItemInfo( gCBP, fDialogID, fControlID, fRowID, fColumnID, text, imageIndex ) ) {
		outText			= text;
		outImage		= imageIndex;
		return true;
	}
	else {
		outText.Clear();
		outImage		= (size_t) -1;
		return false;
	}
}

bool VWListBrowserItem::SetItemData( const Sint32 userData )
{
	return GS_SetListBrowserItemData( gCBP, fDialogID, fControlID, fRowID, fColumnID, userData );
}

bool VWListBrowserItem::GetItemData( Sint32 &outUserData )
{
	return GS_GetListBrowserItemData( gCBP, fDialogID, fControlID, fRowID, fColumnID, outUserData );
}

void VWListBrowserItem::SetItemToolTip(const TXString& text)
{
	gSDK->SetItemToolTipText( fDialogID, fControlID, text, "", fRowID, fColumnID );
}

void VWListBrowserItem::SetItemToolTip(const TXString& text, const TXString& subText)
{
	gSDK->SetItemToolTipText( fDialogID, fControlID, text, subText, fRowID, fColumnID );
}

bool VWListBrowserItem::EnsureItemVisible() const
{
	return ::GS_EnsureListBrowserItemIsVisible( gCBP, fDialogID, fControlID, fRowID ) ? true : false;
}

void VWListBrowserItem::SetItemTextStyle(EItemTextStyle textStyle)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemTextStyle( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<unsigned char> ( kVStanev, textStyle ) ) );
}

EItemTextStyle VWListBrowserItem::GetItemTextStyle()
{
	unsigned char textStyle;
	bool ok = ::GS_GetListBrowserItemTextStyle( gCBP, fDialogID, fControlID, fRowID, fColumnID, textStyle);
	return ok ? (EItemTextStyle) textStyle : (EItemTextStyle) -1;
}

void VWListBrowserItem::SetItemTextJustification(EItemTextJustification justification)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemTextJust( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<Sint32> ( kVStanev, justification ) ) );
}

EItemTextJustification VWListBrowserItem::GetItemTextJustification()
{
	Sint32 justification;
	bool ok = ::GS_GetListBrowserItemTextJust( gCBP, fDialogID, fControlID, fRowID, fColumnID, justification);
	return ok ? (EItemTextJustification) justification : (EItemTextJustification) -1;
}

void VWListBrowserItem::SetMultImageIndexes(size_t imageIndex0, size_t imageIndex1, size_t imageIndex2)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserMultImageIndexes( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<Sint32> ( kVStanev, imageIndex0 ), DemoteTo<Sint32> ( kVStanev, imageIndex1 ), DemoteTo<Sint32> ( kVStanev, imageIndex2 ) ) );
}

bool VWListBrowserItem::GetMultImageIndexes(size_t& outImageIndex0, size_t& outImageIndex1, size_t& outImageIndex2)
{
	Sint32 imageIndex0 = -1;
	Sint32 imageIndex1 = -1;
	Sint32 imageIndex2 = -1;

	if ( ::GS_GetListBrowserMultImageIndexes( gCBP, fDialogID, fControlID, fRowID, fColumnID, imageIndex0, imageIndex1, imageIndex2 ) ) {
		outImageIndex0		= imageIndex0; 
		outImageIndex1		= imageIndex1; 
		outImageIndex2		= imageIndex2; 
		return true;
	}
	else {
		outImageIndex0		= (size_t) -1;
		outImageIndex1		= (size_t) -1;
		outImageIndex2		= (size_t) -1;
		return false;
	}
}

void VWListBrowserItem::SetOwnerDrawnType(EListBrowserOwnerDrawnType ownerDrawnType)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserColumnOwnerDrawnType( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<Sint32> ( kVStanev, ownerDrawnType ) ) );
}

EListBrowserOwnerDrawnType VWListBrowserItem::GetOwnerDrawnType()
{
	Sint32 ownerDrawnType;
	bool ok = ::GS_GetListBrowserColumnOwnerDrawnType( gCBP, fDialogID, fControlID, fRowID, fColumnID, ownerDrawnType );
	return ok ? (EListBrowserOwnerDrawnType) ownerDrawnType : kListBrowserNotOwnerDrawn;
}

void VWListBrowserItem::SetItemUsingColumnDataItem(size_t columnDataItemIndex)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemUsingColumnDataItem( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<short> ( kVStanev, columnDataItemIndex ) ) );
}

bool VWListBrowserItem::GetColumnDataItemInfo()
{
	TXString	text	= "";
	short imageOn	= -1;
	short imageOff	= -1;
	Sint32  itemData	= -1;

	return ::GS_GetListBrowserColumnDataItemInfo( gCBP, fDialogID, fControlID, fColumnID, fRowID, text, imageOn, imageOff, itemData ) ? true : false;
}

// ----------------------------------------------------------------------------------------------------
// attributes
void VWListBrowserItem::SetItemTextColor(const CRGBColor& color)
{
	Sint32		redIndex	= color.GetRed();
	Sint32		greenIndex	= color.GetGreen();
	Sint32		blueIndex	= color.GetBlue();

	VERIFYN( kVStanev, ::GS_SetListBrowserItemTextColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex ) );
}

void VWListBrowserItem::SetItemTextColor(size_t redIndex, size_t greenIndex, size_t blueIndex)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemTextColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<Sint32> ( kVStanev, redIndex ), DemoteTo<Sint32> ( kVStanev, greenIndex ), DemoteTo<Sint32> ( kVStanev, blueIndex ) ) );
}

// Sets the color of item text by color tint.
void VWListBrowserItem::SetItemTextColorN(EUiControlTextTint colorTint)
{
	VERIFYN(kPChang, gSDK->SetListBrowserItemTextColorN(fDialogID, fControlID, fRowID, fColumnID, colorTint));
}

bool VWListBrowserItem::GetItemTextColor(CRGBColor& outColor)
{
	Sint32 redIndex	= -1;
	Sint32 greenIndex	= -1;
	Sint32 blueIndex	= -1;

	bool	ok	= ::GS_GetListBrowserItemTextColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex);
	if ( ok )
	{
		outColor.SetColor( Uint8(redIndex), Uint8(greenIndex), Uint8(blueIndex) );
	}

	return ok;
}

void VWListBrowserItem::SetItemDashStyle(InternalIndex styleIndex, size_t lineWeight)
{
	VERIFYN( kVStanev, gSDK->SetListBrowserItemLineTypeRef( fDialogID, fControlID, fRowID, fColumnID, (styleIndex < 0 ? (-1 * styleIndex) : 0), DemoteTo<Sint32> ( kVStanev, lineWeight ) ) );
}

bool VWListBrowserItem::GetItemDashStyle(InternalIndex& outStyleIndex, size_t& outLineWeight)
{
	outStyleIndex = 0;
	outLineWeight = 0;

	Sint32 styleIndex = -1;
	Sint32 lineWeight = -1;

	Boolean result = gSDK->GetListBrowserItemLineTypeRef( fDialogID, fControlID, fRowID, fColumnID, styleIndex, lineWeight );
	if ( result )
	{
		if ( styleIndex > 0 )
			outStyleIndex	= InternalIndex( -1 * styleIndex );
		outLineWeight	= size_t(lineWeight);
	}

	return result ? true : false;
}

void VWListBrowserItem::SetItemMarkerChoice(const SMarkerStyle& markerStyle)
{
	VERIFYN( kPBlanco, gSDK->SetListBrowserItemMarkerChoice( fDialogID, fControlID, fRowID, fColumnID,
		markerStyle.style,
		markerStyle.nAngle,
		markerStyle.dSize,
		markerStyle.dWidth,
		markerStyle.nThicknessBasis,
		markerStyle.dThickness )
	);
}

bool VWListBrowserItem::GetItemMarkerChoice(SMarkerStyle& markerStyle) const
{
	bool result = gSDK->GetListBrowserItemMarkerChoice( fDialogID, fControlID, fRowID, fColumnID,
		markerStyle.style,
		markerStyle.nAngle,
		markerStyle.dSize,
		markerStyle.dWidth,
		markerStyle.nThicknessBasis,
		markerStyle.dThickness );
	return result;
}

void VWListBrowserItem::ShowItemMarkerByClass(bool bShowByClass)
{
	VERIFYN( kPBlanco, gSDK->ShowListBrowserItemMarkerByClass( fDialogID, fControlID, fRowID, fColumnID, bShowByClass ) );
}

void VWListBrowserItem::ShowItemMarkerEditList(bool bShowEditList)
{
	VERIFYN( kPBlanco, gSDK->ShowListBrowserItemMarkerEditList( fDialogID, fControlID, fRowID, fColumnID, bShowEditList ) );
}

void VWListBrowserItem::SetItemMarkerByClass(bool bByClass)
{
	VERIFYN( kPBlanco, gSDK->SetListBrowserItemMarkerByClass( fDialogID, fControlID, fRowID, fColumnID, bByClass ) );
}

bool VWListBrowserItem::GetItemMarkerByClass(bool& bByClass) const
{
	bool result = gSDK->GetListBrowserItemMarkerByClass( fDialogID, fControlID, fRowID, fColumnID, bByClass );
	return result;
}

void VWListBrowserItem::SetItemFillForeColor(const CRGBColor& color)
{
	Sint32		redIndex	= color.GetRed();
	Sint32		greenIndex	= color.GetGreen();
	Sint32		blueIndex	= color.GetBlue();

	VERIFYN( kVStanev, ::GS_SetListBrowserItemFillForeColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex ) );
}

void VWListBrowserItem::SetItemFillForeColor(const TGSColorV2& color)
{
	VERIFYN( kVStanev, gSDK->SetListBrowserItemFillForeColor( fDialogID, fControlID, fRowID, fColumnID, color ) );
}

void VWListBrowserItem::SetItemFillForeColor(size_t redIndex, size_t greenIndex, size_t blueIndex)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemFillForeColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<Sint32> ( kVStanev, redIndex ), DemoteTo<Sint32> ( kVStanev, greenIndex ), DemoteTo<Sint32> ( kVStanev, blueIndex ) ) );
}

void VWListBrowserItem::SetItemNoFillForeColor()
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemFillForeColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, -1, -1, -1 ) );
}

bool VWListBrowserItem::GetItemFillForeColor( size_t &outRedIndex, size_t &outGreenIndex, size_t &outBlueIndex )
{
	Sint32		redIndex	= -1;
	Sint32		greenIndex	= -1;
	Sint32		blueIndex	= -1;
	bool	success = ::GS_GetListBrowserItemFillForeColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex );
	
	outRedIndex = redIndex; 
	outGreenIndex = greenIndex; 
	outBlueIndex = blueIndex; 
	
	return  success;
}

bool VWListBrowserItem::GetItemFillForeColor(CRGBColor& outColor)
{
	Sint32		redIndex	= -1;
	Sint32		greenIndex	= -1;
	Sint32		blueIndex	= -1;
	bool	ok = ::GS_GetListBrowserItemFillForeColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex );
	
	if ( ok )
	{
		outColor.SetColor( Uint8(redIndex), Uint8(greenIndex), Uint8(blueIndex) );
	}

	return ok;
}

bool VWListBrowserItem::GetItemFillForeColor(TGSColorV2& outColor)
{
	bool	ok = gSDK->GetListBrowserItemFillForeColor( fDialogID, fControlID, fRowID, fColumnID, outColor );

	return ok;
}

void VWListBrowserItem::SetItemFillBackColor(const CRGBColor& color)
{
	Sint32		redIndex	= color.GetRed();
	Sint32		greenIndex	= color.GetGreen();
	Sint32		blueIndex	= color.GetBlue();

	VERIFYN( kVStanev, ::GS_SetListBrowserItemFillBackColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex ) );
}

void VWListBrowserItem::SetItemFillBackColor(const TGSColorV2& color)
{
	VERIFYN( kVStanev, gSDK->SetListBrowserItemFillBackColor( fDialogID, fControlID, fRowID, fColumnID, color ) );
}

void VWListBrowserItem::SetItemFillBackColor(size_t redIndex, size_t greenIndex, size_t blueIndex)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemFillBackColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<Sint32> ( kVStanev, redIndex ), DemoteTo<Sint32> ( kVStanev, greenIndex ), DemoteTo<Sint32> ( kVStanev, blueIndex ) ) );
}

bool VWListBrowserItem::GetItemFillBackColor(CRGBColor& outColor)
{
	Sint32 redIndex	= -1;
	Sint32 greenIndex	= -1;
	Sint32 blueIndex	= -1;

	bool ok = ::GS_GetListBrowserItemFillBackColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex);
	if ( ok )
	{
		outColor.SetColor( Uint8(redIndex), Uint8(greenIndex), Uint8(blueIndex) );
	}

	return ok;
}

bool VWListBrowserItem::GetItemFillBackColor(TGSColorV2& outColor)
{
	VERIFYN( kVStanev, gSDK->GetListBrowserItemFillBackColor( fDialogID, fControlID, fRowID, fColumnID, outColor ) );

	return ok;
}

void VWListBrowserItem::SetItemGradientOrImageRefNumber(size_t refNumber)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemGradientOrImageRefNumber( gCBP, fDialogID, fControlID, fRowID, fColumnID,  DemoteTo<Sint32> ( kVStanev, refNumber ) ) );
}

size_t VWListBrowserItem::GetItemGradientOrImageRefNumber()
{
	Sint32 refNumber;
	bool ok = GS_GetListBrowserItemGradientOrImageRefNumber( gCBP, fDialogID, fControlID, fRowID, fColumnID, refNumber );
	return ok ? (size_t) refNumber : (size_t) -1;; 
}

void VWListBrowserItem::SetItemTileRefNumber(size_t refNumber)
{
	VERIFYN(kVictor, gSDK->SetListBrowserItemTileRefNumber(fDialogID, fControlID, fRowID, fColumnID,  DemoteTo<Sint32>(kVictor, refNumber)));
}

size_t VWListBrowserItem::GetItemTileRefNumber()
{
	Sint32 refNumber;
	bool ok = gSDK->GetListBrowserItemTileRefNumber(fDialogID, fControlID, fRowID, fColumnID, refNumber);
	return ok ? (size_t) refNumber : (size_t) -1;; 
}

void VWListBrowserItem::SetItemHatchRefNumber(size_t refNumber)
{
	VERIFYN(kPBlanco, gSDK->SetListBrowserItemHatchRefNumber(fDialogID, fControlID, fRowID, fColumnID,  DemoteTo<Sint32>(kVictor, refNumber)));
}

size_t VWListBrowserItem::GetItemHatchRefNumber()
{
	InternalIndex refNumber;
	bool ok = gSDK->GetListBrowserItemHatchRefNumber(fDialogID, fControlID, fRowID, fColumnID, refNumber);
	return ok ? (size_t) refNumber : (size_t) -1;;
}

void VWListBrowserItem::SetItemPenForeColor(const CRGBColor& color)
{
	Sint32		redIndex	= color.GetRed();
	Sint32		greenIndex	= color.GetGreen();
	Sint32		blueIndex	= color.GetBlue();

	VERIFYN( kVStanev, ::GS_SetListBrowserItemPenForeColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex ) );
}

void VWListBrowserItem::SetItemPenForeColor(size_t redIndex, size_t greenIndex, size_t blueIndex)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemPenForeColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<Sint32> ( kVStanev, redIndex ), DemoteTo<Sint32> ( kVStanev, greenIndex ), DemoteTo<Sint32> ( kVStanev, blueIndex ) ) );
}

bool VWListBrowserItem::GetItemPenForeColor(CRGBColor& outColor)
{
	Sint32 redIndex	= -1;
	Sint32 greenIndex	= -1;
	Sint32 blueIndex	= -1;

	bool ok = ::GS_GetListBrowserItemPenForeColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex);
	if ( ok )
	{
		outColor.SetColor( Uint8(redIndex), Uint8(greenIndex), Uint8(blueIndex) );
	}

	return ok;
}

void VWListBrowserItem::SetItemPenBackColor(const CRGBColor& color)
{
	Sint32		redIndex	= color.GetRed();
	Sint32		greenIndex	= color.GetGreen();
	Sint32		blueIndex	= color.GetBlue();

	VERIFYN( kVStanev, ::GS_SetListBrowserItemPenBackColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex ) );
}

void VWListBrowserItem::SetItemPenBackColor(size_t redIndex, size_t greenIndex, size_t blueIndex)
{
	VERIFYN( kVStanev, ::GS_SetListBrowserItemPenBackColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, DemoteTo<Sint32> ( kVStanev, redIndex ), DemoteTo<Sint32> ( kVStanev, greenIndex ), DemoteTo<Sint32> ( kVStanev, blueIndex ) ) );
}

bool VWListBrowserItem::GetItemPenBackColor(CRGBColor& outColor)
{
	Sint32 redIndex	= -1;
	Sint32 greenIndex	= -1;
	Sint32 blueIndex	= -1;

	bool ok = ::GS_GetListBrowserItemPenBackColor( gCBP, fDialogID, fControlID, fRowID, fColumnID, redIndex, greenIndex, blueIndex);
	if ( ok )
	{
		outColor.SetColor( Uint8(redIndex), Uint8(greenIndex), Uint8(blueIndex) );
	}

	return ok;
}

void VWListBrowserItem::SetItemPatternIndex(short patternIndex)
{
#if GS_MAC
    Pattern* pPattern = new Pattern();
    
    gSDK->GetPatternBits( patternIndex, pPattern->pat );
    

	if ( VERIFYN( kKIvanov, pPattern ) )
	{				
		VERIFYN( kKIvanov, GS_SetListBrowserItemPattern( gCBP, fDialogID, fControlID, fRowID, fColumnID, pPattern ) );
	}
    
    delete pPattern;
#else
	VERIFYN( kVStanev, gSDK->SetListBrowserItemPatternIndex( fDialogID, fControlID, fRowID, fColumnID, patternIndex ) );	
#endif
}

short VWListBrowserItem::GetItemPatternIndex()
{
	short result = 0;
	VERIFYN( kVStanev, gSDK->GetListBrowserItemPatternIndex( fDialogID, fControlID, fRowID, fColumnID, result ) );
	return result;
}

void VWListBrowserItem::SetItemInteractionType(EListBrowserItemInteractionType interactionType)
{
	bool success = gSDK->SetListBrowserItemInteractionType( fDialogID, fControlID, fRowID, fColumnID, interactionType );
	this->EnableItemDirectEdit( success );
}

void VWListBrowserItem::SetItemCheckState( CGSMultiStateValueChange::EStateValue state )
{
	gSDK->SetListBrowserItemCheckState( fDialogID, fControlID, (short) fRowID, fColumnID, state );
}

bool VWListBrowserItem::GetItemCheckState( CGSMultiStateValueChange::EStateValue& outState ) const
{
	int checkStateInt = 0;
	bool result = gSDK->GetListBrowserItemCheckState( fDialogID, fControlID, (short) fRowID, fColumnID, checkStateInt );

	if ( result )
	{
		outState = ( CGSMultiStateValueChange::EStateValue ) checkStateInt;
	}

	return result;
}

void VWListBrowserItem::Enable3StateCheckbox( bool enable )
{
	gSDK->EnableListBrowserItem3StateCheckBox( fDialogID, fControlID, (short) fRowID, fColumnID, enable );
}

bool VWListBrowserItem::Is3StateCheckboxEnabled() const
{
	return gSDK->IsListBrowserItem3StateCheckBoxEnabled( fDialogID, fControlID, (short) fRowID, fColumnID );
}

void VWListBrowserItem::EnableItemDirectEdit(bool enable)
{
	gSDK->SetListBrowserItemReadOnly( fDialogID, fControlID, fRowID, fColumnID, !enable );
}

bool VWListBrowserItem::IsItemDirectEditEnabled()
{
	return !gSDK->IsListBrowserItemReadOnly( fDialogID, fControlID, fRowID, fColumnID );
}

void VWListBrowserItem::SetItemResourceOnlyCurrentDocument(bool bOnlyCurrentDoc)
{
    gSDK->SetListBrowserItemResourceOnlyCurrentDocument(fDialogID, fControlID, fRowID, fColumnID, bOnlyCurrentDoc);
}

bool VWListBrowserItem::IsItemResourceOnlyCurrentDocument()
{
    return gSDK->IsListBrowserItemResourceOnlyCurrentDocument(fDialogID, fControlID, fRowID, fColumnID);
}






		
