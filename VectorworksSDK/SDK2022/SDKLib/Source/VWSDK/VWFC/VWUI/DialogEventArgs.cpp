//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC/VWUI/DialogEventArgs.h"

using namespace VWFC::VWUI;

// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
VWDialogEventArgs::VWDialogEventArgs()
{
	fDialogID			= 0;
	fpData				= NULL;
	fbNegativeControlID	= false;
	fControlID			= 0;
}

VWDialogEventArgs::VWDialogEventArgs(Sint32 dlgID, Sint32 ctrlID, void* pData)
{
	fDialogID			= dlgID;
	fpData				= pData;
	fbNegativeControlID	= ctrlID < 0;
	fControlID			= ctrlID >= 0 ? ctrlID : - ctrlID;
}

VWDialogEventArgs::~VWDialogEventArgs()
{
	fDialogID	= 0;
	fControlID	= 0;
	fpData		= NULL;
}

Sint32 VWDialogEventArgs::GetEventData() const
{
	Sint32	data	= 0;
	
	if ( fpData ) {
		Sint32*	pData	= (Sint32*) fpData;
		data			= *pData;
	}

	return data;
}

void* VWDialogEventArgs::GetEventDataPtr() const
{
	return fpData;
}

EListBrowserEventType VWDialogEventArgs::GetListBrowserEvent(size_t& outRowIndex, size_t& outColumnIndex) const
{
	EListBrowserEventType	type		= kListBrowserEventType_Unknown;
	if ( fDialogID == 0 || fControlID == 0 )
	{
		outRowIndex		= size_t(-1);
		outColumnIndex	= size_t(-1);
	}
	else
	{
		Sint32	eventType	= 0;
		Sint32	rowIndex	= 0;
		Sint32	columnIndex	= 0;
		if ( ::GS_GetListBrowserEventInfo( gCBP, fDialogID, fControlID, eventType, rowIndex, columnIndex ) ) {
			if ((eventType != kListBrowserEventType_SelectionChangeClick) ||
				(rowIndex >= 0 && columnIndex >=0))
			{
				type			= (EListBrowserEventType) eventType;
				outRowIndex		= rowIndex; 
				outColumnIndex	= columnIndex;
			}
			else
			{
				type = kListBrowserEventType_Unknown;
				outRowIndex = 0;
				outColumnIndex = 0;
			}
			// temp List Broweser event log to easily catch bugs and inconsistencies
			DMSG((kEveryone, TXString::Formatted(">> Dialog Event: %d\n", eventType)));
		}
	}

	return type;
}

bool VWDialogEventArgs::IsListBrowserDoubleClickEvent() const
{
	return fbNegativeControlID;
}

bool VWDialogEventArgs::IsListBrowserNextMessageIsDropInfo() const
{
	return this->GetEventData() == kListBrowserEventType_ReceivingDragAndDrop;
}

SListBrowserDragDropInfo* VWDialogEventArgs::GetListBrowserDropInfo()
{
	SListBrowserDragDropInfo** ppInfo = (SListBrowserDragDropInfo**) this->GetEventDataPtr();
    return ppInfo ? *ppInfo : nullptr;
}

bool VWDialogEventArgs::IsListBrowserDrawNDropEnd() const
{
	return this->GetEventData() == kListBrowserEventType_DragAndDrop;
}

bool VWDialogEventArgs::IsPullDownNotification() const
{
	return this->GetEventData() == -1;
}

bool VWDialogEventArgs::IsImagePopupSelected() const
{
	return !fbNegativeControlID;
}

bool VWDialogEventArgs::IsImagePopupBeforeOpen() const
{
	bool result = false;
	if ( fbNegativeControlID )
	{
		SImagePopupAdvancedMsgData* pInfo = (SImagePopupAdvancedMsgData*) this->GetEventDataPtr();
		result = pInfo ? pInfo->fReason == SImagePopupAdvancedMsgData::Opened : false;
	}

	return result;
}

