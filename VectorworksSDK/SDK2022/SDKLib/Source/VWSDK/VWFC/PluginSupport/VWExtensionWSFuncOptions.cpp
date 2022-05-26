//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::PluginSupport;

// --------------------------------------------------------------------------------------------------------
TXString GetEQTOFunctionString(EQTOFunction function)
{
	TXString result;
	switch ( function )
	{
		case EQTOFunction::Angle:				result << "Angle";				break;
		case EQTOFunction::Count:				result << "Count";				break;
		case EQTOFunction::Length:				result << "Length";				break;
		case EQTOFunction::Perimeter:			result << "Perimeter";			break;
		case EQTOFunction::Width:				result << "Width";				break;
		case EQTOFunction::Height:				result << "Height";				break;
		case EQTOFunction::Depth:				result << "Depth";				break;
		case EQTOFunction::Weight:				result << "Weight";				break;
		case EQTOFunction::Area:				result << "Area";				break;
		case EQTOFunction::SurfaceArea:			result << "SurfaceArea";		break;
		case EQTOFunction::ProjectedArea:		result << "ProjectedArea";		break;
		case EQTOFunction::FootPrintArea:		result << "FootPrintArea";		break;
		case EQTOFunction::CrossSectionArea:	result << "CrossSectionArea";	break;
		case EQTOFunction::SpecialArea:			result << "SpecialArea";		break;
		case EQTOFunction::Volume:				result << "Volume";				break;
		case EQTOFunction::ObjectData:			result << "ObjectData";			break;
	}

	return result;
}

bool GetEQTOFunctionFromString(const TXString& funcName, EQTOFunction& outFunction)
{
	bool result = true;
	     if ( funcName.Equal( "Angle" ) )				outFunction = EQTOFunction::Angle				;
	else if ( funcName.Equal( "Count" ) )				outFunction = EQTOFunction::Count				;
	else if ( funcName.Equal( "Length" ) )				outFunction = EQTOFunction::Length				;
	else if ( funcName.Equal( "Perimeter" ) )			outFunction = EQTOFunction::Perimeter			;
	else if ( funcName.Equal( "Width" ) )				outFunction = EQTOFunction::Width				;
	else if ( funcName.Equal( "Height" ) )				outFunction = EQTOFunction::Height				;
	else if ( funcName.Equal( "Depth" ) )				outFunction = EQTOFunction::Depth				;
	else if ( funcName.Equal( "Weight" ) )				outFunction = EQTOFunction::Weight				;
	else if ( funcName.Equal( "Area" ) )				outFunction = EQTOFunction::Area				;
	else if ( funcName.Equal( "SurfaceArea" ) )			outFunction = EQTOFunction::SurfaceArea			;
	else if ( funcName.Equal( "ProjectedArea" ) )		outFunction = EQTOFunction::ProjectedArea		;
	else if ( funcName.Equal( "FootPrintArea" ) )		outFunction = EQTOFunction::FootPrintArea		;
	else if ( funcName.Equal( "CrossSectionArea" ) )	outFunction = EQTOFunction::CrossSectionArea	;
	else if ( funcName.Equal( "SpecialArea" ) )			outFunction = EQTOFunction::SpecialArea			;
	else if ( funcName.Equal( "Volume" ) )				outFunction = EQTOFunction::Volume				;
	else if ( funcName.Equal( "ObjectData" ) )			outFunction = EQTOFunction::ObjectData			;
	else result = false;

	return result;
}

TXString CreateWSFuncOptionKey(EQTOFunction function, const TXString& univName)
{
	TXString	key;
	key << GetEQTOFunctionString( function );
	key << "-";
	key << univName;

	return key;
}

