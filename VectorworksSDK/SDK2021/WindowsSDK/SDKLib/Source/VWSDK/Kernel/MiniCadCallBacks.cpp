//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Defines SDK library functions & utility functionality.
//	Includes the file which defines the entire set of SDK functions.
//


#include "StdHeaders.h"

// [1/96, MJH] this should be defined in the source file, not the header
#define _MINICADCALLBACKS_CPP

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>



#include "Kernel/CallbackIDs.h"
#include "Kernel/GSString.h"
#include "Kernel/MiniCadCallBacks.h"
#include "VectorworksSDK.h"


Boolean	TVariableBlock::GetTXString(TXString& data) const
{ 
	if (eType == t_TXString) {
        data = fData.uStr;
		return true ;
	} 
	else return false ;
}

TVariableBlock& TVariableBlock::operator=(const TXString& data)
{
    data.CopyInto(fData.uStr, 256);
	eType = t_TXString ;
	return *this ;
}

FormatTextType::FormatTextType()
{
    ioStyle = 0;
    ioCustomStyle = 0;
    ioSize = 12;
    ioSpacing = kTextSingle;
    ioLeading = 0;
    ioHAlignment = kTextLeftJustify; 
    ioVAlignment = kTextTopBox;
    ioTextStyle = 0;
    iDisableMask = 0;
    ioStyleMask = 0;
    cFlag = false;
}

////////////////////////
// GLOBAL pointer to the SDK VCOM funtion interface
////////////////////////

VectorWorks::ISDK* gSDK		= NULL;

////////////////////////
// GLOBAL pointer to the VWMM object
////////////////////////

VWMM::Partition* gVWMM		= NULL;

////////////////////////
// GLOBAL pointer to the IFC support interface
////////////////////////

VectorWorks::IFCLib::IIFCSupportAccessor gIFC;

VectorWorks::IFCLib::IIFCSupportAccessor::operator VectorWorks::IFCLib::IIFCSupport*()
{
	if ( fPtr == nullptr )
		fPtr.Query( IID_IFCSupport );
	return fPtr;
}

VectorWorks::IFCLib::IIFCSupport* VectorWorks::IFCLib::IIFCSupportAccessor::operator->()
{
	if ( fPtr == nullptr )
		fPtr.Query( IID_IFCSupport );
	return fPtr;
}

void VectorWorks::IFCLib::IIFCSupportAccessor::Release()
{
	if ( fPtr )
	{
		fPtr.Release();
	}
}

////////////////////////
// GLOBAL pointer to the DataTag support interface
////////////////////////

VectorWorks::Extension::IDataTagSupportAccessor gDataTagSupport;

VectorWorks::Extension::IDataTagSupportAccessor::operator VectorWorks::Extension::IDataTagSupport*()
{
	if ( fPtr == nullptr )
		fPtr.Query( IID_DataTagSupport );
	return fPtr;
}

VectorWorks::Extension::IDataTagSupport* VectorWorks::Extension::IDataTagSupportAccessor::operator->()
{
	if ( fPtr == nullptr )
		fPtr.Query( IID_DataTagSupport );
	return fPtr;
}

void VectorWorks::Extension::IDataTagSupportAccessor::Release()
{
	if ( fPtr )
	{
		fPtr.Release();
	}
}

////////////////////////
// GLOBAL pointer to the DataTag support interface
////////////////////////

IFormatHandlerSupportAccessor gFormatHandlerSupport;

IFormatHandlerSupportAccessor::operator IFormatHandlerSupport*()
{
	if ( fPtr == nullptr )
		fPtr.Query( IID_FormatHandlerSupport );
	return fPtr;
}

IFormatHandlerSupport* IFormatHandlerSupportAccessor::operator->()
{
	if ( fPtr == nullptr )
		fPtr.Query( IID_FormatHandlerSupport );
	return fPtr;
}

void IFormatHandlerSupportAccessor::Release()
{
	if ( fPtr )
	{
		fPtr.Release();
	}
}

////////////////////////
// GLOBAL CallBackPtr
////////////////////////

CallBackPtr gCBP = nil;

void GS_API SetupGlobalCBP(CallBackPtr cbp)
{
	gCBP = cbp;
}