bool VWDialogEventArgs::IsImagePopupCategoryChanged(size_t& outCategoryIndex)
{
	bool result = false;
	if ( fbNegativeControlID )
	{
		SImagePopupAdvancedMsgData* pInfo = (SImagePopupAdvancedMsgData*) this->GetEventDataPtr();
		result = pInfo ? pInfo->fReason == SImagePopupAdvancedMsgData::CategoryChanged : false;
		if ( result )
		{
			outCategoryIndex = pInfo->fCategoryIndex;
		}
	}

	return result;
}

TTreeItemID VWDialogEventArgs::GetTreeCtrlClickItemID() const
{
	TTreeItemID result = -1;
	if ( fpData )
	{
		TreeControlClickMessageData* msgData = (TreeControlClickMessageData*) fpData;
		result = msgData->fItemClickedOn;
	}

	return result;
}

bool VWDialogEventArgs::IsTreeCtrlSelectionChanged() const
{
	bool result = false;
	if ( fpData )
	{
		TreeControlClickMessageData* msgData = (TreeControlClickMessageData*) fpData;
		result = msgData->fIsSelectionChanged;
	}

	return result;
}

bool VWDialogEventArgs::IsTreeCtrlDoubleClickEvent() const
{
	bool result = false;
	if ( fpData )
	{
		TreeControlClickMessageData* msgData = (TreeControlClickMessageData*) fpData;
		result = msgData->fIsDoubleClick;
	}

	return result;
}

bool VWDialogEventArgs::IsTreeCtrlClickOnIcon() const
{
	bool result = false;
	if ( fpData )
	{
		TreeControlClickMessageData* msgData = (TreeControlClickMessageData*) fpData;
		result = msgData->fIsClickOnIcon;
	}

	return result;
}

bool VWDialogEventArgs::IsTreeCtrlClickOnCheckBox() const
{
	bool result = false;
	if ( fpData )
	{
		TreeControlClickMessageData* msgData = (TreeControlClickMessageData*) fpData;
		result = msgData->fIsCLickOnCheckBox;
	}

	return result;
}

void VWDialogEventArgs::GetTreeCtrlModifiers(bool& outShiftDown, bool& outCtrlDown, bool& outAltDown) const
{
	outShiftDown = false;
	outCtrlDown = false;
	outAltDown = false;
	if ( fpData )
	{
		TreeControlClickMessageData* msgData = (TreeControlClickMessageData*) fpData;
		outShiftDown = msgData->fShiftKeyDown;
		outCtrlDown = msgData->fControlKeyDown;
		outAltDown = msgData->fAltKeyDown;
	}
}

bool VWDialogEventArgs::GetTreeCtrlKeyClick(Sint32& outKeyCode) const
{
	bool result = false;
	if ( fpData )
	{
		TreeControlClickMessageData* msgData = (TreeControlClickMessageData*) fpData;
		result = msgData->fIsKeyClick;
		outKeyCode = msgData->fKeyClickCode;
	}

	return result;
}

bool VWDialogEventArgs::IsCustomCtrlMouseDown() const
{
	Sint32* arr = (Sint32*) fpData;
	return arr[ 0 ] == -1;
}

bool VWDialogEventArgs::IsCustomCtrlClickEvent() const
{
	Sint32* arr = (Sint32*) fpData;
	return arr[ 0 ] == 0;
}

bool VWDialogEventArgs::IsCustomCtrlDoubleClickEvent() const
{
	Sint32* arr = (Sint32*) fpData;
	return arr[ 0 ] == 10;
}

bool VWDialogEventArgs::IsCustomCtrlRightClickEvent() const
{
	Sint32* arr = (Sint32*) fpData;
	return arr[ 0 ] == 1;
}

bool VWDialogEventArgs::IsCustomCtrlRightDoubleClickEvent() const
{
	Sint32* arr = (Sint32*) fpData;
	return arr[ 0 ] == 10;
}

bool VWDialogEventArgs::IsCustomCtrlMiddleClickEvent() const
{
	Sint32* arr = (Sint32*) fpData;
	return arr[ 0 ] == 2;
}

bool VWDialogEventArgs::IsCustomCtrlMiddleDoubleClickEvent() const
{
	Sint32* arr = (Sint32*) fpData;
	return arr[ 0 ] == 20;
}

