//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#if _MINICAD_
# include "HelpText.X.h"
#endif

# include "VWFC//PluginSupport/VWExtensions.h"
# include "VWFC//PluginSupport/VWExtensionMenu.h"

using namespace VWFC::PluginSupport;


// --------------------------------------------------------------------------------------------------------
VWExtensionVSFunctions::VWExtensionVSFunctions(	CallBackPtr cbp,
												const SFunctionDef* arrFunctions)
	: fCBP( cbp )
	, farrFunctions( arrFunctions )
	, fVSFunctionsEventSink( NULL )
	, fProtectionObtained( false )
	, fHasProtection( false )
	, fProtectionSink( NULL )
{
}

VWExtensionVSFunctions::~VWExtensionVSFunctions()
{
}

void VWExtensionVSFunctions::OnRefCountZero()
{
	if ( fVSFunctionsEventSink ) {
		delete fVSFunctionsEventSink;
		fVSFunctionsEventSink	= NULL;
	}

	if ( fProtectionSink ) {
		delete fProtectionSink;
		fProtectionSink	= NULL;
	}
}

IEventSink* VWExtensionVSFunctions::QueryEventSink(const TSinkIID& iid)
{
	if ( fProtectionObtained == false ) {
		fHasProtection			= this->GetProtectionSinkIID( fProtectionSinkIID );
		fProtectionObtained		= true;
	}

	IEventSink*	pResult	= NULL;
	if ( IID_VSFunctionsEventSink == iid ) {
		if ( fVSFunctionsEventSink == NULL ) {
			fVSFunctionsEventSink	= this->CreateVSFunctionsEventSink( this );
			if ( fVSFunctionsEventSink ) {
				this->InitRoutines();
				fVSFunctionsEventSink->AddRef();
				VWVSFunctions_EventSink*	vwfcSink	= dynamic_cast<VWVSFunctions_EventSink*>( fVSFunctionsEventSink );
				if ( vwfcSink ) {
					vwfcSink->SetUniversalName( this->GetUniversalName() );
				}
			}
		}
		pResult	= fVSFunctionsEventSink;
	}
	else if ( fHasProtection && fProtectionSinkIID == iid ) {
		if ( fProtectionSink == NULL ) {
			fProtectionSink	= this->CreateProtectionSink( this );
			if ( fProtectionSink == NULL ) {
				fHasProtection	= false;
			}
		}

		if ( fProtectionSink ) {
			fProtectionSink->AddRef();
			pResult	= fProtectionSink;
		}
	}

	return pResult;
}

bool VWExtensionVSFunctions::GetProtectionSinkIID(TSinkIID& outIID)
{
	return false;
}

IProviderProtection* VWExtensionVSFunctions::CreateProtectionSink(IVWUnknown* parent)
{
	return NULL;
}

Uint32 VWExtensionVSFunctions::Initialize()
{
	return kExtensionVSFunctionsInitFlag_None;
}

size_t VWExtensionVSFunctions::GetFunctionsCount()
{
	size_t				functionsCount	= 0;
	const SFunctionDef*	currFunc		= farrFunctions;
	while ( currFunc && currFunc->fName ) {
		functionsCount++;
		currFunc++;
	}

	return functionsCount;
}

const TXString& VWExtensionVSFunctions::GetFunctionName(size_t funcIndex)
{
	VWFC_ASSERT( funcIndex < this->GetFunctionsCount() );
	const SFunctionDef&		funcDef	= farrFunctions[ funcIndex ];
	TStringCache::iterator	it		= fmapStringCache.find( funcDef.fName );
	if ( it == fmapStringCache.end() ) {
		TResultPair	res	= fmapStringCache.insert( TStringCache::value_type( funcDef.fName, funcDef.fName ) );
		it	= res.first;
	}
	return it->second;
}

const TXString& VWExtensionVSFunctions::GetFunctionCategory(size_t funcIndex)
{
	VWFC_ASSERT( funcIndex < this->GetFunctionsCount() );
	const SFunctionDef&		funcDef	= farrFunctions[ funcIndex ];
	TStringCache::iterator	it		= fmapStringCache.find( funcDef.fCategory );
	if ( it == fmapStringCache.end() ) {
		TResultPair	res	= fmapStringCache.insert( TStringCache::value_type( funcDef.fCategory, funcDef.fCategory ) );
		it	= res.first;
	}
	return it->second;
}

const TXString& VWExtensionVSFunctions::GetFunctionDescription(size_t funcIndex)
{
	VWFC_ASSERT( funcIndex < this->GetFunctionsCount() );
	const SFunctionDef&		funcDef	= farrFunctions[ funcIndex ];
	TStringCache::iterator	it		= fmapStringCache.find( funcDef.fDescription );
	if ( it == fmapStringCache.end() ) {
		TResultPair	res	= fmapStringCache.insert( TStringCache::value_type( funcDef.fDescription, funcDef.fDescription ) );
		it	= res.first;
	}
	return it->second;
}