extern "C" {
// GS_SDKPPC_JAK2
#ifdef _MINICAD_
	// If _MINICAD_ we are building the main application...
	#define CALLBACKPTR CallBackPtr
//	#ifdef powerc
//	#define GET_CB_UPP(fn) UniversalProcPtr f = (UniversalProcPtr) FIDToPtr(kcb##fn); \
//							if (f) f = (UniversalProcPtr) f->routineRecords[0].procDescriptor
//	#else
	// The macro GET_CB_UPP is used by the AppleScript which generates "MiniCadCallBacks.Defs.cpp".
	#define GET_CB_UPP(fn) UniversalProcPtr f = (UniversalProcPtr) FIDToPtr(kcb##fn)
//	#endif
	#define CALL_PROC(fn)	((fn##Ptr) f)
#else
	// else we are building Plug-ins...
//	#define XCALL(fn)	GenericFunctionPtr f = (*cbp->rPtr)(kcb##fn); if (f) ((fn##Ptr) f)
//	#define XFN(fn)		GenericFunctionPtr f = (*cbp->rPtr)(kcb##fn); return f ? ((fn##Ptr) f)
	
	#define CALLBACKPTR CallBackPtr cbp

//	#ifdef powerc		
//		#define GET_CB_UPP(fn) UniversalProcPtr f = (UniversalProcPtr) CallRetrieverProc(cbp->rPtr, kcb##fn); \
//							if (f) f = (UniversalProcPtr) f->routineRecords[0].procDescriptor
//	#else
		#define GET_CB_UPP(fn) GenericFunctionPtr f = cbp ? (*cbp->rPtr)(kcb##fn) : nil;
//	#endif
	#define CALL_PROC(fn)	((fn##Ptr) f)
#endif

// include the automatically generated portion of this file
#if !GS_INLINE_SDK_CALLS
#include "MiniCadCallBacks.Defs.cpp"
#endif


//#undef XCALL
//#undef XFN

}

///////////////////////////////////////////////////////////////////////////////////
/*static*/ size_t	VWFC::Tools::TDisableScreenRefreshState::sDisableState	= 0;

VWFC::Tools::TDisableScreenRefreshState::TDisableScreenRefreshState()
{
	if ( sDisableState == 0 )
	{
		bool enable = false;
		gSDK->SetProgramVariable( varDisableScreenRefreshState, &enable );
	}

	sDisableState++;
}

VWFC::Tools::TDisableScreenRefreshState::~TDisableScreenRefreshState()
{
	if ( sDisableState > 0 )
		sDisableState--;

	if ( sDisableState == 0 )
	{
		bool enable = true;
		gSDK->SetProgramVariable( varDisableScreenRefreshState, &enable );
	}
}

//////////////////////////////////////////////////////////////////////
// Implementations for library calls
//////////////////////////////////////////////////////////////////////



double_gs GS_LIBRARY GS_CoordLengthToPageLengthN(CallBackPtr cbp, WorldCoord len)
{
	double_gs result = 0.0;
	GS_CoordLengthToPageLengthN(cbp, len, result);
	return result;
}

double_gs GS_LIBRARY GS_CoordLengthToUnitsLengthN(CallBackPtr cbp, WorldCoord len)
{
	double_gs result = 0.0;
	GS_CoordLengthToUnitsLengthN(cbp, len, result);
	return result;
}


void GS_LIBRARY GS_HLock(CallBackPtr cbp, GSHandle handle)
{
	GS_SetHandleState(cbp, handle, true);
}

void GS_LIBRARY GS_HUnlock(CallBackPtr cbp, GSHandle handle)
{
	GS_SetHandleState(cbp, handle, false);
}


// ---------------------------------------------------------------------------------------------
// VCOM supprot
// ---------------------------------------------------------------------------------------------
void**		gVCOMCallback		= 0;

#ifndef _MINICAD_
extern "C" void plugin_module_deinit();
#endif

// ---------------------------------------------------------------------------------------------
VCOMError	GS_InitializeVCOM(void* cbpParam)
{
#ifndef _MINICAD_
	// we make this call here for the only reason so the function 'plugin_module_deinit' gets exported as visible in the DLL
	// since we provide this function to the plugins through the SDK.lib, the compiler removes it if not used
	plugin_module_deinit();
#endif

#if ! _MINICAD_
	Sint32 ver = plugin_module_ver();
#else
	Sint32 ver = 0;
#endif

	// init VCOM callback
	::GS_Kludge( (CallBackPtr) cbpParam, 499, &ver, & gVCOMCallback );

	// Temporarily piggy back setting up gVWMM here
	char parName[] = "VWMainPartition";
	VWMM::Partition* mainPartition = VWMM::Partition::GetPartitionByIdentifier(parName, true);
	gVWMM = mainPartition;

	// init legacy Global Callback Pointer
	// for support of legacy GS_ functions
	gCBP	= (CallBackPtr) cbpParam;

	{ // Init gSDK
		using namespace VectorWorks;
		VCOMPtr<ISDK>	localSDK( IID_SDK );
		gSDK	= localSDK;
	}

	return kVCOMError_NoError;
}