// --------------------------------------------------------------------------------------------------------
VWExtensionWSFuncOptions::VWExtensionWSFuncOptions(CallBackPtr, const TWSFunctionOptionsDefArray& arrFunctionOptions)
	: fWSFuncOptionsEventSink( nullptr )
	, fProtectionObtained( false )
	, fHasProtection( false )
	, fProtectionSink( nullptr )
{
	for(const auto& it : arrFunctionOptions)
	{
		SWSFunctionOptionDesc desc;
		desc.fFunction		= it.fFunction;
		desc.fOptionName	= it.fOptionName;
		desc.fEditable		= it.fEditable;
		desc.farrObjects	= it.farrObjects;

		TXString	key = CreateWSFuncOptionKey( it.fFunction, desc.fOptionName );

#if _MINICAD_
# define DefaultPluginVWRIdentifier()	"Vectorworks"
#endif
		const TXString& root = TXString(DefaultPluginVWRIdentifier()) + "/WSFunctionsHelp/";
		desc.fFunctionDef.fDefinition		= TXResource( root + "Opt Desc.vwstrings", key );
		desc.fFunctionDef.fDescription		= TXResource( root + "Opt Desc.vwstrings", key + "-desc", eAllowEmptyResult );
		desc.fFunctionDBDef.fDefinition		= TXResource( root + "Opt Desc DB.vwstrings", key );
		desc.fFunctionDBDef.fDescription	= TXResource( root + "Opt Desc DB.vwstrings", key + "-desc", eAllowEmptyResult );

		if ( desc.fFunctionDBDef.fDescription.IsEmpty() )
			desc.fFunctionDBDef.fDescription = desc.fFunctionDef.fDescription;

		if ( desc.fFunctionDef.fDescription.IsEmpty() )
			desc.fFunctionDef.fDescription = desc.fFunctionDBDef.fDescription;

		if ( desc.fFunctionDBDef.fDefinition.IsEmpty() )
			desc.fFunctionDBDef.fDefinition = desc.fFunctionDef.fDefinition;

		if ( desc.fFunctionDef.fDefinition.IsEmpty() )
			desc.fFunctionDef.fDefinition = desc.fFunctionDBDef.fDefinition;

		desc.fImageSpec	= root + "Opt Images/" + key + ".png";

		TXResource	resourceExample( root + "Opt Examples/" + key + ".txt" );
		const void* buffer = resourceExample.Buffer();
		size_t		bufferSize = resourceExample.Size();
		if ( buffer && bufferSize > 0)
		{
			const static std::vector<char>	sBOM_UTF16 = { char(0xFF), char(0xFE) };
			const static std::vector<char>	sBOM_UTF8  = { char(0xEF), char(0xBB), char(0xBF) };

			if ( bufferSize >= sBOM_UTF16.size() &&
				memcmp( buffer, &sBOM_UTF16[0], sBOM_UTF16.size() )  == 0 )
				desc.fExample = TXString( (const UCChar*) (((const char*)buffer) + sBOM_UTF16.size()), (bufferSize - sBOM_UTF16.size())/2 );
			else if ( bufferSize >= sBOM_UTF8.size() &&
					 memcmp( buffer, &sBOM_UTF8[0], sBOM_UTF8.size() ) == 0 )
				desc.fExample = TXString( ((const char*)buffer) + sBOM_UTF8.size(), bufferSize - sBOM_UTF8.size() );
			else
				desc.fExample	= resourceExample.operator const TXString & ();
		}

		farrFunctionOptions.push_back( desc );
	}
}

VWExtensionWSFuncOptions::~VWExtensionWSFuncOptions()
{
}

void VWExtensionWSFuncOptions::OnRefCountZero()
{
	if ( fWSFuncOptionsEventSink ) {
		delete fWSFuncOptionsEventSink;
		fWSFuncOptionsEventSink	= nullptr;
	}

	if ( fProtectionSink ) {
		delete fProtectionSink;
		fProtectionSink	= nullptr;
	}
}