Sint32 VWDialogEventArgs::GetCustomCtrlEventPosX() const
{
	Sint32* arr = (Sint32*) fpData;
	return arr[ 1 ];
}

Sint32 VWDialogEventArgs::GetCustomCtrlEventPosY() const
{
	Sint32* arr = (Sint32*) fpData;
	return arr[ 2 ];
}

EEditFieldEventType	VWDialogEventArgs::GetEditFieldEvent() const
{
	return (EEditFieldEventType)GetEventData();
}

ESearchEditFieldEventType	VWDialogEventArgs::GetSearchEditFieldEvent() const
{
	return (ESearchEditFieldEventType)GetEventData();
}

// Returns true when a user finishes typing in the search field and presses the enter key.
bool VWDialogEventArgs::IsSearchEditCommitted() const
{
	return (this->GetEventData() == kSearchEditFieldEventType_EnterKeyPressed);
}

// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
VWListBrowserEventArgs::VWListBrowserEventArgs(TControlID dlgID, TItemMessageData& data)
	: fDialogID( dlgID )
	, fData( data )
{
}

VWListBrowserEventArgs::~VWListBrowserEventArgs()
{
}

EListBrowserDirectEditType VWListBrowserEventArgs::GetType()
{
	EListBrowserDirectEditType	 result;
	switch ( fData.fMessageDataId )
	{
		default:
		case kMessageQueryInteractionHandlingType:	result = EListBrowserDirectEditType::QueryInteractionHandlingType    ; break;
		case kMessageQueryItemValue:				result = EListBrowserDirectEditType::QueryItemValue                  ; break;
		case kMessageQueryItemListRetrieval:		result = EListBrowserDirectEditType::QueryItemListRetrieval          ; break;
		case kMessageItemEditCompletionData:		result = EListBrowserDirectEditType::ItemEditCompletionData          ; break;
	}
	// temp List Broweser event log to easily catch bugs and inconsistencies
	DMSG((kEveryone, TXString::Formatted(">> List Browser Direct Edit Event: %d\n", fData.fMessageDataId)));

	return result;
}

EListBrowserDirectEditType VWListBrowserEventArgs::GetType(size_t& outRowIndex, size_t& outColumnIndex)
{
	outRowIndex		= fData.fItemId;
	outColumnIndex	= fData.fAuxiliaryItemData;

	return this->GetType();
}

size_t VWListBrowserEventArgs::GetRowIndex()
{
	return fData.fItemId;
}

size_t VWListBrowserEventArgs::GetColumnIndex()
{
	return fData.fAuxiliaryItemData;
}

void VWListBrowserEventArgs::SetInteractionHandlingType(EListBrowserItemInteractionType type)
{
	DSTOPIF( fData.fMessageDataId != kMessageQueryInteractionHandlingType, (kVStanev, "this function is expected to be used only during EListBrowserDirectEditType::QueryInteractionHandlingType"));
	fData.fReturnCode = type;
}

void VWListBrowserEventArgs::SetInvalidEditCompletionData()
{
	if (fData.fMessageDataId == kMessageItemEditCompletionData) {
		fData.fReturnCode = 0;
	}
	else {
		DSTOP((kILane, "This function is expected to be used only during EListBrowserDirectEditType::kMessageItemEditCompletionData"));
	}
}