void GS_ReleaseStandardVCOMGlobals(Sint32 action)
{
	if ( action == kPluginModuleDeinit )
	{
		gIFC.Release();
		gDataTagSupport.Release();
	}
}

VCOMError	GS_VWRegisterInterface(const VWIID& iid, void* argTable, bool cacheIt/*=true*/)
{
	typedef Sint32 (*TRegisterInterface)(void* pInLibFile, void* pInIID, bool cacheIt);
	void*		pLibFile	= argTable;

	VCOMError	err			= kVCOMError_NotInitialized;
	if ( gVCOMCallback ) {
		TRegisterInterface	pRegisterInterfaceFunc	= (TRegisterInterface) gVCOMCallback[0];
		if ( pRegisterInterfaceFunc ) {
			err	= (*pRegisterInterfaceFunc)( pLibFile, (void*) & iid, cacheIt );
		}
	}

	return err;
}

VCOMError	GS_VWRegisterInterface(const VWIID& iid, const VWIID& iidContainer, void* argTable, bool cacheIt/*=true*/)
{
	typedef Sint32 (*TRegisterInterfaceInContainer)(void* pInLibFile, void* pInIID, void* pInIIDContainer, bool cacheIt);
	void*		pLibFile	= argTable;

	VCOMError	err			= kVCOMError_NotInitialized;
	if ( gVCOMCallback ) {
		TRegisterInterfaceInContainer	pRegisterInterfaceInContainerFunc	= (TRegisterInterfaceInContainer) gVCOMCallback[3];
		if ( pRegisterInterfaceInContainerFunc ) {
			err	= (*pRegisterInterfaceInContainerFunc)( pLibFile, (void*) & iid, (void*) & iidContainer, cacheIt );
		}
	}

	return err;
}

VCOMError	GS_VWQueryInterface(const VWIID& iid, IVWUnknown** ppInterface)
{
	typedef Sint32 (*TQueryInterface)(void* pInIID, void** ppInInterface);

	if ( gVCOMCallback == NULL )
		return kVCOMError_NotInitialized;
	
	TQueryInterface		pQueryInterfaceFunc		= (TQueryInterface) gVCOMCallback[1];
	
	if ( pQueryInterfaceFunc == NULL )
		return kVCOMError_InvalidArg;

	return (*pQueryInterfaceFunc)( (void*) & iid, (void**) ppInterface );
}

bool		GS_VWQueryInterfaceRTTI(const VWIID& iid, IVWUnknownRTTI** ppInterfaceRTTI)
{
	typedef Sint32 (*TQueryInterfaceRTTI)(void* pInIID, void** ppInterfaceRTTI);

	if ( gVCOMCallback == NULL )
		return kVCOMError_NotInitialized;
	
	TQueryInterfaceRTTI		pQueryInterfaceRTTIFunc		= (TQueryInterfaceRTTI) gVCOMCallback[8];
	
	if ( pQueryInterfaceRTTIFunc == NULL )
		return kVCOMError_InvalidArg;

	return (*pQueryInterfaceRTTIFunc)( (void*) & iid, (void**) ppInterfaceRTTI );
}

void		GS_VWNotifyDeleteInterface(IVWUnknown* pInterface)
{
	typedef Sint32 (*TNotifyDeleteInterface)(void* pInInterface);

	if ( gVCOMCallback ) {
		TNotifyDeleteInterface		pNotifyDeleteInterfaceFunc		= (TNotifyDeleteInterface) gVCOMCallback[2];
	
		if ( pNotifyDeleteInterfaceFunc ) {
			pNotifyDeleteInterfaceFunc( pInterface );
		}
	}
}

size_t		GS_VWGetContainerInterfacesCount(const VWIID& iidContainer)
{
	typedef size_t (*TGetContainerInterfacesCount)(void* pInIIDContainer);

	size_t	interfCnt	= 0;
	if ( gVCOMCallback ) {
		TGetContainerInterfacesCount	pGetInterfCntFun		= (TGetContainerInterfacesCount) gVCOMCallback[4];
		if ( pGetInterfCntFun ) {
			interfCnt	= pGetInterfCntFun( (void*) & iidContainer );
		}
	}

	return interfCnt;
}