Sint32 VWExtensionVSFunctions::GetFunctionVersion(size_t funcIndex)
{
	VWFC_ASSERT( funcIndex < this->GetFunctionsCount() );
	const SFunctionDef&	funcDef	= farrFunctions[ funcIndex ];
	return funcDef.fVersion;
}

Sint8 VWExtensionVSFunctions::GetFunctionScope(size_t funcIndex)
{
	VWFC_ASSERT( funcIndex < this->GetFunctionsCount() );
	const SFunctionDef&	funcDef	= farrFunctions[ funcIndex ];
	return funcDef.fScope;
}

bool VWExtensionVSFunctions::GetFunctionHasReturnValue(size_t funcIndex)
{
	VWFC_ASSERT( funcIndex < this->GetFunctionsCount() );
	const SFunctionDef&	funcDef	= farrFunctions[ funcIndex ];
	return funcDef.fHasReturnValue;
}

size_t VWExtensionVSFunctions::GetFunctionParamsCount(size_t funcIndex)
{
	VWFC_ASSERT( funcIndex < this->GetFunctionsCount() );
	const SFunctionDef&	funcDef	= farrFunctions[ funcIndex ];

	size_t						paramsCount		= 0;
	const SFunctionParamDef*	currParam		= funcDef.fParams;
	while ( currParam && currParam->fName ) {
		paramsCount++;
		currParam++;
	}

	return paramsCount;
}

const TXString& VWExtensionVSFunctions::GetFunctionParamName(size_t funcIndex, size_t paramIndex)
{
	VWFC_ASSERT( paramIndex < this->GetFunctionParamsCount( funcIndex ) );
	const SFunctionDef&			funcDef		= farrFunctions[ funcIndex ];
	const SFunctionParamDef&	paramDef	= funcDef.fParams[ paramIndex ];
	TStringCache::iterator		it			= fmapStringCache.find( paramDef.fName );
	if ( it == fmapStringCache.end() ) {
		TResultPair	res	= fmapStringCache.insert( TStringCache::value_type( paramDef.fName, paramDef.fName ) );
		it	= res.first;
	}
	return it->second;
}

EPluginLibraryArgType VWExtensionVSFunctions::GetFunctionParamType(size_t funcIndex, size_t paramIndex)
{
	VWFC_ASSERT( paramIndex < this->GetFunctionParamsCount( funcIndex ) );
	const SFunctionDef&			funcDef		= farrFunctions[ funcIndex ];
	const SFunctionParamDef&	paramDef	= funcDef.fParams[ paramIndex ];
	return paramDef.fType;
}

// --------------------------------------------------------------------------------------------------------
VWVSFunctions_EventSink::VWVSFunctions_EventSink(IVWUnknown* parent)
	: VCOMImpl<IVSFunctionsEventSink>( parent )
	, fRoutines( NULL )
{
	
}

VWVSFunctions_EventSink::~VWVSFunctions_EventSink()
{
	SRoutinesDef*	currRoutine	= fRoutines;
	while ( currRoutine ) {
		VWPluginLibraryRoutine*	routine	= currRoutine->fRoutine;
		SRoutinesDef*			prev	= currRoutine->fPrev;

		if ( ! currRoutine->fIsLocalMemory && routine ) {
			delete routine;
		}
		delete currRoutine;

		currRoutine	= prev;
	}
	fRoutines = NULL;
}

void VWVSFunctions_EventSink::SetUniversalName(const TXString& name)
{
	fUnivName	= name;
}

void VWVSFunctions_EventSink::AddRoutine(VWPluginLibraryRoutine* routine, bool isLocalMemory)
{
	SRoutinesDef*	newRoutineDef = SDK_NEW SRoutinesDef;

	newRoutineDef->fRoutine			= routine;
	newRoutineDef->fIsLocalMemory	= isLocalMemory;
	newRoutineDef->fPrev			= fRoutines;

	fRoutines					= newRoutineDef;
}

Sint32 VWVSFunctions_EventSink::Execute(Sint32 action, PluginLibraryArgTable* argumentTable)
{
	VWPluginLibraryArgTable		argTable( argumentTable );

	Sint32 reply	= 0;

	SRoutinesDef*	currRoutine	= fRoutines;
	while ( currRoutine ) {
		VWPluginLibraryRoutine*	routine	= currRoutine->fRoutine;
		if ( routine ) {
			routine->DispatchRoutine( action, argTable );
		}

		currRoutine	= currRoutine->fPrev;
	}

	return reply;
}