CGSStringValueChange& VWListBrowserEventArgs::GetCellString()
{
	static CGSStringValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;

	CGSStringValueChange* value = (CGSStringValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSColorValueChange& VWListBrowserEventArgs::GetCellColor()
{
	static CGSColorValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;
	
	CGSColorValueChange* value = (CGSColorValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSPatternValueChange& VWListBrowserEventArgs::GetCellPattern()
{
	static CGSPatternValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;
	
	CGSPatternValueChange* value = (CGSPatternValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSPatternWithColorValueChange& VWListBrowserEventArgs::GetCellPatternWithColor()
{
	static CGSPatternWithColorValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;
	
	CGSPatternWithColorValueChange* value = (CGSPatternWithColorValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSHatchStyleValueChange& VWListBrowserEventArgs::GetCellHatchStyle()
{
	static CGSHatchStyleValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;

	CGSHatchStyleValueChange* value = (CGSHatchStyleValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSGradientValueChange& VWListBrowserEventArgs::GetCellGradient()
{
	static CGSGradientValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;
	
	CGSGradientValueChange* value = (CGSGradientValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSImageResourceValueChange& VWListBrowserEventArgs::GetCellImageResource()
{
	static CGSImageResourceValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;
	
	CGSImageResourceValueChange* value = (CGSImageResourceValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSTileResourceValueChange& VWListBrowserEventArgs::GetCellTileResource()
{
	static CGSTileResourceValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;
	
	CGSTileResourceValueChange* value = (CGSTileResourceValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSLineTypeValueChange& VWListBrowserEventArgs::GetCellLineType()
{
	static CGSLineTypeValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;
	
	CGSLineTypeValueChange* value = (CGSLineTypeValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSLineWeightValueChange& VWListBrowserEventArgs::GetCellLineWeight()
{
	static CGSLineWeightValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;
	
	CGSLineWeightValueChange* value = (CGSLineWeightValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSLineEndValueChange& VWListBrowserEventArgs::GetCellLineEnd()
{
	static CGSLineEndValueChange sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;

	CGSLineEndValueChange* value = (CGSLineEndValueChange*)(fData.fItemChangeData.get());
	return value ? *value : sEmptyValue;
}

CGSMenuItemCollection& VWListBrowserEventArgs::GetCellMenuItemCollection()
{
	static CGSMenuItemCollection sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemListRetrieval) ? 1 : 0;
	
	CGSMenuItemCollection* value = (CGSMenuItemCollection*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSMenuItemValue& VWListBrowserEventArgs::GetCellMenuItemValue()
{
	static CGSMenuItemValue sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemListRetrieval || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;

	CGSMenuItemValue* value = (CGSMenuItemValue*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSMultiStateValueChange& VWListBrowserEventArgs::GetCellCheckbox()
{
	static CGSMultiStateValueChange sEmptyValue;
		
	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemValue || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;

	CGSMultiStateValueChange* value = (CGSMultiStateValueChange*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSClassAndLayerPulldownCollection& VWListBrowserEventArgs::GetCellClassLayerPulldownCollection()
{
	static CGSClassAndLayerPulldownCollection sEmptyValue(NULL);

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemListRetrieval) ? 1 : 0;

	CGSClassAndLayerPulldownCollection* value = (CGSClassAndLayerPulldownCollection*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSClassAndLayerPulldownItemValue& VWListBrowserEventArgs::GetCellClassLayerPulldownValue()
{
	static CGSClassAndLayerPulldownItemValue sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;

	CGSClassAndLayerPulldownItemValue* value = (CGSClassAndLayerPulldownItemValue*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSListItemValue & VWListBrowserEventArgs::GetCellListItemValue()
{
	static CGSListItemValue sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemListRetrieval || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;

	CGSListItemValue* value = (CGSListItemValue*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSSearchablePulldownCollection& VWListBrowserEventArgs::GetCellSearchablePulldownCollection()
{
	static CGSSearchablePulldownCollection sEmptyValue( nullptr );

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemListRetrieval) ? 1 : 0;

	CGSSearchablePulldownCollection* value = (CGSSearchablePulldownCollection*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}

CGSSearchablePulldownItemValue& VWListBrowserEventArgs::GetCellSearchablePulldownItemValue()
{
	static CGSSearchablePulldownItemValue sEmptyValue;

	// for simplicity we assume that getting a cell value is ok result code for this message
	fData.fReturnCode = (fData.fMessageDataId == kMessageQueryItemListRetrieval || fData.fMessageDataId == kMessageItemEditCompletionData) ? 1 : 0;

	CGSSearchablePulldownItemValue* value = (CGSSearchablePulldownItemValue*)( fData.fItemChangeData.get() );
	return value ? *value : sEmptyValue;
}