VWIID		GS_VWGetContainerInterface(const VWIID& iidContainer, size_t index)
{
	typedef size_t (*TGetContainerInterface)(void* pInIIDContainer, size_t index, void* pOutIID);

	VWIID	resultIID;
    resultIID.data1		= 0;
    resultIID.data2		= 0;
    resultIID.data3		= 0;
    resultIID.data4[0]	= 0;
    resultIID.data4[1]	= 0;
    resultIID.data4[2]	= 0;
    resultIID.data4[3]	= 0;
    resultIID.data4[4]	= 0;
    resultIID.data4[5]	= 0;
    resultIID.data4[6]	= 0;
    resultIID.data4[7]	= 0;
	if ( gVCOMCallback ) {
		TGetContainerInterface	pGetInterfFun		= (TGetContainerInterface) gVCOMCallback[5];
		if ( pGetInterfFun ) {
			pGetInterfFun( (void*) & iidContainer, index, (void*) & resultIID );
		}
	}

	return resultIID;
}

void		GS_VWReleaseInterfaces(bool takeYourTime)
{
	typedef Sint32 (*TReleaseInterfaces)(bool takeYourTime);

	if ( gVCOMCallback ) {
		TReleaseInterfaces		pUnloadInterfaceResourceFunc		= (TReleaseInterfaces) gVCOMCallback[9];
	
		if ( pUnloadInterfaceResourceFunc ) {
			pUnloadInterfaceResourceFunc( takeYourTime );
		}
	}
}

size_t	GS_VWGetInterfaceModulePath(const VWIID& iid, char* buffer, size_t bufferSize)
{
	typedef size_t (*TGetInterfaceModulePath)(void* pInIID, char* buffer, size_t bufferSize);

	size_t result = 0;
	if ( gVCOMCallback ) {
		TGetInterfaceModulePath		pGetInterfaceModulePath		= (TGetInterfaceModulePath) gVCOMCallback[10];
	
		if ( pGetInterfaceModulePath ) {
			result = pGetInterfaceModulePath( (void*) & iid, buffer, bufferSize );
		}
	}

	return result;
}

VCOMError	GS_VWRegisterInterface(const VWIID& iid, TRegisterAllocateCallback allocateCallback, TRegisterFreeCallback freeCallback)
{
	typedef Sint32 (*TRegisterInterface)(void* pInIID, TRegisterAllocateCallback allocateCallback, TRegisterFreeCallback freeCallback);

	VCOMError	err			= kVCOMError_NotInitialized;
	if ( gVCOMCallback ) {
		TRegisterInterface	pRegisterInterfaceFunc	= (TRegisterInterface) gVCOMCallback[11];
		if ( pRegisterInterfaceFunc ) {
			err	= (*pRegisterInterfaceFunc)( (void*) & iid, allocateCallback, freeCallback );
		}
	}

	return err;
}

VCOMError	GS_VWRegisterInterface(const VWIID& iid, const VWIID& iidContainer, TRegisterAllocateCallback allocateCallback, TRegisterFreeCallback freeCallback)
{
	typedef Sint32 (*TRegisterInterface)(void* pInIID, void* pInIIDContainer, TRegisterAllocateCallback allocateCallback, TRegisterFreeCallback freeCallback);

	VCOMError	err			= kVCOMError_NotInitialized;
	if ( gVCOMCallback ) {
		TRegisterInterface	pRegisterInterfaceFunc	= (TRegisterInterface) gVCOMCallback[12];
		if ( pRegisterInterfaceFunc ) {
			err	= (*pRegisterInterfaceFunc)( (void*) & iid, (void*) & iidContainer, allocateCallback, freeCallback );
		}
	}

	return err;
}


TMultiplePseudoDashIndexConverter::TMultiplePseudoDashIndexConverter()  {
    gSDK->BeginMultiplePseudoDashIndexConvert();
}

TMultiplePseudoDashIndexConverter::~TMultiplePseudoDashIndexConverter() {
    gSDK->EndMultiplePseudoDashIndexConvert();
}

Sint32 TMultiplePseudoDashIndexConverter::GetPseudoDashIndexFromDashLineType(Sint32 lineTypeInternalIndex) const {
    Sint16 index = 0;
    
    // If the call fails (i.e. a bad value was sent it), return the same value. This allows us to preserve exisiting
    // behavior with our dashStyles are stored in Records.
    if (gSDK->GetPseudoDashIndexFromDashLineType(lineTypeInternalIndex, index))
        return index;
    else
        return lineTypeInternalIndex;
}

