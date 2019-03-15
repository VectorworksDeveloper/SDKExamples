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