IEventSink* VWExtensionWSFuncOptions::QueryEventSink(const TSinkIID& iid)
{
	if ( fProtectionObtained == false ) {
		fHasProtection			= this->GetProtectionSinkIID( fProtectionSinkIID );
		fProtectionObtained		= true;
	}

	IEventSink*	pResult	= nullptr;
	if ( IID_WSFunctionCallEventSink == iid ) {
		if ( fWSFuncOptionsEventSink == nullptr ) {
			fWSFuncOptionsEventSink	= this->CreateWSFuncOptionsEventSink( this );
			if ( fWSFuncOptionsEventSink ) {
				fWSFuncOptionsEventSink->AddRef();
			}
		}
		pResult	= fWSFuncOptionsEventSink;
	}
	else if ( fHasProtection && fProtectionSinkIID == iid ) {
		if ( fProtectionSink == nullptr ) {
			fProtectionSink	= this->CreateProtectionSink( this );
			if ( fProtectionSink == nullptr ) {
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

bool VWExtensionWSFuncOptions::GetProtectionSinkIID(TSinkIID& outIID)
{
	return false;
}

IProviderProtection* VWExtensionWSFuncOptions::CreateProtectionSink(IVWUnknown* parent)
{
	return nullptr;
}

size_t VWExtensionWSFuncOptions::GetFunctionsCount()
{
	return farrFunctionOptions.size();
}

bool VWExtensionWSFuncOptions::GetFunctionOption(size_t funcIndex, EQTOFunction& outFunction, TXString& outUnivName, bool& outEditable)
{
	bool result = false;
	outUnivName.Clear();
	if ( funcIndex < farrFunctionOptions.size() )
	{
		const auto& def = farrFunctionOptions[funcIndex];
		outFunction			= def.fFunction;
		outUnivName			= def.fOptionName;
		outEditable			= def.fEditable;
		result = true;
	}

	return result;
}

bool VWExtensionWSFuncOptions::GetFunctionOptionDesc(size_t funcIndex,  TXString& outCategory, SIExtensionWSFunctionDefDesc& outFuncDef, SIExtensionWSFunctionDefDesc& outFuncDBDef, TXString& outImageSpec, TXString& outExample)
{
	bool result = false;

	outCategory.Clear();
	outFuncDef.fDefinition.Clear();	
	outFuncDef.fDescription.Clear();
	outFuncDBDef.fDefinition.Clear();	
	outFuncDBDef.fDescription.Clear();
	outImageSpec.Clear();
	outExample.Clear();

	if ( funcIndex < farrFunctionOptions.size() )
	{
		const auto& def = farrFunctionOptions[funcIndex];
		outCategory		= def.fCategory;
		outFuncDef		= def.fFunctionDef;
		outFuncDBDef	= def.fFunctionDBDef;
		outImageSpec	= def.fImageSpec;
		outExample		= def.fExample;

		result = true;
	}

	return result;
}

size_t VWExtensionWSFuncOptions::GetFunctionOptionObjsCount(size_t funcIndex)
{
	if ( funcIndex >= farrFunctionOptions.size() )
		return 0;

	const auto& def = farrFunctionOptions[funcIndex];
	return def.farrObjects.size();
}

bool VWExtensionWSFuncOptions::GetFunctionOptionObj(size_t funcIndex, size_t objIndex, short& outTdType, TInternalID& outInternalIndex, TXString& outUnivName)
{
	bool result = false;
	if ( funcIndex < farrFunctionOptions.size() )
	{
		const auto& def = farrFunctionOptions[funcIndex];
		if ( objIndex < def.farrObjects.size() )
		{
			const auto& objDef = def.farrObjects[ objIndex ];
			outTdType = objDef.fTdType;
			outInternalIndex = objDef.fParametricInternalID;
			if ( objDef.fParametricUnivName )
				outUnivName = objDef.fParametricUnivName;
			result = true;
		}
	}

	return result;
}

// --------------------------------------------------------------------------------------------------------
VWWSFunctionCall_EventSink::VWWSFunctionCall_EventSink(IVWUnknown* parent)
	: VCOMImpl<IWSFunctionCallEventSink>( parent )
{
}

VWWSFunctionCall_EventSink::~VWWSFunctionCall_EventSink()
{
}