Sint32 TMultiplePseudoDashIndexConverter::GetDashLineTypeFromPseudoDashIndex(Sint16 pseudoIndex) const {
    Sint32 lineTypeVal = 0;
    
    // If the call fails (i.e. a bad value was sent it), return the same value. This allows us to preserve exisiting
    // behavior with our dashStyles are stored in Records.
    if (gSDK->GetDashLineTypeFromPseudoDashIndex(pseudoIndex, lineTypeVal))
        return lineTypeVal;
    else
        return pseudoIndex;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSBaseDataContainer::CGSBaseDataContainer()
	: m_documentId(0)
{
 	// read DocumentId from 'ftd'
 	short documentId = 0;  
 	if(gSDK->Kludge(/*kKludgeFTD*/7319, NULL, &documentId));
	{
		m_documentId = documentId;
	}
}

//-----------------------------------------------------------------------------
CGSBaseDataContainer::~CGSBaseDataContainer()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSStringValueChange::CGSStringValueChange()
{
}

//-----------------------------------------------------------------------------
CGSStringValueChange::CGSStringValueChange(const TXString& oldStringValue, const TXString& newStringValue) :
    fOldStringValue(oldStringValue),
    fNewStringValue(newStringValue)
{
}

//-----------------------------------------------------------------------------
CGSStringValueChange::~CGSStringValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSIntValueChange::CGSIntValueChange() :
    fValue(0)
{
}

//-----------------------------------------------------------------------------
CGSIntValueChange::CGSIntValueChange(const Sint32 value) :
    fValue(value)
{
}

//-----------------------------------------------------------------------------
CGSIntValueChange::~CGSIntValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSMultiStateValueChange::CGSMultiStateValueChange()
{
}

//-----------------------------------------------------------------------------
CGSMultiStateValueChange::CGSMultiStateValueChange(const EStateValue stateValue) :
    fStateValue(stateValue)
{
}

//-----------------------------------------------------------------------------
CGSMultiStateValueChange::~CGSMultiStateValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSRangedValueChange::CGSRangedValueChange() :
    CGSIntValueChange(0),
    fMinimumValue(0),
    fMaximumValue(0)
{
}

//-----------------------------------------------------------------------------
CGSRangedValueChange::CGSRangedValueChange(const Sint32 value,
    const Sint32 minValue, const Sint32 maxValue) :
    CGSIntValueChange(value),
    fMinimumValue(minValue),
    fMaximumValue(maxValue)
{
}

//-----------------------------------------------------------------------------
CGSRangedValueChange::~CGSRangedValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSColorValueChange::CGSColorValueChange() :
    fNewColor(0),
    fSpecialIndex(0)
{
}

//-----------------------------------------------------------------------------
CGSColorValueChange::CGSColorValueChange(const ColorRef newColor, const ColorRef specialIndex) :
    fNewColor(newColor),
    fSpecialIndex(specialIndex)
{
}

//-----------------------------------------------------------------------------
CGSColorValueChange::~CGSColorValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSPatternValueChange::CGSPatternValueChange() :
    fNewPattern(0),
    fbLocalMapping(false)
{
}

//-----------------------------------------------------------------------------
CGSPatternValueChange::CGSPatternValueChange(const Sint32 newPattern, const bool bLocalMapping) :
    fNewPattern(newPattern),
    fbLocalMapping(bLocalMapping)
{
}

//-----------------------------------------------------------------------------
CGSPatternValueChange::~CGSPatternValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

CGSPatternWithColorValueChange::CGSPatternWithColorValueChange()
{
}

//-----------------------------------------------------------------------------
CGSPatternWithColorValueChange::CGSPatternWithColorValueChange(const CGSColorValueChange& newForegroundColor,
    const CGSColorValueChange& newBackgroundColor,
    const CGSPatternValueChange& newPattern)
{
    fForegroundColor = newForegroundColor;
    fBackgroundColor = newBackgroundColor;
    fPatternValueChange = newPattern;
}

//-----------------------------------------------------------------------------
CGSPatternWithColorValueChange::~CGSPatternWithColorValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSHatchStyleValueChange::CGSHatchStyleValueChange() :
    fNewHatchStyle(0),
    fOldHatchStyle(0)
{
}

//-----------------------------------------------------------------------------
CGSHatchStyleValueChange::CGSHatchStyleValueChange(const Sint32 newHatchStyle, const Sint32 oldHatchStyle) :
    fNewHatchStyle(newHatchStyle),
    fOldHatchStyle(oldHatchStyle)
{
}

//-----------------------------------------------------------------------------
CGSHatchStyleValueChange::~CGSHatchStyleValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSGradientValueChange::CGSGradientValueChange() :
    fNewGradient(0)
{
}

//-----------------------------------------------------------------------------
CGSGradientValueChange::CGSGradientValueChange(const Sint32 newGradient) :
    fNewGradient(newGradient)
{
}

//-----------------------------------------------------------------------------
CGSGradientValueChange::~CGSGradientValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSImageResourceValueChange::CGSImageResourceValueChange()
{
}

//-----------------------------------------------------------------------------
CGSImageResourceValueChange::CGSImageResourceValueChange(const Sint32 newImageResource) :
    fNewImageResource(newImageResource)
{
}

//-----------------------------------------------------------------------------
CGSImageResourceValueChange::~CGSImageResourceValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSTileResourceValueChange::CGSTileResourceValueChange()
{
}

//-----------------------------------------------------------------------------
CGSTileResourceValueChange::CGSTileResourceValueChange(const Sint32 newTileResource) :
    fNewTileResource(newTileResource)
{
}

//-----------------------------------------------------------------------------
CGSTileResourceValueChange::~CGSTileResourceValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSLineTypeValueChange::CGSLineTypeValueChange()
{
}

//-----------------------------------------------------------------------------
CGSLineTypeValueChange::CGSLineTypeValueChange(const Sint32 newLineType)
{
    fNewLineType = newLineType;
}

//-----------------------------------------------------------------------------
CGSLineTypeValueChange::~CGSLineTypeValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSLineWeightValueChange::CGSLineWeightValueChange() :
    fNewLineWeightValue(0),
    fbWeightByClass(false)
{
}

//-----------------------------------------------------------------------------
CGSLineWeightValueChange::CGSLineWeightValueChange(const short newLineWeight, const bool bWeightByClass) :
    fNewLineWeightValue(newLineWeight),
    fbWeightByClass(bWeightByClass)
{
}

//-----------------------------------------------------------------------------
CGSLineWeightValueChange::~CGSLineWeightValueChange()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSMenuItemCollection::CGSMenuItemCollection()
{
    
}

//-----------------------------------------------------------------------------
CGSMenuItemCollection::CGSMenuItemCollection(const CGSMenuItemCollection& menuItemCollection)
{
    *this = menuItemCollection;
}

//-----------------------------------------------------------------------------
CGSMenuItemCollection::~CGSMenuItemCollection()
{
    RemoveAllMenuItems();
}

//-----------------------------------------------------------------------------
bool CGSMenuItemCollection::AddMenuItem(const CGSMenuItemValue& menuItemValue)
{
    bool bAddedSuccessfully = false;
    
    CGSMenuItemValue* pMenuItemValue = new CGSMenuItemValue(menuItemValue);
    if (pMenuItemValue != nullptr)
    {
        fMenuItemCollection.push_back(pMenuItemValue);
        bAddedSuccessfully = true;
    }
    
    return bAddedSuccessfully;
}

//-----------------------------------------------------------------------------
unsigned int CGSMenuItemCollection::GetMenuItemCount() const
{
    return (unsigned int)fMenuItemCollection.size();
}

//-----------------------------------------------------------------------------
const CGSMenuItemValue* CGSMenuItemCollection::GetMenuItemAtIndex(const unsigned int menuItemIndex) const
{
    const CGSMenuItemValue* pMenuItemValue = nullptr;
    
    if ((size_t)menuItemIndex < fMenuItemCollection.size())
    {
        pMenuItemValue = *(fMenuItemCollection.begin() + (size_t)menuItemIndex);
    }
    
    return pMenuItemValue;
}

//-----------------------------------------------------------------------------
bool CGSMenuItemCollection::RemoveMenuItemAtIndex(const unsigned int menuItemIndex)
{
	bool bSuccess = false;

	if ((size_t)menuItemIndex < fMenuItemCollection.size())
	{
		delete *(fMenuItemCollection.begin() + (size_t)menuItemIndex);
		fMenuItemCollection.erase(fMenuItemCollection.begin() + (size_t)menuItemIndex);		
		bSuccess = true;
	}

	return bSuccess;
}

//-----------------------------------------------------------------------------
void CGSMenuItemCollection::operator=(const CGSMenuItemCollection& sourceMenuItemValue)
{
    RemoveAllMenuItems();
    for (auto currentItem : sourceMenuItemValue.fMenuItemCollection)
    {
        // Create an exact duplicate of the collection, even if some
        // of the contained menu item pointers are null.
        if (currentItem != nullptr)
        {
            fMenuItemCollection.push_back(new CGSMenuItemValue(currentItem));
        }
        else
        {
            fMenuItemCollection.push_back(nullptr);
        }
    }
}

//-----------------------------------------------------------------------------
bool CGSMenuItemCollection::operator==(const CGSMenuItemCollection& referenceItemValue)
{
    bool bCollectionsAreEqual = false;
    
    if (fMenuItemCollection.size() == referenceItemValue.fMenuItemCollection.size())
    {
        bCollectionsAreEqual = true;
        auto menuItemIterator = fMenuItemCollection.begin();
        auto referenceMenuItemIterator = referenceItemValue.fMenuItemCollection.begin();
        while (bCollectionsAreEqual && (menuItemIterator != fMenuItemCollection.end()) &&
               (referenceMenuItemIterator != referenceItemValue.fMenuItemCollection.end()))
        {
            if ((*menuItemIterator != nullptr) && (*referenceMenuItemIterator != nullptr))
            {
                // Compare the menu objects.
                bCollectionsAreEqual = (*menuItemIterator == *referenceMenuItemIterator);
            }
            else if (*menuItemIterator == *referenceMenuItemIterator)
            {
                // ...Both objects are null pointers - consider the
                // objects to be equal in value.
                bCollectionsAreEqual = true;
            }
            
            menuItemIterator++;
            referenceMenuItemIterator++;
        }
    }

    return bCollectionsAreEqual;
}

//-----------------------------------------------------------------------------
void CGSMenuItemCollection::RemoveAllMenuItems()
{
    while (!fMenuItemCollection.empty())
    {
        auto currentItem = fMenuItemCollection.back();
        if (currentItem != nullptr)
        {
            delete currentItem;
        }
        
        fMenuItemCollection.pop_back();
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSMenuItemValue::CGSMenuItemValue()
{
    
}

//-----------------------------------------------------------------------------
CGSMenuItemValue::CGSMenuItemValue(const CGSMenuItemValue& menuItemValue)
{
    *this = menuItemValue;
}

//-----------------------------------------------------------------------------
CGSMenuItemValue::CGSMenuItemValue(const TXString& menuItemName, const Sint64 menuItemId) :
    fbIsSeparator(false)
{
    fMenuItemName = menuItemName;
    fMenuItemId = menuItemId;
}

//-----------------------------------------------------------------------------
CGSMenuItemValue::CGSMenuItemValue(const TXString& menuItemName, const TXString& menuItemIdStr) :
    fbIsSeparator(false)
{
    fMenuItemName = menuItemName;
    fMenuItemIdStr = menuItemIdStr;
}
//-----------------------------------------------------------------------------
CGSMenuItemValue::CGSMenuItemValue(const TXString& menuItemName, const Sint64 menuItemId, const TXString& menuItemIdStr, const double menuItemIdDbl):
    fbIsSeparator(false)
{
    fMenuItemName = menuItemName;
    fMenuItemIdStr = menuItemIdStr;
    fMenuItemId = menuItemId;
    fMenuItemIdDbl = menuItemIdDbl;
}
//-----------------------------------------------------------------------------
CGSMenuItemValue::CGSMenuItemValue(const TXString& menuItemName, const Sint64 menuItemId, const TXString& menuItemImageSpec) :
	fbIsSeparator(false)
{
	fMenuItemName = menuItemName;
	fMenuItemId = menuItemId;
	fMenuItemImageSpec = menuItemImageSpec;
}
//-----------------------------------------------------------------------------
CGSMenuItemValue::CGSMenuItemValue(const bool bIsSeparator)
{
    fbIsSeparator = bIsSeparator;
}

//-----------------------------------------------------------------------------
CGSMenuItemValue::~CGSMenuItemValue()
{
}

//-----------------------------------------------------------------------------
void CGSMenuItemValue::AddSubMenu(const CGSMenuItemCollection& subMenu)
{
    fSubMenu = subMenu;
}

//-----------------------------------------------------------------------------
bool CGSMenuItemValue::IsItemEnabled() const
{
    return (fMenuItemState.find(eStateDisabled) == fMenuItemState.end());
}

//-----------------------------------------------------------------------------
bool CGSMenuItemValue::IsItemChecked() const
{
    return (fMenuItemState.find(eStateChecked) != fMenuItemState.end());
}

//-----------------------------------------------------------------------------
void CGSMenuItemValue::SetEnabledState(const bool bEnabledState)
{
    if (bEnabledState)
    {
        fMenuItemState.erase(eStateDisabled);
    }
    else
    {
        fMenuItemState.insert(eStateDisabled);
    }
}

//-----------------------------------------------------------------------------
void CGSMenuItemValue::SetCheckedState(const bool bCheckedState)
{
    if (bCheckedState)
    {
        fMenuItemState.insert(eStateChecked);
    }
    else
    {
        fMenuItemState.erase(eStateChecked);
    }
}

//-----------------------------------------------------------------------------
void CGSMenuItemValue::operator=(const CGSMenuItemValue& sourceMenuItemValue)
{
    fMenuItemName = sourceMenuItemValue.fMenuItemName;
    fMenuItemImageSpec = sourceMenuItemValue.fMenuItemImageSpec;
    fMenuItemId = sourceMenuItemValue.fMenuItemId;
    fMenuItemIdStr = sourceMenuItemValue.fMenuItemIdStr;
    fMenuItemIdDbl = sourceMenuItemValue.fMenuItemIdDbl;
    fbIsSeparator = sourceMenuItemValue.fbIsSeparator;
    
    fMenuItemState = sourceMenuItemValue.fMenuItemState;
    fSubMenu = sourceMenuItemValue.fSubMenu;
}

//-----------------------------------------------------------------------------
bool CGSMenuItemValue::operator==(const CGSMenuItemValue& referenceItemValue)
{
    bool bItemsAreEqual = false;
    
    if (fbIsSeparator)
    {
        bItemsAreEqual = (fbIsSeparator == referenceItemValue.fbIsSeparator);
    }
    else if (!referenceItemValue.fbIsSeparator)
    {
        bItemsAreEqual =
            (fMenuItemName == referenceItemValue.fMenuItemName) &&
            (fMenuItemImageSpec == referenceItemValue.fMenuItemImageSpec) &&
            (fMenuItemId == referenceItemValue.fMenuItemId) &&
            (fMenuItemIdStr == referenceItemValue.fMenuItemIdStr) &&
            (fMenuItemIdDbl == referenceItemValue.fMenuItemIdDbl) &&
            (fMenuItemState == referenceItemValue.fMenuItemState) &&
            (fSubMenu == referenceItemValue.fSubMenu);
    }
    
    return bItemsAreEqual;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CGSListItemValue::CGSListItemValue() : fItemIndex(0)
{
}

//-----------------------------------------------------------------------------
CGSListItemValue::CGSListItemValue(const TXString& itemName, const Sint64 itemIdentifier,
                                   const Uint32 itemIndex) :
    fItemName(itemName),
    fItemIdentifier(itemIdentifier),
    fItemIndex(itemIndex)
{
    
}

//-----------------------------------------------------------------------------
CGSListItemValue::CGSListItemValue(const TXString& itemName, const TXString& itemIdentifierStr,
                                   const Uint32 itemIndex) :
    fItemName(itemName),
    fItemIdentifierStr(itemIdentifierStr),
    fItemIndex(itemIndex)
{
}

//-----------------------------------------------------------------------------
CGSListItemValue::CGSListItemValue(const TXString& itemName, const Sint64 itemIdentifierNum,
                                   const TXString& itemIdentifierStr, const Uint32 itemIndex) :
    fItemName(itemName),
    fItemIdentifier(itemIdentifierNum),
    fItemIdentifierStr(itemIdentifierStr),
    fItemIndex(itemIndex)
{
}

//-----------------------------------------------------------------------------
CGSListItemValue::CGSListItemValue(const TXString& itemName, const Sint64 itemIdentifierNum,
	const TXString& itemIdentifierStr, const double itemIdentifierDbl, const Uint32 itemIndex) :
	fItemName(itemName),
	fItemIdentifier(itemIdentifierNum),
	fItemIdentifierStr(itemIdentifierStr),
	fItemIdentifierDbl(itemIdentifierDbl),
	fItemIndex(itemIndex)
{
}

//-----------------------------------------------------------------------------
CGSListItemValue::~CGSListItemValue()
{
}

//-----------------------------------------------------------------------------
CGSClassAndLayerPulldownCollection::CGSClassAndLayerPulldownCollection(VCOMPtr<ICGSClassAndLayerPulldownCollection> data)
	: fpPulldownInterface(data)
{
}

//-----------------------------------------------------------------------------
CGSClassAndLayerPulldownCollection::~CGSClassAndLayerPulldownCollection()
{
}

//-----------------------------------------------------------------------------
CGSClassAndLayerPulldownItemValue::CGSClassAndLayerPulldownItemValue()
	: fItemIsProposed(false)
	, fItemInternalIndex(-999)
	, fItemIsNew(false)
{
}

//-----------------------------------------------------------------------------
CGSClassAndLayerPulldownItemValue::CGSClassAndLayerPulldownItemValue(const TXString& itemName, bool itemIsProposed, const TXString& proposedItemIDStr, Sint32 itemInternalIndex, bool itemIsNew)
	: fItemName(itemName)
	, fItemIsProposed(itemIsProposed)
	, fProposedItemIDStr(proposedItemIDStr)
	, fItemInternalIndex(itemInternalIndex)
	, fItemIsNew(fItemIsNew)
{
}

//-----------------------------------------------------------------------------
CGSClassAndLayerPulldownItemValue::~CGSClassAndLayerPulldownItemValue()
{
}

